#ifndef XSCRIPTS_H
#define XSCRIPTS_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� (scr) */
/*****************************************************************************/

class CScr : public CParser {
    public:
        CScr();
        ~CScr();
        bool Initialization(void);
};

extern CScr Scr;


// ����������� �������� ����������
extern int SCR_NUMBER;  //��������
extern int SCR_EXPR;  //�������
extern int SCR_MESSAGE;  //���������
extern int SCR_MVNUM;  //���������.���
extern int SCR_MCHAR;  //���������.������
extern int SCR_MROOM;  //���������.�������
extern int SCR_MZONE;  //���������.�������

extern int SCR_ERROR;  //������
extern int SCR_ECHAR;  //������.������
extern int SCR_EROOM;  //������.�������
extern int SCR_EZONE;  //������.�������
extern int SCR_ESCRIPT;  //������.��������

extern int SCR_LOAD;  //��������
extern int SCR_LOBJ;  //��������.�������
extern int SCR_LEQ;  //��������.���������
extern int SCR_LRANDOM;  //��������.���������
extern int SCR_LMOB;  //��������.������
extern int SCR_LEXIT;  //��������.�����
extern int SCR_LPORTAL;  //��������.������
extern int SCR_LCHAR;  //��������.������
extern int SCR_LROOM;  //��������.�������
extern int SCR_LGOLD;  //��������.������

extern int SCR_OBJ_LIMIT; //��������.�����

extern int SCR_LE_ROOM; // �����.���
extern int SCR_LE_DIRECTION; // �����.����������� (LIST)
extern int SCR_LE_ROOMNUMBER; // �����.������� (INT)
extern int SCR_LE_DESCRIPTION; // �����.�������� (STRING)
extern int SCR_LE_NAME;  // �����.���  (LIST)
extern int SCR_LE_ALIAS; // �����.������� (STRING)
extern int SCR_LE_KEY;  // �����.����  (INT)
extern int SCR_LE_PROPERTIES; // �����.�������� (VECTOR)
extern int SCR_LE_QUALITY; // �����.��������
extern int SCR_LE_TRAP;  // �����.������� (INT)
extern int SCR_LE_TRAP_CHANCE; // �����.�������.���� (INT)
extern int SCR_LE_TRAP_TYPEDAMAGE; // �����.�������.�����  (LIST)
extern int SCR_LE_TRAP_FORCEDAMAGE; // �����.�������.�����  (RANDOM)
extern int SCR_LE_TRAP_SAVE;  // �����.�������.�������
extern int SCR_LE_TRAP_MESS_CHAR; // �����.�������.�����
extern int SCR_LE_TRAP_MESS_ROOM; // �����.�������.�������
extern int SCR_LE_TRAP_MESS_SCHAR; // �����.�������.������
extern int SCR_LE_TRAP_MESS_SROOM; // �����.�������.��������
extern int SCR_LE_TRAP_MESS_KCHAR; // �����.�������.����_�����
extern int SCR_LE_TRAP_MESS_KROOM; // �����.�������.����_�������
extern int SCR_LE_SEX;  // �����.���

extern int SCR_LP_PORTAL; //������
extern int SCR_LP_ROOM;  //������.���
extern int SCR_LP_DIRECTION; //������.�����������
extern int SCR_LP_TYPE;  //������.���
extern int SCR_LP_TIME;  //������.�����
extern int SCR_LP_ROOMNUMBER;  //������.�������
extern int SCR_LP_KEY;  //������.����
extern int SCR_LP_DESCRIPTION; //������.��������
extern int SCR_LP_ACTIVE;  //������.��������
extern int SCR_LP_DEACTIVE; //������.����������
extern int SCR_LP_MESS_CHAR; //������.�����
extern int SCR_LP_MESS_ROOM; //������.���������
extern int SCR_LP_WORK_TIME; //������.�����_������

extern int SCR_DELETE;  //��������
extern int SCR_DOBJ;  //��������.�������
extern int SCR_DEQ;  //��������.���������
extern int SCR_DMOB;  //��������.������
extern int SCR_DGOLD;  //��������.������
extern int SCR_DEXIT;  //��������.�����
extern int SCR_DE_ROOM;  //�����,���
extern int SCR_DE_DIRECTION; //�����.�����������
extern int SCR_DPORTAL;  //��������.������
extern int SCR_DP_ROOM;  //������.���
extern int SCR_DP_DIRECTION; //������.�����������
extern int SCR_DCHAR;  //��������.�����
extern int SCR_DROOM;  //��������.���������

extern int SCR_TELEPORT; //�����������
extern int SCR_TWHERE;  //���
extern int SCR_TROOM;  //�������
extern int SCR_TCHAROUT;  //��������
extern int SCR_TCHARIN;  //���������
extern int SCR_TROOMOUT;  //��������
extern int SCR_TROOMIN;  //���������

extern int SCR_SPELL;  //����������
extern int SCR_SPELL_NO; //����������.�����
extern int SCR_SPELL_LEVEL; //����������.�������
extern int SCR_SPELL_MCHAR; //����������.�����
extern int SCR_SPELL_MROOM; //����������.�������

extern int SCR_VAR;  //����������
extern int SCR_VAR_NAME; //����������.��������
extern int SCR_VAR_VALUE; //����������.��������
extern int SCR_VAR_TIME; //����������.�����

extern int SCR_GLB;  //����������
extern int SCR_GLB_NAME; //����������.��������
extern int SCR_GLB_VALUE; //����������.��������
extern int SCR_GLB_TIME; //����������.�����

extern int SCR_RESET; //�����

extern int SCR_AGRO; //��������
extern int SCR_AMOB; //��������.������
extern int SCR_ATARGET; //��������.����

extern int SCR_DAMAGE;    //����
extern int SCR_DAM_TARGET; //����.����
extern int SCR_DAM_SHANCE; //����.����
extern int SCR_DAM_TYPE;   //����.�����
extern int SCR_DAM_DAMAGE; //����.�����
extern int SCR_DAM_STYPE;  //����.������
extern int SCR_DAM_SAVE;   //����.����������
extern int SCR_DAM_KVICT;  //����.�������
extern int SCR_DAM_KROOM;  //����.��������
extern int SCR_DAM_HVICT;  //����.�������
extern int SCR_DAM_HROOM;  //����.��������
extern int SCR_DAM_MVICT;  //����.�������
extern int SCR_DAM_MROOM;  //����.��������

extern int SCR_EXP; //����
extern int SCR_EXP_TYPE; //���
extern int SCR_EXP_SCHAR; //������������
extern int SCR_EXP_SGROUP; //������������
extern int SCR_EXP_CHAR; //������
extern int SCR_EXP_GROUP; //������

extern int SCR_APPLY; //�����������

extern int SCR_CONTINUE; //�����������
extern int SCR_CNT_VNUM; //�����������.�����
extern int SCR_CNT_TIMER; //�����������.������

#endif
