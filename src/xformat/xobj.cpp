/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xobj.h"
#include "xspells.h"
#include "parser_id.h"
#include "xtempl.h"
#include "strlib.h"
#include "expr.h"

/****/
// ����������� �������� ����������
int OBJ_NUMBER;  //�������
int OBJ_GUID; //������
int OBJ_ALIAS;  //��������
int OBJ_NAME;  //���
int OBJ_LINE;  //������
int OBJ_DESCRIPTION; //��������
int OBJ_ADDITION; //�������������
int OBJ_PROPERTIES; //���������
int OBJ_SEX;  //���
int OBJ_MATERIAL; //��������
int OBJ_WEIGHT;  //���
int OBJ_COST;  //����
int OBJ_TYPE;  //���
int OBJ_WEAR;  //�������������
int OBJ_ANTI;  //����������
int OBJ_NO;  //������
int OBJ_AFFECTS; //��������
int OBJ_APPLY;  //�������
int OBJ_TIMER;  //������
int OBJ_TIMELOAD; //������
int OBJ_QUALITY; //��������
int OBJ_LIMIT;  //������
int OBJ_DURAB;  //���������
int OBJ_CURRENT_DURAB;  //���.���������
int OBJ_MAGIC;  //�����
int OBJ_INTERCEPTION; //��������
int OBJ_SCRIPT;  //�������
int OBJ_SHANCE;  //����
int OBJ_VAL0;  //����0
int OBJ_VAL1;  //����1
int OBJ_VAL2;  //����2
int OBJ_VAL3;  //����3
int OBJ_LIGHT;  //����
int OBJ_LEVEL;  //�������
int OBJ_SPELL1;  //����1
int OBJ_SPELL2;  //����2
int OBJ_SPELL3;  //����3
int OBJ_ENCHANT; //�������
int OBJ_SLOT_MAX; //�������
int OBJ_SLOT_CUR; //������
int OBJ_SPELL;  //����������
int OBJ_AC;  //�����
int OBJ_ARM0;  //�������
int OBJ_ARM1;  //�������
int OBJ_ARM2;  //�������
int OBJ_DAMAGE;  //C���� v1+v2
int OBJ_SKILL;  //������
int OBJ_HIT;  //����� v3
int OBJ_SIZE;  //����������� v0
int OBJ_BAG_PROPERTIES; //��������� v1
int OBJ_KEY;  //����   v2
int OBJ_BAG_MAGIC; //��������  v3
int OBJ_BAG_NOTFIT; //������������
int OBJ_OLIST;  //����������
int OBJ_OGOLD;  //������
int OBJ_VALUE;  //������� v0
int OBJ_CUR_VALUE; //�������� v1
int OBJ_LIQ;  //�������� v2
int OBJ_POISON;  //�� v3
int OBJ_FOOD;  //��������� v0
int OBJ_GOLD;  //����� v0
int OBJ_BRIGHT;  //�������
int OBJ_TR_PROPERTIES; //����������
int OBJ_TRAP;  //������� (int)
int OBJ_XSAVE;          //����������
int OBJ_POWER;  //��������
int OBJ_TEMPLATE; //������� (����� �������)
int OBJ_ARM_CLASS; //�����
int OBJ_P0;
int OBJ_P1;
int OBJ_P2;
int OBJ_COMMAND; //�����������
int OBJ_TOOL;  //����������
int OBJ_ADD_HIT; //�����
int OBJ_AHIT_TYPE; //�����.���
int OBJ_AHIT_DAMAGE; //�����.�����
int OBJ_QUEST;  //������

//�����������
int OBJ_COMMAND_NO; //�����������.�������
int OBJ_COMMAND_ARG; //�����������.��������
int OBJ_COMMAND_TOOL; //�����������.����������
int OBJ_COMMAND_EXPR; //�����������.�������
int OBJ_COMMAND_ECHAR; //�����������.������_������
int OBJ_COMMAND_EROOM; //�����������.������_�������
int OBJ_COMMAND_ACTIVE;
int OBJ_COMMAND_ARG_OBJ; //�����������.��������.�������
int OBJ_COMMAND_ARG_ARG; //�����������.��������.������
int OBJ_COMMAND_ARG_MOB; //�����������.��������.������
int OBJ_COMMAND_ARG_ERR; //�����������.��������.������
int OBJ_COMMAND_SCRIPT; //�����������.������
int OBJ_COMMAND_EXTRACT; //�����������.����������
int OBJ_COMMAND_LOAD;     //�����������.��������
int OBJ_COMMAND_LOAD_ROOM; //�����������.��������.��������
int OBJ_COMMAND_LOAD_CHAR; //�����������.��������.����������
int OBJ_COMMAND_ACTIVE_ROOM;
int OBJ_COMMAND_MESS_ROOM;
int OBJ_COMMAND_MESS_CHAR;
int OBJ_COMMAND_XSCRIPT; //�����������.��������

//����������
int OBJ_XSAVE_EQ; //����������.����������
int OBJ_XSAVE_POS; //����������.���������

// �������������
int OBJ_ADD_KEY; //�������������.����
int OBJ_ADD_TEXT; //�������������.�����

// ��������
int OBJ_MAT_TYPE; //��������.���
int OBJ_MAT_VAL; //����������
int OBJ_MAT_MAIN; //��������

int OBJ_INT_COMMAND; // ��������.������� (LIST)
int OBJ_INT_STOP; // ��������.���� (int)
int OBJ_INT_EXPR; // ��������.������� (EXP)
int OBJ_INT_SCRIPT; // ��������.�������� (int)
int OBJ_INT_MESSPLAYER; // ��������.����� (STRING)
int OBJ_INT_MESSVICTIM; // ��������.������ (STRING)
int OBJ_INT_MESSOTHER; // ��������.��������� (STRING)
int OBJ_INT_MESSROOM; // ��������.������� (STRING)

//�����
int OBJ_MAGIC_SPELL; //�����.���������� (LIST)
int OBJ_MAGIC_LEVEL; //�����.�������  (int)
int OBJ_MAGIC_PERCENT; //�����.����  (int)
int OBJ_MAGIC_MESS_CHAR; //�����.������ (STRING)
int OBJ_MAGIC_MESS_VICT; //�����.������ (STRING)
int OBJ_MAGIC_MESS_ROOM; //�����.��������� (STRING)

//�������
int OBJ_TRAP_COMMAND;  //�������.�������
int OBJ_TRAP_CHANCE;  //�������.���� (int)
int OBJ_TRAP_TYPEDAMAGE; //�������.�����  (LIST)
int OBJ_TRAP_FORCEDAMAGE; //�������.�����  (RANDOM)
int OBJ_TRAP_SAVE;  //�������.�������
int OBJ_TRAP_MESS_CHAR;  //�������.�����
int OBJ_TRAP_MESS_ROOM;  //�������.�������
int OBJ_TRAP_MESS_SCHAR; //�������.������
int OBJ_TRAP_MESS_SROOM; //�������.��������
int OBJ_TRAP_MESS_KCHAR; //�������.����_�����
int OBJ_TRAP_MESS_KROOM; //�������.����_�������

//����������
int OBJ_AFFECT;
int AFFECT_TYPE;
int AFFECT_LOC;
int AFFECT_MOD;
int AFFECT_VEC;
int AFFECT_EXT;
int AFFECT_DUR;
int AFFECT_NFL;
int AFFECT_AFL;
int OBJ_OWNER;

//��������

int OBJ_SPECHIT;  //���������
int OBJ_SPECHIT_SHANCE;  //���������.����
int OBJ_SPECHIT_XRACE;  //���������.�����
int OBJ_SPECHIT_ZRACE;  //���������.�����
int OBJ_SPECHIT_XTYPE;  //���������.����
int OBJ_SPECHIT_ZTYPE;  //���������.����
int OBJ_SPECHIT_CHAR;  //���������.������
int OBJ_SPECHIT_VICTIM;  //���������.������
int OBJ_SPECHIT_ROOM;  //���������.�������
int OBJ_SPECHIT_KOEF;  //���������.����������
int OBJ_SPECHIT_HTYPE;  //���������.����
int OBJ_SPECHIT_HDAMAGE; //���������.������
int OBJ_SPECHIT_SPELL;  //���������.����������
int OBJ_SPECHIT_SLEVEL;  //���������.�������
int OBJ_SPECHIT_TARGET;  //���������.����

//�������
int OBJ_MISSILE;  //������
int OBJ_MISS_TYPE; //������.���
int OBJ_MISS_COUNT; //������.�����������
int OBJ_MISS_TCOUNT; //������.�����������
int OBJ_MISS_TEMPL; //������.�������
int OBJ_MADD_HIT; //������.�����
int OBJ_MAHIT_TYPE; //������.�����.���
int OBJ_MAHIT_DAMAGE; //������.�����.�����

/****/

///////////////////////////////////////////////////////////////////////////////
CObj::CObj() {
}

CObj::~CObj() {
}
///////////////////////////////////////////////////////////////////////////////

bool CObj::Initialization(void) {

    OBJ_NUMBER = Proto->AddItem(TYPE_INT, "�������");
    OBJ_GUID = Proto->AddItem(TYPE_LONGLONG, "������", false);
    OBJ_ALIAS = Proto->AddItem(TYPE_STRING, "��������");
    OBJ_NAME = Proto->AddItem(TYPE_STRING, "��������");
    OBJ_LINE = Proto->AddItem(TYPE_STRING, "������");
    OBJ_DESCRIPTION = Proto->AddItem(TYPE_STRING, "��������", false);
    OBJ_ADDITION = Proto->AddItem(TYPE_STRUCT, "�������������", false);
    CItemProto *add = Proto->GetItem(OBJ_ADDITION);
    OBJ_ADD_KEY = add->AddItem(TYPE_STRING, "����");
    OBJ_ADD_TEXT = add->AddItem(TYPE_STRING, "�����");
    OBJ_PROPERTIES = Proto->AddItem(TYPE_VECTOR, "���������", false, ParserConst.GetVector(VEC_OBJ_PROP));
    OBJ_SEX = Proto->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_SEX));
    OBJ_MATERIAL = Proto->AddItem(TYPE_STRUCT, "��������", true);
    CItemProto *mat = Proto->GetItem(OBJ_MATERIAL);
    OBJ_MAT_TYPE = mat->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_MAT_TYPES));
    OBJ_MAT_VAL = mat->AddItem(TYPE_INT, "����������", true);
    OBJ_MAT_MAIN  = mat->AddItem(TYPE_INT, "��������", false);
    OBJ_WEIGHT = Proto->AddItem(TYPE_INT, "���");
    OBJ_COST = Proto->AddItem(TYPE_INT, "����");
    OBJ_TYPE = Proto->AddItem(TYPE_LIST, "���", true,
                              ParserConst.GetList(LIST_OBJ_TYPES));
    OBJ_WEAR = Proto->AddItem(TYPE_VECTOR, "�������������", false,
                              ParserConst.GetVector(VEC_OBJ_WEAR));
    OBJ_ANTI = Proto->AddItem(TYPE_VECTOR, "����������", false,
                              ParserConst.GetVector(VEC_ANTI));
    OBJ_NO  = Proto->AddItem(TYPE_VECTOR, "������", false,
                             ParserConst.GetVector(VEC_ANTI));
    OBJ_AFFECTS = Proto->AddItem(TYPE_VECTOR, "��������", false,
                                 ParserConst.GetVector(VEC_MOB_AFF));
    OBJ_ARM_CLASS  = Proto->AddItem(TYPE_LIST, "�����", false,
                                    ParserConst.GetList(LIST_TYPE_ACLASS));
    OBJ_AFFECT = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *saffect = Proto->GetItem(OBJ_AFFECT);
    AFFECT_TYPE = saffect->AddItem(TYPE_INT, "���");
    AFFECT_LOC = saffect->AddItem(TYPE_LIST, "��������", false, ParserConst.GetList(LIST_APPLY));
    AFFECT_MOD = saffect->AddItem(TYPE_INT, "�����������");
    AFFECT_VEC = saffect->AddItem(TYPE_INT, "���������", false);
    AFFECT_EXT = saffect->AddItem(TYPE_INT, "������", false);
    AFFECT_DUR = saffect->AddItem(TYPE_INT, "�����");
    AFFECT_NFL = saffect->AddItem(TYPE_INT, "������", false);
    AFFECT_AFL = saffect->AddItem(TYPE_INT, "����������", false);
    OBJ_OWNER = Proto->AddItem(TYPE_INT, "��������", false);

    OBJ_APPLY = Proto->AddItem(TYPE_STRLIST, "�������", false,
                               ParserConst.GetList(LIST_APPLY));
    OBJ_TIMER = Proto->AddItem(TYPE_INT, "������", false);
    OBJ_TIMELOAD = Proto->AddItem(TYPE_INT, "������", false);
    OBJ_QUALITY = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_LIMIT = Proto->AddItem(TYPE_INT, "������", true);
    OBJ_DURAB = Proto->AddItem(TYPE_INT, "���������", true);
    OBJ_CURRENT_DURAB = Proto->AddItem(TYPE_INT, "�������_���������", false);
    OBJ_MAGIC = Proto->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *magic = Proto->GetItem(OBJ_MAGIC);
    OBJ_MAGIC_SPELL = magic->AddItem(TYPE_LIST, "����������", true,
                                     ParserConst.GetList(LIST_SPELLS));
    OBJ_MAGIC_LEVEL = magic->AddItem(TYPE_INT, "�������");
    OBJ_MAGIC_PERCENT = magic->AddItem(TYPE_INT, "����");
    OBJ_MAGIC_MESS_CHAR = magic->AddItem(TYPE_STRING, "������", false);
    OBJ_MAGIC_MESS_VICT = magic->AddItem(TYPE_STRING, "������", false);
    OBJ_MAGIC_MESS_ROOM = magic->AddItem(TYPE_STRING, "���������", false);
    OBJ_INTERCEPTION = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *intercept = Proto->GetItem(OBJ_INTERCEPTION);
    OBJ_INT_COMMAND = intercept->AddItem(TYPE_LIST, "�������", true,
                                         ParserConst.GetList(LIST_COMMANDS));
    OBJ_INT_STOP = intercept->AddItem(TYPE_INT, "����", false);
    OBJ_INT_EXPR = intercept->AddItem(TYPE_EXPR, "�������", false);
    OBJ_INT_SCRIPT = intercept->AddItem(TYPE_INT, "��������", false);
    OBJ_INT_MESSPLAYER = intercept->AddItem(TYPE_STRING, "�����", false);
    OBJ_INT_MESSVICTIM = intercept->AddItem(TYPE_STRING, "������", false);
    OBJ_INT_MESSOTHER  = intercept->AddItem(TYPE_STRING, "���������", false);
    OBJ_INT_MESSROOM   = intercept->AddItem(TYPE_STRING, "�������", false);
    OBJ_SHANCE = Proto->AddItem(TYPE_INT, "����", false);
    OBJ_SCRIPT = Proto->AddItem(TYPE_SCRIPT, "������", false);
    OBJ_VAL0 = Proto->AddItem(TYPE_INT, "����0", false);
    OBJ_VAL1 = Proto->AddItem(TYPE_INT, "����1", false);
    OBJ_VAL2 = Proto->AddItem(TYPE_INT, "����2", false);
    OBJ_VAL3 = Proto->AddItem(TYPE_INT, "����3", false);
    OBJ_LIGHT = Proto->AddItem(TYPE_INT, "����", false);
    OBJ_LEVEL = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_SPELL1 = Proto->AddItem(TYPE_LIST, "����1", false,
                                ParserConst.GetList(LIST_SPELLS));
    OBJ_SPELL2 = Proto->AddItem(TYPE_LIST, "����2", false,
                                ParserConst.GetList(LIST_SPELLS));
    OBJ_SPELL3 = Proto->AddItem(TYPE_LIST, "����3", false,
                                ParserConst.GetList(LIST_SPELLS));
    OBJ_ENCHANT    = Proto->AddItem(TYPE_LIST, "�������", false,
                                    ParserConst.GetList(LIST_ENCHANT));
    OBJ_SLOT_MAX = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_SLOT_CUR = Proto->AddItem(TYPE_INT, "������", false);
    OBJ_SPELL = Proto->AddItem(TYPE_LIST, "����������", false,
                               ParserConst.GetList(LIST_SPELLS));

    OBJ_AC  = Proto->AddItem(TYPE_INT, "�����", false);
    OBJ_ARM0 = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_ARM1 = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_ARM2 = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_DAMAGE = Proto->AddItem(TYPE_RANDOM, "�����", false);
    OBJ_SKILL = Proto->AddItem(TYPE_LIST, "������", false,
                               ParserConst.GetList(LIST_WEAPON_SKILLS));
    OBJ_HIT = Proto->AddItem(TYPE_LIST, "�����", false,
                             ParserConst.GetList(LIST_WEAPON_TYPE));

    OBJ_ADD_HIT = Proto->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *ahit = Proto->GetItem(OBJ_ADD_HIT);
    OBJ_AHIT_TYPE = ahit->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_DAMAGE));
    OBJ_AHIT_DAMAGE = ahit->AddItem(TYPE_STRING, "�����", true);

    OBJ_SIZE = Proto->AddItem(TYPE_INT, "�����������", false);
    OBJ_BAG_PROPERTIES = Proto->AddItem(TYPE_VECTOR, "���������", false,
                                        ParserConst.GetVector(VEC_EXIT_PROP));
    OBJ_BAG_NOTFIT = Proto->AddItem(TYPE_STRLIST, "������������", false,
                                    ParserConst.GetList(LIST_OBJ_TYPES));
    OBJ_KEY = Proto->AddItem(TYPE_INT, "����", false);
    OBJ_BAG_MAGIC = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_OLIST = Proto->AddItem(TYPE_STRLIST, "����������", false);
    OBJ_OGOLD = Proto->AddItem(TYPE_INT, "������", false);
    OBJ_VALUE = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_CUR_VALUE = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_LIQ = Proto->AddItem(TYPE_LIST, "��������", false,
                             ParserConst.GetList(LIST_LIQUID_TYPE));
    OBJ_POISON = Proto->AddItem(TYPE_INT, "��", false);
    OBJ_FOOD = Proto->AddItem(TYPE_INT, "���������", false);
    OBJ_GOLD = Proto->AddItem(TYPE_INT, "�����", false);
    OBJ_BRIGHT = Proto->AddItem(TYPE_INT, "�������", false);
    OBJ_TR_PROPERTIES = Proto->AddItem(TYPE_VECTOR, "����������", false,
                                       ParserConst.GetVector(VEC_TRANS_PROP));

    OBJ_TRAP = Proto->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *etrap = Proto->GetItem(OBJ_TRAP);
    OBJ_TRAP_COMMAND = etrap->AddItem(TYPE_LIST, "�������", false,
                                      ParserConst.GetList(LIST_COMMANDS));
    OBJ_TRAP_CHANCE = etrap->AddItem(TYPE_INT, "����");
    OBJ_TRAP_TYPEDAMAGE = etrap->AddItem(TYPE_LIST, "�����", true,
                                         ParserConst.GetList(LIST_DAMAGE));
    OBJ_TRAP_FORCEDAMAGE = etrap->AddItem(TYPE_RANDOM, "�����");
    OBJ_TRAP_SAVE = etrap->AddItem(TYPE_INT, "�������", false);
    OBJ_TRAP_MESS_CHAR = etrap->AddItem(TYPE_STRING, "�����", false);
    OBJ_TRAP_MESS_ROOM = etrap->AddItem(TYPE_STRING, "���������", false);
    OBJ_TRAP_MESS_SCHAR = etrap->AddItem(TYPE_STRING, "������", false);
    OBJ_TRAP_MESS_SROOM = etrap->AddItem(TYPE_STRING, "����������", false);
    OBJ_TRAP_MESS_KCHAR = etrap->AddItem(TYPE_STRING, "����_�����", false);
    OBJ_TRAP_MESS_KROOM = etrap->AddItem(TYPE_STRING, "����_�������", false);

    OBJ_XSAVE = Proto->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *xsave = Proto->GetItem(OBJ_XSAVE);
    OBJ_XSAVE_POS = xsave->AddItem(TYPE_INT, "���������", false);
    OBJ_XSAVE_EQ = xsave->AddItem(TYPE_INT, "����������", false);

    OBJ_POWER    = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_TEMPLATE = Proto->AddItem(TYPE_INT, "�������", false);

    OBJ_P0  = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_P1  = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_P2  = Proto->AddItem(TYPE_INT, "��������", false);
    OBJ_TOOL = Proto->AddItem(TYPE_LIST, "����������", false, ParserConst.GetList(LIST_TOOLS));

    OBJ_COMMAND  = Proto->AddItem(TYPE_STRUCT, "�����������", false);
    CItemProto *command = Proto->GetItem(OBJ_COMMAND);
    OBJ_COMMAND_NO = command->AddItem(TYPE_LIST, "�������", true, ParserConst.GetList(LIST_COMMANDS));
    OBJ_COMMAND_ARG = command->AddItem(TYPE_STRUCT, "��������", false);
    OBJ_COMMAND_TOOL = command->AddItem(TYPE_LIST, "����������", false, ParserConst.GetList(LIST_TOOLS));
    OBJ_COMMAND_EXPR = command->AddItem(TYPE_EXPR, "�������", false);
    OBJ_COMMAND_ECHAR = command->AddItem(TYPE_STRING, "������", false);
    OBJ_COMMAND_EROOM = command->AddItem(TYPE_STRING, "������_�������", false);

    OBJ_COMMAND_ACTIVE = command->AddItem(TYPE_STRING, "���������", false);
    OBJ_COMMAND_ACTIVE_ROOM = command->AddItem(TYPE_STRING, "���������_�������", false);

    CItemProto *comarg = command->GetItem(OBJ_COMMAND_ARG);
    OBJ_COMMAND_ARG_OBJ = comarg->AddItem(TYPE_INT, "�������", false);
    OBJ_COMMAND_ARG_ARG = comarg->AddItem(TYPE_STRING, "������", false);
    OBJ_COMMAND_ARG_MOB = comarg->AddItem(TYPE_INT, "������", false);
    OBJ_COMMAND_ARG_ERR = comarg->AddItem(TYPE_STRING, "������", false);
    OBJ_COMMAND_SCRIPT = command->AddItem(TYPE_INT, "������", false);
    OBJ_COMMAND_XSCRIPT = command->AddItem(TYPE_INT, "��������", false);
    OBJ_COMMAND_EXTRACT = command->AddItem(TYPE_INT, "����������", false);
    OBJ_COMMAND_LOAD = command->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *cload = command->GetItem(OBJ_COMMAND_LOAD);
    OBJ_COMMAND_LOAD_ROOM = cload->AddItem(TYPE_INT, "��������", false);
    OBJ_COMMAND_LOAD_CHAR = cload->AddItem(TYPE_INT, "����������", false);
    OBJ_COMMAND_MESS_CHAR = cload->AddItem(TYPE_STRING, "�����", false);
    OBJ_COMMAND_MESS_ROOM = cload->AddItem(TYPE_STRING, "�������", false);

    OBJ_SPECHIT  = Proto->AddItem(TYPE_STRUCT, "���������", false);
    CItemProto *spech = Proto->GetItem(OBJ_SPECHIT);
    OBJ_SPECHIT_SHANCE = spech->AddItem(TYPE_INT, "����", true);
    OBJ_SPECHIT_XRACE = spech->AddItem(TYPE_STRLIST, "�����", false, ParserConst.GetList(LIST_RACE));
    OBJ_SPECHIT_ZRACE = spech->AddItem(TYPE_STRLIST, "�����", false, ParserConst.GetList(LIST_RACE));
    OBJ_SPECHIT_XTYPE = spech->AddItem(TYPE_STRLIST, "����", false, ParserConst.GetList(LIST_MOB_TYPE));
    OBJ_SPECHIT_ZTYPE = spech->AddItem(TYPE_STRLIST, "����", false, ParserConst.GetList(LIST_MOB_TYPE));
    OBJ_SPECHIT_CHAR = spech->AddItem(TYPE_STRING, "������", true);
    OBJ_SPECHIT_VICTIM = spech->AddItem(TYPE_STRING, "������", true);
    OBJ_SPECHIT_ROOM = spech->AddItem(TYPE_STRING, "�������", true);
    OBJ_SPECHIT_KOEF = spech->AddItem(TYPE_FLOAT, "����������", false);
    OBJ_SPECHIT_HTYPE = spech->AddItem(TYPE_LIST, "����", false, ParserConst.GetList(LIST_DAMAGE));
    OBJ_SPECHIT_HDAMAGE = spech->AddItem(TYPE_STRING, "������", false);
    OBJ_SPECHIT_SPELL = spech->AddItem(TYPE_LIST, "����������", false, ParserConst.GetList(LIST_SPELLS));
    OBJ_SPECHIT_SLEVEL = spech->AddItem(TYPE_INT, "�������", false);
    OBJ_SPECHIT_TARGET = spech->AddItem(TYPE_LIST, "����", false, ParserConst.GetList(LIST_TARGET));

    OBJ_QUEST = Proto->AddItem(TYPE_SCRIPT, "�������", false);

    OBJ_MISSILE = Proto->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *missl = Proto->GetItem(OBJ_MISSILE);
    OBJ_MISS_TYPE = missl->AddItem(TYPE_LIST, "���", false, ParserConst.GetList(LIST_MISSILE));
    OBJ_MISS_COUNT = missl->AddItem(TYPE_INT, "�����������", true);
    OBJ_MISS_TCOUNT = missl->AddItem(TYPE_INT, "�����������", false);
    OBJ_MISS_TEMPL = missl->AddItem(TYPE_INT, "�������", false);
    OBJ_MADD_HIT = missl->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *mah = missl->GetItem(OBJ_MADD_HIT);
    OBJ_MAHIT_TYPE = mah->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_DAMAGE));
    OBJ_MAHIT_DAMAGE = mah->AddItem(TYPE_STRING, "�����", true);

    return CheckInit();
}

CObj * Obj;

