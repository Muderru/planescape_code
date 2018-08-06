/**************************************************************************
    ��� "����� ����" (�) 2002-2005 ������ �������
    �������� ��������
 **************************************************************************/

#include "xenchant.h"
#include "parser_id.h"

int ECH_NUMBER;  //�����������
int ECH_IDENTIFER; //��������������
int ECH_NAME;  //��������
int ECH_ALIAS;  //�������
int ECH_DESCRIPTION; //��������
int ECH_INCLUDE; //������
int ECH_INC_TYPE; //���
int ECH_INC_COUNT; //����������
int ECH_OBJECT_TYPE; //�������
int ECH_WEAR_TYPE; //�������������
int ECH_APPLY;  //�������
int ECH_AFFECT;  //�������
int ECH_SKILL;  //������
int ECH_MINIMAL;  //�������
int ECH_MAXIMUM;  //��������

///////////////////////////////////////////////////////////////////////////////
CEnchant::CEnchant() {
}

CEnchant::~CEnchant() {
}
///////////////////////////////////////////////////////////////////////////////

bool CEnchant::Initialization(void) {

    ECH_NUMBER = Proto->AddItem(TYPE_INT, "�������");
    ECH_IDENTIFER = Proto->AddItem(TYPE_STRING, "�������������");
    ECH_NAME = Proto->AddItem(TYPE_STRING, "��������");
    ECH_ALIAS = Proto->AddItem(TYPE_STRING, "�������");
    ECH_DESCRIPTION = Proto->AddItem(TYPE_STRING, "��������");
    ECH_INCLUDE = Proto->AddItem(TYPE_STRUCT, "������");
    CItemProto *include = Proto->GetItem(ECH_INCLUDE);
    ECH_INC_TYPE = include->AddItem(TYPE_INT, "���");
    ECH_INC_COUNT = include->AddItem(TYPE_INT, "����������");
    ECH_OBJECT_TYPE = Proto->AddItem(TYPE_LIST, "�������", true, ParserConst.GetList(LIST_OBJ_TYPES));
    ECH_WEAR_TYPE = Proto->AddItem(TYPE_VECTOR, "�������������", false, ParserConst.GetVector(VEC_OBJ_WEAR));
    ECH_APPLY = Proto->AddItem(TYPE_STRLIST, "�������", false, ParserConst.GetList(LIST_APPLY));
    ECH_AFFECT = Proto->AddItem(TYPE_VECTOR, "�������", false, ParserConst.GetVector(VEC_MOB_AFF));
    ECH_SKILL = Proto->AddItem(TYPE_STRLIST, "������", false, ParserConst.GetList(LIST_SKILLS));
    ECH_MINIMAL = Proto->AddItem(TYPE_INT, "�������", true);
    ECH_MAXIMUM = Proto->AddItem(TYPE_INT, "��������", true);

    return CheckInit();
}

CEnchant xEnchant;

