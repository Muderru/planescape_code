#ifndef XQUESTS_H
#define XQUESTS_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ ������� */
/*****************************************************************************/

class CQstSave : public CParser {
    public:
        CQstSave();
        ~CQstSave();
        bool Initialization(void);
};


extern int QUEST_QUEST;  //�������
extern int QUEST_MOB_VNUM; //������
extern int QUEST_NUMBER;  //�����
extern int QUEST_DONE_MOB; //������� (STRLIST, �������� ����, �������� ���-��)
extern int QUEST_DONE_OBJ; //��������(STRLIST, �������� ����, �������� ���-��)
extern int QUEST_DONE_FLW; //������������� (STRLIST, �������� ����, �������� ���-��)
extern int QUEST_VAR;  //����������
extern int QUEST_VAR_NAME; //����������.��������
extern int QUEST_VAR_CURRENT; //����������.��������

#endif
