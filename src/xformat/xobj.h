#ifndef XOBJ_H
#define XOBJ_H
#include "parser.h"
#include "parser_const.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� ��������� (*.obx)                */
/*****************************************************************************/

class CObj : public CParser {
    public:
        CObj();
        ~CObj();
        bool Initialization(void);
};

// ����������� �������� ����������
extern int OBJ_NUMBER;  //�������
extern int OBJ_GUID; //������
extern int OBJ_ALIAS;  //��������
extern int OBJ_NAME;  //���
extern int OBJ_LINE;  //������
extern int OBJ_DESCRIPTION; //��������
extern int OBJ_ADDITION; //�������������
extern int OBJ_PROPERTIES; //���������
extern int OBJ_SEX;  //���
extern int OBJ_MATERIAL; //��������
extern int OBJ_WEIGHT;  //���
extern int OBJ_COST;  //����
extern int OBJ_TYPE;  //���
extern int OBJ_WEAR;  //�������������
extern int OBJ_ANTI;  //����������
extern int OBJ_NO;  //������
extern int OBJ_AFFECTS; //��������
extern int OBJ_APPLY;  //�������
extern int OBJ_TIMER;  //������
extern int OBJ_TIMELOAD; //������
extern int OBJ_QUALITY; //��������
extern int OBJ_LIMIT;  //������
extern int OBJ_DURAB;  //���������
extern int OBJ_CURRENT_DURAB;  //���.���������
extern int OBJ_MAGIC;  //�����
extern int OBJ_INTERCEPTION; //��������
extern int OBJ_SCRIPT;  //�������
extern int OBJ_SHANCE;  //����
extern int OBJ_VAL0;  //����0
extern int OBJ_VAL1;  //����1
extern int OBJ_VAL2;  //����2
extern int OBJ_VAL3;  //����3
extern int OBJ_LIGHT;  //����
extern int OBJ_LEVEL;  //�������
extern int OBJ_SPELL1;  //����1
extern int OBJ_SPELL2;  //����2
extern int OBJ_SPELL3;  //����3
extern int OBJ_ENCHANT;  //�����������
extern int OBJ_SLOT_MAX; //�������
extern int OBJ_SLOT_CUR; //������
extern int OBJ_SPELL;  //����������
extern int OBJ_AC;  //�����
extern int OBJ_ARM0;  //�������
extern int OBJ_ARM1;  //�������
extern int OBJ_ARM2;  //�������
extern int OBJ_DAMAGE;  //C���� v1+v2
extern int OBJ_SKILL;  //������
extern int OBJ_HIT;  //����� v3
extern int OBJ_SIZE;  //����������� v0
extern int OBJ_BAG_PROPERTIES; //��������� v1
extern int OBJ_BAG_NOTFIT; //������������
extern int OBJ_KEY;  //����   v2
extern int OBJ_BAG_MAGIC; //��������  v3
extern int OBJ_OLIST;  //����������
extern int OBJ_OGOLD;  //������
extern int OBJ_VALUE;  //������� v0
extern int OBJ_CUR_VALUE; //�������� v1
extern int OBJ_LIQ;  //�������� v2
extern int OBJ_POISON;  //�� v3
extern int OBJ_FOOD;  //��������� v0
extern int OBJ_GOLD;  //����� v0
extern int OBJ_BRIGHT;  //�������
extern int OBJ_TR_PROPERTIES; //����������
extern int OBJ_TRAP;  //������� (extern int)
extern int OBJ_XSAVE;          //����������
extern int OBJ_POWER;  //��������
extern int OBJ_TEMPLATE; //������� (����� �������)
extern int OBJ_ARM_CLASS; //�����
extern int OBJ_P0;  //��������
extern int OBJ_P1;  //��������
extern int OBJ_P2;  //��������
extern int OBJ_COMMAND;  //�����������
extern int OBJ_TOOL;  //����������
extern int OBJ_QUEST;  //������

//�����������
extern int OBJ_COMMAND_NO; //�����������.�������
extern int OBJ_COMMAND_ARG; //�����������.��������
extern int OBJ_COMMAND_TOOL; //�����������.����������
extern int OBJ_COMMAND_EXPR; //�����������.�������
extern int OBJ_COMMAND_ECHAR; //�����������.������_������
extern int OBJ_COMMAND_EROOM; //�����������.������_�������
extern int OBJ_COMMAND_ACTIVE;
extern int OBJ_COMMAND_ARG_OBJ; //�����������.��������.�������
extern int OBJ_COMMAND_ARG_ARG; //�����������.��������.������
extern int OBJ_COMMAND_ARG_MOB; //�����������.��������.������
extern int OBJ_COMMAND_ARG_ERR; //�����������.��������.������
extern int OBJ_COMMAND_SCRIPT; //�����������.������
extern int OBJ_COMMAND_XSCRIPT; //�����������.��������
extern int OBJ_COMMAND_EXTRACT; //�����������.����������
extern int OBJ_COMMAND_LOAD;     //�����������.��������
extern int OBJ_COMMAND_LOAD_ROOM; //�����������.��������.��������
extern int OBJ_COMMAND_LOAD_CHAR; //�����������.��������.����������
extern int OBJ_COMMAND_ACTIVE_ROOM;
extern int OBJ_COMMAND_MESS_ROOM;
extern int OBJ_COMMAND_MESS_CHAR;


//����������
extern int OBJ_XSAVE_EQ; //����������.����������
extern int OBJ_XSAVE_POS; //����������.���������

// �������������
extern int OBJ_ADD_KEY; //�������������.����
extern int OBJ_ADD_TEXT; //�������������.�����

// ��������
extern int OBJ_MAT_TYPE; //��������.���
extern int OBJ_MAT_VAL; //����������
extern int OBJ_MAT_MAIN; //��������

extern int OBJ_INT_COMMAND; // ��������.������� (LIST)
extern int OBJ_INT_STOP; // ��������.���� (extern int)
extern int OBJ_INT_EXPR; // ��������.������� (expr)
extern int OBJ_INT_SCRIPT; // ��������.������ (extern int)
extern int OBJ_INT_MESSPLAYER; // ��������.����� (STRING)
extern int OBJ_INT_MESSVICTIM; // ��������.������ (STRING)
extern int OBJ_INT_MESSOTHER; // ��������.��������� (STRING)
extern int OBJ_INT_MESSROOM; // ��������.������� (STRING)

//�����
extern int OBJ_MAGIC_SPELL; //�����.���������� (LIST)
extern int OBJ_MAGIC_LEVEL; //�����.�������  (extern int)
extern int OBJ_MAGIC_PERCENT; //�����.����  (extern int)
extern int OBJ_MAGIC_MESS_CHAR; //�����.������ (STRING)
extern int OBJ_MAGIC_MESS_VICT; //�����.������ (STRING)
extern int OBJ_MAGIC_MESS_ROOM; //�����.��������� (STRING)

//�������
extern int OBJ_TRAP_COMMAND;  //�������.�������
extern int OBJ_TRAP_CHANCE;  //�������.���� (extern int)
extern int OBJ_TRAP_TYPEDAMAGE; //�������.�����  (LIST)
extern int OBJ_TRAP_FORCEDAMAGE; //�������.�����  (RANDOM)
extern int OBJ_TRAP_SAVE;  //�������.�������
extern int OBJ_TRAP_MESS_CHAR;  //�������.�����
extern int OBJ_TRAP_MESS_ROOM;  //�������.�������
extern int OBJ_TRAP_MESS_SCHAR; //�������.������
extern int OBJ_TRAP_MESS_SROOM; //�������.��������
extern int OBJ_TRAP_MESS_KCHAR; //�������.����_�����
extern int OBJ_TRAP_MESS_KROOM; //�������.����_�������

//����������
extern int OBJ_AFFECT;
extern int AFFECT_TYPE;
extern int AFFECT_LOC;
extern int AFFECT_MOD;
extern int AFFECT_VEC;
extern int AFFECT_EXT;
extern int AFFECT_DUR;
extern int AFFECT_NFL;
extern int AFFECT_AFL;
extern int OBJ_OWNER;

//������

extern int OBJ_WEAP_TEMPL; //�������

extern int OBJ_ADD_HIT;  //�����
extern int OBJ_AHIT_TYPE; //�����.���
extern int OBJ_AHIT_DAMAGE; //�����.�����

extern int OBJ_SPECHIT;   //���������
extern int OBJ_SPECHIT_SHANCE;  //���������.����
extern int OBJ_SPECHIT_XRACE;  //���������.�����
extern int OBJ_SPECHIT_ZRACE;  //���������.�����
extern int OBJ_SPECHIT_XTYPE;  //���������.����
extern int OBJ_SPECHIT_ZTYPE;  //���������.����
extern int OBJ_SPECHIT_CHAR;  //���������.������
extern int OBJ_SPECHIT_VICTIM;  //���������.������
extern int OBJ_SPECHIT_ROOM;  //���������.�������
extern int OBJ_SPECHIT_KOEF;  //���������.����������
extern int OBJ_SPECHIT_HTYPE;  //���������.����
extern int OBJ_SPECHIT_HDAMAGE;  //���������.������
extern int OBJ_SPECHIT_SPELL;  //���������.����������
extern int OBJ_SPECHIT_SLEVEL;  //���������.�������
extern int OBJ_SPECHIT_TARGET;  //���������.����

extern int OBJ_MISSILE;  //������
extern int OBJ_MISS_TYPE; //������.���
extern int OBJ_MISS_COUNT; //������.�����������
extern int OBJ_MISS_TCOUNT; //������.�����������
extern int OBJ_MISS_TEMPL; //������.�������
extern int OBJ_MADD_HIT; //������.�����
extern int OBJ_MAHIT_TYPE; //������.�����.���
extern int OBJ_MAHIT_DAMAGE; //������.�����.�����

extern CObj *Obj;

#endif
