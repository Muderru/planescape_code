
#include "sysdep.h"
#include "ai.h"
#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "handler.h"
#include "db.h"
#include "screen.h"
#include "spells.h"
#include "xspells.h"
#include "xboot.h"
#include "constants.h"


/* external functions */
ACMD(do_use);
ACMD(do_addshot);

/* local functions */
void priest_cast_peace(struct char_data *ch);
int priest_cast_fight(struct char_data *ch);

void mob_casting_peace(struct char_data *ch)
{
    if (!IS_NPC(ch))
        return;
    if (AFF_FLAGGED(ch, AFF_CHARM))
        return;

    if (check_class(ch, CLASS_PRIEST))
        priest_cast_peace(ch);
}

int mob_casting_fight(struct char_data *ch)
{
    if (!IS_NPC(ch))
        return (FALSE);
    if (AFF_FLAGGED(ch, AFF_CHARM))
        return (FALSE);

    if (check_class(ch, CLASS_PRIEST))
        return (priest_cast_fight(ch));

    return (FALSE);
}

struct char_data *find_best_cast_target(struct char_data *ch)
{
    struct char_data *attacker = FIGHTING(ch), *victim = NULL, *tch;
    int max_hp = GET_HIT(attacker);


    for (tch = world[IN_ROOM(ch)].people; tch; tch = tch->next_in_room)
        if (same_group(attacker, tch) && get_missed(ch, tch) < 3 && GET_HIT(tch) < max_hp) {
            victim = tch;
            max_hp = GET_HIT(tch);
        }

    if (victim)
        return victim;
    return attacker;

}

/****************************************************************************/

void priest_cast_peace(struct char_data *ch)
{
    int i, spellnum, spell_no;
    struct char_data *victim = NULL;

//�������
    if ((victim = need_heal(ch)) != NULL)
        for (i = 0; spells_health[i] != -1; i++) {
            spell_no = spells_health[i];
            spellnum = find_spell_num(spell_no);
            if (check_spell_mob(ch, spellnum)) {
                do_mob_cast(ch, victim, spellnum);
                return;
            }
        }

    victim = NULL;

//�������� ������
//�������� ��������� ���� � ���� ���-�� ����
    if (!check_in_zone(ch))
        return;

    for (i = 0; spells_defence[i] != -1; i++) {
        spell_no = spells_defence[i];
        spellnum = find_spell_num(spell_no);
        if ((victim = need_fa(ch, spell_no)) != NULL)
            if (check_spell_mob(victim, spellnum) && !affected_by_spell_real(victim, spellnum)
                && number(0, 2) == TRUE) {
                do_mob_cast(ch, victim, spellnum);
                return;
            }
    }

    victim = NULL;

//�������� �������
//�������� ��������� ���� � ���� ���-�� ����
//if (check_in_zone(ch))
    for (i = 0; spells_helped[i] != -1; i++) {
        spell_no = spells_helped[i];
        spellnum = find_spell_num(spell_no);

        if (spell_no == SPELL_DESECRATE
            && affected_room_by_bitvector(&world[IN_ROOM(ch)], ROOM_AFF_DESECRATE))
            continue;

        if ((victim = need_fa(ch, spell_no)) != NULL)
            if (check_spell_mob(ch, spellnum) && !affected_by_spell_real(victim, spellnum)
                && number(0, 2) == TRUE) {
                do_mob_cast(ch, victim, spellnum);
                return;
            }
    }

}

/****************************************************************************/

int priest_cast_fight(struct char_data *ch)
{
    struct char_data *victim;
    int i, spellnum, spell_no;

//�������
    if ((victim = need_heal_battle(ch)) != NULL)
        for (i = 0; spells_health[i] != -1; i++) {
            spell_no = spells_health[i];
            spellnum = find_spell_num(spell_no);
            if (check_spell_mob(ch, spellnum)) {
                do_mob_cast(ch, victim, spellnum);
                return (TRUE);
            }
        }


    if ((victim = find_best_cast_target(ch))) {
        //act("T1",FALSE,ch,0,0,TO_ROOM);
        //������� �������
        for (i = 0; spells_harmed[i] != -1; i++) {
            spell_no = spells_harmed[i];
            spellnum = find_spell_num(spell_no);
            if (spell_no == SPELL_POWER_WORD_BLIND && affected_by_spell(victim, SPELL_BLIND))
                continue;
            if (spell_no == SPELL_POWER_WORD_STUNE && affected_by_spell(victim, SPELL_STUNE))
                continue;
            if (check_spell_mob(ch, spellnum) && !affected_by_spell(victim, spell_no)
                && number(0, 2) == TRUE) {
                do_mob_cast(ch, victim, spellnum);
                return (TRUE);
            }
        }

        //act("T2",FALSE,ch,0,0,TO_ROOM);
        //�����������
        for (i = 0; spells_damages[i] != -1; i++) {
            spell_no = spells_damages[i];
            spellnum = find_spell_num(spell_no);
            //������� ������������ ������
            if (spell_no == SPELL_HOLY_WORD && IS_GOODS(victim))
                continue;
            if (spell_no == SPELL_HOLY_SMITE && IS_GOODS(victim))
                continue;
            if ((spell_no == SPELL_FLAME_STRIKE_WAR || spell_no == SPELL_FLAME_STRIKE)
                && !OUTSIDE(ch))
                continue;
            if (check_spell_mob(ch, spellnum) && !affected_by_spell(victim, spell_no)
                && number(0, 2) == TRUE) {
                do_mob_cast(ch, victim, spellnum);
                return (TRUE);
            }
        }
        //act("T3",FALSE,ch,0,0,TO_ROOM);
    }
//�������� ������
    for (i = 0; spells_defence_war[i] != -1; i++) {
        spell_no = spells_defence_war[i];
        spellnum = find_spell_num(spell_no);
        if ((victim = need_fa(ch, spell_no)) != NULL)
            if (check_spell_mob(victim, spellnum) && !affected_by_spell(victim, spell_no)
                && number(0, 2) == TRUE) {
                do_mob_cast(ch, victim, spellnum);
                return (TRUE);
            }
    }

    return (FALSE);
}

/* ����� �� ���� ��������� */
bool check_in_zone(struct char_data * ch)
{
    struct char_data *zch = NULL;
    int in_zone = -1;

    if (IN_ROOM(ch) == NOWHERE)
        return (FALSE);

    in_zone = world[IN_ROOM(ch)].zone;

    for (zch = character_list; zch; zch = zch->next)
        if (!IS_NPC(zch) && IN_ROOM(zch) != NOWHERE && world[IN_ROOM(zch)].zone == in_zone)
            return (TRUE);

    return (FALSE);
}

/* ����� �� ��������� */
struct char_data *need_fa(struct char_data *ch, int spell_no)
{
    struct char_data *tch = NULL;

    if (IN_ROOM(ch) == NOWHERE)
        return (NULL);

    for (tch = world[IN_ROOM(ch)].people; tch; tch = tch->next_in_room) {
        if ((ch == tch || same_group(ch, tch)) && !affected_by_spell(ch, spell_no))
            return (tch);
    }

    return (NULL);
}


/* ����� �� ���� ������ */
struct char_data *need_heal(struct char_data *ch)
{
    struct char_data *tch = NULL;

    for (tch = world[IN_ROOM(ch)].people; tch; tch = tch->next_in_room)
        if ((same_group(ch, tch) || (SAME_ALIGN(ch, tch) && FIGHTING(ch) == FIGHTING(tch))
            ) &&
            (IS_NPC(tch) && !AFF_FLAGGED(tch, AFF_CHARM) && CAN_SEE(ch, tch) &&
             GET_HIT(tch) < (GET_REAL_MAX_HIT(tch) * 7) / 8)
            )
            return (tch);

    if (!tch && GET_HIT(ch) <= (GET_REAL_MAX_HIT(ch) * 7) / 8)
        return (ch);

    return (tch);
}

/* ������� �����, ���� ���� ������ �� ���� ���� ��� */
struct char_data *need_heal_battle(struct char_data *ch)
{
    struct char_data *tch = NULL, *victim = NULL;

    for (tch = world[IN_ROOM(ch)].people; tch; tch = tch->next_in_room)
        if (same_group(ch, tch) && GET_HIT(tch) <= GET_REAL_MAX_HIT(tch) / 2) {
            if (FIGHTING(tch) && tch == FIGHTING(FIGHTING(tch)) && CAN_SEE(ch, tch))    //��� ����
                victim = tch;
            else if (GET_POS(tch) < POS_SLEEPING)       //�������
                victim = tch;
            else if (!victim)   //����
                victim = ch;
        }

    return (victim);
}


int cast_item(struct char_data *ch, struct obj_data *obj)
{
    int spellnum, spell_no, spell_agro;
    char tname[MAX_INPUT_LENGTH];
    struct char_data *victim = NULL;

    *tname = '\0';
    switch (GET_OBJ_TYPE(obj)) {
        case ITEM_WAND:
        case ITEM_STAFF:
            spell_no = GET_OBJ_VAL(obj, 3);
            break;
        case ITEM_SCROLL:
            if (AFF_FLAGGED(ch, AFF_BLIND))
                return (FALSE);
            spell_no = GET_OBJ_VAL(obj, 1);
            break;
        case ITEM_POTION:
            spell_no = GET_OBJ_VAL(obj, 1);
            break;
        default:
            return (FALSE);
            break;
    }

    spellnum = find_spell_num(spell_no);

    if (spellnum < 0)
        return (FALSE);
    spell_agro = 0;
    asciiflag_conv((char *) SPELL_AGRO(spellnum), &spell_agro);
    if (IS_SET(spell_agro, AGRO_ALL) || IS_SET(spell_agro, AGRO_EVIL) || IS_SET(spell_agro, AGRO_GOOD) || IS_SET(spell_agro, AGRO_NEUTRAL) || spell_no == SPELL_RECALL) {       //�� �����
        if (FIGHTING(ch)) {
            victim = FIGHTING(ch);
            if (victim)
                sprintf(tname, "%s", GET_NAME(victim));
        }
    } else {                    //�� ����
        victim = ch;
        sprintf(tname, "�");
    }

    if (victim && !affected_by_spell_real(victim, spellnum)) {
        //� ����� ��� ������� �����, � �� �������
        if ((spell_no == SPELL_HEAL || spell_no == SPELL_CURE || spell_no == SPELL_CURE_CRITICAL) &&
            GET_HIT(victim) > GET_REAL_MAX_HIT(victim) / 2)
            return (FALSE);

        mag_objectmagic(ch, obj, tname);
        return (TRUE);
    }

    return (FALSE);
}


int mob_use(struct char_data *ch)
{
    struct obj_data *obj;

    for (obj = ch->carrying; obj; obj = obj->next_content)
        switch GET_OBJ_TYPE
            (obj) {
            case ITEM_WAND:
            case ITEM_STAFF:
                if (GET_OBJ_VAL(obj, 2) <= 0)
                    continue;
                if (cast_item(ch, obj))
                    return (TRUE);
                break;
            case ITEM_POTION:
            case ITEM_SCROLL:
                if (cast_item(ch, obj))
                    return (TRUE);
                break;
            }

    return (FALSE);
}



void mob_fight(struct char_data *ch)
{
    bool use = FALSE;

//�� ������ ���������
    if (GET_POS(ch) < POS_FIGHTING)
        return;

    if (AFF_FLAGGED(ch, AFF_CHARM))
        return;

//����
    if (GET_MOB_HOLD(ch) || AFF_FLAGGED(ch, AFF_STOPFIGHT) || AFF_FLAGGED(ch, AFF_STUNE)
        || GET_WAIT(ch) > 0)
        return;


    /* �������� ���:

       1. ������ ����-����.

       2. ���� ���������� �������� � ��������� (���� ����.������ ������ 40% �� ������� ��� ����)

       2�.���� ���� ������, �� �������� �� �������, �����, �������� (���� �� �������), ������� ������ ���� � �.�.
       2�.���� �������� ���, �� ��������� ����������� ����, ����� � ��. ����������� ������ ���� ���� 70%
       2�.����� �������� ��� ���������, ���� ���� ���, �� �������� �������, ����� � �.�.

     */

    /* ����������� */
    if (GET_HIT(ch) < GET_REAL_MAX_HIT(ch) / 3 && GET_SKILL_MOB(ch, SKILL_DIRFLEE)) {
        int i, attempt;

        for (i = 0; i < 18; i++) {
            attempt = number(0, NUM_OF_DIRS - 1);       /* Select a random direction */
            if (CAN_GO(ch, attempt) && !ROOM_FLAGGED(EXIT(ch, attempt)->to_room, ROOM_DEATH)) {
                if (SECT(EXIT(ch, attempt)->to_room) == SECT_FLYING && GET_POS(ch) != POS_FLYING)
                    continue;
                go_dir_flee(ch, attempt);
                return;
            }
        }
    }

    /* ������� */
    if ((GET_SKILL_MOB(ch, SKILL_RESCUE) || MOB_FLAGGED(ch, MOB_ANGEL))
        && GET_POS(ch) > POS_SITTING) {
        struct char_data *caster = NULL;
        struct char_data *damager = NULL;
        struct char_data *vict = NULL;

        for (vict = world[ch->in_room].people; vict; vict = vict->next_in_room) {
            if (!FIGHTING(vict) || (IS_NPC(vict) && !AFF_FLAGGED(vict, AFF_CHARM)))
                continue;

            if ((vict != ch && FIGHTING(vict) != ch
                 && check_distance(vict, FIGHTING(vict)) == DIST_0) && (GET_HIT(vict) <= GET_HIT(ch)
                                                                        || IS_PRIEST(vict)
                                                                        || IS_MAGIC_USER(vict))
                && same_group(ch, vict)) {
                caster = vict;
                damager = FIGHTING(vict);
            }
        }

        if (caster && damager)
            go_rescue(ch, caster, damager);
    }

    use = mob_casting_fight(ch);

    if (use || !FIGHTING(ch) || IN_ROOM(ch) != IN_ROOM(FIGHTING(ch)))
        return;

    use = mob_use(ch);

    if (use || !FIGHTING(ch) || IN_ROOM(ch) != IN_ROOM(FIGHTING(ch)))
        return;

    /* ���� ���-�� �������� � ������ caster=����� ������������� ������, victim=����� ������������� ���� */

    struct char_data *caster = NULL;
    struct char_data *damager = NULL;
    struct char_data *vict = NULL;
    struct char_data *attacker = FIGHTING(ch);
    int count_caster = 0, min_level = 0, min_hp = GET_REAL_MAX_HIT(attacker), max_level =
        (GET_LEVEL(attacker) * 7) / 10;
    int count_damager = 0;

    for (vict = world[ch->in_room].people; vict; vict = vict->next_in_room) {
        if (same_group(attacker, vict) || vict == attacker || FIGHTING(attacker) == ch) {
            int rlevel = GET_LEVEL(vict);
            int cst_level = check_class(vict, CLASS_PRIEST) + check_class(vict, CLASS_NECRO);
            int koef = (int) (((float) cst_level / (float) rlevel) * 100.0);

            if (koef > 70) {
                count_caster++; //������
                if (!caster)
                    caster = vict;
                if (GET_LEVEL(vict) > min_level) {
                    caster = vict;
                    min_level = GET_LEVEL(vict);
                }
                //�� ���� � ��� ������ �������� ����� ������ ������
            } else {
                count_damager++;        //����
                if (!damager)
                    damager = vict;
                if (GET_LEVEL(vict) <= max_level && GET_REAL_MAX_HIT(vict) < min_hp) {
                    damager = vict;
                    min_hp = GET_REAL_MAX_HIT(vict);
                }
                //��� � ��� ����� ����� ���� � ������� �� ������
            }
        }
    }

    if (!caster && !damager) {
        act("&M����������� ������. 1� ��� ������! �������� ����������!", "��", ch);
        return;                 //�������� ������ �� ������ ����� �� �����
    }

    struct char_data *victim;
    bool fnn = FALSE;

//C ������ � 25% �������� ��������� ������
    for (vict = world[ch->in_room].people; vict; vict = vict->next_in_room)
        if ((same_group(attacker, vict) || vict == attacker || FIGHTING(attacker) == ch)
            && number(1, 4) == 1) {
            victim = vict;
            break;
            fnn = TRUE;
        }


    if (!fnn) {
        if (caster)
            victim = caster;
        else
            victim = damager;
    }

    int dist = check_distance(ch, victim);

    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_SWITCH)) {
        clear_battle_affect(ch);
        mob_switch(ch);
        return;
    }

//����� ������������ ������� ����
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_TOUCH)) {
        clear_battle_affect(ch);
        go_touch(ch, victim);
        return;
    }
//�������� �������
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_BASH)
        && GET_REAL_SIZE(victim) < (GET_REAL_SIZE(ch) * 2) && GET_POS(victim) > POS_SITTING) {
        clear_battle_affect(ch);
        go_bash(ch, victim);
        return;
    }

    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_MIGHTHIT) && !timed_by_skill(ch, SKILL_MIGHTHIT)) {
        clear_battle_affect(ch);
        go_mighthit(ch, victim);
        return;
    }
//������
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_KICK)) {
        clear_battle_affect(ch);
        go_kick(ch, victim);
        return;
    }
//���� ����
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_MIGHTHIT) && !timed_by_skill(ch, SKILL_MIGHTHIT)) {
        clear_battle_affect(ch);
        go_mighthit(ch, victim);
        return;
    }
//����������� ����
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_CRITIC) && !timed_by_skill(ch, SKILL_CRITIC)) {
        clear_battle_affect(ch);
        go_critichit(ch, victim, WEAR_BODY);
        return;
    }
//������������� ����
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_BLOODLET)) {
        clear_battle_affect(ch);
        go_bloodlet(ch, victim);
        return;
    }
//�������������� �������
    if (dist == DIST_1 && GET_SKILL_MOB(ch, SKILL_ADDSHOT)
        && check_distance(ch, FIGHTING(ch)) == DIST_1) {
        struct obj_data *wield;

        wield = GET_EQ(ch, WEAR_WIELD) ? GET_EQ(ch, WEAR_WIELD) : GET_EQ(ch, WEAR_BOTHS);
        if (wield
            && (GET_OBJ_SKILL(wield) == SKILL_BOWS || GET_OBJ_SKILL(wield) == SKILL_CROSSBOWS)) {
            clear_battle_affect(ch);
            do_addshot(ch, GET_NAME(victim), 0, 0, 0);
            return;
        }
    }
//������ �����
    if (dist == DIST_0 && GET_SKILL_MOB(ch, SKILL_CIRCLESTAB)) {
        clear_battle_affect(ch);
        go_circlestab(ch, victim);
        return;
    }
//���������� ����������-����������� � �.�.
//���������
    if (GET_SKILL_MOB(ch, SKILL_BLOCK) && !GET_AF_BATTLE(ch, EAF_BLOCK)) {
        clear_battle_affect(ch);
        SET_AF_BATTLE(ch, EAF_BLOCK);
        return;
    }
//����������
    if (GET_SKILL_MOB(ch, SKILL_DEVIATE) && !GET_AF_BATTLE(victim, EAF_DEVIATE)) {
        clear_battle_affect(ch);
        SET_AF_BATTLE(ch, EAF_DEVIATE);
        return;
    }
//��������
    if (GET_SKILL_MOB(ch, SKILL_PARRY) && !GET_AF_BATTLE(ch, EAF_PARRY)) {
        clear_battle_affect(ch);
        SET_AF_BATTLE(ch, EAF_PARRY);
        return;
    }
//����������������
    if (GET_SKILL_MOB(ch, SKILL_COUNTERACT) && !GET_AF_BATTLE(ch, EAF_CACT_RIGHT) &&
        (GET_AF_BATTLE(attacker, EAF_PARRY) || GET_AF_BATTLE(attacker, EAF_DEVIATE)
         || GET_AF_BATTLE(attacker, EAF_BLOCK))) {
        clear_battle_affect(ch);
        go_counteract(ch, victim);
        return;
    }

}
