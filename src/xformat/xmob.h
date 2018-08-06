#ifndef XMOB_H
#define XMOB_H
#include "parser.h"
#include "parser_const.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� �������� (*.mox)                 */
/*****************************************************************************/

class CMob : public CParser {
    public:
        CMob();
        ~CMob();
        bool Initialization(void);
};

// ����������� �������� ����������
extern int MOB_NUMBER;  //������
extern int MOB_ALIAS;  //��������
extern int MOB_NAME;  //���
extern int MOB_LINE;  //������
extern int MOB_DESCRIPTION; //��������
extern int MOB_ADDITION; //�������������
extern int MOB_PROPERTIES; //���������
extern int MOB_ADDONS;  //�����������
extern int MOB_AFFECTS; //��������
extern int MOB_SEX;  //���
extern int MOB_LEVEL;  //�������
extern int MOB_CLASS;  //���������
extern int MOB_RACE;  //����
extern int MOB_TYPE;  //���
extern int MOB_ALIGN;  //����������
extern int MOB_LAWS;  //����������
extern int MOB_EXP;  //����
extern int MOB_LIMIT;  //������
extern int MOB_HITPOINTS; //�����
extern int MOB_AC;  //�����
extern int MOB_HITROLL; //�����
extern int MOB_HIT1;  //����1
extern int MOB_DAMAGE1; //����1
extern int MOB_COUNT1;  //�����1
extern int MOB_HIT2;  //����2
extern int MOB_DAMAGE2; //����2
extern int MOB_COUNT2;  //�����2
extern int MOB_STR;  //����
extern int MOB_CON;  //������������
extern int MOB_DEX;  //��������
extern int MOB_INT;  //�����
extern int MOB_WIS;  //��������
extern int MOB_CHA;  //�������
extern int MOB_SIZE;  //������
extern int MOB_HEIGHT;  //����
extern int MOB_WEIGHT;  //���
extern int MOB_POSITION; //���������
extern int MOB_MOVED;  //�����������
extern int MOB_MOVESTR; //������������
extern int MOB_GOLD;  //������
extern int MOB_WIMP;  //��������
extern int MOB_SKILL;  //������
extern int MOB_EQ;  //����������
extern int MOB_INV;  //���������
extern int MOB_DEATH;  //���������
extern int MOB_TATOO;  //����������
extern int MOB_SAVE;  //������
extern int MOB_FOLLOW;  //�������
extern int MOB_HELPED;  //���������-������
extern int MOB_DEST;  //����
extern int MOB_SCRIPT;  //������
extern int MOB_SHOP;  //�������
extern int MOB_SPECIAL; //��������
extern int MOB_LACKY;  //�����
extern int MOB_SPEED;  //��������
extern int MOB_LIKEWORK; //������
extern int MOB_GOD;  //���
extern int MOB_FRACTION; //�������
extern int MOB_RANG;           //����
extern int MOB_RANK;           //����
extern int MOB_HORSE;  //������
extern int MOB_SDEATH;  //������
extern int MOB_ALARM;  //����������
extern int MOB_POWER;  //��������
extern int MOB_BODY;  //����
extern int MOB_CLASSES; //���������
extern int MOB_AGE;  //������

// �������������� ���������
extern int MOB_CLASS_TYPE; //���������.�����
extern int MOB_CLASS_LEVEL; //���������.�������

extern int MOB_BODY_POSITION; //����.�������
extern int MOB_BODY_SNAME; //����.�����������
extern int MOB_BODY_NAME; //����.��������
extern int MOB_BODY_CHANCE; //����.���������
extern int MOB_BODY_KDAM; //����,���������

extern int MOB_SDT_CORPSE; //������.����
extern int MOB_SDT_SCRIPT; //������.��������
extern int MOB_SDT_DCHAR; //������.������
extern int MOB_SDT_DROOM;      //������.��������
extern int MOB_SDT_DAMAGE; //������.�����
extern int MOB_SDT_HIT; //������.�����
extern int MOB_SDT_TARGET; //������.����
extern int MOB_SDT_CHAR; //������.�����
extern int MOB_SDT_ROOM; //������.���������

extern int MOB_ADD_KEY; //�������������.����
extern int MOB_ADD_TEXT; //�������������.�����

extern int MOB_SPEC_TYPE; //��������.���
extern int MOB_SPEC_POS; //��������.���������
extern int MOB_SPEC_PERC; //��������.����
extern int MOB_SPEC_HIT; //��������.����������
extern int MOB_SPEC_SPELL; //��������.����������
extern int MOB_SPEC_POWER; //��������.��������
extern int MOB_SPEC_DAMAGE; //��������.����
extern int MOB_SPEC_VICTIM; //��������.������
extern int MOB_SPEC_ROOM; //��������.���������
extern int MOB_SPEC_SAVE; //��������.����������
extern int MOB_SPEC_PROP; //��������.��������

extern int MOB_SHOP_SELL; //�������.������� (int)
extern int MOB_SHOP_BUY; //�������.������� (int)
extern int MOB_SHOP_REPAIR; //�������.������ (int)
extern int MOB_SHOP_QUALITY; //�������.���������� (int)
extern int MOB_SHOP_TYPE; //�������.����� (list)
extern int MOB_SHOP_LIST; //�������.���� (list)
extern int MOB_SHOP_ANTI; //�������.������� (bitvector)

extern int MOB_ALARM_HELPER; //����������.���������
extern int MOB_ALARM_CHAR;   //����������.�����
extern int MOB_ALARM_ROOM;   //����������.�������
extern int MOB_ALARM_LEVEL;  //����������.�������

extern int MOB_PERIOD;  //�������������
extern int MOB_PRD_START; //������
extern int MOB_PRD_STOP; //�����
extern int MOB_PRD_TIME; //������
extern int MOB_PRD_TARGET; //����
extern int MOB_PRD_CHAR; //������
extern int MOB_PRD_ROOM; //�������

extern int MOB_WELCOME; //����������
extern int MOB_GOODBYE; //��������
extern int MOB_QUEST;  //�������
extern int MOB_QNUMBER; //�������.�����
extern int MOB_QNAME;  //�������.��������
extern int MOB_QEXPR;  //�������.�������
extern int MOB_QPRE;  //�������.�������
extern int MOB_QTEXT;  //�������.�����
extern int MOB_QCOMPLITE; //�������.����������
extern int MOB_QMULTY;  //�������.������������
extern int MOB_QREQUEST; //�������.�������
extern int MOB_QR_VAR;  //�������.�������.����������
extern int MOB_QRV_TITLE; //�������.��������.����������.�����������
extern int MOB_QRV_NAME; //�������.��������.����������.��������
extern int MOB_QRV_VALUE; //�������.��������.����������.��������
extern int MOB_QR_MOBILES;     //�������.��������.������
extern int MOB_QR_OBJECTS; //�������.��������.�������
extern int MOB_QR_FOLLOWERS; //�������.��������.�������������
extern int MOB_QACCEPT; //�������.������
extern int MOB_QDONE;  //�������.����������
extern int MOB_QSCRIPT;  //��������
extern int MOB_QSCR_NUMBER; //��������.�����
extern int MOB_QSCR_EXPR; //��������.�������
extern int MOB_QSCR_TEXT; //��������.�����
extern int MOB_QSCR_SCRIPT;  //��������.��������

//�����������
extern int MOB_COMMAND; //�����������
extern int MOB_COMMAND_NO; //�����������.�������
extern int MOB_COMMAND_ARG; //�����������.��������
extern int MOB_COMMAND_TOOL; //�����������.����������
extern int MOB_COMMAND_ACTIVE;
extern int MOB_COMMAND_ARG_OBJ; //�����������.��������.�������
extern int MOB_COMMAND_ARG_ARG; //�����������.��������.������
extern int MOB_COMMAND_ARG_MOB; //�����������.��������.������
extern int MOB_COMMAND_ARG_ERR; //�����������.��������.������
extern int MOB_COMMAND_SCRIPT; //�����������.��������
extern int MOB_COMMAND_EXTRACT; //�����������.����������
extern int MOB_COMMAND_LOAD;     //�����������.��������
extern int MOB_COMMAND_LOAD_ROOM; //�����������.��������.��������
extern int MOB_COMMAND_LOAD_CHAR; //�����������.��������.����������
extern int MOB_COMMAND_ACTIVE_ROOM;
extern int MOB_COMMAND_MESS_ROOM;
extern int MOB_COMMAND_MESS_CHAR;

//��������
extern int MOB_INTERCEPTION; //��������
extern int MOB_INT_COMMAND; // ��������.������� (LIST)
extern int MOB_INT_STOP; // ��������.���� (extern int)
extern int MOB_INT_MESSPLAYER; // ��������.����� (STRING)
extern int MOB_INT_MESSVICTIM; // ��������.������ (STRING)
extern int MOB_INT_MESSOTHER; // ��������.��������� (STRING)
extern int MOB_INT_MESSROOM; // ��������.������� (STRING)
extern int MOB_INT_SCRIPT; // ��������.�������� (STRING)
extern int MOB_INT_SARG; // ��������.��������� (STRING)

//�������
extern int MOB_EVENT;  //�������
extern int MOB_EVN_TYPE; //�������.���
extern int MOB_EVN_ARG; //�������.��������
extern int MOB_EVN_SCRIPT; //�������.��������

extern CMob *Mob;

#endif
