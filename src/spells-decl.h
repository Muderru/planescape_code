#ifndef SPELLS_DECL_H
#define SPELLS_DECL_H
/* ************************************************************************
*   File: spells.h                                      Part of CircleMUD *
*  Usage: header file: constants and fn prototypes for spell system       *
*                                                                         *
*  All rights reserved.  See license.doc for complete information.        *
*                                                                         *
*  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
*  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
************************************************************************ */

#include <string>

//���� �����
#define MIRC_MOVE 0
#define MIRC_DIE 1
#define MIRC_FIGHT 2
#define MIRC_HEAL 3
#define NUM_MIRC        4

//���� �������
#define SPL_DEF  1


#define TYPE_MESS_KILL 0
#define TYPE_MESS_HIT 1
#define TYPE_MESS_FAIL 2
#define TYPE_MESS_GOD 3

//���� ����������
#define TYPE_SPEC_SPELL 0 //����������
#define TYPE_SPEC_HIT 1 //����������
#define TYPE_SPEC_ROOM 2 //�������

//���� �����������
#define TYPE_HITS 1 //������� ����
#define TYPE_FIRE 2 //����������� �����
#define TYPE_COLD 3 //�������
#define TYPE_ELECTRO 4 //��������������
#define TYPE_ACID 5 //��������
#define TYPE_POISON 6 //��
#define TYPE_LIGHT 7 //������
#define TYPE_DARK 8 //��������
#define TYPE_SKILL 9 //������

//��������� ���������� � exp

//����������� �������������� ������
#define SKILL_TWEAPON   0 // ��������� ������
#define SKILL_TMAGIC 1 // ����������
#define SKILL_TWARRIOR 2 // �����
#define SKILL_TTHIEF 3 // ����
#define SKILL_TRANGER 4 // ��������
#define SKILL_TPRIEST 5 // ����������
#define SKILL_TLANG 253 //�����
#define SKILL_TRACE 254 //�������
#define SKILL_TOTHER 255 //���������

//����������� ���� �����
#define SP_ENCHANTMENT 0// �����������
#define SP_DIVINITION 1// ����������
#define SP_NECROMANCE 2// �����������
#define SP_ALTERATION 3// �����������
#define SP_INVOCATION 4// ����������
#define SP_CONJURATION 5// ���������
#define SP_ILLUSION 6// �������
#define SP_ABJURATION 7// ���������

//����������� ���� ������
#define SP_KINDNESS 8//�����
#define SP_HEALING 9//���������
#define SP_LIGHT 10//����
#define SP_SUN  11//������
#define SP_WAR  12//�����
#define SP_PROTECTION 13//������
#define SP_NATURE 14//�������
#define SP_SUCCESS 15//�����
#define SP_TRAVEL 16//�����������
#define SP_FORCE 17//����
#define SP_MAGIC 18//�����
#define SP_EVIL  19//���
#define SP_DEATH 20//������
#define SP_DESTRUCTION 21//����������
#define NUM_SPHERE 22


//����������� ������ �������������
#define S_BASIC         0 // ��������
#define S_NOVICE        1 // �������
#define S_SPEC          2 // ����������
#define S_MASTER        3 // ������
#define S_PROFES        4 // ������������
#define S_GRANDM        5 // ����� ������


#define DEFAULT_STAFF_LVL       12
#define DEFAULT_WAND_LVL        12
#define CAST_UNDEFINED  -1
#define CAST_SPELL      0
#define CAST_POTION     1
#define CAST_WAND       2
#define CAST_STAFF      3
#define CAST_SCROLL     4
#define CAST_WEAPON 5
#define CAST_RUNES  6

#define MTYPE_NEUTRAL (1 << 0)
#define MTYPE_AIR     (1 << 1)
#define MTYPE_FIRE    (1 << 2)
#define MTYPE_WATER   (1 << 3)
#define MTYPE_EARTH   (1 << 4)

#define MAG_DAMAGE          (1 << 0)
#define MAG_AFFECTS         (1 << 1)
#define MAG_UNAFFECTS   (1 << 2)
#define MAG_POINTS          (1 << 3)
#define MAG_ALTER_OBJS  (1 << 4)
#define MAG_GROUPS          (1 << 5)
#define MAG_MASSES          (1 << 6)
#define MAG_AREAS           (1 << 7)
#define MAG_SUMMONS         (1 << 8)
#define MAG_CREATIONS   (1 << 9)
#define MAG_MANUAL          (1 << 10)
#define MAG_ALL_AREAS          (1 << 11)

#define NPC_DAMAGE_PC           (1 << 16)
#define NPC_DAMAGE_PC_MINHP     (1 << 17)
#define NPC_AFFECT_PC           (1 << 18)
#define NPC_AFFECT_PC_CASTER    (1 << 19)
#define NPC_AFFECT_NPC          (1 << 20)
#define NPC_UNAFFECT_NPC        (1 << 21)
#define NPC_UNAFFECT_NPC_CASTER (1 << 22)
#define NPC_DUMMY               (1 << 23)
#define NPC_CALCULATE           (0xff << 16)
/***** Extra attack bit flags */
#define EAF_PARRY       (1 << 0)
#define EAF_BLOCK       (1 << 1)
#define EAF_TOUCH       (1 << 2)
#define EAF_CRITIC      (1 << 3)
#define EAF_DEVIATE     (1 << 4)
#define EAF_NOCRITIC    (1 << 5)
#define EAF_ADDSLASH_LEFT (1 << 6)
#define EAF_SLOW        (1 << 7)
#define EAF_ADDSHOT (1 << 8)
#define EAF_ADDSLASH (1 << 9)
#define EAF_FIRST       (1 << 10)
#define EAF_SECOND      (1 << 11)
#define EAF_STAND       (1 << 13)
#define EAF_USEDRIGHT   (1 << 14)
#define EAF_USEDLEFT    (1 << 15)
#define EAF_MULTYPARRY  (1 << 16)
#define EAF_SLEEP       (1 << 17)
#define EAF_CACT_RIGHT (1 << 18)
#define EAF_CACT_LEFT (1 << 19)

#define TYPE_NOPARRY                -2
#define TYPE_UNDEFINED              -1
#define SPELL_RESERVED_DBC          0  /* SKILL NUMBER ZERO -- RESERVED */

/* PLAYER SPELLS TYPES */
#define   SPELL_KNOW   (1 << 0)
#define   SPELL_TEMP   (1 << 1)
#define   SPELL_POTION (1 << 2)
#define   SPELL_WAND   (1 << 3)
#define   SPELL_SCROLL (1 << 4)
#define   SPELL_ITEMS  (1 << 5)
#define   SPELL_RUNES  (1 << 6)

#define   ITEM_RUNES       (1 << 0)
#define   ITEM_CHECK_USES  (1 << 1)
#define   ITEM_CHECK_LAG   (1 << 2)
#define   ITEM_CHECK_LEVEL (1 << 3)
#define   ITEM_DECAY_EMPTY (1 << 4)

#define   MI_LAG1s       (1 << 0)
#define   MI_LAG2s       (1 << 1)
#define   MI_LAG4s       (1 << 2)
#define   MI_LAG8s       (1 << 3)
#define   MI_LAG16s      (1 << 4)
#define   MI_LAG32s      (1 << 5)
#define   MI_LAG64s      (1 << 6)
#define   MI_LAG128s     (1 << 7)
#define   MI_LEVEL1      (1 << 8)
#define   MI_LEVEL2      (1 << 9)
#define   MI_LEVEL4      (1 << 10)
#define   MI_LEVEL8      (1 << 11)
#define   MI_LEVEL16     (1 << 12)

/* PLAYER SPELLS -- Numbered from 1 to MAX_SPELLS */
#define NUM_SPELLZ  142
#define NUM_SKILLZ  160

//����� ����������
#define SPELL_IDENTIFY   1 //�������������
#define SPELL_RECALL   2 //�������
#define SPELL_CAST_HOLD   3 //����� ��������

//����� �����
#define SPELL_PROTECT_FROM_EVIL  10 //������ �� ���
#define SPELL_CONSECRATE  11 //���������
#define SPELL_CIRCLE_AGANIST_EVIL 12 //���� ������ �� ���
#define SPELL_HOLY_SMITE  13 //������ ����
#define SPELL_DISPEL_EVIL  14 //������� ���
#define SPELL_ASPECT_GOD  15 //������ ����
#define SPELL_HOLY_WORD   16 //������ �����
#define SPELL_HOLY_AURA   17 //������ ����
#define SPELL_SUMMON_ANGEL  18 //�������� ������� ����� �����

//����� �����
#define SPELL_ENDURE_ELEMENTS  20 //������ �� ������
#define SPELL_HEAT_METALL  21 //��������� �����
#define SPELL_SEARING_LIGHT  22 //��������� ���
#define SPELL_FIRE_SHIELD  23 //������� ���
#define SPELL_FLAME_STRIKE  24 //�������� ����
#define SPELL_FIRE_SEEDS  25 //�������� ������
#define SPELL_SUNBEAM   26 //��� �����
#define SPELL_SUNBURST   27 //�������� �����
#define SPELL_FIRE_CROWN  28 //�������� ������
#define SPELL_PRISMA_WALL  29 //�������������� �����

//����� ���������
#define SPELL_CURE   30 //������� ���
#define SPELL_REMOVE_ILLNESS  31 //������ �������
#define SPELL_CURE_CRITICAL  32 //������� ����������� ���
#define SPELL_CURE_MASS   33 //���� ��������� 
#define SPELL_HEAL   34 //���������
#define SPELL_HEAL_MASS   35 //�������� ���������
#define SPELL_REMOVE_POISON  36 //������� ���
#define SPELL_REMOVE_BLIND  37 //������� �������
#define SPELL_REFRESH_MASS  38 //�������� ��������������
#define SPELL_RESSURECT   39 //�����������
#define SPELL_REMOVE_CURSE  123 //����� ���������

//����� �����
#define SPELL_MAGIC_WEAPON  40 //��������� ������
#define SPELL_SPIRIT_WEAPON  41 //�������� ������
#define SPELL_MAGIC_VESTMENT  42 //��������� ���������
#define SPELL_DIVINE_POWER  43 //������������ ����
#define SPELL_FLAME_STRIKE_WAR  44 //���� �������
#define SPELL_BLADE_BARRIER  45 //����� ������
#define SPELL_POWER_WORD_STUNE  46 //����� ���� ��������
#define SPELL_POWER_WORD_BLIND  47 //����� ���� �������
#define SPELL_POWER_WORD_KILL  48 //����� ���� �����

//����� ���
#define SPELL_PROTECT_FROM_GOOD  50 //������ �� �����
#define SPELL_DESECRATE   51 //�����������
#define SPELL_CREATE_UNDEAD  52 //������� ������
#define SPELL_UNHOLY_BLIGHT  53 //�����
#define SPELL_DISPEL_GOOD  54 //������� �����
#define SPELL_CREATE_SHADOW  55 //������� ����
#define SPELL_BLASPHEMY   56 //������������
#define SPELL_UNHOLY_AURA  57 //���� �������
#define SPELL_SUMMON_MONSTER_2  58 //�������� ������� ����� ���

//����� ����
#define SPELL_ENDURE_ELEMENTS_P  60 //������ �� ������_����� �����
#define SPELL_BULL_STRENGH  61 //����� ����
#define SPELL_MAGIC_VESTMENT_P  62 //��������� ���������
#define SPELL_BROTH_WEAPON              63 //�������� �� ������
#define SPELL_RIGHTEOUS_MIGHT  64 //��������� ����
#define SPELL_STONE_SKIN  65 //������� ����
#define SPELL_GRASPING_HAND  66 //��������� ����
#define SPELL_CLENCHED_FIST  67 //������ �����
#define SPELL_CRUSHING_FIST  68 //����������� ����

//����� �����������
#define SPELL_FASTER_MOVE  70 //������� ������������
#define SPELL_LOCATE_OBJECT  71 //����� �������
#define SPELL_LEVITATION  72 //���������
#define SPELL_DIMENSION_DOOR  73 //���������� �����
#define SPELL_LOCATE_PERSON  74 //����� �������
#define SPELL_TELEPORT   75 //��������� �����
#define SPELL_REFRESH   76 //�������������� ��������
#define SPELL_FREE_MOVES  77 //������� ��������
#define SPELL_ASTRAL_PROJECT  78 //���������� ��������

//����� ������
#define SPELL_SANCTUARY               80 //���������
#define SPELL_SHIELD_OTHER              81 //��� �������
#define SPELL_IMUN_ELEMENTS  82 //��������� �� ������
#define SPELL_SAVE_WILL   83 //�������� ����
#define SPELL_NOMAGIC_FIELD  84 //���� ���������
#define SPELL_REPULSION   85 //����������
#define SPELL_MAGIC_IMMUNITY  86 //�������� � �����
#define SPELL_MIND_BLANK  87 //������� ������
#define SPELL_PRISMA_SPHERE  88 //�������������� �����

//����� �����
#define SPELL_ENTROPIC_SHIELD  90 //��� ��������
#define SPELL_AID   91 //������
#define SPELL_FPANTACLE   92 //�������� ����������
#define SPELL_MAGIC_PARRY  93 //���������� �����
#define SPELL_EXPAND_SKILL  94 //��������� ������
#define SPELL_EVIL_FATE   95 //���� ���
#define SPELL_FAST_LEARN  96 //������� ��������
#define SPELL_MISLEAD   97 //�����������
#define SPELL_MIRACLE   98 //����

//����� �����������
#define SPELL_ANIMATE_ANIMAL  100 //������� ��������
#define SPELL_DETECT_UNDEAD  101 //������ ������
#define SPELL_PROTECT_UNDEAD  102 //������ �� ������
#define SPELL_CAUSE_FEAR  103 //������� �����
#define SPELL_SKULL_SNARE  104 //�����-�������
#define SPELL_ANIMATE_SKELET  105 //������� ������
#define SPELL_MAKE_SKELET  106 //��������� ����
#define SPELL_FREEZE_BLOOD  107 //�������� �����
#define SPELL_SHADOW_DEATH  108 //���� ������
#define SPELL_WAKEUP_DEAD  109 //������� �����
#define SPELL_OR   110 //���������� ����
#define SPELL_STEEL_BONES  111 //�������� �����
#define SPELL_ENERGY_UNDEAD  112 //������� ����
#define SPELL_GHOST_FEAR  113 //���������� ����
#define SPELL_SLAVED_SHADOW  114 //����������� ����
#define SPELL_MAKE_GHOLA  115 //����������� � �����
#define SPELL_IMPLANT_WEAPON  116 //������� ������
#define SPELL_IS_UNDEAD   117 //����� ��������
#define SPELL_BONES_WALL  118 //�������� �����
#define SPELL_BONES_PICK  119 //�������� ����
#define SPELL_THR_DEATH   120 //��������� ������
#define SPELL_FOUL_FLESH  121 //����������� �����
#define SPELL_PRISMATIC_SKIN  122 //�������������� ����
#define SPELL_DEATH_ARROWS  124 //������ ������
#define SPELL_SHADOW_PROTECT  125 //������ ����
#define SPELL_FREEDOM_UNDEAD  126 //���������� ������
#define SPELL_MASS_FEAR   127 //�������� �����
#define SPELL_DEATH_WEAPON  128 //������ ������
#define SPELL_BURY   129 //��������
#define SPELL_POISON_FOG  130 //��������� ������
#define SPELL_RESSURECT_NECRO  131 //������� ���

//�������� ���������� 300-350
#define SPELL_INFRAVISION  350 //������� �����
#define SPELL_DETECT_MAGIC  351 //����������� �����
#define SPELL_FLY   352 //�����
#define SPELL_INVISIBLE   353 //�����������
//��������������
#define SPELL_BLIND   4 //���������� ������� �������
#define SPELL_HOLD   5 //���������� ��������
#define SPELL_ELEM_FIRE   6 //������ �� ����
#define SPELL_ELEM_COLD   7 //������ �� ������
#define SPELL_ELEM_ELEC   8 //������ �� �������������
#define SPELL_ELEM_ACID   9 //������ �� �������
//��� ����������
#define SPELL_DE_MIND   500 //����� �����

#define SPELL_DANCE   369 //������ �� �����
#define SPELL_MEDITATION                370 //���������
#define SPELL_PRISMA_FIRE  371 //������ �� ����
#define SPELL_PRISMA_COLD  372 //������ �� ������
#define SPELL_PRISMA_ELEC  373 //������ �� �������������
#define SPELL_PRISMA_ACID               374 //������ �� �������
#define SPELL_PRISMA_HIT                375 //������ �� �����

#define SPELL_IMM_FIRE   376 //��������� �� ����
#define SPELL_IMM_COLD   377 //��������� �� ������
#define SPELL_IMM_ELEC   378 //��������� �� �������������
#define SPELL_IMM_ACID   379 //��������� �� �������

#define SPELL_PREPLAGUE   380 //���������-����
#define SPELL_PLAGUE   381 //�������-����
#define SPELL_IMM_PLAGUE  382 //���������-����
#define SPELL_CAMOUFLAGE          384 //����������
#define SPELL_HOLYLIGHT   385 //�������
#define SPELL_COURAGE             386 //������ 
#define SPELL_BATTLE              387 //������ �� �����
#define SPELL_DRUNKED             388 //���������
#define SPELL_FIRE_BLADES  389 //�������� ������
#define SPELL_UNHOLY   390 //���������� ������� �������� �� ���� �������
#define SPELL_GRASP   391 //���������
#define SPELL_ILLNESS   392 //�������
#define SPELL_POISON   393 //����������
#define SPELL_STUNE   394 //��������
#define SPELL_DB   395 //����������� ��� �������� ������� 
//��� �������� �� �����
#define SPELL_BANDAGE   396 //������ ����������
#define SPELL_HIDE                397 //������ ������
#define SPELL_SNEAK               398 //������ ����������
#define SPELL_CHARM                   401 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_WATERD   402
#define SPELL_HAEMORRAGIA  403 //���������� ������������
#define SPELL_FIRE_BLADES_WEAP  404
#define SPELL_FIRE_SHIELD_WEAP  406
#define SPELL_BLADE_BARRIER_WEAP 405
#define SPELL_ENCHANT   406 /*�����������*/
//
#define SPELL_MAKE_GHOLA_S1  441
#define SPELL_MAKE_GHOLA_S2  442
#define SPELL_MAKE_GHOLA_S3  443
#define SPELL_MAKE_GHOLA_S4  444
#define SPELL_MAKE_GHOLA_S5  445
#define SPELL_SUMMON_HORSE  499

#define LAST_USED_SPELL                  399

/* PLAYER SKILLS - Numbered from 1 to MAX_SKILLS */
#define SKILL_THAC0                 0  /* Internal */
//#define SKILL_PROTECT               1 /**** Protect grouppers    */
#define SKILL_TOUCH                 2 /**** Touch attacker       */
#define SKILL_SHIT                  3
#define SKILL_STUPOR                5
#define SKILL_POISONED              6
//#define SKILL_SENSE               7
#define SKILL_HORSE                 8
#define SKILL_HIDETRACK             9
#define SKILL_COUNTERACT            10
#define SKILL_MAKEFOOD              11
#define SKILL_MULTYPARRY            12
#define SKILL_SAPPER            13
#define SKILL_MAKETRAP      14
#define SKILL_LEADERSHIP            20
//#define SKILL_ADDSHOT               21
//#define SKILL_AWAKE                 22
#define SKILL_IDENTIFY              23
#define SKILL_TRACKON      24
#define SKILL_ORENT      25
#define SKILL_CREATE_SCROLL         26
#define SKILL_CREATE_WAND           27
#define SKILL_LOOK_HIDE             28
#define SKILL_CRITIC                29
#define SKILL_RUNUPB                30
#define SKILL_AID                   31
#define SKILL_FIRE                  32
#define SKILL_GUARD                 33
#define SKILL_CHARM                 34
#define SKILL_SHOOT                 35
#define SKILL_HOLYLIGHT      36 /* ������� ������ ��������� */
#define SKILL_HOLYDARK      37 /* ������� ������ ��������� */
#define SKILL_SWITCH      38 /* ����������� �������� */
#define SKILL_CONCENTRATE     39 /* ������������ */
#define SKILL_ENCHANT      40 /* ����������� */
#define SKILL_LEARN                 41 /* �������� */

#define SKILL_SNAPSHOT              123 //������ �������
#define SKILL_RDANCE                124 //��������� �����
#define SKILL_CIRCLESTAB     125 //������ �����
#define SKILL_SHIELDHIT      126 //���� �����
#define SKILL_BLOODLET      127 //�������������
#define SKILL_RUNUP                 128
#define SKILL_MIGHTHIT              129
#define SKILL_THROW                 130
#define SKILL_BACKSTAB              131 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_BASH                  132 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_ABASH                 1000 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_NBASH                 1001 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_HIDE                  133 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_KICK                  134 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_KICKB                 599 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_PICK_LOCK             135 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_PUNCH                 136 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_RESCUE                137 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_SNEAK                 138 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_STEAL                 139 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_TRACK                 140 /* Reserved Skill[] DO NOT CHANGE */
//��������� ������
#define SKILL_STAFFS                141 // ������
#define SKILL_AXES                  142 // ������
#define SKILL_SWORDS                143 // ����
#define SKILL_DAGGERS               144 // �������
#define SKILL_MACES                 145 // ������
#define SKILL_FLAILS                146 // �������
#define SKILL_WHIPS                 147 // �����
#define SKILL_SPAEKS                148 // �����
#define SKILL_BOWS                  149 // ����
#define SKILL_CROSSBOWS             150 // ��������
#define SKILL_BOTHHANDS             151 // ���������

#define SKILL_SATTACK               160
#define SKILL_DISARM                161
#define SKILL_PARRY                 162
#define SKILL_HEAL                  163
#define SKILL_TURN                  164
#define SKILL_ADDSHOT               165
#define SKILL_CAMOUFLAGE            166
#define SKILL_DEVIATE               167
#define SKILL_BLOCK                 168
#define SKILL_LOOKING               169
#define SKILL_CHOPOFF               170
//#define SKILL_REPAIR                171
#define SKILL_PRAY                  172
#define SKILL_COURAGE               173
#define SKILL_DIRFLEE               174
#define SKILL_CRASHDOOR      175
#define SKILL_FIND      176
#define SKILL_BALSAM      177

// �����
#define SKILL_LANG_COMMON         180
#define SKILL_LANG_ORC             181
#define SKILL_LANG_DWARN           182
#define SKILL_LANG_ELF             183
#define SKILL_LANG_HUMAN           184
#define SKILL_LANG_BARIAUR         185
#define SKILL_LANG_AASIMAR         186
#define SKILL_LANG_TIEFLING        187


// ���������� ������

//����������� ����
#define TYPE_SPHERE_SKILL 190 //������� ����� ��������� � ������ �����
                              //����� �������� ����� ������
#define SKILL_SP_ENCHANTMENT 190// �����������
#define SKILL_SP_DIVINITION     191// ����������
#define SKILL_SP_NECROMANCE 192// �����������
#define SKILL_SP_ALTERATION 193// �����������
#define SKILL_SP_INVOCATION 194// ����������
#define SKILL_SP_CONJURATION 195// ���������
#define SKILL_SP_ILLUSION 196// �������
#define SKILL_SP_ABJURATION 197// ���������
#define SKILL_SP_KINDNESS 198//�����
#define SKILL_SP_HEALING 199//���������
#define SKILL_SP_LIGHT  200//����
#define SKILL_SP_WAR  202//�����
#define SKILL_SP_PROTECTION 203//������
#define SKILL_SP_NATURE  204//�������
#define SKILL_SP_SUCCESS 205//�����
#define SKILL_SP_TRAVEL  206//�����������
#define SKILL_SP_FORCE  207//����
#define SKILL_SP_MAGIC  208//�����
#define SKILL_SP_EVIL  209//���
#define SKILL_SP_DEATH  210//������
#define SKILL_SP_DESTRUCTION 211//����������


/* New skills may be added here up to MAX_SKILLS (200) */


/*
 *  NON-PLAYER AND OBJECT SPELLS AND SKILLS
 *  The practice levels for the spells and skills below are _not_ recorded
 *  in the playerfile; therefore, the intended use is for spells and skills
 *  associated with objects (such as SPELL_IDENTIFY used with scrolls of
 *  identify) or non-players (such as NPC-only spells).
 */

#define SPELL_BLADE_BARRIER_OFF      501

#define TOP_SPELL_DEFINE                 399
#define TOP_SKILL_DEFINE             211

//�����
#define SAV_FORT 0
#define SAV_REFL 1
#define SAV_WILL 2
#define SAV_FIRE 3
#define SAV_COLD 4
#define SAV_ELECTRO 5
#define SAV_ACID 6
#define SAV_XAOS 7
#define SAV_ORDER 8
#define SAV_NONE 9
#define SAV_POSITIVE 10
#define SAV_NEGATIVE 11
#define SAV_NONE2 12
#define SAV_POISON 13

#define TAR_IGNORE      (1 << 0) //     a
#define TAR_CHAR_ROOM   (1 << 1) //1    b
#define TAR_CHAR_WORLD  (1 << 2) //2    c
#define TAR_FIGHT_SELF  (1 << 3) //4    d
#define TAR_FIGHT_VICT  (1 << 4) //8    e
#define TAR_SELF_ONLY   (1 << 5) //16   f
#define TAR_NOT_SELF    (1 << 6) //32   g
#define TAR_OBJ_INV     (1 << 7) //64   h
#define TAR_OBJ_ROOM    (1 << 8) //128  i 
#define TAR_OBJ_WORLD   (1 << 9) //256  j  
#define TAR_OBJ_EQUIP   (1 << 10) //512 k
#define MAX_SLOT        10

struct skill_info_type {
    byte  min_position;   /* Position for caster */
    int k_improove[NUM_CLASSES][NUM_GODS];
    int ability[NUM_CLASSES][NUM_GODS];
    int learn_level[NUM_CLASSES][NUM_GODS];
    int max_percent;
    std::string name;
    int skill_type;
};

extern struct skill_info_type skill_info[];

/* Possible Targets:

   bit 0: IGNORE TARGET
   bit 1: PC/NPC in room
   bit 2: PC/NPC in world
   bit 3: Object held
   bit 4: Object in inventory
   bit 5: Object in room
   bit 6: Object in world
   bit 7: If fighting, and no argument, select tar_char as self
   bit 8: If fighting, and no argument, select tar_char as victim (fighting)
   bit 9: If no argument, select self, if argument check that it IS self.

*/

#define SPELL_TYPE_SPELL   0
#define SPELL_TYPE_POTION  1
#define SPELL_TYPE_WAND    2
#define SPELL_TYPE_STAFF   3
#define SPELL_TYPE_SCROLL  4


extern const char *unused_spellname;

extern int sphere_class[NUM_SPHERE];
extern int what_sky;
extern char cast_argument[MAX_STRING_LENGTH];

// ���������� ������ ��������� ���������� ����������
extern int spellnum_db;


#endif
