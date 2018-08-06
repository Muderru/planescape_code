/* ************************************************************************
*   File: spell_parser.c                                Part of CircleMUD *
*  Usage: top-level magic routines; outside points of entry to magic sys. *
*                                                                         *
*  All rights reserved.  See license.doc for complete information.        *
*                                                                         *
*  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
*  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
************************************************************************ */

#include "sysdep.h"
#include "structs.h"
#include "utils.h"
#include "interpreter.h"
#include "spells.h"
#include "handler.h"
#include "comm.h"
#include "db.h"
#include "screen.h"
#include "constants.h"
#include "pk.h"
#include "xspells.h"
#include "xenchant.h"
#include "xboot.h"
#include "sp_define.h"
#include "ai.h"

#define SkINFO skill_info[skillnum]

/* local functions */
void say_spell(struct char_data *ch, int spellnum, struct char_data *tch, struct obj_data *tobj);
void check_spellhaunt(struct char_data *ch, int mana);
int check_spell_agro(int spellnum, struct char_data *victim, int spell_agro);
void unused_skill(int spl);

const char *unused_spellname = "!UNUSED!";      /* So we can get &unused_spellname */


/*
 * This arrangement is pretty stupid, but the number of skills is limited by
 * the playerfile.  We can arbitrarily increase the number of skills by
 * increasing the space in the playerfile. Meanwhile, 200 should provide
 * ample slots for skills.
 */

struct syllable {
    const char *org;
    const char *news;
};


struct syllable syls[] = {
    {" ", " "},
    {"ar", "abra"},
    {"ate", "i"},
    {"cau", "kada"},
    {"blind", "nose"},
    {"bur", "mosa"},
    {"cu", "judi"},
    {"de", "oculo"},
    {"dis", "mar"},
    {"ect", "kamina"},
    {"en", "uns"},
    {"gro", "cra"},
    {"light", "dies"},
    {"lo", "hi"},
    {"magi", "kari"},
    {"mon", "bar"},
    {"mor", "zak"},
    {"move", "sido"},
    {"ness", "lacri"},
    {"ning", "illa"},
    {"per", "duda"},
    {"ra", "gru"},
    {"re", "candus"},
    {"son", "sabru"},
    {"tect", "infra"},
    {"tri", "cula"},
    {"ven", "nofo"},
    {"word of", "inset"},
    {"a", "i"}, {"b", "v"}, {"c", "q"}, {"d", "m"}, {"e", "o"}, {"f", "y"}, {"g", "t"},
    {"h", "p"}, {"i", "u"}, {"j", "y"}, {"k", "t"}, {"l", "r"}, {"m", "w"}, {"n", "b"},
    {"o", "a"}, {"p", "s"}, {"q", "d"}, {"r", "f"}, {"s", "g"}, {"t", "h"}, {"u", "e"},
    {"v", "z"}, {"w", "x"}, {"x", "n"}, {"y", "l"}, {"z", "k"}, {"", ""}
};


/* say_spell erodes buf, buf1, buf2 */
void say_spell(struct char_data *ch, int spellnum, struct char_data *tch, struct obj_data *tobj)
{
    const char *to_char = NULL, *to_vict = NULL, *to_room = NULL;
    const char *format;
    struct char_data *i;
    char buf[MAX_STRING_LENGTH];

    CItem *spell = Spl.GetItem(spellnum);

    if (!spell->GetItem(SPL_SAY_MESS)->GetNumberItem()) {
        return;
    }

    CItem *say = spell->GetItem(SPL_SAY_MESS)->GetItem(0);

    if (ch == tch && say->GetItem(SPL_SAY_ME)->GetString()) {
        to_char = say->GetItem(SPL_SAY_ME)->GetString();
    } else {
        if (say->GetItem(SPL_SAY_CHAR)->GetString())
            to_char = say->GetItem(SPL_SAY_CHAR)->GetString();
        else
            to_char = "�� ����������: '%s'";
    }

    format = to_char;
    sprintf(buf, to_char, SPELL_NAME(spellnum));
    act(buf, "���", ch, tch, tobj);

    if (say->GetItem(SPL_SAY_VICTIM)->GetString() && ch != tch)
        to_vict = say->GetItem(SPL_SAY_VICTIM)->GetString();

    if (ch == tch && say->GetItem(SPL_SAY_MROOM)->GetString()) {
        to_room = say->GetItem(SPL_SAY_MROOM)->GetString();
    } else {
        if (say->GetItem(SPL_SAY_ROOM)->GetString())
            to_room = say->GetItem(SPL_SAY_ROOM)->GetString();
        else
            to_room = "1� ��������1(,��,��,��): '%s'";
    }

    format = to_room;
    for (i = world[IN_ROOM(ch)].people; i; i = i->next_in_room) {
        if (to_vict && i == tch)
            continue;
        if (i == ch || !i->desc || !AWAKE(i))
            continue;

        if (IS_AFFECTED(i, AFF_DETECT_MAGIC) ||
            IS_SET(GET_SPELL_TYPE(i, SPELL_NO(spellnum)), SPELL_KNOW))
            sprintf(buf, to_room, SPELL_NAME(spellnum));
        else
            sprintf(buf, to_room, SPELL_SYN(spellnum));

        act(buf, "����", ch, tch, i, tobj);
    }

    if (to_vict) {
        format = to_vict;
        if (IS_AFFECTED(tch, AFF_DETECT_MAGIC) ||
            IS_SET(GET_SPELL_TYPE(tch, SPELL_NO(spellnum)), SPELL_KNOW))
            sprintf(buf, to_vict, SPELL_NAME(spellnum));
        else
            sprintf(buf, to_vict, SPELL_SYN(spellnum));

        act(buf, "���", ch, tch, tobj);
    }

}

/*
 * This function should be used anytime you are not 100% sure that you have
 * a valid spell/skill number.  A typical for() loop would not need to use
 * this because you can guarantee > 0 and <= TOP_SPELL_DEFINE.
 */
const char *skill_name(int num)
{
    if (num > 0 && num <= MAX_SPELLS)
        return (skill_info[num].name.c_str());
    else if (num == -1)
        return "UNUSED";
    else
        return "UNDEFINED";
}

const char *spell_name(int num)
{
    num = find_spell_num(num);

    if (num >= 0)
        return (SPELL_NAME(num));
    else if (num == -1)
        return "�����������";
    else
        return "��������������";
}


int find_skill_num(char *name)
{
    int index, ok;
    char *temp, *temp2;
    char first[256], first2[256];

    for (index = 1; index <= TOP_SKILL_DEFINE; index++) {
        if (is_abbrev(name, skill_info[index].name.c_str()))
            return (index);

        ok = TRUE;
        /* It won't be changed, but other uses of this function elsewhere may. */
        temp = any_one_arg((char *) skill_info[index].name.c_str(), first);
        temp2 = any_one_arg(name, first2);
        while (*first && *first2 && ok) {
            if (!is_abbrev(first2, first))
                ok = FALSE;
            temp = any_one_arg(temp, first);
            temp2 = any_one_arg(temp2, first2);
        }

        if (ok && !*first2)
            return (index);
    }
    return (-1);
}

//���������� ��������� ����� ����������
int find_spell_num(int spell_no)
{
    int index, number;

    number = Spl.GetNumberItem();
    for (index = 0; index < number; index++) {
        CItem *spell = Spl.GetItem(index);

        if (spell->GetItem(SPL_NUMBER)->GetInt() == spell_no)
            return (index);
    }

    return (-1);
}


int find_spell_num(char *name)
{
    int index, ok, number;
    char *temp, *temp2;
    char first[256], first2[256], *realname;

    number = Spl.GetNumberItem();
    for (index = 0; index < number; index++) {
        CItem *spell = Spl.GetItem(index);

        realname = spell->GetItem(SPL_NAME)->GetString();
        if (!realname || !*realname)
            continue;
        if (is_abbrev(name, realname))
            return (index);
        ok = TRUE;
        temp = any_one_arg((char *) realname, first);
        temp2 = any_one_arg(name, first2);
        while (*first && *first2 && ok) {
            if (!is_abbrev(first2, first))
                ok = FALSE;
            temp = any_one_arg(temp, first);
            temp2 = any_one_arg(temp2, first2);
        }
        if (ok && !*first2)
            return (index);
    }

    return (-1);
}


int may_kill_here(struct char_data *ch, struct char_data *victim, int show)
{
    if (IS_NPC(ch) && MOB_FLAGGED(ch, MOB_NOFIGHT))
        return (FALSE);

    if (IS_SOUL(victim))
        return (FALSE);

    if ((FIGHTING(ch) && FIGHTING(ch) == victim) || (FIGHTING(victim) && FIGHTING(victim) == ch)) {
        return (TRUE);
    } else if (ch != victim && ROOM_FLAGGED(ch->in_room, ROOM_PEACEFUL)) {
        if (IS_IMMORTAL(ch) ||
            may_pkill(ch, victim) == PC_REVENGE_PC ||
            (IS_NPC(ch) && ch->nr == real_mobile(CASTER_PROXY)) || IS_KILLER(victim))
            return (TRUE);
        else {
            if (show)
                send_to_char("����� ������� �����, ����� �������� �����...\r\n", ch);
            return (FALSE);
        }
    }

    if (ch->party_leader == victim || (ch->party_leader && ch->party_leader == victim->party_leader)
        || victim->party_leader == ch) {
        if (show)
            send_to_charf(ch, "�� �� ������ ��������� ������ ����������!!!\r\n");

        return (FALSE);
    }

    if (IS_NPC(victim) && MOB_FLAGGED(victim, MOB_NOFIGHT)) {
        if (show)
            act("��������� �� $N3 ����������, � ��� ������ �� �����.", FALSE, ch, 0, victim,
                TO_CHAR);
        return (FALSE);
    }

    if (!IS_NPC(victim) && (!victim->desc || PLR_FLAGGED(victim, PLR_DROPLINK))) {
        if (show)
            act("��������� �� ��������� ����������� ����� ����������!", FALSE, ch, 0, victim,
                TO_CHAR);
        return (FALSE);
    }

    return (TRUE);
}

int may_kill_here(struct char_data *ch, struct char_data *victim)
{
    return may_kill_here(ch, victim, TRUE);
}



int may_cast_in_nomagic(struct char_data *caster, struct char_data *victim, int spellnum)
{
    // More than 33 level - may cast always
    if (IS_GRGOD(caster))
        return (TRUE);

    // In nomagic cast only to victim
    if (!victim)
        return (FALSE);

    return (FALSE);
}



int may_cast_in_peacefull(struct char_data *caster, struct char_data *victim, int spellnum)
{
    int spell_agro = 0;

    if (!victim)
        return (TRUE);

    asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);

    /*  More than 33 level - may cast always */
    if (IS_GRGOD(caster))
        return (TRUE);

    if (check_spell_agro(spellnum, victim, spell_agro)) {
        if (victim && (FIGHTING(caster) == victim || may_pkill(caster, victim) == PC_REVENGE_PC))
            return (TRUE);
        else
            return (FALSE);
    }
    return (TRUE);
}

int check_mobile_list(struct char_data *ch)
{
    struct char_data *vict;

    for (vict = character_list; vict; vict = vict->next)
        if (vict == ch)
            return (TRUE);

    return (FALSE);
}

void cast_reaction_one(struct char_data *victim, struct char_data *caster, int spellnum)
{
//send_to_charf(caster,"��� �� %s\r\n",GET_NAME(victim));

    if (AFF_FLAGGED(victim, AFF_CHARM) || AFF_FLAGGED(victim, AFF_SLEEP) ||
        //AFF_FLAGGED(victim,AFF_BLIND)     ||
        AFF_FLAGGED(victim, AFF_STOPFIGHT) ||
        AFF_FLAGGED(victim, AFF_STUNE) || AFF_FLAGGED(victim, AFF_HOLD) || IS_HORSE(victim)
        )
        return;

    if (IS_NPC(caster) && GET_MOB_RNUM(caster) == real_mobile(CASTER_PROXY))
        return;

    if (may_pkill(caster, victim) != PC_REVENGE_PC &&
        (!IS_NPC(victim) || (IS_NPC(victim) && MOB_FLAGGED(victim, MOB_MEMORY)))) {
        //send_to_charf(victim,"���� �� %s\r\n",GET_NAME(caster));
        inc_pkill_group(victim, caster, 1, 0);
    }

    if (CAN_SEE(victim, caster) && MAY_ATTACK(victim) && IN_ROOM(victim) == IN_ROOM(caster)
        ) {
        if (may_pkill(caster, victim) != PC_REVENGE_PC)
            inc_pkill_group(victim, caster, 1, 0);
        if (IS_NPC(victim))
            attack_best(victim, caster);
    }
}

int check_spell_agro(int spellnum, struct char_data *victim, int spell_agro)
{
    if (IS_EVILS(victim) && (IS_SET(spell_agro, AGRO_EVIL) || IS_SET(spell_agro, AGRO_ALL)))
        return (TRUE);

    if (IS_GOODS(victim) && (IS_SET(spell_agro, AGRO_GOOD) || IS_SET(spell_agro, AGRO_ALL)))
        return (TRUE);

    if (IS_NEUTRALS(victim) && (IS_SET(spell_agro, AGRO_NEUTRAL) || IS_SET(spell_agro, AGRO_ALL)))
        return (TRUE);

    return (FALSE);
}

void cast_reaction(struct char_data *victim, struct char_data *caster, int spellnum)
{
    int spell_targets = 0, spell_agro = 0;
    struct char_data *tch;

    asciiflag_conv((char *) SPELL_TARGET(spellnum), &spell_targets);
    asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);

    if ((!check_mobile_list(victim) && !IS_SET(spell_targets, TAR_IGNORE)) || spell_agro == 0)
        return;

    if (victim) {
        if (check_spell_agro(spellnum, victim, spell_agro))
            cast_reaction_one(victim, caster, spellnum);
    } else if (!victim)
        for (tch = world[IN_ROOM(caster)].people; tch; tch = tch->next_in_room) {
            if (tch == caster)
                continue;
            if (same_group(caster, tch))
                continue;
            if (!may_kill_here(caster, tch))
                continue;

            if (check_spell_agro(spellnum, tch, spell_agro))
                cast_reaction_one(tch, caster, spellnum);
        }
}


/*
 * This function is the very heart of the entire magic system.  All
 * invocations of all types of magic -- objects, spoken and unspoken PC
 * and NPC spells, the works -- all come through this function eventually.
 * This is also the entry point for non-spoken or unrestricted spells.
 * Spellnum 0 is legal but silently ignored here, to make callers simpler.
 */
int call_magic(struct char_data *caster,
               struct char_data *cvict,
               struct obj_data *ovict, int spellnum, int level, int casttype, int show_mess)
{
    int i, found = FALSE, spell_agro = 0, sl = 0;
    char buf[MAX_STRING_LENGTH];

    if (casttype != CAST_WEAPON)
        GET_MISSED(caster)++;

    if (spellnum < 0 || spellnum > SPELL_NUMBERS) {
        sprintf(buf, "������: ������� ����������� ���������� � call_magic(): spellnum %d.",
                spellnum);
        log(buf);
        mudlog(buf, CMP, LVL_HIGOD, TRUE);
        return (FALSE);
    }

    if (!IS_NPC(caster) && casttype != CAST_WEAPON) {
        if (ROOM_FLAGGED(IN_ROOM(caster), ROOM_NOMAGIC) &&
            !may_cast_in_nomagic(caster, cvict, spellnum)) {
            send_to_char("���� ����� ������������ � ����� ��� � ������������.\r\n", caster);
            act("����� $n1 ������������ � ����� ��� � ������������.", FALSE, caster, 0, 0, TO_ROOM);
            return (FALSE);
        }

        if (ROOM_FLAGGED(IN_ROOM(caster), ROOM_PEACEFUL) &&
            !may_cast_in_peacefull(caster, cvict, spellnum) && casttype != CAST_WEAPON) {
            send_to_char("���� ����� ���������� ����� ���� � ����� �������!\r\n", caster);
            act("����� ������� �� ��� �������� $n1, � ��� �� �������.", FALSE, caster, 0, 0,
                TO_ROOM);
            return (FALSE);
        }
    }

    if ((sl = affected_room_by_spell(&world[IN_ROOM(caster)], SPELL_NOMAGIC_FIELD))
        && casttype != CAST_WEAPON) {
        if (number(sl / 2, sl) >= level) {
            send_to_char("���� ����� ���������������� ����� ���������.\r\n", caster);
            act("����� $n1 ���������������� ����� ���������.", FALSE, caster, 0, 0, TO_ROOM);
            return (FALSE);
        }
    }

    asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);

    struct char_data *tch, *temp = NULL;
    int plevel;

    if (cvict && ((plevel = affected_by_spell(cvict, SPELL_MAGIC_PARRY)) > number(1, level + 50))
        && check_spell_agro(spellnum, cvict, spell_agro)) {
        distract_magic_parry(cvict, SPELL_MANA(spellnum));

        //send_to_charf(caster,"����������\r\n");
        for (tch = world[IN_ROOM(cvict)].people; tch; tch = tch->next_in_room) {
            if (tch == cvict)
                continue;

            //send_to_charf(caster,"::%s",GET_NAME(tch));

            if (!general_savingthrow_3(cvict, SAV_WILL, plevel / 2)) {
                int ll;

                if ((ll = number(1, 10)) > GET_REAL_LCK(tch) && !temp) {        //���� ������� ����������
                    temp = tch;
                    //send_to_charf(caster,"+ %d > %d",ll,GET_REAL_LCK(tch));
                }
                //else send_to_charf(caster,"%d > %d",ll,GET_REAL_LCK(tch));
            }
            //send_to_charf(caster,"\r\n");
        }


        if (temp) {
            if (cvict != temp) {
                ;
            }
            cvict = temp;
        }

    }


    int concentration =
        10 + (SPELL_LEVEL(spellnum) / 10) + ((GET_REAL_INT(caster) - 10) / 2) + MAX(1,
                                                                                    (level / 100));
    if (cvict && check_spell_agro(spellnum, cvict, spell_agro)
        && general_savingthrow_3(cvict, SAV_WILL, concentration) && casttype == CAST_SPELL) {
        act("��� �� ������� ����������������� �� $N5.", FALSE, caster, 0, cvict, TO_CHAR);
        act("�� �������������, ��� ���-�� ������� �� ��� ������� ����������.", FALSE, caster, 0,
            cvict, TO_VICT);
        if (IS_NPC(caster))
            add_missed(caster, cvict);
        cast_reaction(cvict, caster, spellnum);
        return (FALSE);
    }
//�������� ���������
    for (i = 0; spell_functions[i].name; i++) {
        if (strcmp(SPELL_PROCEDURE(spellnum), spell_functions[i].name) == 0) {
            spell_functions[i].func(spellnum, level, caster, cvict, ovict, show_mess);
            found = TRUE;
        }
    }

    if (!found) {
        mudlogf(CMP, LVL_HIGOD, TRUE, "��������� ��� ���������� '%d' �� �������.", spellnum);
        return (FALSE);
    }

    if (cvict && check_spell_agro(spellnum, cvict, spell_agro))
        cast_reaction(cvict, caster, spellnum);
    return (TRUE);
}

ACMD(do_ident)
{
    struct char_data *cvict = NULL, *caster = ch;
    struct obj_data *ovict = NULL;
    struct timed_type timed;
    int k, level = 0, show_mess = TRUE, spellnum;
    char arg[MAX_STRING_LENGTH];

    if (IS_NPC(ch) || GET_SKILL(ch, SKILL_IDENTIFY) <= 0) {
        send_to_char("��� ����� ������� ����� ���������.\r\n", ch);
        return;
    }

    one_argument(argument, arg);

    if (timed_by_skill(ch, SKILL_IDENTIFY)) {
        send_to_char("��� ����� ������ ����������.\r\n", ch);
        return;
    }

    k = generic_find(arg, FIND_CHAR_ROOM |
                     FIND_OBJ_INV | FIND_OBJ_ROOM | FIND_OBJ_EQUIP, caster, &cvict, &ovict);
    if (!k) {
        send_to_char("������, ����� ����� ���.\r\n", ch);
        return;
    }
    if (!IS_IMMORTAL(ch)) {
        timed.skill = SKILL_IDENTIFY;
        timed.time = 12;
        timed_to_char(ch, &timed);
    }


    spellnum = find_spell_num(SPELL_IDENTIFY);
    MANUAL_SPELL(skill_identify)
}

/*
 * mag_objectmagic: This is the entry-point for all magic items.  This should
 * only be called by the 'quaff', 'use', 'recite', etc. routines.
 *
 * For reference, object values 0-3:
 * staff  - [0] level   [1] max charges [2] num charges [3] spell num
 * wand   - [0] level   [1] max charges [2] num charges [3] spell num
 * scroll - [0] level   [1] spell num   [2] spell num   [3] spell num
 * potion - [0] level   [1] spell num   [2] spell num   [3] spell num
 *
 * Staves and wands will default to level 14 if the level is not specified;
 * the DikuMUD format did not specify staff and wand levels in the world
 * files (this is a CircleMUD enhancement).
 */

const char *what_save_type[] = {
    "", "",                     //������������
    "", "",                     //�������
    "", "",                     //����
    "�����", "fire",
    "�����", "cold",
    "�������������", "electro",
    "�������", "acid",
    "", "",
    "", "",
    "", "",
    "", "",
    "", "",
    "", "",
    "", "",
    "\n"
};

const char *what_weapon[] = { "�����",
    "whip",
    "������",
    "club",
    "\n"
};

int find_cast_target(int spellnum, char *t, struct char_data *ch, struct char_data **tch,
                     struct obj_data **tobj)
{
    int spell_no = SPELL_NO(spellnum);
    int spell_agro = 0;
    int spell_targets = 0;

    *tch = NULL;
    *tobj = NULL;
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_STRING_LENGTH];
    char tmpl[MAX_STRING_LENGTH];

    asciiflag_conv((char *) SPELL_TARGET(spellnum), &spell_targets);
    asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);


    if (spell_no == SPELL_LOCATE_OBJECT && !t) {
        send_to_charf(ch, "����� ������� �� ������ �����?\r\n");
        return (FALSE);
    }

    if (spell_no == SPELL_DIMENSION_DOOR && !t) {
        send_to_charf(ch, "������� �����������?\r\n");
        return (FALSE);
    }

    if (spell_no == SPELL_LOCATE_PERSON && !t) {
        send_to_charf(ch, "���� �� ������ �����?\r\n");
        return (FALSE);
    }

    if (spell_no == SPELL_TELEPORT && !t) {
        send_to_charf(ch, "� ����� ����� ��� ���������?\r\n");
        return (FALSE);
    }

    if (spell_no == SPELL_ENDURE_ELEMENTS || spell_no == SPELL_ENDURE_ELEMENTS_P ||
        spell_no == SPELL_IMUN_ELEMENTS) {
        if (t != NULL)
            two_arguments(t, arg, t);
        else
            *arg = '\0';
        if (!*arg || (what_sky = search_block(arg, what_save_type, FALSE)) <= 0) {
            send_to_char("������ �� ���� (�����, �����, �������������, �������)?\r\n", ch);
            return FALSE;
        } else
            what_sky >>= 1;
    }
    //��������� ������
    if (spell_no == SPELL_IMPLANT_WEAPON) {
        if (t != NULL)
            two_arguments(t, arg, t);
        else
            *arg = '\0';
        if (!*arg) {
            send_to_charf(ch, "����� ������ ������ �������?\r\n");
            return (FALSE);
        } else {
            if (!(*tobj = get_obj_in_list_vis(ch, arg, ch->carrying))) {
                send_to_charf(ch, "� ��� ��� '%s' ��� �� �������.\r\n", arg);
                return (FALSE);
            }
        }
    }
    //���������� ������
    if (spell_no == SPELL_EXPAND_SKILL) {
        int qend, skill;
        char help[MAX_STRING_LENGTH];

        if (t != NULL) {
            t = one_argument(t, arg);
            skip_spaces(&t);
            strcpy(tmpl, t);
            strcpy(t, arg);
            strcpy(arg, tmpl);
        } else
            *arg = '\0';
        if (!*arg) {
            send_to_charf(ch, "������� �������� ������.\r\n");
            return (FALSE);
        } else {
            if (*arg != *ch->divd) {
                send_to_charf(ch, "������ ���� ��������� � �������: '%s'.\r\n", ch->divd);
                return (FALSE);
            }

            for (qend = 1; arg[qend] && arg[qend] != *ch->divd; qend++)
                arg[qend] = LOWER(arg[qend]);

            if (arg[qend] != *ch->divd) {
                send_to_charf(ch, "������ ������ ���� ��������� � �������: '%s'.\r\n", ch->divd);
                return (FALSE);
            }

            strcpy(help, (arg + 1));
            help[qend - 1] = '\0';

            if ((skill = find_skill_num(help)) < 0) {
                send_to_char("����������� ������.\r\n", ch);
                return (FALSE);
            } else {
                what_sky = skill;
                //what_sky >>=1;
            }
        }
    }

    if (spell_no == SPELL_BONES_WALL) {
        if (t && (what_sky = search_block(t, DirIs, FALSE)) >= 0)
            what_sky = what_sky;
        else
            what_sky = -1;
    }

    *cast_argument = '\0';

    if (t)
        strcat(cast_argument, t);

    if (t && spell_no == SPELL_IMPLANT_WEAPON)
        one_argument(t, t);

    if (IS_SET(spell_targets, TAR_IGNORE) &&
        !IS_SET(spell_targets,
                TAR_CHAR_ROOM | TAR_CHAR_WORLD | TAR_FIGHT_SELF | TAR_FIGHT_VICT |
                TAR_OBJ_INV | TAR_OBJ_ROOM | TAR_OBJ_WORLD | TAR_OBJ_EQUIP))
        return TRUE;
    else if (t != NULL && *t) {
        if (IS_SET(spell_targets, TAR_CHAR_ROOM)) {
            if ((*tch = get_char_vis(ch, t, FIND_CHAR_ROOM)) != NULL) {

                if (check_spell_agro(spellnum, *tch, spell_agro) && check_pkill(ch, *tch, t))
                    return FALSE;
                return TRUE;
            }
        }

        if (IS_SET(spell_targets, TAR_CHAR_WORLD)) {
            if ((*tch = get_char_vis(ch, t, FIND_CHAR_WORLD)) != NULL) {
                if (check_spell_agro(spellnum, *tch, spell_agro) && check_pkill(ch, *tch, t))
                    return FALSE;
                return TRUE;
            }
        }

        if (IS_SET(spell_targets, TAR_OBJ_INV))
            if ((*tobj = get_obj_in_list_vis(ch, t, ch->carrying)) != NULL)
                return TRUE;

        if (IS_SET(spell_targets, TAR_OBJ_EQUIP)) {
            int i;

            for (i = 0; i < NUM_WEARS; i++)
                if (GET_EQ(ch, i) && isname(t, GET_EQ(ch, i)->name)) {
                    *tobj = GET_EQ(ch, i);
                    return TRUE;
                }
        }

        if (IS_SET(spell_targets, TAR_OBJ_ROOM))
            if ((*tobj = get_obj_in_list_vis(ch, t, world[IN_ROOM(ch)].contents)) != NULL)
                return TRUE;

        if (IS_SET(spell_targets, TAR_OBJ_WORLD))
            if ((*tobj = get_obj_vis(ch, t)) != NULL)
                return TRUE;
    } else {
        if (IS_SET(spell_targets, TAR_FIGHT_SELF))
            if (FIGHTING(ch) != NULL) {
                *tch = ch;
                return TRUE;
            }
        if (IS_SET(spell_targets, TAR_FIGHT_VICT))
            if (FIGHTING(ch) != NULL) {
                *tch = FIGHTING(ch);
                return TRUE;
            }
        if (IS_SET(spell_targets, TAR_CHAR_ROOM) && !check_spell_agro(spellnum, ch, spell_agro)) {
            *tch = ch;
            return TRUE;
        }
    }

    if (IS_SET(spell_targets, TAR_IGNORE) && !t)
        return TRUE;

    sprintf(buf, "�� %s �� ������ ��� ���������?\r\n",
            IS_SET(spell_targets,
                   TAR_OBJ_ROOM | TAR_OBJ_INV | TAR_OBJ_WORLD | TAR_OBJ_EQUIP) ? "���" : "����");
    send_to_char(buf, ch);

    return (FALSE);
}

void mag_objectmagic(struct char_data *ch, struct obj_data *obj, char *argument)
{
    int found = FALSE, spellnum, level, i, spell_agro;
    struct char_data *tch = NULL;
    struct obj_data *tobj = NULL;
    struct mess_p_data *m;
    char *mess_to_char = NULL, *mess_to_room = NULL, *mess_to_vict = NULL, *mess_to_other = NULL;
    char buf[MAX_STRING_LENGTH];

    /* �������� �� �������� ��������� */
    for (m = obj->mess_data; m; m = m->next)
        if (m->command == CMD_USE) {
            found = TRUE;
            mess_to_char = m->mess_to_char;
            mess_to_vict = m->mess_to_vict;
            mess_to_other = m->mess_to_other;
            mess_to_room = m->mess_to_room;
        }

    /* ����� ���� */
    switch (GET_OBJ_TYPE(obj)) {
        case ITEM_STAFF:
        case ITEM_WAND:
            if (GET_OBJ_VAL(obj, 2) <= 0 && GET_OBJ_VAL(obj, 2) != -255) {
                if (GET_OBJ_VAL(obj, 2) != -255)
                    GET_OBJ_VAL(obj, 2) = -1;
                act("������ � @1� �����������.", "��", ch, obj);
                return;
            }

            spellnum = find_spell_num(GET_OBJ_VAL(obj, 3));
            if (spellnum < 0) {
                send_to_charf(ch, "�� ������� ���������� %d �������� �� ����������.\r\n",
                              GET_OBJ_VAL(obj, 1));
                return;
            }
            spell_agro = 0;
            asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);
            if (!*argument)
                tch = ch;
            else if (!find_cast_target(spellnum, argument, ch, &tch, &tobj))
                return;
            if (tch && check_spell_agro(spellnum, tch, spell_agro) && MOB_FLAGGED(tch, MOB_NOFIGHT)) {
                act("�������� �� $N3 ����������!", FALSE, ch, 0, tch, TO_CHAR);
                return;
            }

            if (!found) {
                if (tobj) {
                    sprintf(buf, "�� ������� %s �� $o3.", GET_OBJ_PNAME(obj, 4));
                    act(buf, FALSE, ch, tobj, tch, TO_CHAR);
                    sprintf(buf, "$n ������$g %s �� $o3.", GET_OBJ_PNAME(obj, 4));
                    act(buf, FALSE, ch, tobj, tch, TO_ROOM);
                } else if (tch) {
                    if (ch == tch) {
                        sprintf(buf, "�� ������� %s �� ����.", GET_OBJ_PNAME(obj, 4));
                        act(buf, FALSE, ch, tobj, tch, TO_CHAR);
                        sprintf(buf, "$n ������$g %s �� ����.", GET_OBJ_PNAME(obj, 4));
                        act(buf, FALSE, ch, tobj, tch, TO_ROOM);
                    } else {
                        sprintf(buf, "�� ������� %s �� $N3.", GET_OBJ_PNAME(obj, 4));
                        act(buf, FALSE, ch, tobj, tch, TO_CHAR);
                        sprintf(buf, "$n ������$g %s �� ���.", GET_OBJ_PNAME(obj, 4));
                        act(buf, FALSE, ch, tobj, tch, TO_VICT);
                        sprintf(buf, "$n ������$g %s �� $N3.", GET_OBJ_PNAME(obj, 4));
                        act(buf, FALSE, ch, tobj, tch, TO_NOTVICT);
                    }
                }
            } else {
                act(mess_to_char, "����", ch, tch, obj, tobj);
                act(mess_to_vict, "����", ch, tch, obj, tobj);
                act(mess_to_room, "�����", ch, tch, obj, tobj);
            }

            WAIT_STATE(ch, PULSE_VIOLENCE);
            level = GET_OBJ_VAL(obj, 0);
            call_magic(ch, tch, tobj, spellnum, level, CAST_WAND, TRUE);

            if (GET_OBJ_VAL(obj, 2) != -255)
                GET_OBJ_VAL(obj, 2)--;

            if (GET_OBJ_VAL(obj, 2) <= 0 && GET_OBJ_VAL(obj, 2) != -255) {
                GET_OBJ_VAL(obj, 2) = -1;
                act("������ � @1� �����������.", "��", ch, obj);
            }
            break;
        case ITEM_SCROLL:
        case ITEM_POTION:
            if (AFF_FLAGGED(ch, AFF_SIELENCE) && GET_OBJ_TYPE(obj) == ITEM_SCROLL) {
                send_to_char("�� �� ������ ���������� ����� ����������.\r\n", ch);
                return;
            }
            if (AFF_FLAGGED(ch, AFF_BLIND) && GET_OBJ_TYPE(obj) == ITEM_SCROLL) {
                send_to_char("�� �����.\r\n", ch);
                return;
            }

            spellnum = find_spell_num(GET_OBJ_VAL(obj, 1));
            if (spellnum < 0) {
                send_to_charf(ch, "�� ������� ���������� %d �������� �� ����������.\r\n",
                              GET_OBJ_VAL(obj, 1));
                return;
            }
            int spell_agro = 0;

            asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);
            if (!*argument)
                tch = ch;
            else if (!find_cast_target(spellnum, argument, ch, &tch, &tobj))
                return;
            if (tch && check_spell_agro(spellnum, tch, spell_agro) && MOB_FLAGGED(tch, MOB_NOFIGHT)) {
                act("�������� �� $N3 ����������!", FALSE, ch, 0, tch, TO_CHAR);
                return;
            }
            if (GET_OBJ_TYPE(obj) == ITEM_SCROLL) {
                if (tobj) {
                    sprintf(buf, "�� �������� %s �� $o3.", GET_OBJ_PNAME(obj, 3));
                    act(buf, FALSE, ch, tobj, tch, TO_CHAR);
                    sprintf(buf, "$n �������$g %s �� $o3.", GET_OBJ_PNAME(obj, 3));
                    act(buf, FALSE, ch, tobj, tch, TO_ROOM);
                } else if (tch) {
                    if (ch == tch) {
                        sprintf(buf, "�� �������� %s �� ����.", GET_OBJ_PNAME(obj, 3));
                        act(buf, FALSE, ch, tobj, tch, TO_CHAR);
                        sprintf(buf, "$n �������$g %s �� ����.", GET_OBJ_PNAME(obj, 3));
                        act(buf, FALSE, ch, tobj, tch, TO_ROOM);
                    } else {
                        sprintf(buf, "�� �������� %s �� $N3.", GET_OBJ_PNAME(obj, 3));
                        act(buf, FALSE, ch, tobj, tch, TO_CHAR);
                        sprintf(buf, "$n �������$g %s �� ���.", GET_OBJ_PNAME(obj, 3));
                        act(buf, FALSE, ch, tobj, tch, TO_VICT);
                        sprintf(buf, "$n �������$g %s �� $N3.", GET_OBJ_PNAME(obj, 3));
                        act(buf, FALSE, ch, tobj, tch, TO_NOTVICT);
                    }
                }
            }

            if (GET_OBJ_TYPE(obj) == ITEM_POTION) {
                tch = ch;
                act("�� ������� $o3.", FALSE, ch, obj, NULL, TO_CHAR);
                act("$n ������$g $o3.", TRUE, ch, obj, NULL, TO_ROOM);
            }

            WAIT_STATE(ch, PULSE_VIOLENCE);
            level = GET_OBJ_VAL(obj, 0);
            for (i = 1; i <= 3; i++) {
                spellnum = find_spell_num(GET_OBJ_VAL(obj, i));
                if (spellnum < 0)
                    continue;
                call_magic(ch, tch, tobj, spellnum, level, CAST_SCROLL, TRUE);
            }
            // break;

            if (obj != NULL)
                extract_obj(obj);
            break;
    }

}


/*
 * cast_spell is used generically to cast any spoken spell, assuming we
 * already have the target char/obj and spell number.  It checks all
 * restrictions, etc., prints the words, etc.
 *
 * Entry point for NPC casts.  Recommended entry point for spells cast
 * by NPCs via specprocs.
 */

int cast_spell(struct char_data *ch, struct char_data *tch, struct obj_data *tobj, int spellnum)
{
    int casting, skillz, manacost = 0, level;
    int spell_targets = 0;
    float tflt = 0;

    if (spellnum < 0 || spellnum > SPELL_NUMBERS) {
        log("������: ������� ����������� ���������� � cast_spell(): spellnum %d.", spellnum);
        return (FALSE);
    }

    asciiflag_conv((char *) SPELL_TARGET(spellnum), &spell_targets);

    if (GET_POS(ch) < SPELL_POS(spellnum)) {
        switch (GET_POS(ch)) {
            case POS_SLEEPING:
                send_to_char("��������� �� ��� ������!\r\n", ch);
                break;
            case POS_RESTING:
                send_to_char("�������, ��� �� �������� �����������������.\r\n", ch);
                break;
            case POS_SITTING:
                send_to_char("� ����� ���� �� ������ ���������.\r\n", ch);
                break;
            case POS_FIGHTING:
                send_to_char("��� �� ������ ����������.\r\n", ch);
                break;
            default:
                send_to_char("��� ���� �� ��� ��������.\r\n", ch);
                break;
        }
        return (FALSE);
    }

    if (AFF_FLAGGED(ch, AFF_CHARM) && (ch->master == tch)) {
        send_to_char("�� �� ������ ��������� ���� ������ ����������!\r\n", ch);
        return (FALSE);
    }

    if (tch != ch && !IS_GOD(ch) && IS_SET(spell_targets, TAR_SELF_ONLY)) {
        send_to_char("��� ���������� ����� ��������� ������ �� ����!\r\n", ch);
        return (FALSE);
    }

    if (tch == ch && IS_SET(spell_targets, TAR_NOT_SELF)) {
        send_to_char("�� ����� ��������� ��� �� ����!\r\n", ch);
        return (FALSE);
    }

    if ((!tch || IN_ROOM(tch) == NOWHERE) && !tobj &&
        IS_SET(spell_targets,
               TAR_CHAR_ROOM | TAR_CHAR_WORLD | TAR_FIGHT_SELF | TAR_FIGHT_VICT |
               TAR_OBJ_INV | TAR_OBJ_ROOM | TAR_OBJ_WORLD | TAR_OBJ_EQUIP) &&
        !IS_SET(spell_targets, TAR_IGNORE)) {
        send_to_char("���� �� �������.\r\n", ch);
        return (FALSE);
    }
    // ���� �� �����
    skillz = SPELL_SPHERE(spellnum) + TYPE_SPHERE_SKILL;

    level = GET_SKILL(ch, skillz);

    casting = level + GET_CAST_SUCCESS(ch);

    /* ������� ������� �������� ��� ������� �������� ��� �������� */
    if (IS_GOD(ch))
        tflt = 0;
    else
        tflt = SPELL_MANA(spellnum);
    if (GET_MANA(ch) < tflt) {
        act("� ��� ���� ���������� �������!", FALSE, ch, 0, 0, TO_CHAR);
        //act("�� ������ �� ��������.",TRUE,caster,0,0,TO_ROOM);
        return (FALSE);
    } else
        GET_MANA(ch) = (int) (GET_MANA(ch) - tflt);

    if (tch && check_distance(ch, tch) == DIST_0 && FIGHTING(ch)) {
        int skill = GET_SKILL(ch, SKILL_CONCENTRATE);

        if ((skill > 50 && number(1, 100) > skill) || (skill <= 50 && number(1, 4) == 2)) {
            act("��� �� ������� ������������������ � ���.", "�", ch);
            act("1� �� ����1(,��,��,��) ������������������ � ���.", "��", ch);
            check_spellhaunt(ch, SPELL_MANA(spellnum));
            WAIT_STATE(ch, PULSE_VIOLENCE);
            return (0);
        }
        improove_skill(ch, tch, 0, SKILL_CONCENTRATE);
    }

    if (!IS_NPC(ch) && SPELL_CONCENT(spellnum) && (number(1, SPELL_CONCENT(spellnum)) > casting)) {
        act("��� �� ������� ������������������.", "�", ch);
        act("1� �� ����1(,��,��,��) ������������������.", "��", ch);
        check_spellhaunt(ch, SPELL_MANA(spellnum));
        WAIT_STATE(ch, PULSE_VIOLENCE);
        return (0);
    }

    say_spell(ch, spellnum, tch, tobj);

    if (IS_GOD(ch) || IS_MOB(ch))
        manacost = 0;
    else
        manacost = GET_MOVE_COST(caster, spellnum);

    if (GET_MOVE(ch) > manacost)
        GET_MOVE(ch) -= manacost;
    else {
        GET_HIT(ch) -= manacost;
        send_to_char("�� ���������� �� ���������, � ���� ���� ����� �����������.\r\n", ch);
        act("���� $n ����������� �� ���������, � �� $s ��� ������� �����.", TRUE, ch, 0, 0,
            TO_ROOM);
    }

    if (tch && affected_by_spell(tch, SPELL_MAGIC_IMMUNITY)) {
        if (tch == ch) {
            act("���������� ��� ���������� ���� �������� ���� ����������.", FALSE, ch, 0, tch,
                TO_CHAR);
            act("���������� $N3 ���������� ���� �������� ���������� � ����������.", FALSE, ch, 0,
                tch, TO_ROOM);
        } else {
            act("���������� $N3 ���������� ���� �������� ���� ���������� � ����������.", FALSE, ch,
                0, tch, TO_CHAR);
            act("���������� ��� ���������� ���� �������� ���������� $n1.", FALSE, ch, 0, tch,
                TO_VICT);
            act("���������� $N3 ���������� ���� �������� ���������� $n1 � ����������.", FALSE, ch,
                0, tch, TO_NOTVICT);
        }
        affect_from_char(tch, SPELL_MAGIC_IMMUNITY);
        return (TRUE);
    }

    return (call_magic(ch, tch, tobj, spellnum, level, CAST_SPELL, TRUE));
}

ACMD(do_cast)
{
    struct char_data *tch = NULL;
    struct obj_data *tobj = NULL;
    char *s, *t;
    int spellnum, target = 0, casting = 0, skillz = 0, spell_agro = 0;
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_STRING_LENGTH];

    if (!IS_NPC(ch) && !check_class(ch, CLASS_MAGIC_USER) && !check_class(ch, CLASS_NECRO)
        && subcmd == SCMD_CAST) {
        send_to_char("�� ������ �� ��������� � �����.\r\n", ch);
        return;
    }

    if (!IS_NPC(ch) && !check_class(ch, CLASS_PRIEST) && subcmd == SCMD_PRAY) {
        send_to_char("�� �� ������ ��������.\r\n", ch);
        return;
    }


    if (AFF_FLAGGED(ch, AFF_SIELENCE)) {
        send_to_char("�� �� ������ ��������� � �����.\r\n", ch);
        return;
    }

    /* get: blank, spell name, target name */
    s = strtok(argument, ch->divd);
    if (s == NULL) {
        if (subcmd == SCMD_CAST)
            send_to_char("��� �� ������ ���������?\r\n", ch);
        else
            send_to_char("����� ������� �� ������ ����������?\r\n", ch);
        return;
    }


    s = strtok(NULL, ch->divd);

    if (s == NULL) {
        send_to_charf(ch, "�������� %s ������ ���� ��������� � �������: &C'%s'&n.\r\n",
                      subcmd == SCMD_CAST ? "����������" : "�������", ch->divd);
        return;
    }

    t = strtok(NULL, "\0");

    spellnum = find_spell_num(s);
    if (spellnum < 0) {
        if (subcmd == SCMD_CAST)
            send_to_char("�� �� ������ ������ ����������.\r\n", ch);
        else
            send_to_char("�� �� ������ ����� �������.\r\n", ch);

        return;
    }


    /* �������� ����� ���������� */
    skillz = TYPE_SPHERE_SKILL + SPELL_SPHERE(spellnum);

    /* Caster �� ����� ����� ���������� */
    if (!skillz) {
        sprintf(buf, "�� ������ ������� %s\r\n", sphere_name[SPELL_SPHERE(spellnum)]);
        send_to_char(buf, ch);
        return;
    }

    /* ��������� ������� ��� ���������� */

    if ((sphere_class[SPELL_SPHERE(spellnum)] == CLASS_MAGIC_USER ||
         sphere_class[SPELL_SPHERE(spellnum)] == CLASS_NECRO) && subcmd == SCMD_PRAY) {
        send_to_char("�� �� ������ ����� �������.\r\n", ch);
        return;
    } else if (sphere_class[SPELL_SPHERE(spellnum)] == CLASS_PRIEST && subcmd == SCMD_CAST) {
        send_to_char("�� �� ������ ������ ����������.\r\n", ch);
        return;
    }

    /* ��������� ������� ������� */
    if (!IS_SET(GET_SPELL_TYPE(ch, SPELL_NO(spellnum)), SPELL_TEMP | SPELL_KNOW) && !IS_GOD(ch)) {
        if (GET_SKILL(ch, skillz) < SPELL_LEVEL(spellnum)) {
            send_to_char("���� ��� ��� ��������� ������ �������!\r\n", ch);
            return;
        } else {
            if (subcmd == SCMD_CAST)
                send_to_char("�� �� ������ ������ ����������.\r\n", ch);
            else
                send_to_char("�� �� ������ ����� �������.\r\n", ch);
            return;
        }
    }

    if (t != NULL) {
        strcpy(arg, t);
        if (SPELL_NO(spellnum) != SPELL_ENDURE_ELEMENTS
            && SPELL_NO(spellnum) != SPELL_ENDURE_ELEMENTS_P
            && SPELL_NO(spellnum) != SPELL_IMUN_ELEMENTS && SPELL_NO(spellnum) != SPELL_EXPAND_SKILL
            && SPELL_NO(spellnum) != SPELL_IMPLANT_WEAPON)
            one_argument(arg, t);
        skip_spaces(&t);
    }

    target = find_cast_target(spellnum, t, ch, &tch, &tobj);

    asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);

    if (tch && check_spell_agro(spellnum, tch, spell_agro) && MOB_FLAGGED(tch, MOB_NOFIGHT)) {
        act("�������� �� $N3 ����������!", FALSE, ch, 0, tch, TO_CHAR);
        return;
    }

    if (target && (tch == ch) && check_spell_agro(spellnum, tch, spell_agro)) {
        send_to_char("������ ���������� ����� �� ����!\r\n", ch);
        return;
    }

    if (!target) {
        if (SPELL_NO(spellnum) != SPELL_ENDURE_ELEMENTS
            && SPELL_NO(spellnum) != SPELL_ENDURE_ELEMENTS_P)
            send_to_char("������ ����� ���� ������ ����������!\r\n", ch);
        return;
    }
// ����� � ��� �� ������� � ��� ���������� �����������!!!
    SET_CAST(ch, 0, NULL, NULL);

    if (AFF_FLAGGED(ch, AFF_SIELENCE)) {
        send_to_char("�� �� ������ ��������� � �����.\r\n", ch);
        return;
    }

    if (GET_SPELL_MEM(ch, SPELL_NO(spellnum)) && !IS_GOD(ch)) {
        sprintf(buf, "�� ��� �� ������������ ���� ���� ��� %s: '%s'.",
                subcmd == SCMD_CAST ? "����������" : "�������", SPELL_NAME(spellnum));
        act(buf, FALSE, ch, 0, 0, TO_CHAR);
        return;
    }

    if (IS_NPC(ch)) {
        do_mob_cast(ch, tch, spellnum);
        return;
    }

    if ((casting = cast_spell(ch, tch, tobj, spellnum)) > 0)
        if (tch && SPELL_VLAG(spellnum) > 0)
            WAIT_STATE(tch, PULSE_VIOLENCE * SPELL_VLAG(spellnum));

    int remem = MIN(MAX(1, GET_REMEMORY(ch)), 100) + 100;

    remem = remem + MAX(0, (GET_REAL_INT(ch) - 10) / 2);
    if (casting > 0 && ch && SPELL_MEMORY(spellnum) > 0)
        GET_SPELL_MEM(ch, SPELL_NO(spellnum)) = (SPELL_MEMORY(spellnum) * 100) / remem;

    if (casting > 0 && ch) {    // && SPELL_LAG(spellnum) > 0)
        if (!tch)
            tch = ch;
        train_magic(ch, spellnum, tch);
        /*    if (PRF_FLAGGED(ch,PRF_CODERINFO))
           send_to_charf(ch,"������������ ���������� ��� �� %d\r\n",SPELL_LAG(spellnum)); */
        WAIT_STATE(ch, PULSE_VIOLENCE);
        //WAIT_STATE(ch, PULSE_VIOLENCE * SPELL_LAG(spellnum));
    }

}

ACMD(do_mixture)
{
    send_to_charf(ch, "������ ������ ��� �� ���������.\r\n");
    return;
}

void learn_reciept(struct char_data *ch, struct obj_data *obj, int recieptnum)
{
    char buf[MAX_STRING_LENGTH];
    int addchance = 0;

    if (ENCHANT_LEVEL(recieptnum) > GET_SKILL(ch, SKILL_ENCHANT)) {
        act("����������� ������ $o, �� �� ������ ��������� �� ����� �������.", FALSE, ch, obj, 0,
            TO_CHAR);
        act("$n �������� � ����� $o3 ������� ���-�� ���������.", FALSE, ch, obj, 0, TO_ROOM);
        return;
    }

    if (GET_SPELL_TYPE(ch, ENCHANT_NO(recieptnum)) & SPELL_KNOW) {
        sprintf(buf, "����������� ������ ������� �� $o5, �� ������ ��� ������ '%s'.",
                ENCHANT_NAME(recieptnum));
        act(buf, FALSE, ch, obj, 0, TO_CHAR);
        act("����������� ������ $o3, $n �������$u ����� ������.", FALSE, ch, obj, 0, TO_ROOM);
        return;
    }

    if (GET_POS(ch) == POS_SITTING)
        addchance += 10;

    if (ENCHANT_LEVEL(recieptnum) <= 10)
        addchance += 10;
    else if (ENCHANT_LEVEL(recieptnum) <= 40)
        addchance += 0;
    else if (ENCHANT_LEVEL(recieptnum) <= 40)
        addchance -= 1;
    else if (ENCHANT_LEVEL(recieptnum) <= 50)
        addchance -= 3;
    else if (ENCHANT_LEVEL(recieptnum) <= 60)
        addchance -= 5;
    else if (ENCHANT_LEVEL(recieptnum) <= 70)
        addchance -= 7;
    else if (ENCHANT_LEVEL(recieptnum) <= 80)
        addchance -= 9;
    else
        addchance -= 10;

    if (((GET_REAL_INT(ch) * 3) + addchance) >= number(1, 100)) {
        sprintf(buf, "����������� �������� ������� �� $o5, �� ������ ������ ������� '%s'.",
                ENCHANT_NAME(recieptnum));
        act(buf, FALSE, ch, obj, 0, TO_CHAR);
        act("����������� ������ ������� �� $o5, $n �������� �������$u.", FALSE, ch, obj, 0,
            TO_ROOM);

        GET_ENCHANT_TYPE(ch, ENCHANT_NO(recieptnum)) |= SPELL_KNOW;
        obj_from_char(obj);
        extract_obj(obj);
    } else {
        sprintf(buf, "����������� ������ ������� �� $o5, �� �� ������ ��������� �����.");
        act(buf, FALSE, ch, obj, 0, TO_CHAR);
        act("����������� ������ ������� �� $o5, $n ������������� ��������$g.", FALSE, ch, obj, 0,
            TO_ROOM);
        obj_from_char(obj);
        extract_obj(obj);
    }
}

ACMD(do_learn)
{
    int spellnum = -1, i, spell_no, addchance = 0, sphere = -1, recieptnum = -1;
    bool isMag = FALSE;
    struct obj_data *obj;
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_STRING_LENGTH];

    *buf = '\0';
    *arg = '\0';


    if (IS_NPC(ch))
        return;

    one_argument(argument, arg);

    if (!*arg) {
        send_to_char("�� ��������� ����������� ������� ����� ��� ������.\r\n", ch);
        act("$n ��������$g ������ � �������$u �� �����.", FALSE, ch, 0, 0, TO_ROOM);
        return;
    }

    if (!(obj = get_obj_in_list_vis(ch, arg, ch->carrying))) {
        send_to_charf(ch, "� ��� ��� '%s'.\r\n", arg);
        return;
    }

    if (GET_OBJ_TYPE(obj) != ITEM_BOOK) {
        act("�� ����������� ������� $o3.", FALSE, ch, obj, 0, TO_CHAR);
        act("$n �����$g ����������� ������� ���������� $o1.", FALSE, ch, obj, 0, TO_ROOM);
        return;
    }

    if (obj->obj_flags.reciept)
        recieptnum = find_enchant_num(obj->obj_flags.reciept);
    else {
        if (GET_OBJ_VAL(obj, 1) == 0 && GET_OBJ_VAL(obj, 2) == 0 && GET_OBJ_VAL(obj, 3) == 0) {
            act("����������� ������ @1�, �� �� ����� ��� ���� ���-���� ����������.", "��", ch, obj);
            act("1� ��������1(,�,�,�) � ����� @1�, ������������������� �������1(,�,�,�).", "���",
                ch, obj);
            return;
        }
        do
            i = number(1, 3);
        while (GET_OBJ_VAL(obj, i) < 1 || GET_OBJ_VAL(obj, i) > MAX_SPELLS);
        spellnum = find_spell_num(GET_OBJ_VAL(obj, i));
    }

    if (spellnum < 0 && recieptnum < 0) {
        send_to_charf(ch, "����������� ����������/�������/������. �������� �����.\r\n");
        sprintf(buf, "������������ ����������-������ #%d � ����� #%d.",
                GET_OBJ_VAL(obj, 1), GET_OBJ_VNUM(obj));
        mudlog(buf, CMP, LVL_GOD, TRUE);
        return;
    }

    if (recieptnum > -1) {
        learn_reciept(ch, obj, recieptnum);
        return;
    }

    spell_no = SPELL_NO(spellnum);
    sphere = SPELL_SPHERE(spellnum) + TYPE_SPHERE_SKILL;

    if (sphere >= SKILL_SP_KINDNESS)
        isMag = FALSE;
    else
        isMag = TRUE;

//������ �� ����� ����� ����������
    if (SPELL_LEVEL(spellnum) > GET_SKILL(ch, sphere)) {
        act("����������� ������ $o, �� �� ������ ��������� �� ����� �������.", FALSE, ch, obj, 0,
            TO_CHAR);
        act("$n �������� � ����� $o3 ������� ���-�� ���������.", FALSE, ch, obj, 0, TO_ROOM);
        return;
    }

    if (GET_SPELL_TYPE(ch, spell_no) & SPELL_KNOW) {
        sprintf(buf, "����������� ������ ������� �� $o5, �� ������ ��� %s '%s'.",
                isMag ? "����������" : "�������", SPELL_NAME(spellnum));
        act(buf, FALSE, ch, obj, 0, TO_CHAR);
        act("����������� ������ $o3, $n �������$u ����� ������.", FALSE, ch, obj, 0, TO_ROOM);
        return;
    }

    if (GET_POS(ch) == POS_SITTING)
        addchance += 10;

    if (SPELL_LEVEL(spellnum) <= 10)
        addchance += 10;
    else if (SPELL_LEVEL(spellnum) <= 40)
        addchance += 0;
    else if (SPELL_LEVEL(spellnum) <= 40)
        addchance -= 1;
    else if (SPELL_LEVEL(spellnum) <= 50)
        addchance -= 3;
    else if (SPELL_LEVEL(spellnum) <= 60)
        addchance -= 5;
    else if (SPELL_LEVEL(spellnum) <= 70)
        addchance -= 7;
    else if (SPELL_LEVEL(spellnum) <= 80)
        addchance -= 9;
    else
        addchance -= 10;

    addchance += ((IS_MAGIC_USER(ch) || IS_NECRO(ch))
                  && ROOM_FLAGGED(IN_ROOM(ch), ROOM_MAGIC_USER)) ? 50 : 0;
    addchance += (IS_PRIEST(ch) && ROOM_FLAGGED(IN_ROOM(ch), ROOM_PRIEST)) ? 50 : 0;

    if (((GET_REAL_INT(ch) * 3) + addchance) >= number(1, 100)) {
        if (isMag) {
            sprintf(buf, "����������� �������� ������� �� $o5, �� ������ ������� ���������� '%s'.",
                    SPELL_NAME(spellnum));
            act(buf, FALSE, ch, obj, 0, TO_CHAR);
            act("����������� ������ ������� �� $o5, $n �������� �������$u.", FALSE, ch, obj, 0,
                TO_ROOM);
        } else {
            sprintf(buf, "����������� �������� ������� �� $o5, �� ������ ����� ������� '%s'.",
                    SPELL_NAME(spellnum));
            act(buf, FALSE, ch, obj, 0, TO_CHAR);
            act("����������� ������ ������� �� $o5, $n �������� �������$u.", FALSE, ch, obj, 0,
                TO_ROOM);
        }

        GET_SPELL_TYPE(ch, spell_no) |= SPELL_KNOW;
        obj_from_char(obj);
        extract_obj(obj);
    } else {
        if (isMag) {
            sprintf(buf,
                    "����������� ������ ������� �� $o5, �� �� ������ ��������� ����� ����������.");
            act(buf, FALSE, ch, obj, 0, TO_CHAR);
            act("����������� ������ ������� �� $o5, $n ������������� ��������$g.", FALSE, ch, obj,
                0, TO_ROOM);
        } else {
            sprintf(buf, "����������� ������ ������� �� $o5, �� �� ������ ��������� �����.");
            act(buf, FALSE, ch, obj, 0, TO_CHAR);
            act("����������� ������ ������� �� $o5, $n ������������� ��������$g.", FALSE, ch, obj,
                0, TO_ROOM);
        }
        obj_from_char(obj);
        extract_obj(obj);
    }

}

ACMD(do_forget)
{
    char *s;
    int spellnum;

    s = strtok(argument, "'*!");
    if (s == NULL) {
        send_to_char("����� ���������� �� ������ ������?\r\n", ch);
        return;
    }
    s = strtok(NULL, "'*!");
    if (s == NULL) {
        send_to_char("�������� ���������� ������ ���� ��������� � ���������� �������: '*!\r\n", ch);
        return;
    }

    spellnum = find_spell_num(s);

    if (spellnum < 0 || !IS_SET(GET_SPELL_TYPE(ch, SPELL_NO(spellnum)), SPELL_KNOW | SPELL_TEMP)) {
        send_to_char("� �� � �� ����� ������ ����������.\r\n", ch);
        return;
    }

    REMOVE_BIT(GET_SPELL_TYPE(ch, SPELL_NO(spellnum)), SPELL_KNOW);
    REMOVE_BIT(GET_SPELL_TYPE(ch, SPELL_NO(spellnum)), SPELL_TEMP);
    send_to_charf(ch, "�� ���������� ���������� '%s' �� ����� ������.\r\n", SPELL_NAME(spellnum));

}


/* Assign the spells on boot up */
void skillo(int spl, const char *name, int max_percent, int skill_type)
{
    int i, j;

    for (i = 0; i < NUM_CLASSES; i++)
        for (j = 0; j < NUM_GODS; j++) {
            skill_info[spl].k_improove[i][j] = 0;
            skill_info[spl].learn_level[i][j] = 0;
        }
    skill_info[spl].min_position = 0;
    skill_info[spl].name = name;
    skill_info[spl].max_percent = max_percent;
    skill_info[spl].skill_type = skill_type;
}

void unused_skill(int spl)
{
    int i, j;

    for (i = 0; i < NUM_CLASSES; i++)
        for (j = 0; j < NUM_GODS; j++) {
            skill_info[spl].k_improove[i][j] = 1;
            skill_info[spl].learn_level[i][j] = 0;
            skill_info[spl].ability[i][j] = 0;
        }

    skill_info[spl].min_position = 0;
    skill_info[spl].max_percent = 200;
    skill_info[spl].name = unused_spellname;
    skill_info[spl].skill_type = 0;

}


void assign_skills(void)
{
    int i;

    for (i = 0; i <= TOP_SKILL_DEFINE; i++)
        unused_skill(i);
    skillo(SKILL_THAC0, "!�����", 150, 0);
    skillo(SKILL_SWITCH, "����������� ��������", 150, SKILL_TWARRIOR);
    skillo(SKILL_HOLYLIGHT, "�������", 150, SKILL_TRACE);
    skillo(SKILL_BACKSTAB, "��������", 150, SKILL_TTHIEF);
    skillo(SKILL_BASH, "�����", 150, SKILL_TWARRIOR);
    skillo(SKILL_HIDE, "���������", 150, SKILL_TTHIEF);
    skillo(SKILL_KICK, "�����", 150, SKILL_TWARRIOR);
    skillo(SKILL_PICK_LOCK, "��������", 150, SKILL_TTHIEF);
    skillo(SKILL_PUNCH, "����������", 150, SKILL_TWEAPON);
    skillo(SKILL_RESCUE, "������", 150, SKILL_TWARRIOR);
    skillo(SKILL_GUARD, "��������", 150, SKILL_TWARRIOR);
    skillo(SKILL_SNEAK, "��������", 150, SKILL_TTHIEF);
    skillo(SKILL_STEAL, "�������", 150, SKILL_TTHIEF);
    skillo(SKILL_TRACK, "���������", 150, SKILL_TRANGER);
    skillo(SKILL_TRACKON, "��������", 150, SKILL_TRANGER);
    skillo(SKILL_ORENT, "��������������", 150, SKILL_TRANGER);
    skillo(SKILL_PARRY, "����������", 150, SKILL_TWARRIOR);
    skillo(SKILL_BLOCK, "����������� �����", 150, SKILL_TWARRIOR);
    skillo(SKILL_TOUCH, "��������", 150, SKILL_TTHIEF);
    skillo(SKILL_SATTACK, "�������������� �����", 150, SKILL_TRACE);
    skillo(SKILL_DISARM, "�����������", 150, SKILL_TWARRIOR);
    skillo(SKILL_HEAL, "!heal!", 150, SKILL_TOTHER);
    skillo(SKILL_TURN, "!turn!", 150, SKILL_TOTHER);
    skillo(SKILL_ADDSHOT, "�������������� �������", 150, SKILL_TRANGER);
    skillo(SKILL_CAMOUFLAGE, "����������", 150, SKILL_TRANGER);
    skillo(SKILL_DEVIATE, "����������", 150, SKILL_TTHIEF);
    skillo(SKILL_CHARM, "���������", 150, SKILL_TRANGER);
    skillo(SKILL_CHOPOFF, "�������", 150, SKILL_TTHIEF);
    skillo(SKILL_COURAGE, "������", 150, SKILL_TRACE);
    skillo(SKILL_IDENTIFY, "���������", 150, SKILL_TOTHER);
    skillo(SKILL_LOOK_HIDE, "������������", 150, SKILL_TTHIEF);
    skillo(SKILL_CRITIC, "������ ����", 150, SKILL_TWARRIOR);
    skillo(SKILL_LOOKING, "�����������", 150, SKILL_TTHIEF);
    skillo(SKILL_PRAY, "���������", 150, SKILL_TOTHER);
    skillo(SKILL_CONCENTRATE, "������������", 150, SKILL_TOTHER);
    skillo(SKILL_ENCHANT, "�����������", 150, SKILL_TOTHER);
    skillo(SKILL_LEARN, "��������", 150, SKILL_TRANGER);
    skillo(SKILL_RUNUP, "�����������", 150, SKILL_TWARRIOR);
    skillo(SKILL_AID, "���������� ����", 150, SKILL_TRANGER);
    skillo(SKILL_FIRE, "������� ������", 150, SKILL_TRANGER);
    skillo(SKILL_SHIT, "���� ����� �����", 150, SKILL_TWEAPON);
    skillo(SKILL_MIGHTHIT, "���� ����", 150, SKILL_TWARRIOR);
    skillo(SKILL_SHIELDHIT, "���� �����", 150, SKILL_TWARRIOR);
    skillo(SKILL_CIRCLESTAB, "������ �����", 150, SKILL_TTHIEF);
    skillo(SKILL_BLOODLET, "�������������", 150, SKILL_TRANGER);
    skillo(SKILL_STUPOR, "��������", 150, SKILL_TWARRIOR);
    skillo(SKILL_POISONED, "��������", 150, SKILL_TTHIEF);
    skillo(SKILL_LEADERSHIP, "���������", 150, SKILL_TOTHER);
    skillo(SKILL_HORSE, "�������� ������", 150, SKILL_TOTHER);
    skillo(SKILL_HIDETRACK, "������� �����", 150, SKILL_TTHIEF);
    skillo(SKILL_COUNTERACT, "���������������", 150, SKILL_TTHIEF);
    skillo(SKILL_MAKEFOOD, "���������", 150, SKILL_TRANGER);
    skillo(SKILL_MULTYPARRY, "�������� ������", 150, SKILL_TWARRIOR);
    skillo(SKILL_SAPPER, "����������� �������", 150, SKILL_TTHIEF);
    skillo(SKILL_MAKETRAP, "���������� ������", 150, SKILL_TRANGER);
    skillo(SKILL_THROW, "�������", 150, SKILL_TTHIEF);
    skillo(SKILL_DIRFLEE, "�������������", 150, SKILL_TTHIEF);
    skillo(SKILL_CRASHDOOR, "��������", 150, SKILL_TWARRIOR);
    skillo(SKILL_FIND, "������ ���������", 150, SKILL_TTHIEF);
    skillo(SKILL_BALSAM, "���������������", 150, SKILL_TMAGIC);
    skillo(SKILL_RDANCE, "��������� �����", 150, SKILL_TRANGER);
    skillo(SKILL_SNAPSHOT, "������ �������", 150, SKILL_TRANGER);

// �����
    skillo(SKILL_LANG_COMMON, "���� ��������", 100, SKILL_TLANG);
    skillo(SKILL_LANG_HUMAN, "���� �����", 100, SKILL_TLANG);
    skillo(SKILL_LANG_ORC, "���� �����", 100, SKILL_TLANG);
    skillo(SKILL_LANG_DWARN, "���� ������", 100, SKILL_TLANG);
    skillo(SKILL_LANG_ELF, "���� ������", 100, SKILL_TLANG);
    skillo(SKILL_LANG_BARIAUR, "���� ���������", 100, SKILL_TLANG);
    skillo(SKILL_LANG_AASIMAR, "���� ���������", 100, SKILL_TLANG);
    skillo(SKILL_LANG_TIEFLING, "���� ���������", 100, SKILL_TLANG);

    //��������� ������
    skillo(SKILL_STAFFS, "������", 300, SKILL_TWEAPON);
    skillo(SKILL_AXES, "������", 300, SKILL_TWEAPON);
    skillo(SKILL_SWORDS, "����", 300, SKILL_TWEAPON);
    skillo(SKILL_DAGGERS, "�������", 300, SKILL_TWEAPON);
    skillo(SKILL_MACES, "������", 300, SKILL_TWEAPON);
    skillo(SKILL_FLAILS, "�������", 300, SKILL_TWEAPON);
    skillo(SKILL_WHIPS, "�����", 300, SKILL_TWEAPON);
    skillo(SKILL_SPAEKS, "�����", 300, SKILL_TWEAPON);
    skillo(SKILL_BOWS, "����", 300, SKILL_TWEAPON);
    skillo(SKILL_CROSSBOWS, "��������", 300, SKILL_TWEAPON);
    skillo(SKILL_BOTHHANDS, "���������", 300, SKILL_TWEAPON);
    skillo(SKILL_SHOOT, "������������� ������", 300, SKILL_TWEAPON);

// ���������� ������
    skillo(SKILL_SP_ENCHANTMENT, "����� �����������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_DIVINITION, "����� ����������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_NECROMANCE, "����� �����������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_ALTERATION, "����� �����������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_INVOCATION, "����� ����������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_CONJURATION, "����� ���������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_ILLUSION, "����� �������", 300, SKILL_TMAGIC);
    skillo(SKILL_SP_ABJURATION, "����� ���������", 300, SKILL_TMAGIC);
//��������� ������
    skillo(SKILL_SP_KINDNESS, "����� �����", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_HEALING, "����� ���������", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_LIGHT, "����� �����", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_WAR, "����� �����", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_PROTECTION, "����� ������", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_NATURE, "����� �������", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_SUCCESS, "����� �����", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_TRAVEL, "����� �����������", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_FORCE, "����� ����", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_MAGIC, "����� �����", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_EVIL, "����� ���", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_DEATH, "����� ������", 300, SKILL_TPRIEST);
    skillo(SKILL_SP_DESTRUCTION, "����� ����������", 300, SKILL_TPRIEST);
}

#define SPELLHAUNT_MOB 104

void check_spellhaunt(struct char_data *ch, int mana)
{
    int room = IN_ROOM(ch);
    struct char_data *tmp_mob = NULL;

    GET_SPELLHAUNT(room) += mana;

    if (GET_SPELLHAUNT(room) >= 1000) {
        if (!(tmp_mob = read_mobile(SPELLHAUNT_MOB, VIRTUAL)))
            return;

        act("������ $n1 ������������ ������ ������ ����.", FALSE, ch, 0, tmp_mob, TO_ROOM);
        act("������ ��� ������������ ������ ������ ����.", FALSE, ch, 0, tmp_mob, TO_CHAR);
        char_to_room(tmp_mob, room);
        GET_SPELLHAUNT(room) = 0;
        _damage(tmp_mob, ch, WEAP_RIGHT, 0, TRUE, C_POWER);
    }

}
