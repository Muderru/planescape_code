/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xmob.h"
#include "xbody.h"
#include "xspells.h"
#include "parser_id.h"
#include "strlib.h"
#include "expr.h"


///////////////////////////////////////////////////////////////////////////////
// ����������� �������� ����������
int MOB_NUMBER;  //������
int MOB_ALIAS;  //��������
int MOB_NAME;  //���
int MOB_LINE;  //������
int MOB_DESCRIPTION; //��������
int MOB_ADDITION; //�������������
int MOB_PROPERTIES; //���������
int MOB_ADDONS;  //�����������
int MOB_AFFECTS; //��������
int MOB_SEX;  //���
int MOB_LEVEL;  //�������
int MOB_CLASS;  //���������
int MOB_RACE;  //����
int MOB_TYPE;  //���
int MOB_ALIGN;  //����������
int MOB_LAWS;  //����������
int MOB_EXP;  //����
int MOB_LIMIT;  //������
int MOB_HITPOINTS; //�����
int MOB_AC;  //�����
int MOB_HITROLL; //�����
int MOB_HIT1;  //����1
int MOB_DAMAGE1; //����1
int MOB_COUNT1;  //�����1
int MOB_HIT2;  //����2
int MOB_DAMAGE2; //����2
int MOB_COUNT2;  //�����2
int MOB_STR;  //����
int MOB_CON;  //������������
int MOB_DEX;  //��������
int MOB_INT;  //�����
int MOB_WIS;  //��������
int MOB_CHA;  //�������
int MOB_SIZE;  //������
int MOB_HEIGHT;  //����
int MOB_WEIGHT;  //���
int MOB_POSITION; //���������
int MOB_MOVED;  //�����������
int MOB_MOVESTR; //������������
int MOB_GOLD;  //������
int MOB_WIMP;  //��������
int MOB_SKILL;  //������
int MOB_EQ;  //����������
int MOB_INV;  //���������
int MOB_DEATH;  //���������
int MOB_TATOO;  //����������
int MOB_SAVE;  //������
int MOB_FOLLOW;  //�������
int MOB_HELPED;  //���������-������
int MOB_DEST;  //����
int MOB_SCRIPT;  //������
int MOB_SHOP;  //�������
int MOB_SPECIAL; //��������
int MOB_LACKY;  //�����
int MOB_SPEED;  //��������
int MOB_LIKEWORK; //������
int MOB_GOD;  //���
int MOB_FRACTION; //�������
int MOB_RANG;           //����
int MOB_RANK;           //����
int MOB_HORSE;  //������
int MOB_SDEATH;  //������
int MOB_ALARM;  //����������
int MOB_POWER;  //��������
int MOB_BODY;  //����
int MOB_CLASSES; //���������
int MOB_AGE;  //������

// �������������� ���������
int MOB_CLASS_TYPE; //���������.�����
int MOB_CLASS_LEVEL; //���������.�������

int MOB_BODY_POSITION; //����.�������
int MOB_BODY_SNAME; //����.�����������
int MOB_BODY_NAME; //����.��������
int MOB_BODY_CHANCE; //����.���������
int MOB_BODY_KDAM; //����,���������

int MOB_SDT_CORPSE; //������.����
int MOB_SDT_SCRIPT; //������.��������
int MOB_SDT_DCHAR; //������.������
int MOB_SDT_DROOM;      //������.��������
int MOB_SDT_DAMAGE; //������.�����
int MOB_SDT_HIT; //������.�����
int MOB_SDT_TARGET; //������.����
int MOB_SDT_CHAR; //������.�����
int MOB_SDT_ROOM; //������.���������

int MOB_ADD_KEY; //�������������.����
int MOB_ADD_TEXT; //�������������.�����

int MOB_SPEC_TYPE; //��������.���
int MOB_SPEC_POS; //��������.���������
int MOB_SPEC_PERC; //��������.����
int MOB_SPEC_HIT; //��������.����������
int MOB_SPEC_SPELL; //��������.����������
int MOB_SPEC_POWER; //��������.��������
int MOB_SPEC_DAMAGE; //��������.����
int MOB_SPEC_VICTIM; //��������.������
int MOB_SPEC_ROOM; //��������.���������
int MOB_SPEC_SAVE; //��������.����������
int MOB_SPEC_PROP; //��������.��������

int MOB_SHOP_SELL; //�������.������� (int)
int MOB_SHOP_BUY; //�������.������� (int)
int MOB_SHOP_REPAIR; //�������.������ (int)
int MOB_SHOP_QUALITY; //�������.���������� (int)
int MOB_SHOP_TYPE; //�������.����� (list)
int MOB_SHOP_LIST; //�������.���� (list)
int MOB_SHOP_ANTI; //�������.������� (bitvector)

int MOB_ALARM_HELPER; //����������.���������
int MOB_ALARM_CHAR;   //����������.�����
int MOB_ALARM_ROOM;   //����������.�������
int MOB_ALARM_LEVEL;  //����������.�������

int MOB_PERIOD;  //�������������
int MOB_PRD_START; //������
int MOB_PRD_STOP; //�����
int MOB_PRD_TIME; //������
int MOB_PRD_TARGET; //����
int MOB_PRD_CHAR; //������
int MOB_PRD_ROOM; //�������

int MOB_WELCOME; //����������
int MOB_GOODBYE; //��������
int MOB_QUEST;  //�������
int MOB_QNUMBER; //�������.�����
int MOB_QNAME;  //�������.��������
int MOB_QEXPR;  //�������.�������
int MOB_QPRE;  //�������.�������
int MOB_QTEXT;  //�������.�����
int MOB_QCOMPLITE; //�������.����������
int MOB_QMULTY;  //�������.������������
int MOB_QREQUEST; //�������.�������
int MOB_QR_VAR;  //�������.�������.����������
int MOB_QRV_TITLE; //�������.��������.����������.�����������
int MOB_QRV_NAME; //�������.��������.����������.��������
int MOB_QRV_VALUE; //�������.��������.����������.��������
int MOB_QR_MOBILES;     //�������.��������.������
int MOB_QR_OBJECTS; //�������.��������.�������
int MOB_QR_FOLLOWERS; //�������.��������.�������������
int MOB_QACCEPT; //�������.������
int MOB_QDONE;  //�������.����������
int MOB_QSCRIPT;  //��������
int MOB_QSCR_NUMBER; //��������.�����
int MOB_QSCR_EXPR; //��������.�������
int MOB_QSCR_TEXT; //��������.�����
int MOB_QSCR_SCRIPT;  //��������.��������

//�����������
int MOB_COMMAND; //�����������
int MOB_COMMAND_NO; //�����������.�������
int MOB_COMMAND_ARG; //�����������.��������
int MOB_COMMAND_TOOL; //�����������.����������
int MOB_COMMAND_ACTIVE;
int MOB_COMMAND_ARG_OBJ; //�����������.��������.�������
int MOB_COMMAND_ARG_ARG; //�����������.��������.������
int MOB_COMMAND_ARG_MOB; //�����������.��������.������
int MOB_COMMAND_ARG_ERR; //�����������.��������.������
int MOB_COMMAND_SCRIPT; //�����������.��������
int MOB_COMMAND_EXTRACT; //�����������.����������
int MOB_COMMAND_LOAD;     //�����������.��������
int MOB_COMMAND_LOAD_ROOM; //�����������.��������.��������
int MOB_COMMAND_LOAD_CHAR; //�����������.��������.����������
int MOB_COMMAND_ACTIVE_ROOM;
int MOB_COMMAND_MESS_ROOM;
int MOB_COMMAND_MESS_CHAR;

//��������
int MOB_INTERCEPTION; //��������
int MOB_INT_COMMAND; // ��������.������� (LIST)
int MOB_INT_STOP; // ��������.���� (extern int)
int MOB_INT_MESSPLAYER; // ��������.����� (STRING)
int MOB_INT_MESSVICTIM; // ��������.������ (STRING)
int MOB_INT_MESSOTHER; // ��������.��������� (STRING)
int MOB_INT_MESSROOM; // ��������.������� (STRING)
int MOB_INT_SCRIPT; // ��������.�������� (STRING)
int MOB_INT_SARG; // ��������.��������� (STRING)

//�������
int MOB_EVENT;  //�������
int MOB_EVN_TYPE; //�������.���
int MOB_EVN_ARG; //�������.��������
int MOB_EVN_SCRIPT; //�������.��������

CMob::CMob() {
}

CMob::~CMob() {
}
///////////////////////////////////////////////////////////////////////////////

bool CMob::Initialization(void) {
    MOB_NUMBER = Proto->AddItem(TYPE_INT, "������");
    MOB_ALIAS = Proto->AddItem(TYPE_STRING, "��������");
    MOB_NAME = Proto->AddItem(TYPE_STRING, "���");
    MOB_LINE = Proto->AddItem(TYPE_STRING, "������");
    MOB_DESCRIPTION = Proto->AddItem(TYPE_STRING, "��������", false);
    MOB_ADDITION = Proto->AddItem(TYPE_STRUCT, "�������������", false);
    CItemProto *add = Proto->GetItem(MOB_ADDITION);
    MOB_ADD_KEY = add->AddItem(TYPE_STRING, "����");
    MOB_ADD_TEXT = add->AddItem(TYPE_STRING, "�����");
    MOB_PROPERTIES = Proto->AddItem(TYPE_VECTOR, "���������", false,
                                    ParserConst.GetVector(VEC_MOB_PROP));
    MOB_ADDONS = Proto->AddItem(TYPE_VECTOR, "�����������", false,
                                ParserConst.GetVector(VEC_MOB_ADDS));
    MOB_AFFECTS = Proto->AddItem(TYPE_VECTOR, "��������", false,
                                 ParserConst.GetVector(VEC_MOB_AFF));
    MOB_SEX = Proto->AddItem(TYPE_LIST, "���", true,
                             ParserConst.GetList(LIST_SEX));
    MOB_LEVEL =  Proto->AddItem(TYPE_INT, "�������", false);
    MOB_CLASS = Proto->AddItem(TYPE_LIST, "���������", false,
                               ParserConst.GetList(LIST_CLASS));

    MOB_CLASSES =  Proto->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *classes = Proto->GetItem(MOB_CLASSES);
    MOB_CLASS_TYPE = classes->AddItem(TYPE_LIST, "���", true,
                                      ParserConst.GetList(LIST_CLASS));
    MOB_CLASS_LEVEL = classes->AddItem(TYPE_INT, "�������", true);

    MOB_RACE = Proto->AddItem(TYPE_LIST, "����", true,
                              ParserConst.GetList(LIST_RACE));
    MOB_TYPE = Proto->AddItem(TYPE_LIST, "���", false,
                              ParserConst.GetList(LIST_MOB_TYPE));
    MOB_ALIGN =  Proto->AddItem(TYPE_INT, "����������");
    MOB_LAWS =  Proto->AddItem(TYPE_INT, "����������", false);
    MOB_EXP = Proto->AddItem(TYPE_INT, "����");
    MOB_LIMIT = Proto->AddItem(TYPE_INT, "������", false);
    MOB_HITPOINTS = Proto->AddItem(TYPE_RANDOM, "�����");
    MOB_AC = Proto->AddItem(TYPE_INT, "�����");
    MOB_HITROLL =  Proto->AddItem(TYPE_INT, "�����");
    MOB_HIT1 = Proto->AddItem(TYPE_LIST, "����1", true,
                              ParserConst.GetList(LIST_MOB_HIT));
    MOB_DAMAGE1 = Proto->AddItem(TYPE_RANDOM, "����1", true);
    MOB_COUNT1 = Proto->AddItem(TYPE_INT, "�����1");
    MOB_HIT2 = Proto->AddItem(TYPE_LIST, "����2", false,
                              ParserConst.GetList(LIST_MOB_HIT));
    MOB_DAMAGE2 = Proto->AddItem(TYPE_RANDOM, "����2", false);
    MOB_COUNT2 = Proto->AddItem(TYPE_INT, "�����2", false);
    MOB_STR = Proto->AddItem(TYPE_INT, "����");
    MOB_CON =  Proto->AddItem(TYPE_INT, "������������");
    MOB_DEX = Proto->AddItem(TYPE_INT, "��������");
    MOB_INT = Proto->AddItem(TYPE_INT, "�����");
    MOB_WIS = Proto->AddItem(TYPE_INT, "��������");
    MOB_CHA = Proto->AddItem(TYPE_INT, "�������");
    MOB_SIZE = Proto->AddItem(TYPE_INT, "������");
    MOB_HEIGHT =  Proto->AddItem(TYPE_INT, "����", false);
    MOB_WEIGHT =  Proto->AddItem(TYPE_INT, "���", false);
    MOB_POSITION = Proto->AddItem(TYPE_LIST, "���������", true,
                                  ParserConst.GetList(LIST_POSITIONS));
    MOB_AGE = Proto->AddItem(TYPE_LIST, "�������", false,
                             ParserConst.GetList(LIST_AGE));
    MOB_MOVED = Proto->AddItem(TYPE_LIST, "�����������", false,
                               ParserConst.GetList(LIST_MOB_MOVE));
    MOB_MOVESTR = Proto->AddItem(TYPE_STRING, "������������", false);
    MOB_GOLD = Proto->AddItem(TYPE_RANDOM, "������", false);
    MOB_WIMP = Proto->AddItem(TYPE_INT, "����", false);
    MOB_SKILL =  Proto->AddItem(TYPE_STRLIST, "������", false,
                                ParserConst.GetList(LIST_SKILLS));
    MOB_EQ = Proto->AddItem(TYPE_STRLIST, "����������", false,
                            ParserConst.GetList(LIST_EQ_POS));
    MOB_INV = Proto->AddItem(TYPE_STRLIST, "���������", false);
    MOB_DEATH = Proto->AddItem(TYPE_STRLIST, "���������", false);
    MOB_TATOO = Proto->AddItem(TYPE_STRLIST, "����������", false,
                               ParserConst.GetList(LIST_EQ_POS));
    MOB_SAVE = Proto->AddItem(TYPE_STRLIST, "������", false,
                              ParserConst.GetList(LIST_SAVE_TYPES));

    MOB_FOLLOW = Proto->AddItem(TYPE_INT, "�������", false);
    MOB_HELPED = Proto->AddItem(TYPE_SCRIPT, "������", false);
    MOB_DEST = Proto->AddItem(TYPE_SCRIPT, "����", false);
    MOB_SCRIPT = Proto->AddItem(TYPE_SCRIPT, "������", false);

    MOB_SHOP = Proto->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto * shop = Proto->GetItem(MOB_SHOP);
    MOB_SHOP_SELL = shop->AddItem(TYPE_INT, "�������", true);
    MOB_SHOP_BUY = shop->AddItem(TYPE_INT, "�������", true);
    MOB_SHOP_REPAIR = shop->AddItem(TYPE_INT, "������", true);
    MOB_SHOP_QUALITY = shop->AddItem(TYPE_INT, "����������", true);
    MOB_SHOP_TYPE = shop->AddItem(TYPE_STRLIST, "�����", true,
                                  ParserConst.GetList(LIST_OBJ_TYPES));
    MOB_SHOP_LIST = shop->AddItem(TYPE_SCRIPT, "������", false);
    MOB_SHOP_ANTI = shop->AddItem(TYPE_VECTOR, "�������", false,
                                  ParserConst.GetVector(VEC_ANTI));

    MOB_SPECIAL = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *spec = Proto->GetItem(MOB_SPECIAL);
    MOB_SPEC_TYPE = spec->AddItem(TYPE_LIST, "���", true,
                                  ParserConst.GetList(LIST_MOB_SPEC_TYPE));
    MOB_SPEC_POS = spec->AddItem(TYPE_STRLIST, "���������", false, ParserConst.GetList(LIST_POSITIONS));
    MOB_SPEC_PERC = spec->AddItem(TYPE_INT, "����", false);
    MOB_SPEC_HIT = spec->AddItem(TYPE_LIST, "����������", false,
                                 ParserConst.GetList(LIST_DAMAGE));
    MOB_SPEC_SPELL = spec->AddItem(TYPE_LIST, "����������", false,
                                   ParserConst.GetList(LIST_SPELLS));
    MOB_SPEC_POWER = spec->AddItem(TYPE_INT, "��������", false);
    MOB_SPEC_DAMAGE = spec->AddItem(TYPE_RANDOM, "����", false);
    MOB_SPEC_VICTIM = spec->AddItem(TYPE_STRING, "������", false);
    MOB_SPEC_ROOM = spec->AddItem(TYPE_STRING, "���������", false);
    MOB_SPEC_SAVE = spec->AddItem(TYPE_STRLIST, "����������", false, ParserConst.GetList(LIST_SAVE_TYPES));
    MOB_SPEC_PROP = spec->AddItem(TYPE_VECTOR, "��������", false, ParserConst.GetVector(VEC_MOB_SPEC));

    MOB_LACKY = Proto->AddItem(TYPE_INT, "�����", false);
    MOB_SPEED = Proto->AddItem(TYPE_INT, "��������", false);
    MOB_LIKEWORK = Proto->AddItem(TYPE_INT, "������", false);
    MOB_GOD   = Proto->AddItem(TYPE_LIST, "���", false,
                               ParserConst.GetList(LIST_GODS));
    MOB_FRACTION = Proto->AddItem(TYPE_LIST, "�������", false,
                                  ParserConst.GetList(LIST_FRACTION));
    MOB_RANG     = Proto->AddItem(TYPE_LIST, "����", false,
                                  ParserConst.GetList(LIST_RANK));

    MOB_RANK     = Proto->AddItem(TYPE_INT, "����", false);

    MOB_HORSE    = Proto->AddItem(TYPE_INT, "������", false);

    MOB_SDEATH   = Proto->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *sdt = Proto->GetItem(MOB_SDEATH);
    MOB_SDT_CORPSE = sdt->AddItem(TYPE_INT, "����", false);
    MOB_SDT_SCRIPT = sdt->AddItem(TYPE_INT, "��������", false);
    MOB_SDT_DCHAR  = sdt->AddItem(TYPE_STRING, "������", false);
    MOB_SDT_DROOM  = sdt->AddItem(TYPE_STRING, "��������", false);
    MOB_SDT_DAMAGE = sdt->AddItem(TYPE_LIST, "�����", false,
                                  ParserConst.GetList(LIST_DAMAGE));
    MOB_SDT_HIT    = sdt->AddItem(TYPE_RANDOM, "�����", false);
    MOB_SDT_TARGET = sdt->AddItem(TYPE_LIST, "����", false,
                                  ParserConst.GetList(LIST_TARGET));
    MOB_SDT_CHAR   = sdt->AddItem(TYPE_STRING, "�����", false);
    MOB_SDT_ROOM   = sdt->AddItem(TYPE_STRING, "���������", false);

    MOB_ALARM = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *alarm = Proto->GetItem(MOB_ALARM);
    MOB_ALARM_HELPER = alarm->AddItem(TYPE_SCRIPT, "���������");
    MOB_ALARM_CHAR   = alarm->AddItem(TYPE_STRING, "�����", false);
    MOB_ALARM_ROOM   = alarm->AddItem(TYPE_STRING, "�������", false);
    MOB_ALARM_LEVEL  = alarm->AddItem(TYPE_INT, "�����", false);
    MOB_POWER = Proto->AddItem(TYPE_INT, "��������", false);
    MOB_BODY = Proto->AddItem(TYPE_STRUCT, "����", false);
    CItemProto *body = Proto->GetItem(MOB_BODY);
    MOB_BODY_POSITION = body->AddItem(TYPE_LIST, "�������", true,
                                      ParserConst.GetList(LIST_BODY_POSITION));
    MOB_BODY_SNAME = body->AddItem(TYPE_LIST, "�����������", false, ParserConst.GetList(LIST_BODY_NAME));
    MOB_BODY_NAME = body->AddItem(TYPE_STRING, "��������", false);
    MOB_BODY_CHANCE = body->AddItem(TYPE_INT, "���������", true);
    MOB_BODY_KDAM = body->AddItem(TYPE_INT, "���������", false);

    MOB_PERIOD = Proto->AddItem(TYPE_STRUCT, "�������������", false);
    CItemProto *prd = Proto->GetItem(MOB_PERIOD);
    MOB_PRD_START = prd->AddItem(TYPE_INT, "������", false);
    MOB_PRD_STOP = prd->AddItem(TYPE_INT, "�����", false);
    MOB_PRD_TIME  = prd->AddItem(TYPE_INT, "������", false);
    MOB_PRD_TARGET = prd->AddItem(TYPE_LIST, "����", false, ParserConst.GetList(LIST_TARGET));
    MOB_PRD_CHAR = prd->AddItem(TYPE_STRING, "������", false);
    MOB_PRD_ROOM = prd->AddItem(TYPE_STRING, "�������", false);


    MOB_WELCOME = Proto->AddItem(TYPE_STRING, "����������", false);
    MOB_GOODBYE = Proto->AddItem(TYPE_STRING, "��������", false);
    MOB_QUEST = Proto->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *quest = Proto->GetItem(MOB_QUEST);
    MOB_QNUMBER = quest->AddItem(TYPE_INT, "�����", true);
    MOB_QNAME = quest->AddItem(TYPE_STRING, "��������", true);
    MOB_QEXPR = quest->AddItem(TYPE_EXPR, "�������", false);
    MOB_QPRE = quest->AddItem(TYPE_STRING, "�������", true);
    MOB_QTEXT = quest->AddItem(TYPE_STRING, "�����", true);
    MOB_QCOMPLITE = quest->AddItem(TYPE_STRING, "����������", false);
    MOB_QMULTY = quest->AddItem(TYPE_INT, "������������", false);
    MOB_QREQUEST = quest->AddItem(TYPE_STRUCT, "����������", true);
    CItemProto *request = quest->GetItem(MOB_QREQUEST);
    MOB_QR_VAR = request->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *rvar = request->GetItem(MOB_QR_VAR);
    MOB_QRV_TITLE = rvar->AddItem(TYPE_STRING, "�����������", false);
    MOB_QRV_NAME = rvar->AddItem(TYPE_STRING, "��������", false);
    MOB_QRV_VALUE = rvar->AddItem(TYPE_STRING, "��������", false);
    MOB_QR_MOBILES = request->AddItem(TYPE_STRLIST, "������", false);
    MOB_QR_OBJECTS = request->AddItem(TYPE_STRLIST, "�������", false);
    MOB_QR_FOLLOWERS = request->AddItem(TYPE_STRLIST, "�������������", false);
    MOB_QACCEPT = quest->AddItem(TYPE_INT, "������", false);
    MOB_QDONE = quest->AddItem(TYPE_INT, "����������", false);

    MOB_COMMAND  = Proto->AddItem(TYPE_STRUCT, "�����������", false);
    CItemProto *command = Proto->GetItem(MOB_COMMAND);
    MOB_COMMAND_NO = command->AddItem(TYPE_LIST, "�������", true, ParserConst.GetList(LIST_COMMANDS));
    MOB_COMMAND_ARG = command->AddItem(TYPE_STRUCT, "��������", false);
    MOB_COMMAND_TOOL = command->AddItem(TYPE_LIST, "����������", false, ParserConst.GetList(LIST_TOOLS));
    MOB_COMMAND_ACTIVE = command->AddItem(TYPE_STRING, "���������", false);
    MOB_COMMAND_ACTIVE_ROOM = command->AddItem(TYPE_STRING, "���������_�������", false);

    CItemProto *comarg = command->GetItem(MOB_COMMAND_ARG);
    MOB_COMMAND_ARG_OBJ = comarg->AddItem(TYPE_INT, "�������", false);
    MOB_COMMAND_ARG_ARG = comarg->AddItem(TYPE_STRING, "������", false);
    MOB_COMMAND_ARG_MOB = comarg->AddItem(TYPE_INT, "������", false);
    MOB_COMMAND_ARG_ERR = comarg->AddItem(TYPE_STRING, "������", false);
    MOB_COMMAND_SCRIPT = command->AddItem(TYPE_INT, "��������", false);
    MOB_COMMAND_EXTRACT = command->AddItem(TYPE_INT, "����������", false);
    MOB_COMMAND_LOAD = command->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *cload = command->GetItem(MOB_COMMAND_LOAD);
    MOB_COMMAND_LOAD_ROOM = cload->AddItem(TYPE_INT, "��������", false);
    MOB_COMMAND_LOAD_CHAR = cload->AddItem(TYPE_INT, "����������", false);
    MOB_COMMAND_MESS_CHAR = cload->AddItem(TYPE_STRING, "�����", false);
    MOB_COMMAND_MESS_ROOM = cload->AddItem(TYPE_STRING, "�������", false);


    MOB_INTERCEPTION = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *intercept = Proto->GetItem(MOB_INTERCEPTION);
    MOB_INT_COMMAND = intercept->AddItem(TYPE_LIST, "�������", true,
                                         ParserConst.GetList(LIST_COMMANDS));
    MOB_INT_STOP = intercept->AddItem(TYPE_INT, "����", false);
    MOB_INT_MESSPLAYER = intercept->AddItem(TYPE_STRING, "�����", false);
    MOB_INT_MESSVICTIM = intercept->AddItem(TYPE_STRING, "������", false);
    MOB_INT_MESSOTHER  = intercept->AddItem(TYPE_STRING, "���������", false);
    MOB_INT_MESSROOM   = intercept->AddItem(TYPE_STRING, "�������", false);
    MOB_INT_SCRIPT   = intercept->AddItem(TYPE_INT, "��������", false);
    MOB_INT_SARG   = intercept->AddItem(TYPE_STRING, "���������", false);


    MOB_QSCRIPT = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *qscript = Proto->GetItem(MOB_QSCRIPT);
    MOB_QSCR_NUMBER = qscript->AddItem(TYPE_INT, "�����", true);
    MOB_QSCR_EXPR   = qscript->AddItem(TYPE_EXPR, "�������", false);
    MOB_QSCR_TEXT   = qscript->AddItem(TYPE_STRING, "�����", true);
    MOB_QSCR_SCRIPT = qscript->AddItem(TYPE_INT, "��������", true);

    MOB_EVENT = Proto->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *evnt = Proto->GetItem(MOB_EVENT);
    MOB_EVN_TYPE = evnt->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_EVENTS));
    MOB_EVN_ARG = evnt->AddItem(TYPE_INT, "��������", true);
    MOB_EVN_SCRIPT = evnt->AddItem(TYPE_INT, "��������", true);

    return CheckInit();
};

CMob * Mob;

///////////////////////////////////////////////////////////////////////////////
