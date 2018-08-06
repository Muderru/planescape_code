#include "xquests.h"
#include "parser_id.h"
#include "strlib.h"
#include "expr.h"


int QUEST_QUEST;  //�������
int QUEST_MOB_VNUM; //������
int QUEST_NUMBER;  //�����
int QUEST_DONE_MOB; //������� (STRLIST, �������� ����, �������� ���-��)
int QUEST_DONE_OBJ; //��������(STRLIST, �������� ����, �������� ���-��)
int QUEST_DONE_FLW; //������������� (STRLIST, �������� ����, �������� ���-��)
int QUEST_VAR;  //����������
int QUEST_VAR_NAME; //����������.��������
int QUEST_VAR_CURRENT; //����������.��������



///////////////////////////////////////////////////////////////////////////////
CQstSave::CQstSave() {
}

CQstSave::~CQstSave() {
}

///////////////////////////////////////////////////////////////////////////////

bool CQstSave::Initialization(void) {
    QUEST_QUEST = Proto->AddItem(TYPE_INT, "�������");
    QUEST_MOB_VNUM = Proto->AddItem(TYPE_INT, "������");
    QUEST_NUMBER = Proto->AddItem(TYPE_INT, "�����");
    QUEST_DONE_MOB = Proto->AddItem(TYPE_STRLIST, "�������", false);
    QUEST_DONE_OBJ = Proto->AddItem(TYPE_STRLIST, "��������", false);
    QUEST_DONE_FLW = Proto->AddItem(TYPE_STRLIST, "�������������", false);
    QUEST_VAR = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *var = Proto->GetItem(QUEST_VAR);
    QUEST_VAR_NAME = var->AddItem(TYPE_STRING, "��������");
    QUEST_VAR_CURRENT = var->AddItem(TYPE_STRING, "��������");

    return CheckInit();
}

