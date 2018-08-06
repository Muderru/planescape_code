/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xzon.h"
#include "parser_id.h"

// ����������� �������� ����������
int ZON_NUMBER;  // ����
int ZON_NAME_MAJ;  // �������
int ZON_NAME_MIN;  // ��������
int ZON_AUTHOR;  // �����
int ZON_DESCRIPTION;  // ��������
int ZON_TYPE;   // ���
int ZON_TOP;   // ������
int ZON_RESET_TYPE;  // �����
int ZON_RESET_TIME;  // �����
int ZON_TIME;  // �����
int ZON_RECALL;  // ������
int ZON_COMMET;  // �����������
int ZON_MESTO;  // ��������������
int ZON_MESTO_PLANE; // ��������������.�����
int ZON_MESTO_WARD; // ��������������.�����
///////////////////////////////////////////////////////////////////////////////
CZon::CZon() {
}
CZon::~CZon() {
}
///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
bool CZon::Initialization(void) {

    ZON_NUMBER   = Proto->AddItem(TYPE_INT, "����");
    ZON_NAME_MAJ = Proto->AddItem(TYPE_STRING, "�������", false);
    ZON_NAME_MIN = Proto->AddItem(TYPE_STRING, "��������");
    ZON_AUTHOR   = Proto->AddItem(TYPE_STRING, "�����");
    ZON_DESCRIPTION = Proto->AddItem(TYPE_STRING, "��������");
    ZON_TYPE     = Proto->AddItem(TYPE_LIST, "���", false,
                                  ParserConst.GetList(LIST_ZONE_TYPE));
    ZON_TOP      = Proto->AddItem(TYPE_INT, "������", false);
    ZON_RESET_TYPE = Proto->AddItem(TYPE_LIST, "�����", true, ParserConst.GetList(LIST_RESET_TYPES));
    ZON_RESET_TIME = Proto->AddItem(TYPE_INT, "�����", false);
    ZON_TIME     = Proto->AddItem(TYPE_INT, "�����", false);
    ZON_RECALL = Proto->AddItem(TYPE_INT, "�������", false);
    ZON_COMMET = Proto->AddItem(TYPE_STRING, "�����������", false);
    ZON_MESTO = Proto->AddItem(TYPE_STRUCT, "��������������", false);
    CItemProto *mesto = Proto->GetItem(ZON_MESTO);
    ZON_MESTO_PLANE   = mesto->AddItem(TYPE_LIST, "�����", false, ParserConst.GetList(LIST_PLANE_TYPES));
    ZON_MESTO_WARD    = mesto->AddItem(TYPE_LIST, "�����", false, ParserConst.GetList(LIST_WARD_TYPES));

    return CheckInit();
};

CZon Zon;

