/********************************/
/* ��� ����� ���� (�) 2002-2005 */
/********************************/

#include "sysdep.h"

#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "handler.h"
#include "db.h"
#include "spells.h"
#include "constants.h"
#include "case.h"
#include "screen.h"
#include "events.h"
#include "expr.h"
#include "xboot.h"


#define TURN_RIGHT 1
#define TURN_LEFT 2

struct item_op_data *find_operations(struct obj_data *obj, struct char_data *actor, int no_cmd,
                                     int obj_arg)
{
    struct item_op_data *k;

    for (k = obj->operations; k; k = k->next)
        if ((k->command == no_cmd && !obj_arg) ||
            (k->command == no_cmd && obj_arg && obj_arg == k->obj_vnum)) {
            if (!EXPR(k->expr)->Expr(actor, NULL, NULL))
                continue;
            return (k);
        }
    return (NULL);
}

struct item_op_data *find_operations(struct obj_data *obj, struct char_data *actor, int no_cmd)
{
    return find_operations(obj, actor, no_cmd, 0);
}

struct item_op_data *find_operations(struct obj_data *obj, struct char_data *actor, int no_cmd,
                                     int obj_arg, int mob_arg)
{
    struct item_op_data *k;

    for (k = obj->operations; k; k = k->next)
        if ((k->command == no_cmd && !mob_arg) ||
            (k->command == no_cmd && mob_arg && mob_arg == k->mob_vnum)) {
            if (!EXPR(k->expr)->Expr(actor, NULL, NULL))
                continue;
            return (k);
        }

    return (NULL);
}

struct item_op_data *find_operations(struct char_data *mob, int no_cmd, int obj_arg)
{
    struct item_op_data *k;

    for (k = mob->operations; k; k = k->next)
        if ((k->command == no_cmd && !obj_arg) ||
            (k->command == no_cmd && obj_arg && obj_arg == k->obj_vnum))
            return (k);

    return (NULL);
}

struct item_op_data *find_operations(struct char_data *mob, int no_cmd)
{
    return find_operations(mob, no_cmd, 0);
}

struct item_op_data *find_operations(struct char_data *mob, int no_cmd, int obj_arg, int mob_arg)
{
    struct item_op_data *k;

    for (k = mob->operations; k; k = k->next)
        if ((k->command == no_cmd && !mob_arg) ||
            (k->command == no_cmd && mob_arg && mob_arg == k->mob_vnum))
            return (k);

    return (NULL);
}

///////////////////////////////////////////

void exe_script(struct char_data *actor, struct obj_data *obj, int nr, struct obj_data *tobj)
{
//����� ��� �������� ����������� � post_exe�
}

void post_exec(struct char_data *ch, struct obj_data *obj, struct obj_data *tobj,
               struct item_op_data *k)
{
    struct obj_data *robj = NULL;
    bool show_mess = FALSE;
    int in_room = IN_ROOM(ch);
    struct room_data *room = NULL;

    if (in_room != NOWHERE)
        room = &world[in_room];

    if (k->load_room) {
        robj = read_object(k->load_room, VIRTUAL, TRUE);
        if (robj) {
            if (IN_ROOM(ch) != NOWHERE) {
                int rnum = GET_OBJ_RNUM(robj);

                if (GET_OBJ_LIMIT(robj) >= obj_index[rnum].number + obj_index[rnum].stored) {
                    obj_to_room(robj, IN_ROOM(ch));
                    show_mess = TRUE;
                } else {
                    send_to_charf(ch, "�� ������ �� ���������.\r\n");
                    extract_obj(robj);
                }
            } else
                extract_obj(robj);
        }
    }

    if (k->load_char) {
        robj = read_object(k->load_char, VIRTUAL, TRUE);
        if (robj) {
            int rnum = GET_OBJ_RNUM(robj);

            if (GET_OBJ_LIMIT(robj) >= obj_index[rnum].number + obj_index[rnum].stored) {
                obj_to_char(robj, ch);
                show_mess = TRUE;
            } else {
                send_to_charf(ch, "�� ������ �� ���������.\r\n");
                extract_obj(robj);
            }
        }
    }

    if (show_mess) {
        if (k->mess_load_char)
            act(k->mess_load_char, "����", ch, obj, tobj, robj);
        if (k->mess_load_room)
            act(k->mess_load_room, "�����", ch, obj, tobj, robj);
    }

    if (k->script)
        go_script(k->script, ch, obj);

    if (k->extract >= 1)
        extract_obj(obj);
    if (tobj && k->extract >= 2)
        extract_obj(tobj);
    return;
}

void post_exec_victim(struct char_data *ch, struct obj_data *obj, struct char_data *victim,
                      struct item_op_data *k)
{
    int in_room = IN_ROOM(ch);
    struct obj_data *robj = NULL;
    bool show_mess = FALSE;
    struct room_data *room = NULL;

    if (in_room != NOWHERE)
        room = &world[in_room];

    if (k->load_room) {
        robj = read_object(k->load_room, VIRTUAL, TRUE);
        if (robj) {
            if (IN_ROOM(ch) != NOWHERE) {
                int rnum = GET_OBJ_RNUM(robj);

                if (GET_OBJ_LIMIT(robj) >= obj_index[rnum].number + obj_index[rnum].stored) {
                    obj_to_room(robj, IN_ROOM(ch));
                    show_mess = TRUE;
                } else {
                    send_to_charf(ch, "�� ������ �� ���������.\r\n");
                    extract_obj(robj);
                }
            } else
                extract_obj(robj);
        }
    }

    if (k->load_char) {
        robj = read_object(k->load_char, VIRTUAL, TRUE);
        if (robj) {
            int rnum = GET_OBJ_RNUM(robj);

            if (GET_OBJ_LIMIT(robj) >= obj_index[rnum].number + obj_index[rnum].stored) {
                obj_to_char(robj, ch);
                show_mess = TRUE;
            } else {
                send_to_charf(ch, "�� ������ �� ���������.\r\n");
                extract_obj(robj);
            }
        }
    }

    if (show_mess) {
        if (k->mess_load_char)
            act(k->mess_load_char, "����", ch, obj, victim, robj);
        if (k->mess_load_room)
            act(k->mess_load_room, "�����", ch, obj, victim, robj);
    }

    if (k->script)
        go_script(k->script, ch, obj);

    if (k->extract >= 1)
        extract_obj(obj);
    if (victim && k->extract >= 2)
        extract_char(victim, FALSE);
    return;
}


void turn_lockpick(struct char_data *ch, struct obj_data *obj, char *turn)
{
    int trn = 0;

    if (!IS_LOCKPICK(obj)) {
        act("��������� @1� ����� ������� ������, ���� ����������.", "��", ch, obj);
        return;
    }

    if (ch->dir_pick == -1 && ch->obj_pick == NULL) {
        act("������, ��� ������������ @1�, ������� ���-������ ����������.", "��", ch, obj);
        return;
    }

    if (!*turn) {
        act("���� �� ������ ��������� @1�, ������ ��� �����?", "��", ch, obj);
        return;
    }

    if (isname(turn, "������"))
        trn = TURN_RIGHT;
    else if (isname(turn, "�����"))
        trn = TURN_LEFT;

    if (!trn) {
        send_to_charf(ch, "����������� ����������� ��� ��������.\r\n");
        return;
    }

    char *lcode;
    int *pstep;

    if (ch->dir_pick != -1) {
        lcode = EXITDATA(IN_ROOM(ch), ch->dir_pick)->lock_code;
        pstep = &(EXITDATA(IN_ROOM(ch), ch->dir_pick)->lock_step);
    } else if (ch->obj_pick) {
        lcode = ch->obj_pick->lock_code;
        pstep = &(ch->obj_pick->lock_step);
    } else
        return;

    int skill = IS_MOB(ch) ? GET_SKILL_MOB(ch, SKILL_PICK_LOCK) : GET_SKILL(ch, SKILL_PICK_LOCK);
    int pick_quality = GET_OBJ_QUALITY(obj) * 3;
    int dir_pick = ch->dir_pick;
    struct obj_data *obj_pick = ch->obj_pick;

    act("�� ��������� ��������� @1� %1.", "���", ch, obj, trn == TURN_LEFT ? "������" : "�������");
    act("1� ��������� ��������1(,�,�,�) @1� %1.", "����", ch, obj,
        trn == TURN_LEFT ? "������" : "�������");
    if ((trn == TURN_RIGHT && lcode[*pstep] == '>') || (trn == TURN_LEFT && lcode[*pstep] == '<')) {
        (*pstep)++;
        if (!lcode[*pstep]) {
            act("��������� �������, ����� ������� ����� �������.", "�", ch);
            if (dir_pick != -1) {
                get_pick_door(ch, dir_pick);
                EXIT(ch, dir_pick)->lock_step = 0;
                pstep = 0;

            } else if (obj_pick) {
                get_pick_cont(ch, obj_pick);
                obj_pick->lock_step = 0;
                pstep = 0;
            }
            ch->dir_pick = -1;
            ch->obj_pick = NULL;
            return;
        } else {
            switch (number(0, 2)) {
                case 0:
                    act("����� ��������� ����� �������.", "�", ch);
                    break;
                case 1:
                    act("� ����� ���-�� ���� ��������.", "�", ch);
                    break;
                case 2:
                    act("�� ������� ���� ������� ������.", "�", ch);
                    break;
            }
        }
    } else {
        if (dir_pick != -1) {
            act("�� ������� �������������, $1� �������1(��,���,���,���) �� %1.", "���", ch,
                get_name_pad(EXIT(ch, dir_pick)->exit_name, PAD_VIN, PAD_OBJECT));
            ch->dir_pick = -1;
            ch->obj_pick = NULL;
            EXIT(ch, dir_pick)->lock_step = 0;
            pstep = 0;
        } else if (obj_pick) {
            act("�� ������� �������������, $1� �������1(��,���,���,���) �� @1�.", "���", ch,
                obj_pick);
            ch->dir_pick = -1;
            ch->obj_pick = NULL;
            obj->lock_step = 0;
            pstep = 0;
        }
        if (50 + pick_quality + (skill / 4) < number(0, 100)) {
            switch (number(0, 2)) {
                case 0:
                    act("� ����� ���-�� ����������� � @1� ������@1(��,���,���,���).", "��", ch,
                        obj);
                    break;
                case 1:
                    act("� ����� ���-�� ����� ��������� � @1� ������@1(��,���,���,���).", "��", ch,
                        obj);
                    break;
                case 2:
                    act("����� ��������� ������������� ��������� � @1� ������@1(��,���,���,���).",
                        "��", ch, obj);
                    break;
            }
            extract_obj(obj);
            if (number(1, 4) == 2) {
                char lock_code[32];

                *lock_code = '\0';
                if (dir_pick != -1) {
                    set_door_code(lock_code,
                                  (world[IN_ROOM(ch)].dir_option[dir_pick]->quality * 15) / 100);
                    strcpy(world[IN_ROOM(ch)].dir_option[dir_pick]->lock_code, lock_code);
                    world[IN_ROOM(ch)].dir_option[dir_pick]->lock_step = 0;
                } else if (obj_pick) {
                    set_door_code(lock_code, (GET_OBJ_QUALITY(obj_pick) * 15) / 10);
                    strcpy(obj_pick->lock_code, lock_code);
                    obj_pick->lock_step = 0;
                }
                act("�� �������� ��� ���������� � ����� ������ � ��������.", "�", ch);
            }
            act("������, �������� �������� ��� �������.", "�", ch);
            return;
        } else {
            switch (number(0, 2)) {
                case 0:
                    act("� ����� ���-�� ��������� �����������.", "�", ch);
                    break;
                case 1:
                    act("� ����� ���-�� ����� ���������.", "�", ch);
                    break;
                case 2:
                    act("����� ��������� ������������� ���������.", "�", ch);
                    break;
            }
        }
        act("������, �������� �������� ��� �������.", "�", ch);
    }

}

ACMD(do_item_turn)
{
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH], turn[MAX_STRING_LENGTH];
    struct obj_data *obj = NULL;
    struct char_data *found_char = NULL;

    skip_spaces(&argument);
    argument = two_arguments(argument, arg, turn);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ ���������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_EQUIP | FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (is_abbrev(turn, "��") || is_abbrev(turn, "to"))
        strcpy(turn, argument);

    if (IS_LOCKPICK(obj))
        turn_lockpick(ch, obj, turn);
    else {
        if ((k = find_operations(obj, ch, CMD_TURN))) {
            if (*turn && k->arg && !isname(k->arg, turn)) {
                act("�� ���������� ��������� @1�, �� ������ �� ��������.", "��", ch, obj);
                act("$1� �������1(��,����,����,����) ��������� @1�, �� ������ �� �����1(��,���,���,���).", "���", ch, obj);
                return;
            }

            if (k->active)
                act(k->active, "��", ch, obj);
            else
                act("�� �������� ��������� @1�.", "��", ch, obj);

            if (k->active_room)
                act(k->active_room, "���", ch, obj);
            else
                act("$1� �������� ��������1(,�,�,�) @1�.", "���", ch, obj);

            post_exec(ch, obj, NULL, k);
            return;
        } else {
            act("��������� @1�? � ���� ��� �������� ������.", "��", ch, obj);
            act("$1� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
        }
    }
}


ACMD(do_item_press)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "��") || is_abbrev(arg, "to"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ ������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_PRESS))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ��������� ������ �� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ��������� �����$1(,�,�,�) �� @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("������ �� @1�? ���� � �� ���������.", "��", ch, obj);
        act("$1� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}


ACMD(do_item_insert)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "��� ������ � ���� �� ������ ��������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);


    if (is_abbrev(arg, "�") || is_abbrev(arg, "in"))
        strcpy(arg, argument);

    if (!*name) {
        send_to_charf(ch, "��� �� ������ ��������?\r\n");
        return;
    }

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (!*arg) {
        act("���� �� ������ �������� @1�?", "��", ch, obj);
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &tobj);


    if (!tobj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_INSERT, GET_OBJ_VNUM(tobj)))) {
        if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
            act("�� ���������� �������� @1� � @2�, �� ������ �� �����.", "���", ch, obj, tobj);
            act("$1+� ���������1(,�,�,�) @1� � @2�, �� ������ �� �����1(��,���,���,���).", "���",
                ch, obj, tobj);
            return;
        }

        if (k->active)
            act(k->active, "���", ch, obj, tobj);
        else
            act("�� �������� @1� � @2�.", "���", ch, obj, tobj);

        if (k->active_room)
            act(k->active_room, "����", ch, obj, tobj);
        else
            act("$1� �������1(,�,�,�) @1� � @2�.", "����", ch, obj, tobj);

        post_exec(ch, obj, tobj, k);
        return;
    } else {
        act("���� �� ���������, �������� @1� � @2� ��� �� �������.", "���", ch, obj, tobj);
        act("$1+� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}

ACMD(do_item_join)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "��� ������ � � ��� �� ������ ���������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);

    if (is_abbrev(arg, "�") || is_abbrev(arg, "and"))
        strcpy(arg, argument);

    if (!*name) {
        send_to_charf(ch, "��� �� ������ ���������?\r\n");
        return;
    }

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (!*arg) {
        act("� ��� �� ������ ��������� @1�?", "��", ch, obj);
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &tobj);


    if (!tobj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_JOIN, GET_OBJ_VNUM(tobj)))) {
        if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
            act("�� ���������� ��������� @1� � @2�, �� ������ �� �����.", "���", ch, obj, tobj);
            act("$1� �������1(��,���,���,���) ��������� @1� � @2�, �� ������ �� �����1(��,���,���,���).", "���", ch, obj, tobj);
            return;
        }

        if (k->active)
            act(k->active, "���", ch, obj, tobj);
        else
            act("�� ��������� @1� � @2�.", "���", ch, obj, tobj);

        if (k->active_room)
            act(k->active_room, "����", ch, obj, tobj);
        else
            act("$1� ��������1(,�,�,�) @1� � @2�.", "����", ch, obj, tobj);

        post_exec(ch, obj, tobj, k);
        return;
    } else {
        act("���� �� ���������, ��������� @1� � @2� ��� �� �������.", "���", ch, obj, tobj);
        act("$1+� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}


ACMD(do_item_push)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ �������� � �����?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_PUSH))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("���������� � ������, �� �������� � ����� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("���������� � ������, $1� �������1(,�,�,�) � ����� @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("���� � �� ���������, �������� � ����� @1� ��� ����� �� �������.", "��", ch, obj);
        act("$1� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}


ACMD(do_item_twist)
{
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH], turn[MAX_STRING_LENGTH];
    struct obj_data *obj = NULL;
    struct char_data *found_char = NULL;

    skip_spaces(&argument);
    argument = two_arguments(argument, arg, turn);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ ���������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (is_abbrev(turn, "��") || is_abbrev(turn, "to"))
        strcpy(turn, argument);

    if (IS_LOCKPICK(obj))
        turn_lockpick(ch, obj, turn);
    else {
        if ((k = find_operations(obj, ch, CMD_TWIST))) {
            if (*turn && k->arg && !isname(k->arg, turn)) {
                act("�� ���������� ������� @1�, �� ������ �� �����.", "��", ch, obj);
                act("$1� �������1(��,���,���,���) ������� @1�, �� � �1�� ������ �� �����.", "���",
                    ch, obj);
                return;
            }

            if (k->active)
                act(k->active, "��", ch, obj);
            else
                act("�� ��������� ��������� @1�.", "��", ch, obj);

            if (k->active_room)
                act(k->active_room, "���", ch, obj);
            else
                act("$1� ��������� ��������1(,�,�,�) @1�.", "���", ch, obj);

            post_exec(ch, obj, NULL, k);
            return;
        } else {
            act("������� @1�? ���� � �� ���������.", "��", ch, obj);
            act("$1� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
        }
    }
}

ACMD(do_item_breach)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "��� ������ � ��� �� ������ �� �������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);

    if (!*name) {
        send_to_charf(ch, "� ��� �� ������ �������?\r\n");
        return;
    }

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (!*arg) {
        act("���� �� ������ �������� @1�?", "��", ch, obj);
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &tobj);


    if (!tobj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_BREACH, GET_OBJ_VNUM(tobj)))) {
        if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
            act("�� ���������� ������� @1� @2�, �� ������ �� �����.", "���", ch, obj, tobj);
            act("$1� �������1(��,���,���,���) ������� @1� @2�, �� � �1�� ������ �� �����.", "���",
                ch, obj, tobj);
            return;
        }

        if (k->active)
            act(k->active, "���", ch, obj, tobj);
        else
            act("��������� ������������, �� ������� @1� @2�.", "���", ch, obj, tobj);

        if (k->active_room)
            act(k->active_room, "����", ch, obj, tobj);
        else
            act("��������� ������������, $1� ������1(,�,�,�) @1� @2�.", "����", ch, obj, tobj);

        post_exec(ch, obj, tobj, k);
        return;
    } else {
        act("������� @1�? �� � ����� �� �� ���?", "���", ch, obj, tobj);
        act("$1+� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}


ACMD(do_item_nailup)
{
    struct char_data *found_char = NULL;
    struct obj_data *hammer =
        GET_EQ(ch, WEAR_WIELD) ? GET_EQ(ch,
                                        WEAR_WIELD) : (GET_EQ(ch, WEAR_BOTHS) ? GET_EQ(ch,
                                                                                       WEAR_BOTHS) :
                                                       NULL);
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "��� ������ � ��� �� ������ �� ������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);

    if (!*name) {
        send_to_charf(ch, "��� ������ � ���� �� ������ �� ������?\r\n");
        return;
    }

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (!*arg) {
        act("���� ������ �� ������ �� ������ @1�?", "��", ch, obj);
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &tobj);


    if (!tobj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (!hammer || (hammer && !IS_HAMMER(hammer))) {
        send_to_charf(ch, "������ ��� ������� ���-�� ��������, �������� � ���� �������.\r\n");
        return;
    }

    if ((k = find_operations(obj, ch, CMD_NAILUP, GET_OBJ_VNUM(tobj)))) {
        if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
            act("�� ��������� @1�, �� ������ @2� � @3� �� �������.", "����", ch, hammer, obj, tobj);
            act("$1� ��������1(,�,�,�) @1�, �� ������� @2� @3�, 1�� �� �������.", "����", ch,
                hammer, obj, tobj);
            return;
        }

        if (k->active)
            act(k->active, "����", ch, obj, tobj);
        else
            act("����� ������ @1�, �� ������ @2� � @3�.", "����", ch, hammer, obj, tobj);

        if (k->active_room)
            act(k->active_room, "�����", ch, obj, tobj);
        else
            act("$1� ��������1(,�,�,�) @1�, �� ������� @2� @3�, 1�� �� �������.", "�����", ch,
                hammer, obj, tobj);

        post_exec(ch, obj, tobj, k);
        return;
    } else {
        act("������ @1� � @2�? ������ �� �����!", "���", ch, obj, tobj);
        act("$1+� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, tobj);
    }
}


ACMD(do_item_shatter)
{
    struct char_data *found_char = NULL;
    struct obj_data *weapon =
        GET_EQ(ch, WEAR_WIELD) ? GET_EQ(ch,
                                        WEAR_WIELD) : (GET_EQ(ch, WEAR_BOTHS) ? GET_EQ(ch,
                                                                                       WEAR_BOTHS) :
                                                       NULL);
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];


    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ �� �������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }



    if ((k = find_operations(obj, ch, CMD_SHATTER))) {
        if (k->tool) {
            if (!GET_EQ(ch, WEAR_BOTHS) || GET_OBJ_TOOL(GET_EQ(ch, WEAR_BOTHS)) != k->tool) {
                act("��� �� ������� @1� �� ������ ������� � ����� %1.", "���", ch, obj,
                    get_name_pad((char *) tool_name[k->tool], 3, PAD_OBJECT));
                return;
            }
        } else
            if (!weapon ||
                (weapon &&
                 (GET_OBJ_TYPE(weapon) != ITEM_WEAPON ||
                  (GET_OBJ_TYPE(weapon) == ITEM_WEAPON &&
                   real_attack_type(GET_OBJ_VAL(weapon, 3)) != HIT_BLOW)))) {
            send_to_charf(ch,
                          "������ ��� ������� ���-�� ��������, �������� � ���� ������� ������.\r\n");
            return;
        }

        if (k->active)
            act(k->active, "���", ch, obj, weapon);
        else
            act("�� ������� @1�, ������ �� �@1�� @2�.", "���", ch, obj, weapon);

        if (k->active_room)
            act(k->active_room, "����", ch, obj, weapon);
        else
            act("$1� ������1(,�,�,�) @1�, ������ �@1�� @2�.", "����", ch, obj, weapon);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("������� @1�? �� �� ���!", "��", ch, obj);
        act("$1+� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}

ACMD(do_item_enter)
{
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH], turn[MAX_STRING_LENGTH];
    struct obj_data *obj = NULL;
    struct char_data *found_char = NULL;

    skip_spaces(&argument);
    argument = two_arguments(argument, arg, turn);

    if (!*arg) {
        send_to_charf(ch, "���� ������ �� ������ �����?\r\n");
        return;
    }

    if (is_abbrev(arg, "�") || is_abbrev(arg, "in")) {
        strcpy(arg, turn);
        strcpy(turn, argument);
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }


    if (GET_OBJ_TYPE(obj) == ITEM_TRANSPORT)
        go_enter(ch, obj);
    else {
        if ((k = find_operations(obj, ch, CMD_ENTER))) {
            if (*turn && k->arg && !isname(k->arg, turn)) {
                send_to_charf(ch, "turn %s arg %s\r\n", turn, k->arg);
                act("�� ���������� ����� � @1�, �� �� ������.", "��", ch, obj);
                act("$1� �������1(��,���,���,���) ����� � @1�, �� �� ����1(,��,��,��).", "���", ch,
                    obj);
                return;
            }

            if (k->active)
                act(k->active, "��", ch, obj);
            else
                act("�� ����� � @1�.", "��", ch, obj);

            if (k->active_room)
                act(k->active_room, "���", ch, obj);
            else
                act("$1� ���1(��,��,��,��) � @1�.", "���", ch, obj);

            post_exec(ch, obj, NULL, k);
            return;
        } else {
            act("����� � @1�? ���� �� ��� ��������.", "��", ch, obj);
            act("$1� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
        }
    }
}

ACMD(do_item_dig)
{
    struct char_data *found_char = NULL;
    struct obj_data *shovel =
        GET_EQ(ch, WEAR_WIELD) ? GET_EQ(ch,
                                        WEAR_WIELD) : (GET_EQ(ch, WEAR_BOTHS) ? GET_EQ(ch,
                                                                                       WEAR_BOTHS) :
                                                       NULL);
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];


    if (!shovel || (shovel && !IS_SHOVEL(shovel))) {
        send_to_charf(ch, "������ ��� ������� ������, �������� � ���� ������.\r\n");
        return;
    }

    if (!*argument) {
        go_dig(ch);
        return;
    }

    skip_spaces(&argument);
    argument = one_argument(argument, arg);


    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ ��������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ �������� ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_DIG, GET_OBJ_VNUM(shovel)))) {
        if (k->obj_vnum != GET_OBJ_VNUM(shovel)) {
            act("�� ���������� ������, �� ������ �� �����.", "���", ch, shovel, obj);
            act("$1� �������1(��,���,���,���) ������, �� � �1�� ������ �� �����.", "���", ch,
                shovel, obj);
            return;
        }

        if (k->active)
            act(k->active, "���", ch, shovel, obj);
        else
            act("��������� ������� ������, �� ��������� ������.", "���", ch, shovel, obj);

        if (k->active_room)
            act(k->active_room, "����", ch, shovel, obj);
        else
            act("��������� ������� ������, $1� ������1(��,���,���,���) ������.", "����", ch, shovel,
                obj);

        post_exec(ch, obj, shovel, k);
        return;
    } else {
        act("������ �����? �� � ����� �� �� ���?", "�", ch);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "��", ch);
    }
}

ACMD(do_item_pull)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ ��������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_PULL))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ������ �������� @1� �� ����.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ������ �������1(,�,�,�) @1� �� ����.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("���� � �� ��������� ������ @1�, ������ �� ����� �� ������.", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}


ACMD(do_item_dive)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "�") || is_abbrev(arg, "in"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "���� ������ �� ������ �������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_DIVE))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ������� � @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� �������1(,�,�,�) � @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("������� � @1�? ���� �� ��� ��������.", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}

ACMD(do_item_ring)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "�") || is_abbrev(arg, "in"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "�� ��� ������ �� ������ �������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_RING))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ��������� ��������� � @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ��������� ��������1(,�,�,�) � @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("���� � �� ��������� ������� � @1�, ������ �� ����� �� ������.", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}

ACMD(do_item_climb)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "�") || is_abbrev(arg, "in") || is_abbrev(arg, "��") || is_abbrev(arg, "at"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "���� ������ �� ������ �������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (IS_BARIAUR(ch)) {
        send_to_charf(ch, "���? �����? �� �� �� ��������, � ������!\r\n");
        return;
    }

    if ((k = find_operations(obj, ch, CMD_CLIMB))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else if (IS_OBJ_STAT(obj, ITEM_EXTERN))
            act("�� ������� � @1�.", "��", ch, obj);
        else
            act("�� ������� �� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else if (IS_OBJ_STAT(obj, ITEM_EXTERN))
            act("$1� �����1(,��,��,��) � @1�.", "���", ch, obj);
        else
            act("$1� �����1(,��,��,��) �� @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("������� � @1�? ���� �� ��� ��������.", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}


ACMD(do_item_jumpdown)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "c") || is_abbrev(arg, "with"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "������ �� ������ �� ���������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_JUMPDOWN))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ��������� � @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ��������1(,�,�,�) � @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("��������� � @1�? ���� �� ��� ��������.", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}

ACMD(do_item_jump)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "��") || is_abbrev(arg, "to"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "���� �� ������ �� ����������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_JUMP))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ���������� �� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ���������1(,�,�,�) �� @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("���������� �� @1�? ���� �� ��� ��������.", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}

ACMD(do_item_break)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ �������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_BREAK))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ������� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ������1(,�,�,�) @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else
        go_break(ch, obj);
}



ACMD(do_item_crack)
{
    struct char_data *found_char = NULL;
    struct obj_data *weapon =
        GET_EQ(ch, WEAR_WIELD) ? GET_EQ(ch,
                                        WEAR_WIELD) : (GET_EQ(ch, WEAR_BOTHS) ? GET_EQ(ch,
                                                                                       WEAR_BOTHS) :
                                                       NULL);
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];


    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ �� ���������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }


    if (!weapon ||
        (weapon &&
         (GET_OBJ_TYPE(weapon) != ITEM_WEAPON ||
          (GET_OBJ_TYPE(weapon) == ITEM_WEAPON &&
           real_attack_type(GET_OBJ_VAL(weapon, 3)) != HIT_SLASH)))) {
        send_to_charf(ch,
                      "������, ��� ���������� ���-������ ���������, ����������� ������� �������.\r\n");
        return;
    }

    if ((k = find_operations(obj, ch, CMD_CRACK))) {

        if (k->active)
            act(k->active, "���", ch, obj, weapon);
        else
            act("�� ��������� @1�, ������� @�� @2�.", "���", ch, obj, weapon);

        if (k->active_room)
            act(k->active_room, "����", ch, obj, weapon);
        else
            act("$1� ��������1(,�,�,�) @1�, ������� @�� @2�.", "����", ch, obj, weapon);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("��������� @1�? �� �� ���!", "��", ch, obj);
        act("$1+� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }
}

ACMD(do_item_clear)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ �� ����������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_CLEAR))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ��������� ���������� ����������� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ��������� ���������1(,�,�,�) ����������� @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("���������� ����������� @1�? �� �����?", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}

ACMD(do_item_erase)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ������ �� �������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_ERASE))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ��������� ������ @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ��������� ������ @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("������� @1�? �� �����?", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}

ACMD(do_item_burrow)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "�") || is_abbrev(arg, "in"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "��� ������ �� ���������� ������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_BURROW))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ��������� ������ � @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� ������1(��,���,���,���) ������ � @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("������ � @1�? �� �����?", "��", ch, obj);
        act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
    }
}


ACMD(do_item_knock)
{

    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "���� �� ������ ���������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);

    if (!*name) {
        send_to_charf(ch, "��������� ����?\r\n");
        return;
    }

    if (is_abbrev(name, "��") || is_abbrev(name, "to"))
        strcpy(name, arg);

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (*arg) {
        if (is_abbrev(arg, "��") || is_abbrev(arg, "to"))
            strcpy(arg, argument);

        generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &tobj);
        if (!tobj) {
            send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
            return;
        }

        if ((k = find_operations(obj, ch, CMD_KNOCK, GET_OBJ_VNUM(tobj)))) {
            if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
                act("�� ��������� @1� �� @2�, �� ������ �� ���������.", "���", ch, obj, tobj);
                act("$1� ��������1(,�,�,�) @1� �� @2�, �� ������ �� ���������.", "���", ch, obj,
                    tobj);
                return;
            }
            if (k->active)
                act(k->active, "���", ch, obj, tobj);
            else
                act("�� ��������� @1� �� @2�.", "���", ch, obj, tobj);
            if (k->active_room)
                act(k->active_room, "����", ch, obj, tobj);
            else
                act("$1� ��������1(,�,�,�) @1� �� @2�.", "����", ch, obj, tobj);

            post_exec(ch, obj, tobj, k);
            return;
        } else {
            act("��������� @1� �� @2�? �������� �� ����!", "���", ch, obj, tobj);
            act("$1� � ���-�� ������� �������1(��,���,���,���).", "���", ch, obj);
        }
    } else {
        if ((k = find_operations(obj, ch, CMD_KNOCK))) {
            if (k->active)
                act(k->active, "���", ch, obj, tobj);
            else
                act("�� ��������� �� @1�.", "���", ch, obj, tobj);
            if (k->active_room)
                act(k->active_room, "����", ch, obj, tobj);
            else
                act("$1� ��������1(,�,�,�) �� @1�.", "����", ch, obj, tobj);

            post_exec(ch, obj, tobj, k);
            return;
        } else {
            act("��������� �� @1�? �������� �� ����!", "���", ch, obj);
            act("$1� � ���-�� ������� �������1(��,���,���,���).", "��", ch);
        }
    }
}

ACMD(do_item_catchon)
{
    struct char_data *found_char = NULL;
    struct obj_data *obj = NULL;
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (is_abbrev(arg, "��") || is_abbrev(arg, "to"))
        strcpy(arg, argument);

    if (!*arg) {
        send_to_charf(ch, "�� ����� ������� �� ������ �� ����������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if ((k = find_operations(obj, ch, CMD_PRESS))) {
        if (k->active)
            act(k->active, "��", ch, obj);
        else
            act("�� ���������� �� @1�.", "��", ch, obj);

        if (k->active_room)
            act(k->active_room, "���", ch, obj);
        else
            act("$1� �������1(,�,�,�) �� @1�.", "���", ch, obj);

        post_exec(ch, obj, NULL, k);
        return;
    } else {
        act("���������� �� @1�? ���� �� ��� ��������.", "��", ch, obj);
        act("$1� ������1(,�,�,�) �������� @1� � ������ ��������1(,�,�,�).", "���", ch, obj);
    }

}

ACMD(do_item_sprinkle)
{
    struct char_data *victim = NULL;
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "��� ������ � ��� �� ������ �� ��������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);

    if (!*name) {
        send_to_charf(ch, "��� �� ������ ��������?\r\n");
        return;
    }

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &victim, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (!*arg) {
        act("��� ������ �� ������ �� ��������?", "��", ch, obj);
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM | FIND_CHAR_ROOM, ch, &victim, &tobj);


    if (!tobj && !victim) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (tobj) {
        if ((k = find_operations(obj, ch, CMD_SPRINKLE, GET_OBJ_VNUM(tobj)))) {
            if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
                act("�� �������� @2� ��������� �� @2�, �� ������ �� ���������.", "���", ch, obj,
                    tobj);
                act("$1� �������1(��,���,���,���) �������� @2� ��������� �� @1�.", "����", ch, obj,
                    tobj);
                return;
            }
            if (k->active)
                act(k->active, "���", ch, obj, tobj);
            else
                act("�� �������� @2� ��������� �� @1�.", "���", ch, obj, tobj);
            if (k->active_room)
                act(k->active_room, "����", ch, obj, tobj);
            else
                act("$1� �������1(,�,�,�) @2� ��������� �� @1�.", "����", ch, obj, tobj);

            post_exec(ch, obj, tobj, k);
            return;
        } else {
            act("�������� @2�? ���� �� ��� ��������.", "���", ch, obj, tobj);
            act("$1� � ���-�� ������� �������1(��,���,���,���).", "��", ch);
        }
    } else {
        if ((k = find_operations(obj, ch, CMD_SPRINKLE, 0, GET_MOB_VNUM(victim)))) {
            if (k->mob_vnum != GET_MOB_VNUM(victim)) {
                act("�� ���������� �������� $2� ��������� �� @1�, �� �� ������.", "���", ch, victim,
                    obj);
                act("$1� �������1(��,���,���,���) �������� $2� ��������� �� @1�.", "����", ch,
                    victim, obj);
                return;
            }

            if (k->active)
                act(k->active, "���", ch, victim, obj);
            else
                act("�� �������� $1� ��������� �� @1�.", "���", ch, victim, obj);

            if (k->active_room)
                act(k->active_room, "����", ch, victim, obj);
            else
                act("$1� �������1(,�,�,�) $1� ��������� �� @1�.", "����", ch, victim, obj);

            post_exec_victim(ch, obj, victim, k);
            return;
        } else {
            act("�������� $2�? ���� �� ��� ��������.", "���", ch, victim, obj);
            act("$1� � ���-�� ������� �������1(��,���,���,���).", "��", ch);
        }
    }

}


ACMD(do_item_smear)
{
    struct char_data *victim = NULL;
    struct obj_data *obj = NULL, *tobj = NULL;
    struct item_op_data *k = NULL;
    char name[MAX_STRING_LENGTH], arg[MAX_STRING_LENGTH];


    if (!*argument) {
        send_to_charf(ch, "��� ������ � ��� �� ������ �� ��������?\r\n");
        return;
    }

    skip_spaces(&argument);
    argument = two_arguments(argument, name, arg);

    if (!*name) {
        send_to_charf(ch, "��� �� ������ ��������?\r\n");
        return;
    }

    generic_find(name, FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &victim, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", name);
        return;
    }

    if (!*arg) {
        act("��� ������ �� ������ �� ��������?", "��", ch, obj);
        return;
    }

    generic_find(arg, FIND_OBJ_INV | FIND_OBJ_ROOM | FIND_CHAR_ROOM, ch, &victim, &tobj);

    if (!tobj && !victim) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (tobj) {
        if ((k = find_operations(obj, ch, CMD_SPRINKLE, GET_OBJ_VNUM(tobj)))) {
            if (k->obj_vnum != GET_OBJ_VNUM(tobj)) {
                act("�� �������� @2� �������� �� @2�, �� ������ �� ���������.", "���", ch, obj,
                    tobj);
                act("$1� �������1(��,���,���,���) �������� @2� �������� �� @1�.", "����", ch, obj,
                    tobj);
                return;
            }
            if (k->active)
                act(k->active, "���", ch, obj, tobj);
            else
                act("�� �������� @2� �������� �� @1�.", "���", ch, obj, tobj);
            if (k->active_room)
                act(k->active_room, "����", ch, obj, tobj);
            else
                act("$1� �������1(,�,�,�) @2� �������� �� @1�.", "����", ch, obj, tobj);

            post_exec(ch, obj, tobj, k);
            return;
        } else {
            act("�������� @2�? ���� �� ��� ��������.", "���", ch, obj, tobj);
            act("$1� � ���-�� ������� �������1(��,���,���,���).", "��", ch);
        }
    } else {
        if ((k = find_operations(obj, ch, CMD_SPRINKLE, 0, GET_MOB_VNUM(victim)))) {
            if (k->mob_vnum != GET_MOB_VNUM(victim)) {
                act("�� ���������� �������� $2� �������� �� @1�, �� �� ������.", "���", ch, victim,
                    obj);
                act("$1� �������1(��,���,���,���) �������� $2� �������� �� @1�.", "����", ch,
                    victim, obj);
                return;
            }

            if (k->active)
                act(k->active, "���", ch, victim, obj);
            else
                act("�� �������� $1� �������� �� @1�.", "���", ch, victim, obj);

            if (k->active_room)
                act(k->active_room, "����", ch, victim, obj);
            else
                act("$1� �������1(,�,�,�) $1� �������� �� @1�.", "����", ch, victim, obj);

            post_exec_victim(ch, obj, victim, k);
            return;
        } else {
            act("�������� $2�? ���� �� ��� ��������.", "���", ch, victim, obj);
            act("$1� � ���-�� ������� �������1(��,���,���,���).", "��", ch);
        }
    }

}

ACMD(do_action)
{
    struct item_op_data *k = NULL;
    char arg[MAX_STRING_LENGTH];
    struct obj_data *obj = NULL;
    struct char_data *found_char = NULL;

    skip_spaces(&argument);
    argument = one_argument(argument, arg);

    if (!*arg) {
        send_to_charf(ch, "�������� � ����� ��������� �� ������ ����������?\r\n");
        return;
    }

    generic_find(arg, FIND_OBJ_EQUIP | FIND_OBJ_INV | FIND_OBJ_ROOM, ch, &found_char, &obj);

    if (!obj) {
        send_to_charf(ch, "�� �� ������ ����� '%s'.\r\n", arg);
        return;
    }

    if (obj->operations) {
        send_to_charf(ch, "�� ������ ��������� ��������� ��������:\r\n");
        for (k = obj->operations; k; k = k->next) {
            int num_cmd = k->command - 100;

            send_to_charf(ch, " %s\r\n", action_name[num_cmd]);
        }
    }

}
