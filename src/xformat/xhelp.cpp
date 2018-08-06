
#include "xhelp.h"
#include "parser_id.h"

int HELP_NUMBER; //����� �������
int HELP_TOPIC;
int HELP_TITLE;  //��������� (������)
int HELP_ALIAS;  //�������� (������)
int HELP_TYPE;  //��� (����)
int HELP_CONTENT; //���������� (������)
int HELP_FORMAT; //������ ������� (������)
int HELP_LINKS;  //���� (������)

///////////////////////////////////////////////////////////////////////////////
CHelp::CHelp() {
}
///////////////////////////////////////////////////////////////////////////////
CHelp::~CHelp() {
}
///////////////////////////////////////////////////////////////////////////////
bool CHelp::Initialization(void) {

    HELP_NUMBER = Proto->AddItem(TYPE_INT, "�����");
    HELP_TITLE  = Proto->AddItem(TYPE_STRING, "���������");
    HELP_TOPIC  = Proto->AddItem(TYPE_INT, "�����", false);
    HELP_ALIAS  = Proto->AddItem(TYPE_STRING, "��������");
    HELP_TYPE   = Proto->AddItem(TYPE_LIST, "���", false, ParserConst.GetList(LIST_HELP_TYPES));
    HELP_CONTENT = Proto->AddItem(TYPE_STRING, "����������");
    HELP_FORMAT = Proto->AddItem(TYPE_STRING, "������", false);
    HELP_LINKS  = Proto->AddItem(TYPE_STRING, "������", false);

    return CheckInit();
}


