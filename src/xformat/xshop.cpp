#include "xshop.h"
#include "parser_id.h"

/* ��� ������ � ������� */
int SHOP_NUMBER; //�������
int SHOP_MOB;  //������
int SHOP_LIST;  //����



CShop::CShop() {
}

CShop::~CShop() {
}

///////////////////////////////////////////////////////////////////////////////

bool CShop::Initialization(void) {

    SHOP_NUMBER =  Proto->AddItem(TYPE_INT, "�������");
    SHOP_MOB =   Proto->AddItem(TYPE_INT, "������");
    SHOP_LIST =  Proto->AddItem(TYPE_STRLIST, "����");

    return CheckInit();
}

