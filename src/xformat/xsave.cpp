/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/

#include "xsave.h"
#include "xspells.h"
#include "xobj.h"
#include "parser_id.h"

int RENT_NUMBER;
int RENT_NAME;
int RENT_TYPE;
int RENT_TIME;
int RENT_ROOM;
int RENT_QUALITY;

int PET_NUMBER; //�����
int PET_GUID; //������
int PET_NAME;   //���
int PET_RACE;   //����
int PET_TYPE;
int PET_CLASS;
int PET_CLASS_TYPE; //���������.�����
int PET_CLASS_LEVEL; //���������.�������
int PET_HIT;  //������
int PET_MOVE;  //���������
int PET_MANA;  //�����
int PET_SPELL; //����������
int PET_TIME; //�����
int PET_EXP; //����
int PET_LIKES; //������
int PET_SKILLS; //������

int VARS_NUMBER;  //����������
int VARS_NAME;  //��������
int VARS_VALUE;  //��������
int VARS_TIME;  //�����
///////////////////////////////////////////////////////////////////////////////
CRent::CRent() {
}

CRent::~CRent() {
}

///////////////////////////////////////////////////////////////////////////////

bool CRent::Initialization(void) {
    RENT_NUMBER = Proto->AddItem(TYPE_INT, "�����");
    RENT_NAME = Proto->AddItem(TYPE_STRING, "���");
    RENT_TYPE = Proto->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_RENT_TYPES));
    RENT_ROOM      = Proto->AddItem(TYPE_INT, "���������");
    RENT_QUALITY   = Proto->AddItem(TYPE_INT, "��������");
    RENT_TIME      = Proto->AddItem(TYPE_INT, "�����");

    return CheckInit();
}


///////////////////////////////////////////////////////////////////////////////
CPet::CPet() {
}

CPet::~CPet() {
}

///////////////////////////////////////////////////////////////////////////////
bool CPet::Initialization(void) {

    PET_NUMBER = Proto->AddItem(TYPE_INT, "�����", true);
    PET_GUID = Proto->AddItem(TYPE_LONGLONG, "������", false);
    PET_NAME = Proto->AddItem(TYPE_STRING, "���", true);
    PET_RACE = Proto->AddItem(TYPE_LIST, "����", true, ParserConst.GetList(LIST_RACE));
    PET_CLASS = Proto->AddItem(TYPE_STRUCT, "�����", false);
    PET_TYPE = Proto->AddItem(TYPE_INT, "���", true);
    PET_SPELL = Proto->AddItem(TYPE_LIST, "����������", true, ParserConst.GetList(LIST_SPELLS));
    PET_TIME = Proto->AddItem(TYPE_INT, "�����", true);
    PET_EXP = Proto->AddItem(TYPE_INT, "����", true);
    CItemProto *classes = Proto->GetItem(PET_CLASS);
    PET_CLASS_TYPE = classes->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_CLASS));
    PET_CLASS_LEVEL = classes->AddItem(TYPE_INT, "�������", true);

    PET_HIT = Proto->AddItem(TYPE_INT, "������", false);
    PET_MOVE = Proto->AddItem(TYPE_INT, "���������", false);
    PET_MANA = Proto->AddItem(TYPE_INT, "�����", false);
    PET_LIKES = Proto->AddItem(TYPE_INT, "������", false);
    PET_SKILLS = Proto->AddItem(TYPE_STRLIST, "������", false, ParserConst.GetList(LIST_SKILLS));

    return CheckInit();
}

///////////////////////////////////////////////////////////////////////////////
CVarSave::CVarSave() {
}

CVarSave::~CVarSave() {
}

///////////////////////////////////////////////////////////////////////////////

bool CVarSave::Initialization(void) {
    VARS_NUMBER = Proto->AddItem(TYPE_INT, "����������");
    VARS_NAME = Proto->AddItem(TYPE_STRING, "��������");
    VARS_VALUE = Proto->AddItem(TYPE_STRING, "��������");
    VARS_TIME = Proto->AddItem(TYPE_INT, "�����");

    return CheckInit();
}

