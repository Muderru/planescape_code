#include "xscripts.h"
#include "parser_id.h"
#include "strlib.h"
#include "expr.h"

// ����������� �������� ����������
int SCR_NUMBER;  //��������
int SCR_EXPR;  //�������
int SCR_MESSAGE; //���������
int SCR_MVNUM;  //���������.���
int SCR_MCHAR;  //���������.������
int SCR_MROOM;  //���������.�������
int SCR_MZONE;  //���������.�������
int SCR_ERROR;  //������
int SCR_ECHAR;  //������.������
int SCR_EROOM;  //������.�������
int SCR_EZONE;  //������.�������
int SCR_ESCRIPT; //������.��������
int SCR_LOAD;  //��������
int SCR_LOBJ;  //��������.�������
int SCR_LEQ;  //��������.���������
int SCR_LRANDOM; //��������.���������
int SCR_LMOB;  //��������.������
int SCR_LEXIT;  //��������.�����
int SCR_LPORTAL; //��������.������
int SCR_LCHAR;  //��������.������
int SCR_LROOM;  //��������.�������
int SCR_LGOLD;  //��������.������
int SCR_OBJ_LIMIT; //��������.�����

int SCR_LE_ROOM; // �����.�������
int SCR_LE_DIRECTION; // �����.����������� (LIST)
int SCR_LE_ROOMNUMBER; // �����.������� (INT)
int SCR_LE_DESCRIPTION; // �����.�������� (STRING)
int SCR_LE_NAME;  // �����.���  (LIST)
int SCR_LE_ALIAS; // �����.������� (STRING)
int SCR_LE_KEY;  // �����.����  (INT)
int SCR_LE_PROPERTIES; // �����.�������� (VECTOR)
int SCR_LE_QUALITY; // �����.��������
int SCR_LE_TRAP;  // �����.������� (INT)
int SCR_LE_TRAP_CHANCE; // �����.�������.���� (INT)
int SCR_LE_TRAP_TYPEDAMAGE; // �����.�������.�����  (LIST)
int SCR_LE_TRAP_FORCEDAMAGE; // �����.�������.�����  (RANDOM)
int SCR_LE_TRAP_SAVE;  // �����.�������.�������
int SCR_LE_TRAP_MESS_CHAR; // �����.�������.�����
int SCR_LE_TRAP_MESS_ROOM; // �����.�������.�������
int SCR_LE_TRAP_MESS_SCHAR; // �����.�������.������
int SCR_LE_TRAP_MESS_SROOM; // �����.�������.��������
int SCR_LE_TRAP_MESS_KCHAR; // �����.�������.����_�����
int SCR_LE_TRAP_MESS_KROOM; // �����.�������.����_�������
int SCR_LE_SEX;  // �����.���

int SCR_LP_PORTAL; //������
int SCR_LP_ROOM;  //������.���
int SCR_LP_DIRECTION; //������.�����������
int SCR_LP_TYPE;  //������.���
int SCR_LP_TIME;  //������.�����
int SCR_LP_ROOMNUMBER;  //������.�������
int SCR_LP_KEY;  //������.����
int SCR_LP_DESCRIPTION; //������.��������
int SCR_LP_ACTIVE;  //������.��������
int SCR_LP_DEACTIVE; //������.����������
int SCR_LP_MESS_CHAR; //������.�����
int SCR_LP_MESS_ROOM; //������.���������
int SCR_LP_WORK_TIME; //������.�����_������

int SCR_DELETE;  //��������
int SCR_DOBJ;  //��������.�������
int SCR_DEQ;  //��������.���������
int SCR_DMOB;  //��������.������
int SCR_DGOLD;  //��������.������
int SCR_DEXIT;  //��������.�����
int SCR_DE_ROOM;  //�����,���
int SCR_DE_DIRECTION; //�����.�����������
int SCR_DPORTAL;  //��������.������
int SCR_DP_ROOM;  //������.���
int SCR_DP_DIRECTION; //������.�����������
int SCR_DCHAR;  //��������.�����
int SCR_DROOM;  //��������.���������

int SCR_SPELL;  //����������
int SCR_SPELL_NO; //����������.�����
int SCR_SPELL_LEVEL; //����������.�������
int SCR_SPELL_MCHAR; //����������.�����
int SCR_SPELL_MROOM; //����������.�������

int SCR_TELEPORT; //�����������
int SCR_TWHERE;  //���
int SCR_TROOM;  //�������
int SCR_TCHAROUT; //��������
int SCR_TCHARIN; //���������
int SCR_TROOMOUT; //��������
int SCR_TROOMIN; //���������


int SCR_VAR;  //����������
int SCR_VAR_NAME; //����������.��������
int SCR_VAR_VALUE; //����������.��������
int SCR_VAR_TIME; //����������.�����

int SCR_GLB;  //����������
int SCR_GLB_NAME; //����������.��������
int SCR_GLB_VALUE; //����������.��������
int SCR_GLB_TIME; //����������.�����

int SCR_RESET;  //�����

int SCR_AGRO;  //��������
int SCR_AMOB;  //��������.������
int SCR_ATARGET; //��������.����

int SCR_DAMAGE;    //����
int SCR_DAM_TARGET; //����.����
int SCR_DAM_SHANCE; //����.����
int SCR_DAM_TYPE;   //����.�����
int SCR_DAM_DAMAGE; //����.�����
int SCR_DAM_STYPE;  //����.������
int SCR_DAM_SAVE;   //����.����������
int SCR_DAM_KVICT;  //����.�������
int SCR_DAM_KROOM;  //����.��������
int SCR_DAM_HVICT;  //����.�������
int SCR_DAM_HROOM;  //����.��������
int SCR_DAM_MVICT;  //����.�������
int SCR_DAM_MROOM;  //����.��������

int SCR_EXP; //����
int SCR_EXP_TYPE; //���
int SCR_EXP_SCHAR; //������������
int SCR_EXP_SGROUP; //������������
int SCR_EXP_CHAR; //������
int SCR_EXP_GROUP; //������

int SCR_APPLY; //�����������

int SCR_CONTINUE; //�����������
int SCR_CNT_VNUM; //�����������.�����
int SCR_CNT_TIMER; //�����������.������


///////////////////////////////////////////////////////////////////////////////
CScr::CScr() {
}

CScr::~CScr() {
}
///////////////////////////////////////////////////////////////////////////////

CScr Scr;

bool CScr::Initialization(void) {
    SCR_NUMBER = Proto->AddItem(TYPE_INT, "��������");
    SCR_EXPR = Proto->AddItem(TYPE_EXPR, "�������", false);
    SCR_MESSAGE = Proto->AddItem(TYPE_STRUCT, "���������", false);
    CItemProto *mess = Proto->GetItem(SCR_MESSAGE);
    SCR_MVNUM = mess->AddItem(TYPE_INT, "���", false);
    SCR_MCHAR  = mess->AddItem(TYPE_STRING, "������", false);
    SCR_MROOM  = mess->AddItem(TYPE_STRING, "�������", false);
    SCR_MZONE  = mess->AddItem(TYPE_STRING, "�������", false);
    SCR_ERROR = Proto->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *error = Proto->GetItem(SCR_ERROR);
    SCR_ECHAR  = error->AddItem(TYPE_STRING, "������", false);
    SCR_EROOM  = error->AddItem(TYPE_STRING, "�������", false);
    SCR_EZONE  = error->AddItem(TYPE_STRING, "�������", false);
    SCR_ESCRIPT = error->AddItem(TYPE_INT, "��������", false);
    SCR_LOAD = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *load = Proto->GetItem(SCR_LOAD);
    SCR_LOBJ = load->AddItem(TYPE_STRLIST, "�������", false);
    SCR_LEQ = load->AddItem(TYPE_SCRIPT, "���������", false);
    SCR_LRANDOM = load->AddItem(TYPE_SCRIPT, "���������", false);
    SCR_LMOB = load->AddItem(TYPE_STRLIST, "������", false);
    SCR_OBJ_LIMIT = load->AddItem(TYPE_INT, "�����", false);
    SCR_LGOLD = load->AddItem(TYPE_INT, "������", false);
    SCR_LEXIT = load->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *exit = load->GetItem(SCR_LEXIT);
    SCR_LE_ROOM = exit->AddItem(TYPE_INT, "���", true);
    SCR_LE_DIRECTION = exit->AddItem(TYPE_LIST, "�����������", true,
                                     ParserConst.GetList(LIST_DIRECTIONS));
    SCR_LE_ROOMNUMBER = exit->AddItem(TYPE_INT, "�������");
    SCR_LE_DESCRIPTION = exit->AddItem(TYPE_STRING, "��������", false);
    SCR_LE_NAME       = exit->AddItem(TYPE_STRING, "��������", false);
    SCR_LE_ALIAS = exit->AddItem(TYPE_STRING, "��������", false);
    SCR_LE_KEY = exit->AddItem(TYPE_INT, "����", false);
    SCR_LE_PROPERTIES = exit->AddItem(TYPE_VECTOR, "��������", false,
                                      ParserConst.GetVector(VEC_EXIT_PROP));
    SCR_LE_QUALITY   = exit->AddItem(TYPE_INT, "��������", false);
    SCR_LE_SEX      = exit->AddItem(TYPE_LIST, "���", false,
                                    ParserConst.GetList(LIST_SEX));
    SCR_LE_TRAP = exit->AddItem(TYPE_STRUCT, "�������", false);
    CItemProto *etrap = exit->GetItem(SCR_LE_TRAP);
    SCR_LE_TRAP_CHANCE = etrap->AddItem(TYPE_INT, "����");
    SCR_LE_TRAP_TYPEDAMAGE = etrap->AddItem(TYPE_LIST, "�����", true,
                                            ParserConst.GetList(LIST_DAMAGE));
    SCR_LE_TRAP_FORCEDAMAGE = etrap->AddItem(TYPE_RANDOM, "�����");
    SCR_LE_TRAP_SAVE = etrap->AddItem(TYPE_INT, "�������", false);
    SCR_LE_TRAP_MESS_CHAR = etrap->AddItem(TYPE_STRING, "�����", false);
    SCR_LE_TRAP_MESS_ROOM = etrap->AddItem(TYPE_STRING, "���������", false);
    SCR_LE_TRAP_MESS_SCHAR = etrap->AddItem(TYPE_STRING, "������", false);
    SCR_LE_TRAP_MESS_SROOM = etrap->AddItem(TYPE_STRING, "����������", false);
    SCR_LE_TRAP_MESS_KCHAR = etrap->AddItem(TYPE_STRING, "����_�����", false);
    SCR_LE_TRAP_MESS_KROOM = etrap->AddItem(TYPE_STRING, "����_�������", false);

    SCR_LPORTAL = load->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *portal = load->GetItem(SCR_LPORTAL);
    SCR_LP_ROOM = portal->AddItem(TYPE_INT, "���", true);
    SCR_LP_DIRECTION = portal->AddItem(TYPE_LIST, "�����������", true,
                                       ParserConst.GetList(LIST_DIRECTIONS));
    SCR_LP_TYPE = portal->AddItem(TYPE_LIST, "���", true,
                                  ParserConst.GetList(LIST_PORTAL_TYPES));
    SCR_LP_TIME = portal->AddItem(TYPE_INT, "�����", false);
    SCR_LP_ROOMNUMBER = portal->AddItem(TYPE_INT, "�������");
    SCR_LP_KEY = portal->AddItem(TYPE_INT, "����");
    SCR_LP_DESCRIPTION = portal->AddItem(TYPE_STRING, "������");
    SCR_LP_ACTIVE = portal->AddItem(TYPE_STRING, "��������");
    SCR_LP_DEACTIVE = portal->AddItem(TYPE_STRING, "����������");
    SCR_LP_MESS_CHAR = portal->AddItem(TYPE_STRING, "�����");
    SCR_LP_MESS_ROOM = portal->AddItem(TYPE_STRING, "���������");
    SCR_LP_WORK_TIME = portal->AddItem(TYPE_STRING, "�����_������", false);

    SCR_LCHAR = load->AddItem(TYPE_STRING, "������", false);
    SCR_LROOM = load->AddItem(TYPE_STRING, "�������", false);


    SCR_DELETE = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *delt = Proto->GetItem(SCR_DELETE);
    SCR_DOBJ = delt->AddItem(TYPE_STRLIST, "�������", false);
    SCR_DEQ = delt->AddItem(TYPE_STRLIST, "���������", false);
    SCR_DMOB = delt->AddItem(TYPE_STRLIST, "������", false);
    SCR_DGOLD = delt->AddItem(TYPE_INT, "������", false);
    SCR_DEXIT = delt->AddItem(TYPE_STRUCT, "�����", false);
    CItemProto *dexit = delt->GetItem(SCR_DEXIT);
    SCR_DE_ROOM = dexit->AddItem(TYPE_INT, "���", true);
    SCR_DE_DIRECTION = dexit->AddItem(TYPE_LIST, "�����������", true, ParserConst.GetList(LIST_DIRECTIONS));

    SCR_DPORTAL = delt->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *dportal = delt->GetItem(SCR_DPORTAL);
    SCR_DP_ROOM = dportal->AddItem(TYPE_INT, "���", true);
    SCR_DP_DIRECTION = dportal->AddItem(TYPE_LIST, "�����������", true, ParserConst.GetList(LIST_DIRECTIONS));

    SCR_DCHAR = delt->AddItem(TYPE_STRING, "������", false);
    SCR_DROOM = delt->AddItem(TYPE_STRING, "�������", false);

    SCR_SPELL = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *spell = Proto->GetItem(SCR_SPELL);
    SCR_SPELL_NO = spell->AddItem(TYPE_LIST, "�����", false, ParserConst.GetList(LIST_SPELLS));
    SCR_SPELL_LEVEL = spell->AddItem(TYPE_INT, "�������", false);
    SCR_SPELL_MCHAR = spell->AddItem(TYPE_STRING, "������", false);
    SCR_SPELL_MROOM = spell->AddItem(TYPE_STRING, "�������", false);

    SCR_TELEPORT = Proto->AddItem(TYPE_STRUCT, "�����������", false);
    CItemProto *telep = Proto->GetItem(SCR_TELEPORT);
    SCR_TROOM = telep->AddItem(TYPE_INT, "�������", true);
    SCR_TWHERE = telep->AddItem(TYPE_INT, "���", false);
    SCR_TCHAROUT = telep->AddItem(TYPE_STRING, "��������", false);
    SCR_TCHARIN  = telep->AddItem(TYPE_STRING, "���������", false);
    SCR_TROOMOUT  = telep->AddItem(TYPE_STRING, "��������", false);
    SCR_TROOMIN   = telep->AddItem(TYPE_STRING, "���������", false);

    SCR_VAR = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *var = Proto->GetItem(SCR_VAR);
    SCR_VAR_NAME = var->AddItem(TYPE_STRING, "��������", true);
    SCR_VAR_VALUE = var->AddItem(TYPE_STRING, "��������", true);
    SCR_VAR_TIME = var->AddItem(TYPE_INT, "�����", false);

    SCR_GLB = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *glb = Proto->GetItem(SCR_GLB);
    SCR_GLB_NAME = glb->AddItem(TYPE_STRING, "��������", true);
    SCR_GLB_VALUE = glb->AddItem(TYPE_STRING, "��������", true);
    SCR_GLB_TIME = glb->AddItem(TYPE_INT, "�����", false);

    SCR_RESET = Proto->AddItem(TYPE_INT, "�����", false);

    SCR_AGRO = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *agro = Proto->GetItem(SCR_AGRO);
    SCR_AMOB = agro->AddItem(TYPE_INT, "������", true);
    SCR_ATARGET = agro->AddItem(TYPE_LIST, "����", false, ParserConst.GetList(LIST_TARGET));

    SCR_DAMAGE = Proto->AddItem(TYPE_STRUCT, "����", false);
    CItemProto *damage = Proto->GetItem(SCR_DAMAGE);
    SCR_DAM_TARGET = damage->AddItem(TYPE_LIST, "����", false, ParserConst.GetList(LIST_TARGET));
    SCR_DAM_SHANCE = damage->AddItem(TYPE_INT, "����", true);
    SCR_DAM_TYPE   = damage->AddItem(TYPE_LIST, "�����", true, ParserConst.GetList(LIST_DAMAGE));
    SCR_DAM_DAMAGE = damage->AddItem(TYPE_STRING, "�����", true);
    SCR_DAM_STYPE  = damage->AddItem(TYPE_LIST, "������", true, ParserConst.GetList(LIST_SAVE_TYPES));
    SCR_DAM_SAVE   = damage->AddItem(TYPE_INT, "����������", false);
    SCR_DAM_KVICT  = damage->AddItem(TYPE_STRING, "�������", false);
    SCR_DAM_KROOM  = damage->AddItem(TYPE_STRING, "��������", false);
    SCR_DAM_HVICT  = damage->AddItem(TYPE_STRING, "�������", false);
    SCR_DAM_HROOM  = damage->AddItem(TYPE_STRING, "��������", false);
    SCR_DAM_MVICT  = damage->AddItem(TYPE_STRING, "�������", false);
    SCR_DAM_MROOM  = damage->AddItem(TYPE_STRING, "��������", false);

    SCR_EXP = Proto->AddItem(TYPE_STRUCT, "����", false);
    CItemProto *exp = Proto->GetItem(SCR_EXP);
    SCR_EXP_TYPE = exp->AddItem(TYPE_LIST, "���", false, ParserConst.GetList(LIST_EXP_TYPE));
    SCR_EXP_SCHAR = exp->AddItem(TYPE_INT, "������������", false);
    SCR_EXP_SGROUP = exp->AddItem(TYPE_INT, "������������", false);
    SCR_EXP_CHAR = exp->AddItem(TYPE_INT, "������", false);
    SCR_EXP_GROUP = exp->AddItem(TYPE_INT, "������", false);

    SCR_APPLY = Proto->AddItem(TYPE_STRLIST, "�������", false, ParserConst.GetList(LIST_APPLY));

    SCR_CONTINUE = Proto->AddItem(TYPE_STRUCT, "�����������", false);
    CItemProto *next = Proto->GetItem(SCR_CONTINUE);
    SCR_CNT_VNUM = next->AddItem(TYPE_INT, "�����", true);
    SCR_CNT_TIMER = next->AddItem(TYPE_INT, "������", false);

    return CheckInit();
}

