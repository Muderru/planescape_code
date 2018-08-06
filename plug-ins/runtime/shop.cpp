/* ************************************************************************
*   File: shop.c                                        Part of CircleMUD *
*  Usage: shopkeepers: loading config files, spec procs.                  *
*                                                                         *
*  All rights reserved.  See license.doc for complete information.        *
*                                                                         *
*  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
*  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
************************************************************************ */

#include "sysdep.h"
#include "screen.h"
#include "structs.h"
#include "comm.h"
#include "handler.h"
#include "db.h"
#include "interpreter.h"
#include "utils.h"
#include "shop.h"
#include "xshop.h"
#include "spells.h"
#include "constants.h"
#include "parser_id.h"
#include "planescape.h"
#include "mudfile.h"


SPECIAL(shoper);

int get_obj_shop_count(struct char_data *shoper, struct obj_data *obj)
{
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;
    int vnum = GET_OBJ_VNUM(obj);

    for (ol = shop->obj_list; ol; ol = ol->next)
        if (ol->vnum == vnum)
            return (ol->percent);

    return (FALSE);
}

char *shop_argument(char *argument, char *first_arg)
{
    char *begin = first_arg;

    if (!argument) {
        log("SYSERR: one_argument received a NULL pointer!");
        *first_arg = '\0';
        return (NULL);
    }

    do {
        skip_spaces(&argument);

        first_arg = begin;
        while (*argument && !a_ihspace(*argument)) {
            *(first_arg++) = LOWER(*argument);
            argument++;
        }

        *first_arg = '\0';
    } while (fill_word(begin));

    return (argument);
}

int transaction_amt(char *arg)
{
    int num;
    char *buywhat;
    char buf[MAX_STRING_LENGTH];

    /*
     * If we have two arguments, it means 'buy 5 3', or buy 5 of #3.
     * We don't do that if we only have one argument, like 'buy 5', buy #5.
     * Code from Andrey Fidrya <andrey@ALEX-UA.COM>
     */
    buywhat = shop_argument(arg, buf);
    if (*buywhat && *buf && is_positive_number(buf)) {
        num = atoi(buf);
        strcpy(arg, arg + strlen(buf) + 1);
        return (num);
    }
    return (1);
}

int ok_damage_shopkeeper(struct char_data *ch, struct char_data *victim)
{

    /*if (victim->shop_data)
       {
       send_to_charf(ch,"� ��������� � ��������� ����� �� ��������� �������� ������.\r\n");
       return (FALSE);
       }
       else */
    return (TRUE);
}


int can_shop_obj(struct obj_data *obj, struct char_data *ch, struct mob_shop_data *m)
{
    struct list_obj_data *i;
    int type = GET_OBJ_TYPE(obj);

    if (GET_OBJ_VNUM(obj) == -1)
        return (FALSE);

    for (i = m->obj_type; i; i = i->next)
        if (type == i->vnum)
            return (TRUE);

    return (FALSE);
}

int sell_price(struct obj_data *obj, struct char_data *ch, struct mob_shop_data *shop)
{
    double profit = shop->sell;

    return (MAX(1, (int) (GET_OBJ_COST(obj) * (double) (profit / 100))));
}

int buy_price(struct obj_data *obj, struct char_data *ch, struct mob_shop_data *shop)
{
    double profit = shop->buy;

    return (MAX(1, (int) (GET_OBJ_COST(obj) * (double) (profit / 100) *
                          (double) ((double) GET_OBJ_CUR(obj) /
                                    (double) MAX(1, GET_OBJ_MAX(obj))))));
}

int repair_price(struct obj_data *obj, struct char_data *ch, struct mob_shop_data *shop)
{
    double profit = shop->repair;
    int price, repair;

    price = GET_OBJ_COST(obj);
    repair = GET_OBJ_MAX(obj) - GET_OBJ_CUR(obj);
    price =
        (int) ((double) price * (double) (profit / 100) *
               ((double) MAX(0, repair) / (double) MAX(1, GET_OBJ_MAX(obj))));

    //send_to_charf(ch,"koef %.2f\r\n", (float)MAX(0,repair) / (float)MAX(1, GET_OBJ_MAX(obj)));

    return price;
}

int count_shop_items(struct char_data *shoper)
{
    int i = 0;
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;

    for (ol = shop->obj_list; ol; ol = ol->next) {
        if (ol->percent == -1)
            continue;
        i++;
    }

    return (i);
}

void list_shop_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    char name[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;
    struct obj_data *obj;
    int rnum, i = 0, price, found = FALSE;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    strcpy(buf, " ##  �������        (����)\r\n");
    strcat(buf, "---------------------------\r\n");

    for (ol = shop->obj_list; ol; ol = ol->next) {
        if ((rnum = real_object(ol->vnum)) < 0)
            continue;

        if (*name && !isname(name, obj_proto[rnum].name))
            continue;

        i++;
        obj = read_object(rnum, REAL, FALSE);

        price = sell_price(obj, ch, shop);

        sprintf(buf + strlen(buf), "%2d) %s &K(&G%d&K %s)&n\r\n",
                i, GET_OBJ_PNAME(obj, 0), price, desc_count(price, WHAT_MONEYa));
        if (obj)
            extract_obj(obj);

        found = TRUE;
    }

    if (found)
        page_string(ch->desc, buf, 1);
    else
        send_to_charf(ch, "������� ���.\r\n");
}

int buy_one_object(struct char_data *ch, struct char_data *shoper, obj_rnum rnum, int price)
{
    struct obj_data *obj;

    if (!IS_NPC(ch) && invalid_no_class(ch, obj_proto + rnum)) {
        act("������������� ������ �������� ��� ������� $o3 $N5.", FALSE, ch, obj_proto + rnum,
            shoper, TO_CHAR);
        //act("������������� ������ �������� $n ������� $o3 $N5.",FALSE,ch,obj_proto+rnum,shoper,TO_ROOM);
        return (FALSE);
    }

    /*if (invalid_anti_class(ch, obj_proto+rnum))
       {
       act("$o �� �������� ��� ���.",FALSE,ch,obj_proto+rnum,shoper,TO_CHAR);
       return (FALSE);
       } */

    if ((IS_CARRYING_N(ch) + 1 > CAN_CARRY_N(ch))) {
        act("�� �� ������ �������� $o3 � ����� � ������� $N2.", FALSE, ch, obj_proto + rnum, shoper,
            TO_CHAR);
        //act("$n �� ����$q �������� $o3 � ����� � ������$g $N2.",FALSE,ch,obj_proto+rnum,shoper,TO_ROOM);
        return (FALSE);
    }

    if ((IS_CARRYING_W(ch) + GET_OBJ_WEIGHT(obj_proto + rnum)) > CAN_CARRY_W(ch)) {
        act("�� �� ������ ������� $o3 � ������� $N2.", FALSE, ch, obj_proto + rnum, shoper,
            TO_CHAR);
        //act("$n �� ����$q ������� $o3 � ������$g $N2.",FALSE,ch,obj_proto+rnum,shoper,TO_ROOM);
        return (FALSE);
    }

    obj = read_object(rnum, REAL, FALSE);
    obj_to_char(obj, ch);

    if (GET_OBJ_TYPE(obj) == ITEM_TATOO) {
        if (!tatoo_to_char(ch, shoper, obj)) {
            obj_from_char(obj);
            extract_obj(obj);
            return (FALSE);
        }
    }

    GET_GOLD(ch) -= price;
    GET_GOLD(shoper) += price;

    if (GET_OBJ_TYPE(obj) != ITEM_TATOO) {
        act("2+� ������2(,�,�,�) ��� @1�.", "���", ch, shoper, obj);
        act("2+� ������2(,�,�,�) 1+� @1+�.", "����", ch, shoper, obj);
    }

    rnum = GET_OBJ_VNUM(obj);
    del_shop_obj(shoper, rnum, 1);

    return (TRUE);
}

void tryon_obj_to_char(struct obj_data *obj, struct char_data *ch, int worn)
{
    if (GET_OBJ_TYPE(obj) == ITEM_ARMOR || GET_OBJ_TYPE(obj) == ITEM_LIGHT
        || GET_OBJ_TYPE(obj) == ITEM_WORN) {
        if (worn) {
            act("��������� $o3 �� ��� ����� ���� ������.", FALSE, ch, obj, 0, TO_CHAR);
        } else if (invalid_anti_class(ch, obj) || !OK_WEAR(ch, obj)) {
            act("���������� ��������� @1�, �� ����������, ��� @1�� �� ������@1(��,��,��,��).", "��",
                ch, obj);
            act("���������� ��������� @1�, 1� ���������1(,�,�,�), ��� @1�� �� ������@1(��,��,��,��).", "���", ch, obj);
        } else {
            act("�������� @1�, �� �����, ��� @1�� ������ ������@1(��,��,��,��).", "��", ch, obj);
            act("�������� @1�, 1� �������������� ������1(,�,�,�).", "���", ch, obj);
        }
    } else if (GET_OBJ_TYPE(obj) == ITEM_WEAPON) {
        if (!worn) {
            if (CAN_WEAR(obj, ITEM_WEAR_BOTHS))
                worn = ITEM_WEAR_BOTHS;
            else if (CAN_WEAR(obj, ITEM_WEAR_WIELD))
                worn = ITEM_WEAR_WIELD;
            else if (CAN_WEAR(obj, ITEM_WEAR_HOLD))
                worn = ITEM_WEAR_HOLD;
        }
        if (!CAN_WEAR(obj, worn) || invalid_no_class(ch, obj) || invalid_anti_class(ch, obj)
            || (worn == WEAR_WIELD && CAN_WEAR(obj, ITEM_WEAR_BOTHS))) {
            switch (worn) {
                case ITEM_WEAR_WIELD:
                    act("����������� �� $o3 �����, �� ����� ������, ��� $j �� ��� ���.", FALSE, ch,
                        obj, 0, TO_CHAR);
                    act("����������� ���� �� $o3 �����, $n ��������$u � �������$g $l � �����.",
                        FALSE, ch, obj, 0, TO_ROOM);
                    break;
                case ITEM_WEAR_HOLD:
                    act("�� ���������� ����� $o3 �� ����� ����, �� ����������, ��� ��� �� �������.",
                        FALSE, ch, obj, 0, TO_CHAR);
                    act("$n �������$u ����� $o3 �� ����� ����, �� $m ��� ������� �� �������.",
                        FALSE, ch, obj, 0, TO_ROOM);
                    break;
                case ITEM_WEAR_BOTHS:
                    act("���������� ����� � ���� @1�, �� ����������, ��� @1�� �� ������@1(��,��,��,��).", "��", ch, obj);
                    act("���������� ����� � ���� @1�, 1� ��������1(,�,�,�) � ��������1(,�,�,�).",
                        "���", ch, obj);
                    break;
            }
        } else {
            switch (worn) {
                case ITEM_WEAR_WIELD:
                    act("���� � ���� $o3, �� ��������� ������. ������ �������!", FALSE, ch, obj, 0,
                        TO_CHAR);
                    act("���� � ���� $o3, $n ��������$g ������ � �������� �������$u.", FALSE, ch,
                        obj, 0, TO_ROOM);
                    break;
                case ITEM_WEAR_HOLD:
                    act("�� �������� $o3, ���� $e �� ������ ����. ��������!", FALSE, ch, obj, 0,
                        TO_CHAR);
                    act("$n �������$g $o3, ���� $e �� ������ ���� � ������ �������$g.", FALSE, ch,
                        obj, 0, TO_ROOM);
                    break;
                case ITEM_WEAR_BOTHS:
                    act("���� $o3 � ����, �� �������� �� ������� � �������.", FALSE, ch, obj, 0,
                        TO_CHAR);
                    act("���� $o3 � ����, $n ����$y ���� ��� �� ������� � �������.", FALSE, ch, obj,
                        0, TO_ROOM);
                    break;
            }
        }
    }
}

void tryon_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    char name[MAX_INPUT_LENGTH], name2[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;
    int rnum, i = 0, worn = 0;
    char buf[MAX_STRING_LENGTH];

    two_arguments(arg, name, name2);

    if (*name2) {
        if (isname(name, "������"))
            worn = ITEM_WEAR_WIELD;
        else if (isname(name, "�����"))
            worn = ITEM_WEAR_HOLD;
        else if (isname(name, "���"))
            worn = ITEM_WEAR_BOTHS;
        else {
            send_to_charf(ch, "����������� ������� ��� ��������.\r\n");
            return;
        }
        strcpy(name, name2);
    }

    if (is_positive_number(name))
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            i++;
            if (i == atoi(name)) {
                if (GET_OBJ_TYPE(&obj_proto[rnum]) == ITEM_WEAPON)
                    act("$N ��������$G ��� ���������� $o3.", FALSE, ch, &obj_proto[rnum], shoper,
                        TO_CHAR);
                else if (GET_OBJ_TYPE(&obj_proto[rnum]) == ITEM_ARMOR
                         || GET_OBJ_TYPE(&obj_proto[rnum]) == ITEM_WORN)
                    act("$N ��������$G ��� ��������� $o3.", FALSE, ch, &obj_proto[rnum], shoper,
                        TO_CHAR);
                else {
                    send_to_charf(ch, "��� �� ����������� ��� ���������?\r\n");
                    return;
                }
                tryon_obj_to_char(&obj_proto[rnum], ch, worn);
                return;
            }
    } else
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            if (*name && isname(name, obj_proto[rnum].name)) {
                if (GET_OBJ_TYPE(&obj_proto[rnum]) == ITEM_WEAPON)
                    act("$N ��������$G ��� ���������� $o3.", FALSE, ch, &obj_proto[rnum], shoper,
                        TO_CHAR);
                else if (GET_OBJ_TYPE(&obj_proto[rnum]) == ITEM_ARMOR
                         || GET_OBJ_TYPE(&obj_proto[rnum]) == ITEM_WORN)
                    act("$N ��������$G ��� ��������� $o3.", FALSE, ch, &obj_proto[rnum], shoper,
                        TO_CHAR);
                else {
                    send_to_charf(ch, "��� �� ����������� ��� ���������?\r\n");
                    return;
                }
                tryon_obj_to_char(&obj_proto[rnum], ch, worn);
                return;
            }
        }

    sprintf(buf, "$N ������$G ���: '� �� ������ %s'.", name);
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
}

void look_shop_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    char name[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;
    int rnum, i = 0;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    if (is_positive_number(name))
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            i++;
            if (i == atoi(name)) {
                act("$N ��������$G ��� ����������� ����������� $o3.", FALSE, ch, &obj_proto[rnum],
                    shoper, TO_CHAR);
                exam_obj_to_char(&obj_proto[rnum], ch, 0, "");
                return;
            }
    } else
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            if (*name && isname(name, obj_proto[rnum].name)) {
                act("$N ��������$G ��� ����������� ����������� $o3.", FALSE, ch, &obj_proto[rnum],
                    shoper, TO_CHAR);
                exam_obj_to_char(&obj_proto[rnum], ch, 0, "");
                return;
            }
        }

    sprintf(buf, "$N ������$G ���: '� �� ������ %s'.", name);
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);

}

void buy_shop_object(char *arg, struct char_data *ch, struct char_data *shoper, int cnt)
{
    char name[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;
    int rnum, i = 0, price, need_gold;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    if (is_positive_number(name))
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            i++;
            if (i == atoi(name)) {
                price = sell_price(obj_proto + rnum, ch, shop);
                need_gold = price * cnt;
                if (need_gold > GET_GOLD(ch)) {
                    sprintf(buf, "$N ������$G ���: '��� ����� ������ %d %s.'", need_gold,
                            desc_count(price, WHAT_MONEYa));
                    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
                    act("$N ������$G ���: '� ��� �� ������ �����.'", FALSE, ch, 0, shoper, TO_CHAR);
                    return;
                } else {
                    need_gold = price * cnt;
                    sprintf(buf, "$N ������$G ���: '��� ����� ������ %d %s.'", need_gold,
                            desc_count(need_gold, WHAT_MONEYu));
                    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
                    for (int i = 1; i <= cnt; i++)
                        if (!buy_one_object(ch, shoper, rnum, price))
                            return;
                    return;
                }
            }
    } else
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            i++;

            if (*name && isname(name, obj_proto[rnum].name)) {
                price = sell_price(obj_proto + rnum, ch, shop);
                need_gold = price * cnt;
                if (need_gold > GET_GOLD(ch)) {
                    sprintf(buf, "$N ������$G ���: '��� ����� ������ %d %s.'", need_gold,
                            desc_count(price, WHAT_MONEYu));
                    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
                    act("$N ������$G ���: '� ��� �� ������ �����.'", FALSE, ch, 0, shoper, TO_CHAR);
                    return;
                } else {
                    if (cnt > ol->percent && ol->percent != -1) {
                        sprintf(buf, "$N ������$G ���: '� ���� ���� ������ %d $o'.", ol->percent);
                        act(buf, FALSE, ch, obj_proto + rnum, shoper, TO_CHAR);
                        cnt = ol->percent;
                    }
                    need_gold = price * cnt;
                    sprintf(buf, "$N ������$G ���: '��� ����� ������ %d %s.'", need_gold,
                            desc_count(need_gold, WHAT_MONEYu));
                    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
                    for (int i = 1; i <= cnt; i++)
                        if (!buy_one_object(ch, shoper, rnum, price))
                            return;
                    return;
                }
            }
        }

    sprintf(buf, "$N ������$G ���: '� �� ������ %s'.", name);
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
}

void sell_all(char *arg, struct char_data *ch, struct char_data *shoper)
{
    struct mob_shop_data *shop = shoper->shop_data;
    struct obj_data *obj, *next_obj;
    int rnum, index = 0, price = 0;
    char buf[MAX_STRING_LENGTH];
    struct mess_p_data *k;

    for (obj = ch->carrying; obj; obj = next_obj) {
        next_obj = obj->next_content;
        if (!CAN_SEE_OBJ(ch, obj))
            continue;

        rnum = GET_OBJ_VNUM(obj);
        if (rnum < 0) {
            sprintf(buf, "$N ������$G ���: '$o ���� �� ����������'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            //obj = next_obj;
            continue;
        }

        bool sfnd = FALSE;

        for (k = obj->mess_data; k; k = k->next)
            if (k->command == CMD_SELL && k->stoping == TRUE) {
                if (k->mess_to_char)
                    act(k->mess_to_char, "�", ch);
                if (k->mess_to_room)
                    act(k->mess_to_room, "��", ch);
                sfnd = TRUE;
                break;
            }

        if (sfnd)
            continue;

        if (!can_shop_obj(obj, ch, shop)) {
            sprintf(buf, "$N ������$G ���: '$o ���� �� ����������'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            //obj = next_obj;
            continue;
        } else
            if (buy_price(obj, ch, shop) < 1 ||
                OBJ_FLAGGED(obj, ITEM_DECAY) ||
                OBJ_FLAGGED(obj, ITEM_NORENT) || OBJ_FLAGGED(obj, ITEM_NOSELL)) {
            sprintf(buf, "$N ������$G ���: '������ �������� $o3 ��� ���� ���� �� �����'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            //obj = next_obj;
            continue;
        } else if (get_obj_shop_count(shoper, obj) > 10) {
            sprintf(buf, "$N ������$G ���: '� ���� ����� ����� ������'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            //obj = next_obj;
            continue;
        } else {

            if (GET_GOLD(shoper) < price + buy_price(obj, ch, shop)) {
                sprintf(buf, "$N ������$G ���: '� ���� ����������� ������'.");
                act(buf, FALSE, ch, 0, shoper, TO_CHAR);
                break;
            }

            act("$N �����$G � ��� $o3.", FALSE, ch, obj, shoper, TO_CHAR);
            act("$N �����$G � $n1 $o3.", FALSE, ch, obj, shoper, TO_ROOM);

            price += buy_price(obj, ch, shop);
            obj_from_char(obj);
            extract_obj(obj);
            add_shop_obj(shoper, rnum, 1);

            index++;
            //obj = next_obj;
        }
    }

    //send_to_charf(ch,"GOLD %d price %d\r\n",GET_GOLD(ch),price);
    GET_GOLD(ch) += price;
    GET_GOLD(shoper) -= price;
    if (price > 0)
        sprintf(buf, "$N ������$G ���: '� ��� ��� �� ��� %d %s'.", price,
                desc_count(price, WHAT_MONEYu));
    else
        sprintf(buf, "$N ������$G ���: '����� �� ���� �� �� ��������.'");
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
}

void sell_all_obj(char *arg, struct char_data *ch, struct char_data *shoper)
{
    struct mob_shop_data *shop = shoper->shop_data;
    struct obj_data *obj, *next_obj;
    int rnum, index = 0, price = 0;
    char buf[MAX_STRING_LENGTH];
    struct mess_p_data *k;

    if (!(obj = get_obj_in_list_vis(ch, arg, ch->carrying))) {
        send_to_charf(ch, "� ��� ��� ������ �������� �� '%s'.\r\n", arg);
        return;
    }

    while (obj) {
        next_obj = get_obj_in_list_vis(ch, arg, obj->next_content);

        rnum = GET_OBJ_VNUM(obj);
        if (rnum < 0) {
            sprintf(buf, "$N ������$G ���: '$o ���� �� ����������'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            obj = next_obj;
            continue;
        }

        bool sfnd = FALSE;

        for (k = obj->mess_data; k; k = k->next)
            if (k->command == CMD_SELL && k->stoping == TRUE) {
                if (k->mess_to_char)
                    act(k->mess_to_char, "�", ch);
                if (k->mess_to_room)
                    act(k->mess_to_room, "��", ch);
                sfnd = TRUE;
                break;
            }

        if (sfnd)
            continue;

        if (!can_shop_obj(obj, ch, shop)) {
            sprintf(buf, "$N ������$G ���: '$o ���� �� ����������'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            obj = next_obj;
            continue;
        } else
            if (buy_price(obj, ch, shop) < 1 ||
                OBJ_FLAGGED(obj, ITEM_DECAY) ||
                OBJ_FLAGGED(obj, ITEM_NORENT) || OBJ_FLAGGED(obj, ITEM_NOSELL)) {
            sprintf(buf, "$N ������$G ���: '������ �������� $o3 ��� ���� ���� �� �����'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            obj = next_obj;
            continue;
        } else if (get_obj_shop_count(shoper, obj) > 10) {
            sprintf(buf, "$N ������$G ���: '� ���� ����� ����� ������'.");
            act(buf, FALSE, ch, obj, shoper, TO_CHAR);
            obj = next_obj;
            continue;
        } else {
            if (GET_GOLD(shoper) < price + buy_price(obj, ch, shop)) {
                sprintf(buf, "$N ������$G ���: '� ���� ����������� ������'.");
                act(buf, FALSE, ch, 0, shoper, TO_CHAR);
                break;
            }

            act("$N �����$G � ��� $o3.", FALSE, ch, obj, shoper, TO_CHAR);
            act("$N �����$G � $n1 $o3.", FALSE, ch, obj, shoper, TO_ROOM);

            price += buy_price(obj, ch, shop);
            obj_from_char(obj);
            extract_obj(obj);
            add_shop_obj(shoper, rnum, 1);

            index++;
            obj = next_obj;
        }
    }

    //send_to_charf(ch,"GOLD %d price %d\r\n",GET_GOLD(ch),price);
    GET_GOLD(ch) += price;
    GET_GOLD(shoper) -= price;
    if (price > 0)
        sprintf(buf, "$N ������$G ���: '� ��� ��� �� ��� %d %s'.", price,
                desc_count(price, WHAT_MONEYu));
    else
        sprintf(buf, "$N ������$G ���: '����� �� ���� �� �� ��������.");
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
}

void sell_shop_object(char *arg, struct char_data *ch, struct char_data *shoper, int cnt)
{
    char name[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct obj_data *obj;
    int rnum, price, dotmode;
    char buf[MAX_STRING_LENGTH];
    struct mess_p_data *k;

    one_argument(arg, name);

//send_to_charf(ch,"name %s %d\r\n",name,cnt);

    dotmode = find_all_dots(name);

    if (dotmode == FIND_ALLDOT) {
        sell_all_obj(name, ch, shoper);
        return;
    } else if (dotmode == FIND_ALL) {
        sell_all(name, ch, shoper);
        return;
    }

    if (!(obj = get_obj_in_list_vis(ch, name, ch->carrying))) {
        send_to_charf(ch, "� ��� ��� ������ �������� �� '%s'.\r\n", name);
        return;
    }

    for (k = obj->mess_data; k; k = k->next)
        if (k->command == CMD_SELL && k->stoping == TRUE) {
            if (k->mess_to_char)
                act(k->mess_to_char, "�", ch);
            if (k->mess_to_room)
                act(k->mess_to_room, "��", ch);
            return;
        }

    if (!can_shop_obj(obj, ch, shop)) {
        sprintf(buf, "$N ������$G ���: '���� ��� �� ����������'.");
        act(buf, FALSE, ch, obj, shoper, TO_CHAR);
        return;
    }

    price = buy_price(obj, ch, shop);

    if (buy_price(obj, ch, shop) < 1 ||
        OBJ_FLAGGED(obj, ITEM_DECAY) ||
        OBJ_FLAGGED(obj, ITEM_NORENT) || OBJ_FLAGGED(obj, ITEM_NOSELL)) {
        sprintf(buf, "$N ������$G ���: '���� ���� ���� �� ����������'.");
        act(buf, FALSE, ch, 0, shoper, TO_CHAR);
        return;
    }

    else if (get_obj_shop_count(shoper, obj) > 10) {
        sprintf(buf, "$N ������$G ���: '� ���� ����� ����� ������'.");
        act(buf, FALSE, ch, obj, shoper, TO_CHAR);
        return;
    }

    if (GET_GOLD(shoper) < price) {
        act("$N ������$G ���: '� ���� �� ������ �����, ����� ������ $o3.'", FALSE, ch, obj, shoper,
            TO_CHAR);
        return;
    }

    sprintf(buf, "$N ������$G ���: '� ��� ��� �� $o3 %d %s'.", price,
            desc_count(price, WHAT_MONEYu));
    act(buf, FALSE, ch, obj, shoper, TO_CHAR);
    act("$N �����$G � ��� $o3.", FALSE, ch, obj, shoper, TO_CHAR);
    act("$N �����$G � $n1 $o3.", FALSE, ch, obj, shoper, TO_ROOM);


    GET_GOLD(ch) += price;
    GET_GOLD(shoper) -= price;
    rnum = GET_OBJ_VNUM(obj);
    obj_from_char(obj);
    extract_obj(obj);
    add_shop_obj(shoper, rnum, 1);

}

void value_shop_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    char name[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct obj_data *obj;
    int price;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    if (!(obj = get_obj_in_list_vis(ch, name, ch->carrying))) {
        send_to_charf(ch, "� ��� ��� ������ �������� �� '%s'.\r\n", name);
        return;
    }

    if (!can_shop_obj(obj, ch, shop)) {
        sprintf(buf, "$N ������$G ���: '���� ��� �� ����������'.");
        act(buf, FALSE, ch, obj, shoper, TO_CHAR);
        return;
    }

    price = buy_price(obj, ch, shop);
    if (GET_GOLD(shoper) < price) {
        act("$N ������$G ���: '� ���� �� ������ �����, ����� ������ $o3.'", FALSE, ch, obj, shoper,
            TO_CHAR);
        return;
    }

    sprintf(buf, "$N ������$G ���: '� ��� ��� �� $o3 %d %s'.", price,
            desc_count(price, WHAT_MONEYu));
    act(buf, FALSE, ch, obj, shoper, TO_CHAR);
}

int price_repair_object(struct obj_data *obj, struct char_data *ch, struct char_data *shoper)
{
    struct mob_shop_data *shop = shoper->shop_data;
    int price;
    char buf[MAX_STRING_LENGTH];

    if (!can_shop_obj(obj, ch, shop)) {
        sprintf(buf, "$N ������$G ���: '� �� ���������� ����� ����'.");
        act(buf, FALSE, ch, obj, shoper, TO_CHAR);
        return (FALSE);
    }

    if (GET_OBJ_MAX(obj) == GET_OBJ_CUR(obj)) {
        sprintf(buf, "$N ������$G ���: '$o �� ��������� � �������'.");
        act(buf, FALSE, ch, obj, shoper, TO_CHAR);
        return (FALSE);
    }

    price = MAX(1, repair_price(obj, ch, shop));

    return (price);
}

void value_repair_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    char name[MAX_INPUT_LENGTH];
    struct obj_data *obj;
    int price;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    if (!(obj = get_obj_in_list_vis(ch, name, ch->carrying))) {
        send_to_charf(ch, "� ��� ��� ������ �������� �� '%s'.\r\n", name);
        return;
    }

    if (!(price = price_repair_object(obj, ch, shoper)))
        return;

    sprintf(buf, "$N ������$G ���: '� ������������ $o3 �� %d %s.'", price,
            desc_count(price, WHAT_MONEYu));
    act(buf, FALSE, ch, obj, shoper, TO_CHAR);
}

void repair_shop_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    char name[MAX_INPUT_LENGTH];
    struct obj_data *obj;
    int price;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    if (!(obj = get_obj_in_list_vis(ch, name, ch->carrying))) {
        send_to_charf(ch, "� ��� ��� ������ �������� �� '%s'.\r\n", name);
        return;
    }

    if (!(price = price_repair_object(obj, ch, shoper)))
        return;


    if (price > GET_GOLD(ch)) {
        sprintf(buf, "$N ������$G ���: '� ��� �� ������ �����, ����� ��������� �� ������!'");
        act(buf, FALSE, ch, 0, shoper, TO_CHAR);
        return;
    }

    GET_GOLD(ch) -= price;
    GET_GOLD(shoper) += price;
    GET_OBJ_CUR(obj) = GET_OBJ_MAX(obj);

    sprintf(buf, "$N ������$G ���: '������ ����� ������ %d %s.'", price,
            desc_count(price, WHAT_MONEYu));
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);

    act("$N ����� �������$G $o3.", FALSE, ch, obj, shoper, TO_CHAR);
    act("$N ����� �������$G $o3 $n1.", FALSE, ch, obj, shoper, TO_ROOM);
}


void prob_shop_object(char *arg, struct char_data *ch, struct char_data *shoper)
{
    void mort_show_obj_values(struct obj_data *obj, struct char_data *ch, int fullness);
    char name[MAX_INPUT_LENGTH];
    struct mob_shop_data *shop = shoper->shop_data;
    struct list_obj_data *ol;
    int rnum, i = 0;
    int price = 150;
    char buf[MAX_STRING_LENGTH];

    one_argument(arg, name);

    if (GET_GOLD(ch) < price) {
        send_to_charf(ch,
                      "� ��� ��� �������� %d %s ����������� ��� ��������� ������� ��������.\r\n",
                      price, desc_count(price, WHAT_MONEYu));
        return;
    }

    if (is_positive_number(name))
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            i++;
            if (i == atoi(name)) {
                if (OBJ_FLAGGED(&obj_proto[rnum], ITEM_NOIDENT)) {
                    act("���������� � ��������� @1� ����������.", "��", ch, &obj_proto[rnum]);
                    return;
                }
                GET_GOLD(ch) -= 150;
                GET_GOLD(shoper) += 70;
                sprintf(buf, "$N ����$G � ��� %d %s �� ���������� � ��������� $o1.", price,
                        desc_count(price, WHAT_MONEYu));
                act(buf, FALSE, ch, &obj_proto[rnum], shoper, TO_CHAR);
                mort_show_obj_values(&obj_proto[rnum], ch, 0);
                return;
            }
    } else
        for (ol = shop->obj_list; ol; ol = ol->next) {
            rnum = real_object(ol->vnum);
            if (rnum < 0)
                continue;
            if (*name && isname(name, obj_proto[rnum].name)) {
                if (OBJ_FLAGGED(&obj_proto[rnum], ITEM_NOIDENT)) {
                    act("���������� � ��������� @1� ����������.", "��", ch, &obj_proto[rnum]);
                    return;
                }
                GET_GOLD(ch) -= 150;
                GET_GOLD(shoper) += 70;
                sprintf(buf, "$N ����$G � ��� %d %s �� ���������� � ��������� $o1.\r\n", price,
                        desc_count(price, WHAT_MONEYu));
                act(buf, FALSE, ch, &obj_proto[rnum], shoper, TO_CHAR);
                mort_show_obj_values(&obj_proto[rnum], ch, 0);
                return;
            }
        }

    sprintf(buf, "$N ������$G ���: '� �� ������ %s'.\r\n", name);
    act(buf, FALSE, ch, 0, shoper, TO_CHAR);
}


SPECIAL(shoper)
{
    struct char_data *shoper = (struct char_data *) me;

    if (shoper->shop_data == NULL)
        return (FALSE);

    if (CMD_IS("������") || CMD_IS("list")) {
        list_shop_object(argument, ch, shoper);
        return (TRUE);
    }

    if (CMD_IS("������") || CMD_IS("buy")) {
        if (!*argument)
            send_to_charf(ch, "��� �� ������ ������?\r\n");
        else
            buy_shop_object(argument, ch, shoper, transaction_amt(argument));
        return (TRUE);
    } else if (CMD_IS("�������") || CMD_IS("sell")) {
        if (!*argument)
            send_to_charf(ch, "��� �� ������ �������?\r\n");
        else if (count_shop_items(shoper) > 65) {
            act("2� ������2(,�,�,�) ���: '� ������ �� �������! ��� ������ ������� �����!!!'", "��",
                ch, shoper);
            return (TRUE);
        }
        sell_shop_object(argument, ch, shoper, transaction_amt(argument));
        return (TRUE);
    } else if (CMD_IS("�������") || CMD_IS("value")) {
        if (!*argument)
            send_to_charf(ch, "��� �� ������ �������?\r\n");
        else
            value_shop_object(argument, ch, shoper);
        return (TRUE);
    } else if (CMD_IS("������") || CMD_IS("repair")) {
        if (!*argument)
            send_to_charf(ch, "��� �� ������ ���������������?\r\n");
        else
            repair_shop_object(argument, ch, shoper);
        return (TRUE);
    } else if (CMD_IS("��������") || CMD_IS("property")) {
        if (!*argument)
            send_to_charf(ch, "�������� ������ �������� �� ������ ������?\r\n");
        else
            prob_shop_object(argument, ch, shoper);
        return (TRUE);
    } else if (CMD_IS("������������")) {
        if (!*argument)
            send_to_charf(ch, "������� ���� �� ������ ������������?\r\n");
        else
            value_repair_object(argument, ch, shoper);
        return (TRUE);
    }
    if (CMD_IS("���������")) {
        if (!*argument)
            send_to_charf(ch, "��� �� ������ ���������?\r\n");
        else
            tryon_object(argument, ch, shoper);
        return (TRUE);
    } else if (CMD_IS("�����������")) {
        if (!*argument)
            send_to_charf(ch, "��� ������ �� ������ �����������?\r\n");
        else
            look_shop_object(argument, ch, shoper);
        return (TRUE);
    }

    return (FALSE);
};



bool boot_shops(void)
{
    int i, j, t[2], number, numadd, rnum;
    struct char_data *shoper;
    CShop Shop;

    if (!Shop.Initialization())
        return (FALSE);

    if (!Shop.ReadConfig(MudFile(mud->shopFile).getCPath()))
        return (FALSE);

    number = Shop.GetNumberItem();
    for (i = 0; i < number; i++) {
        CItem *item = Shop.GetItem(i);
        int nr_mob = item->GetItem(SHOP_MOB)->GetInt();

        if ((rnum = real_mobile(nr_mob)) == -1)
            continue;

        shoper = mob_proto + rnum;

        numadd = item->GetItem(SHOP_LIST)->GetStrListNumber();
        for (j = 0; j < numadd; j++) {
            item->GetItem(SHOP_LIST)->GetStrList(j, t[0], t[1]);
            if (t[1] > 0)
                add_shop_obj(shoper, t[0], t[1]);
        }
    }
    return (TRUE);
}

bool save_shops(void)
{
    struct char_data *shoper;
    struct list_obj_data *ol;
    CShop Shop;

    if (!Shop.Initialization())
        return (FALSE);

    for (shoper = character_list; shoper; shoper = shoper->next) {
        if (!shoper->shop_data)
            continue;

        int num = Shop.NewSubItem();
        CItem *item = Shop.GetItem(num);

        item->GetItem(SHOP_NUMBER)->SetParam(num);
        item->GetItem(SHOP_MOB)->SetParam(GET_MOB_VNUM(shoper));
        for (ol = shoper->shop_data->obj_list; ol; ol = ol->next)
            if (ol->percent > 0)
                item->GetItem(SHOP_LIST)->AddParam(ol->vnum, ol->percent);
    }

    Shop.SaveAll(MudFile(mud->shopFile).getCPath(), TRUE);
    return (TRUE);
}

bool regain_shops(void)
{
    struct char_data *shoper;
    struct list_obj_data *ol;
    int rnum;

    for (shoper = character_list; shoper; shoper = shoper->next) {
        if (!shoper->shop_data)
            continue;
        int gold = 0;

        rnum = real_mobile(GET_MOB_VNUM(shoper));
        if (rnum != -1)
            gold = GET_GOLD(mob_proto + rnum);

        if (GET_GOLD(shoper) < (gold * 8) / 10)
            GET_GOLD(shoper) += gold / 10;

        for (ol = shoper->shop_data->obj_list; ol; ol = ol->next)
            if (ol->percent > 4 && number(1, 3) == 2)
                del_shop_obj(shoper, ol->vnum, 1);
    }

    return (TRUE);
}
