
#include "xmaterial.h"
#include "parser_id.h"


///////////////////////////////////////////////////////////////////////////////
// ����������� �������� ����������
int MAT_NUMBER; //�������� (����)
int MAT_DESCRIPTION;
int MAT_NAME; //�������� (��������)
int MAT_WEIGHT; //���
int MAT_COST; //����
int MAT_DURAB; //���������
int MAT_AC; //�����
int MAT_ARM0; //�������
int MAT_ARM1; //�������
int MAT_ARM2; //�������
int MAT_HITX;
int MAT_HITY;
int MAT_HITZ;
int MAT_ALIAS;
int MAT_TYPE;
int MAT_HITS;
int MAT_FIRE;
int MAT_COLD;
int MAT_ELECTRO;
int MAT_ACID;
int MAT_INCLUDE; //���������

CMaterial::CMaterial() {
}

CMaterial::~CMaterial() {
}
///////////////////////////////////////////////////////////////////////////////

bool CMaterial::Initialization(void) {
    MAT_NUMBER = Proto->AddItem(TYPE_INT, "��������");
    MAT_NAME   = Proto->AddItem(TYPE_STRING, "��������");
    MAT_DESCRIPTION = Proto->AddItem(TYPE_STRING, "��������", false);
    MAT_WEIGHT = Proto->AddItem(TYPE_INT, "���");
    MAT_COST   = Proto->AddItem(TYPE_INT, "����");
    MAT_DURAB  = Proto->AddItem(TYPE_INT, "���������");
    MAT_AC     = Proto->AddItem(TYPE_INT, "�����", false);
    MAT_ARM0   = Proto->AddItem(TYPE_INT, "�������", false);
    MAT_ARM1   = Proto->AddItem(TYPE_INT, "�������", false);
    MAT_ARM2   = Proto->AddItem(TYPE_INT, "�������", false);
    MAT_ALIAS  = Proto->AddItem(TYPE_STRING, "�������������", true);
    MAT_TYPE   = Proto->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_MATERIAL_TYPE));
    MAT_HITS   = Proto->AddItem(TYPE_INT, "����", false);
    MAT_FIRE   = Proto->AddItem(TYPE_INT, "�����", false);
    MAT_COLD   = Proto->AddItem(TYPE_INT, "�����", false);
    MAT_ELECTRO = Proto->AddItem(TYPE_INT, "�������������", false);
    MAT_ACID   = Proto->AddItem(TYPE_INT, "�������", false);
    MAT_INCLUDE = Proto->AddItem(TYPE_INT, "���������", false);
    return CheckInit();
}

///////////////////////////////////////////////////////////////////////////////

