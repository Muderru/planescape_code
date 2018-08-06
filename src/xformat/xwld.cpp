/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xwld.h"
#include "parser_id.h"


///////////////////////////////////////////////////////////////////////////////
// ����������� �������� ����������
int WLD_NUMBER;  // �������
int WLD_ZONE;  //�������
int WLD_POD;  // �������
int WLD_NAME;  // ��������
int WLD_DESCRIPTION; // ��������
int WLD_DESCRIPTION_N; // �������� ����
int WLD_ADDITION; // �������������
int WLD_PROPERTIES; // ���������
int WLD_DISTRICT; // ���������
int WLD_INTERCEPTION; // ��������
int WLD_EXIT;  // �����
int WLD_DAMAGE;  // �����������
int WLD_TRAP;  // �������
int WLD_PORTAL;  // ������
int WLD_SCRIPT;  // ������
int WLD_MOBILE;  // ������
int WLD_OBJECT;  // �������
int WLD_MAP;  // �����
int WLD_FORCEDIR; // �������

// ����������� ��������������� ����������
int WLD_ADD_KEY; //�������������.����
int WLD_ADD_TEXT; //�������������.�����

int WLD_INT_COMMAND;  // ��������.������� (LIST)
int WLD_INT_STOP;  // ��������.���� (INT)
int WLD_INT_MESSPLAYER;  // ��������.����� (STRING)
int WLD_INT_MESSVICTIM;  // ��������.������ (STRING)
int WLD_INT_MESSOTHER;  // ��������.��������� (STRING)
int WLD_INT_MESSROOM;  // ��������.������� (STRING)
int WLD_INT_SCRIPT;  // ��������.�������� (INT)

int WLD_EXIT_DIRECTION;  // �����.����������� (LIST)
int WLD_EXIT_ROOMNUMBER; // �����.������� (INT)
int WLD_EXIT_DESCRIPTION; // �����.�������� (STRING)
int WLD_EXIT_NAME;  // �����.���  (LIST)
int WLD_EXIT_ALIAS;  // �����.������� (STRING)
int WLD_EXIT_KEY;  // �����.����  (INT)
int WLD_EXIT_PROPERTIES; // �����.�������� (VECTOR)
int WLD_EXIT_QUALITY;         // �����.��������
int WLD_EXIT_TRAP;  // �����.������� (INT)
int WLD_EXIT_TRAP_CHANCE; // �����.�������.���� (INT)
int WLD_EXIT_TRAP_TYPEDAMAGE; // �����.�������.�����  (LIST)
int WLD_EXIT_TRAP_FORCEDAMAGE; // �����.�������.�����  (RANDOM)
int WLD_EXIT_TRAP_SAVE;  // �����.�������.�������
int WLD_EXIT_TRAP_MESS_CHAR; // �����.�������.�����
int WLD_EXIT_TRAP_MESS_ROOM; // �����.�������.�������
int WLD_EXIT_TRAP_MESS_SCHAR; // �����.�������.������
int WLD_EXIT_TRAP_MESS_SROOM; // �����.�������.��������
int WLD_EXIT_TRAP_MESS_KCHAR; // �����.�������.����_�����
int WLD_EXIT_TRAP_MESS_KROOM; // �����.�������.����_�������
int WLD_EXIT_SEX;  // �����.���

int WLD_DAM_CHANCE;  //�����������.����
int WLD_DAM_TYPE;  //�����������.���
int WLD_DAM_TYPEDAMAGE;  //�����������.�����
int WLD_DAM_SAVE;  //�����������.�������
int WLD_DAM_FORCEDAMAGE; //�����������.�����
int WLD_DAM_MESS_CHAR;  //�����������.�����
int WLD_DAM_MESS_ROOM;  //�����������.�������
int WLD_DAM_MESS_SCHAR;  //�����������.������
int WLD_DAM_MESS_SROOM;  //�����������.��������

int WLD_TRAP_DIRECTION;  //�������.�����������
int WLD_TRAP_CHANCE;  //�������.����
int WLD_TRAP_TYPE;  //�������.���
int WLD_TRAP_TYPEDAMAGE; //�������.�����
int WLD_TRAP_SAVE;  //�������.�������
int WLD_TRAP_FORCEDAMAGE; //�������.�����
int WLD_TRAP_MESS_CHAR;  //�������.�����
int WLD_TRAP_MESS_ROOM;  //�������.���������
int WLD_TRAP_MESS_SCHAR; //�������.������
int WLD_TRAP_MESS_SROOM; //�������.����������
int WLD_TRAP_MESS_ACT_C; //�������.������
int WLD_TRAP_MESS_ACT_R; //�������.����������
int WLD_TRAP_MESS_KCHAR; //�������.����_�����
int WLD_TRAP_MESS_KROOM; //�������.����_�������

int WLD_PORTAL_DIRECTION; //������.�����������
int WLD_PORTAL_TYPE;  //������.���
int WLD_PORTAL_TIME;  //������.�����
int WLD_PORTAL_ROOM;  //������.�������
int WLD_PORTAL_KEY;  //������.����
int WLD_PORTAL_DESCRIPTION; //������.��������
int WLD_PORTAL_ACTIVE;  //������.��������
int WLD_PORTAL_DEACTIVE; //������.����������
int WLD_PORTAL_MESS_CHAR; //������.�����
int WLD_PORTAL_MESS_ROOM; //������.���������
int WLD_PORTAL_WORK_TIME; //������.�����_������

int WLD_HOTEL;                  //���������
int WLD_HOTEL_TYPE;             //���������.���
int WLD_HOTEL_MASTER;           //���������.������
int WLD_HOTEL_CHAR;             //���������.������
int WLD_HOTEL_ROOM;             //���������.�������
int WLD_HOTEL_RETURN;           //���������.��������

int WLD_FD_ROOM;  //�������.�������
int WLD_FD_DIR;   //�������.�����������
int WLD_FD_TIME;  //�������.�����
int WLD_FD_PERIOD;  //�������.������
int WLD_FD_DAMAGE;  //�������.�����������
int WLD_FD_DAM_TYPE;  //�������.�����������.���
int WLD_FD_DAM_FORCEDAMAGE; //�������.�����������.����
int WLD_FD_DAM_SAVETYPE; //�������.�����������.������
int WLD_FD_DAM_SAVE;  //�������.�����������.����������
int WLD_FD_MESS_MCHAR;  //�������.������_��������
int WLD_FD_MESS_MROOM;  //�������.������_�������
int WLD_FD_MESS_EXCHAR;  //�������.����_��������
int WLD_FD_MESS_EXROOM;  //�������.����_�������
int WLD_FD_MESS_ENCHAR;  //�������.������_��������
int WLD_FD_MESS_ENROOM;  //�������.������_�������
int WLD_FD_MESS_KCHAR;  //�������.����_��������
int WLD_FD_MESS_KROOM;  //�������.����_�������

int WLD_PERIOD;   //�������������
int WLD_PRD_START;  //�������������.������
int WLD_PRD_STOP;  //�������������.�����
int WLD_PRD_WEATHER;  //�������������.������
int WLD_PRD_OBJECT;  //�������������.�������
int WLD_PRD_MONSTER;  //�������������.������
int WLD_PRD_SRLOCATION;  //�������������.��������
int WLD_PRD_SPLOCATION;  //�������������.��������
int WLD_PRD_SRZONE;  //�������������.�����������
int WLD_PRD_SPZONE;  //�������������.�����������

CWld::CWld() {
}

CWld::~CWld() {
}
///////////////////////////////////////////////////////////////////////////////

bool CWld::Initialization(void) {

    WLD_NUMBER = Proto->AddItem(TYPE_INT, "�������");
    WLD_ZONE = Proto->AddItem(TYPE_INT, "�������", false);
    WLD_POD = Proto->AddItem(TYPE_STRING, "�������", false);
    WLD_NAME = Proto->AddItem(TYPE_STRING, "��������");
    WLD_DESCRIPTION = Proto->AddItem(TYPE_STRING, "��������");
    WLD_DESCRIPTION_N = Proto->AddItem(TYPE_STRING, "��������_����", false);
    WLD_ADDITION = Proto->AddItem(TYPE_STRUCT, "�������������", false);
    CItemProto *addition = Proto->GetItem(WLD_ADDITION);
    WLD_ADD_KEY = addition->AddItem(TYPE_STRING, "����");
    WLD_ADD_TEXT = addition->AddItem(TYPE_STRING, "�����");
    WLD_PROPERTIES = Proto->AddItem(TYPE_VECTOR, "���������", false,
                                    ParserConst.GetVector(VEC_PROP_ROOM));
    WLD_DISTRICT = Proto->AddItem(TYPE_LIST, "���������", true,
                                  ParserConst.GetList(LIST_DISTRICT_TYPES));
    WLD_INTERCEPTION = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *intercept = Proto->GetItem(WLD_INTERCEPTION);
    WLD_INT_COMMAND = intercept->AddItem(TYPE_LIST, "�������", true,
                                         ParserConst.GetList(LIST_COMMANDS));
    WLD_INT_STOP = intercept->AddItem(TYPE_LIST, "����", false,
                                      ParserConst.GetList(LIST_YESNO));
    WLD_INT_MESSPLAYER = intercept->AddItem(TYPE_STRING, "�����");
    WLD_INT_MESSVICTIM = intercept->AddItem(TYPE_STRING, "������", false);
    WLD_INT_MESSOTHER  = intercept->AddItem(TYPE_STRING, "���������", false);
    WLD_INT_MESSROOM   = intercept->AddItem(TYPE_STRING, "�������", false);
    WLD_INT_SCRIPT     = intercept->AddItem(TYPE_INT, "��������", false);
    WLD_EXIT = Proto->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *exit = Proto->GetItem(WLD_EXIT);
    WLD_EXIT_DIRECTION = exit->AddItem(TYPE_LIST, "�����������", true,
                                       ParserConst.GetList(LIST_DIRECTIONS));
    WLD_EXIT_ROOMNUMBER = exit->AddItem(TYPE_INT, "�������");
    WLD_EXIT_DESCRIPTION = exit->AddItem(TYPE_STRING, "��������", false);
    WLD_EXIT_NAME       = exit->AddItem(TYPE_STRING, "��������", false);
    WLD_EXIT_ALIAS = exit->AddItem(TYPE_STRING, "��������", false);
    WLD_EXIT_KEY = exit->AddItem(TYPE_INT, "����", false);
    WLD_EXIT_PROPERTIES = exit->AddItem(TYPE_VECTOR, "��������", false,
                                        ParserConst.GetVector(VEC_EXIT_PROP));
    WLD_EXIT_QUALITY   = exit->AddItem(TYPE_INT, "��������", false);
    WLD_EXIT_SEX      = exit->AddItem(TYPE_LIST, "���", false,
                                      ParserConst.GetList(LIST_SEX));
    WLD_EXIT_TRAP = exit->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *etrap = exit->GetItem(WLD_EXIT_TRAP);
    WLD_EXIT_TRAP_CHANCE = etrap->AddItem(TYPE_INT, "����");
    WLD_EXIT_TRAP_TYPEDAMAGE = etrap->AddItem(TYPE_LIST, "�����", true,
                               ParserConst.GetList(LIST_DAMAGE));
    WLD_EXIT_TRAP_FORCEDAMAGE = etrap->AddItem(TYPE_RANDOM, "�����");
    WLD_EXIT_TRAP_SAVE = etrap->AddItem(TYPE_INT, "�������", false);
    WLD_EXIT_TRAP_MESS_CHAR = etrap->AddItem(TYPE_STRING, "�����", false);
    WLD_EXIT_TRAP_MESS_ROOM = etrap->AddItem(TYPE_STRING, "���������", false);
    WLD_EXIT_TRAP_MESS_SCHAR = etrap->AddItem(TYPE_STRING, "������", false);
    WLD_EXIT_TRAP_MESS_SROOM = etrap->AddItem(TYPE_STRING, "����������", false);
    WLD_EXIT_TRAP_MESS_KCHAR = etrap->AddItem(TYPE_STRING, "����_�����", false);
    WLD_EXIT_TRAP_MESS_KROOM = etrap->AddItem(TYPE_STRING, "����_�������", false);

    WLD_DAMAGE = Proto->AddItem(TYPE_STRUCT, "�����������", false);
    CItemProto *damage = Proto->GetItem(WLD_DAMAGE);
    WLD_DAM_CHANCE = damage->AddItem(TYPE_INT, "����");
    WLD_DAM_TYPE = damage->AddItem(TYPE_VECTOR, "���", false,
                                   ParserConst.GetVector(VEC_TRAP_TYPE));
    WLD_DAM_TYPEDAMAGE = damage->AddItem(TYPE_LIST, "�����", true,
                                         ParserConst.GetList(LIST_DAMAGE));
    WLD_DAM_SAVE = damage->AddItem(TYPE_INT, "�������", false);
    WLD_DAM_FORCEDAMAGE = damage->AddItem(TYPE_RANDOM, "�����");
    WLD_DAM_MESS_CHAR = damage->AddItem(TYPE_STRING, "�����");
    WLD_DAM_MESS_ROOM = damage->AddItem(TYPE_STRING, "���������");
    WLD_DAM_MESS_SCHAR = damage->AddItem(TYPE_STRING, "������");
    WLD_DAM_MESS_SROOM = damage->AddItem(TYPE_STRING, "����������");
    WLD_TRAP = Proto->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *trap = Proto->GetItem(WLD_TRAP);
    WLD_TRAP_DIRECTION = trap->AddItem(TYPE_LIST, "�����������", true,
                                       ParserConst.GetList(LIST_DIRECTIONS));
    WLD_TRAP_CHANCE = trap->AddItem(TYPE_INT, "����");
    WLD_TRAP_TYPE = trap->AddItem(TYPE_LIST, "���", true,
                                  ParserConst.GetList(LIST_TRAP_TYPE));
    WLD_TRAP_TYPEDAMAGE = trap->AddItem(TYPE_LIST, "�����", true,
                                        ParserConst.GetList(LIST_DAMAGE));
    WLD_TRAP_SAVE = trap->AddItem(TYPE_INT, "�������", false);
    WLD_TRAP_FORCEDAMAGE = trap->AddItem(TYPE_RANDOM, "�����");
    WLD_TRAP_MESS_CHAR = trap->AddItem(TYPE_STRING, "�����");
    WLD_TRAP_MESS_ROOM = trap->AddItem(TYPE_STRING, "���������");
    WLD_TRAP_MESS_SCHAR = trap->AddItem(TYPE_STRING, "������", false);
    WLD_TRAP_MESS_SROOM = trap->AddItem(TYPE_STRING, "����������", false);
    WLD_TRAP_MESS_ACT_C = trap->AddItem(TYPE_STRING, "������", false);
    WLD_TRAP_MESS_ACT_R = trap->AddItem(TYPE_STRING, "����������", false);
    WLD_TRAP_MESS_KCHAR = trap->AddItem(TYPE_STRING, "����_�����", false);
    WLD_TRAP_MESS_KROOM = trap->AddItem(TYPE_STRING, "����_�������", false);


    WLD_PORTAL = Proto->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *portal = Proto->GetItem(WLD_PORTAL);
    WLD_PORTAL_DIRECTION = portal->AddItem(TYPE_LIST, "�����������", true,
                                           ParserConst.GetList(LIST_DIRECTIONS));
    WLD_PORTAL_TYPE = portal->AddItem(TYPE_LIST, "���", true,
                                      ParserConst.GetList(LIST_PORTAL_TYPES));
    WLD_PORTAL_TIME = portal->AddItem(TYPE_INT, "�����", false);
    WLD_PORTAL_ROOM = portal->AddItem(TYPE_INT, "�������");
    WLD_PORTAL_KEY = portal->AddItem(TYPE_INT, "����");
    WLD_PORTAL_DESCRIPTION = portal->AddItem(TYPE_STRING, "������");
    WLD_PORTAL_ACTIVE = portal->AddItem(TYPE_STRING, "��������");
    WLD_PORTAL_DEACTIVE = portal->AddItem(TYPE_STRING, "����������");
    WLD_PORTAL_MESS_CHAR = portal->AddItem(TYPE_STRING, "�����");
    WLD_PORTAL_MESS_ROOM = portal->AddItem(TYPE_STRING, "���������");
    WLD_PORTAL_WORK_TIME = portal->AddItem(TYPE_STRING, "�����_������", false);
    WLD_SCRIPT = Proto->AddItem(TYPE_SCRIPT, "������", false);
    WLD_MOBILE = Proto->AddItem(TYPE_STRLIST, "������", false);
    WLD_OBJECT = Proto->AddItem(TYPE_STRLIST, "�������", false);
    WLD_MAP    = Proto->AddItem(TYPE_INT, "�����", false);

    WLD_HOTEL = Proto->AddItem(TYPE_STRUCT, "���������", false);
    CItemProto *hotel = Proto->GetItem(WLD_HOTEL);
    WLD_HOTEL_TYPE   = hotel->AddItem(TYPE_INT, "���", true);
    WLD_HOTEL_MASTER = hotel->AddItem(TYPE_INT, "������", false);
    WLD_HOTEL_CHAR   = hotel->AddItem(TYPE_STRING, "������", false);
    WLD_HOTEL_ROOM   = hotel->AddItem(TYPE_STRING, "�������", false);
    WLD_HOTEL_RETURN = hotel->AddItem(TYPE_STRING, "��������", false);

    WLD_FORCEDIR = Proto->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *fd = Proto->GetItem(WLD_FORCEDIR);
    WLD_FD_ROOM = fd->AddItem(TYPE_INT, "�������", false);
    WLD_FD_DIR = fd->AddItem(TYPE_LIST, "�����������", false, ParserConst.GetList(LIST_DIRECTIONS));
    WLD_FD_TIME = fd->AddItem(TYPE_STRING, "�����", false);
    WLD_FD_PERIOD = fd->AddItem(TYPE_INT, "�������������", false);
    WLD_FD_DAMAGE = fd->AddItem(TYPE_STRUCT, "�����������", false);
    CItemProto *fdam = fd->GetItem(WLD_FD_DAMAGE);
    WLD_FD_DAM_TYPE = fdam->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_DAMAGE));
    WLD_FD_DAM_FORCEDAMAGE = fdam->AddItem(TYPE_RANDOM, "����", false);
    WLD_FD_DAM_SAVETYPE = fdam->AddItem(TYPE_LIST, "������", true, ParserConst.GetList(LIST_SAVE_TYPES));
    WLD_FD_DAM_SAVE = fdam->AddItem(TYPE_INT, "����������");
    WLD_FD_MESS_MCHAR = fd->AddItem(TYPE_STRING, "������_��������", false);
    WLD_FD_MESS_MROOM = fd->AddItem(TYPE_STRING, "������_�������", false);
    WLD_FD_MESS_EXCHAR = fd->AddItem(TYPE_STRING, "����_��������", false);
    WLD_FD_MESS_EXROOM = fd->AddItem(TYPE_STRING, "����_�������", false);
    WLD_FD_MESS_ENCHAR = fd->AddItem(TYPE_STRING, "������_��������", false);
    WLD_FD_MESS_ENROOM = fd->AddItem(TYPE_STRING, "������_�������", false);
    WLD_FD_MESS_KCHAR = fd->AddItem(TYPE_STRING, "����_��������", false);
    WLD_FD_MESS_KROOM = fd->AddItem(TYPE_STRING, "����_�������", false);

    WLD_PERIOD = Proto->AddItem(TYPE_STRUCT, "�������������", false);
    CItemProto *prd = Proto->GetItem(WLD_PERIOD);
    WLD_PRD_START = prd->AddItem(TYPE_INT, "������", false);
    WLD_PRD_STOP = prd->AddItem(TYPE_INT, "�����", false);
    WLD_PRD_WEATHER = prd->AddItem(TYPE_LIST, "������", false, ParserConst.GetList(LIST_WEATHER));
    WLD_PRD_OBJECT = prd->AddItem(TYPE_INT, "�������", false);
    WLD_PRD_MONSTER = prd->AddItem(TYPE_INT, "������", false);
    WLD_PRD_SRLOCATION = prd->AddItem(TYPE_STRING, "��������", false);
    WLD_PRD_SPLOCATION = prd->AddItem(TYPE_STRING, "��������", false);
    WLD_PRD_SRZONE = prd->AddItem(TYPE_STRING, "�����������", false);
    WLD_PRD_SPZONE = prd->AddItem(TYPE_STRING, "�����������", false);

    return CheckInit();
}
CWld * Wld;


///////////////////////////////////////////////////////////////////////////////
//world loot ������� (/lib/misc/world_loot)
int WRL_LOOT;   //�������
int WRL_RACE;   //�������.���� LIST(14)
int WRL_TYPE;   //��� LIST(49)
int WRL_LEVEL;   //������� STRING
int WRL_SEX;   //��� LIST(11)
int WRL_CLASS;   //����� STRLIST(13)
int WRL_GOD;   //��� LIST(28)
int WRL_AGE;   //������� STRLIST(52)
int WRL_OBJECT;   //������� INT
int WRL_SHANCE;   //���� INT (1...1000)

CWlt::CWlt() {
}

CWlt::~CWlt() {
}
///////////////////////////////////////////////////////////////////////////////

bool CWlt::Initialization(void) {

    WRL_LOOT = Proto->AddItem(TYPE_INT, "�������");
    WRL_RACE  = Proto->AddItem(TYPE_LIST, "����", false, ParserConst.GetList(LIST_RACE));
    WRL_TYPE = Proto->AddItem(TYPE_LIST, "���", false, ParserConst.GetList(LIST_MOB_TYPE));
    WRL_LEVEL = Proto->AddItem(TYPE_STRING, "�������", true);
    WRL_SEX = Proto->AddItem(TYPE_LIST, "���", false, ParserConst.GetList(LIST_SEX));
    WRL_CLASS = Proto->AddItem(TYPE_STRLIST, "�����", false, ParserConst.GetList(LIST_CLASS));
    WRL_GOD = Proto->AddItem(TYPE_LIST, "���", false, ParserConst.GetList(LIST_GODS));
    WRL_AGE = Proto->AddItem(TYPE_LIST, "�������", false, ParserConst.GetList(LIST_AGE));
    WRL_OBJECT = Proto->AddItem(TYPE_INT, "�������", true);
    WRL_SHANCE = Proto->AddItem(TYPE_INT, "����", true);
    return CheckInit();
}

CWlt Wlt;

