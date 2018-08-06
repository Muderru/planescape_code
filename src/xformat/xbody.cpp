/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xbody.h"
#include "parser_id.h"

// ����������� �������� ����������
int TBD_RACE;  //����
int TBD_HEALTH;
int TBD_BODY;  //����
int TBD_BODY_POSITION; //����.�������
int TBD_BODY_SNAME; //����.�����������
int TBD_BODY_NAME; //����.��������
int TBD_BODY_CHANCE; //����.���������
int TBD_BODY_KDAM; //����.���������
int TBD_AC; //����.�����
int TBD_ARM0; //����.��������
int TBD_ARM1; //����.��������
int TBD_ARM2; //����.��������
int TBD_FIRE;
int TBD_COLD;
int TBD_ELECTRO;
int TBD_ACID;
int TBD_POISON;
int TBD_XAOS;
int TBD_ORDER;
int TBD_POSITIVE;
int TBD_NEGATIVE;

int TCL_CLASS;  //���������
int TCL_ADDSTR;  //���������� ����
int TCL_ADDCON;
int TCL_ADDDEX;
int TCL_ADDINT;
int TCL_ADDWIS;
int TCL_ADDCHA;  //���������� �������
int TCL_HEALTH;
int TCL_MANA;
int TCL_KFORT;
int TCL_KREFL;
int TCL_KWILL;
int TCL_HROLL;
int TCL_AC;
int TCL_ARM0;
int TCL_ARM1;
int TCL_ARM2;


int TBD_BODY_WEAPON; //������
int TBD_BWP_NAME; //������.��������
int TBD_BWP_SEX;  //������.���


///////////////////////////////////////////////////////////////////////////////
CBody::CBody() {
}

CBody::~CBody() {
}

CProf::CProf() {
}

CProf::~CProf() {
}

///////////////////////////////////////////////////////////////////////////////

CBody tBody;
CProf tProf;

bool CBody::Initialization(void) {

    TBD_RACE = Proto->AddItem(TYPE_LIST, "����", true, ParserConst.GetList(LIST_RACE));
    TBD_AC = Proto->AddItem(TYPE_FLOAT, "�����", false);
    TBD_ARM0 = Proto->AddItem(TYPE_FLOAT, "��������", false);
    TBD_ARM1 = Proto->AddItem(TYPE_FLOAT, "��������", false);
    TBD_ARM2 = Proto->AddItem(TYPE_FLOAT, "��������", false);
    TBD_FIRE = Proto->AddItem(TYPE_INT, "������", false);
    TBD_COLD = Proto->AddItem(TYPE_INT, "������", false);
    TBD_ELECTRO = Proto->AddItem(TYPE_INT, "��������", false);
    TBD_ACID = Proto->AddItem(TYPE_INT, "��������", false);
    TBD_POISON = Proto->AddItem(TYPE_INT, "���", false);
    TBD_XAOS = Proto->AddItem(TYPE_INT, "�����", false);
    TBD_ORDER = Proto->AddItem(TYPE_INT, "��������", false);
    TBD_POSITIVE = Proto->AddItem(TYPE_INT, "��������", false);
    TBD_NEGATIVE = Proto->AddItem(TYPE_INT, "��������", false);
    TBD_HEALTH = Proto->AddItem(TYPE_FLOAT, "��������", false);
    TBD_BODY = Proto->AddItem(TYPE_STRUCT, "����", false);
    CItemProto *body = Proto->GetItem(TBD_BODY);
    TBD_BODY_POSITION = body->AddItem(TYPE_LIST, "�������", true,
                                      ParserConst.GetList(LIST_BODY_POSITION));
    TBD_BODY_SNAME = body->AddItem(TYPE_LIST, "�����������", false, ParserConst.GetList(LIST_BODY_NAME));
    TBD_BODY_NAME = body->AddItem(TYPE_STRING, "��������", false);
    TBD_BODY_CHANCE = body->AddItem(TYPE_INT, "���������", true);
    TBD_BODY_KDAM = body->AddItem(TYPE_INT, "���������", false);

    TBD_BODY_WEAPON = Proto->AddItem(TYPE_STRUCT, "������", false);
    CItemProto *bwp = Proto->GetItem(TBD_BODY_WEAPON);
    TBD_BWP_NAME = bwp->AddItem(TYPE_STRING, "��������");
    TBD_BWP_SEX = bwp->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_SEX));

    return CheckInit();
}


bool CProf::Initialization(void) {

    TCL_CLASS = Proto->AddItem(TYPE_LIST, "���������", true, ParserConst.GetList(LIST_CLASS));
    TCL_ADDSTR = Proto->AddItem(TYPE_FLOAT, "�����");
    TCL_ADDCON = Proto->AddItem(TYPE_FLOAT, "�����");
    TCL_ADDDEX = Proto->AddItem(TYPE_FLOAT, "���������");
    TCL_ADDINT = Proto->AddItem(TYPE_FLOAT, "������");
    TCL_ADDWIS = Proto->AddItem(TYPE_FLOAT, "���������");
    TCL_ADDCHA = Proto->AddItem(TYPE_FLOAT, "��������");
    TCL_HEALTH = Proto->AddItem(TYPE_FLOAT, "��������");
    TCL_MANA  = Proto->AddItem(TYPE_FLOAT, "����", false);
    TCL_KFORT = Proto->AddItem(TYPE_INT, "������");
    TCL_KREFL = Proto->AddItem(TYPE_INT, "�����");
    TCL_KWILL = Proto->AddItem(TYPE_INT, "�����");
    TCL_HROLL = Proto->AddItem(TYPE_FLOAT, "�����");
    TCL_AC  = Proto->AddItem(TYPE_FLOAT, "������");
    TCL_ARM0 = Proto->AddItem(TYPE_FLOAT, "��������");
    TCL_ARM1 = Proto->AddItem(TYPE_FLOAT, "��������");
    TCL_ARM2 = Proto->AddItem(TYPE_FLOAT, "��������");

    return CheckInit();
}

