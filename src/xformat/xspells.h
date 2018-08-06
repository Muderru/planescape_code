#ifndef XSPELLS_H
#define XSPELLS_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� ���������� (spells)              */
/*****************************************************************************/

class CSpl : public CParser {
    public:
        CSpl();
        ~CSpl();
        bool Initialization(void);
};


// ����������� �������� ����������
extern int SPL_NUMBER; //����������
extern int SPL_NAME; //��������
extern int SPL_UNAME; //�������
extern int SPL_ALIAS; //�����������
extern int SPL_PROCEDURE; //���������
extern int SPL_SPHERE; //����� (�����)
extern int SPL_MANA; //����
extern int SPL_LEVEL; //�������
extern int SPL_SKILL; //������
extern int SPL_DAMAGE; //�����
extern int SPL_TDAMAGE; //�����
extern int SPL_QUALITY; //�����
extern int SPL_AGRO; //��������
extern int SPL_TARGET; //����
extern int SPL_POSITION; //���������
extern int SPL_LAG; //��������
extern int SPL_VLAG; //���������
extern int SPL_MEMORY; //�����������
extern int SPL_CONCENT; //������������
extern int SPL_SAVES; //����������
extern int SPL_SCORE; //����
extern int SPL_AFF_MESS; //��������
extern int SPL_SAY_MESS; //������������
extern int SPL_MESSAGES_AFFECT; //����������
extern int SPL_MESSAGES_DAMAGE;  //����������
extern int SPL_MESSAGES_OBJECT;  //����������

//���.��������� ��������
extern int SPL_AMESS_SCH; //������_�����
extern int SPL_AMESS_SRM; //������_�������
extern int SPL_AMESS_ECH; //�����_�����
extern int SPL_AMESS_ERM; //�����_�������

//���.��������� ������������
extern int SPL_SAY_CHAR; //�����
extern int SPL_SAY_VICTIM; //������
extern int SPL_SAY_ROOM; //�������
extern int SPL_SAY_ME;  //������
extern int SPL_SAY_MROOM; //��������

//���.��������� x���������
extern int SPL_MESSAGE_KIL_CHAR;   //����_�����
extern int SPL_MESSAGE_KIL_VICT;   //����_������
extern int SPL_MESSAGE_KIL_ROOM;   //����_�������
extern int SPL_MESSAGE_HIT_CHAR;   //����_�����
extern int SPL_MESSAGE_HIT_VICT;   //����_������
extern int SPL_MESSAGE_HIT_ROOM;   //����_�������
extern int SPL_MESSAGE_HIT_ME;     //����_������
extern int SPL_MESSAGE_HIT_MROM;   //����_��������
extern int SPL_MESSAGE_MIS_CHAR;   //������_�����
extern int SPL_MESSAGE_MIS_VICT;   //������_������
extern int SPL_MESSAGE_MIS_ROOM;   //������_�������
extern int SPL_MESSAGE_MIS_ME;     //������_������
extern int SPL_MESSAGE_MIS_MROM;   //������_��������
extern int SPL_MESSAGE_GOD_CHAR;   //����_�����
extern int SPL_MESSAGE_GOD_ME;     //����_������
extern int SPL_MESSAGE_GOD_VICT;   //����_������
extern int SPL_MESSAGE_GOD_ROOM;   //����_�������
extern int SPL_MESSAGE_GOD_MROM;   //����_��������
extern int SPL_MESSAGE_ARM_CHAR;   //����������
extern int SPL_MESSAGE_ARM_VICT;
extern int SPL_MESSAGE_ARM_ROOM;
extern int SPL_MESSAGE_AR2_CHAR;   //�������������� ����������
extern int SPL_MESSAGE_AR2_VICT;
extern int SPL_MESSAGE_AR2_ROOM;

extern CSpl Spl;

#endif
