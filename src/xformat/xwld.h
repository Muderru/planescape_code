#ifndef XWLD_H
#define XWLD_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� ������� (*.wlx)                  */
/*****************************************************************************/

class CWld : public CParser {
    public:
        CWld();
        ~CWld();
        bool Initialization(void);
};

// ����������� �������� ����������
extern int WLD_NUMBER;  // �������
extern int WLD_ZONE;  //�������
extern int WLD_POD;  // �������
extern int WLD_NAME;  // ��������
extern int WLD_DESCRIPTION; // ��������
extern int WLD_DESCRIPTION_N; // �������� ����
extern int WLD_ADDITION; // �������������
extern int WLD_PROPERTIES; // ���������
extern int WLD_DISTRICT; // ���������
extern int WLD_INTERCEPTION; // ��������
extern int WLD_EXIT;  // �����
extern int WLD_DAMAGE;  // �����������
extern int WLD_TRAP;  // �������
extern int WLD_PORTAL;  // ������
extern int WLD_SCRIPT;  // ������
extern int WLD_MOBILE;  // ������
extern int WLD_OBJECT;  // �������
extern int WLD_MAP;  // �����
extern int WLD_FORCEDIR; // �������

// ����������� ��������������� ����������
extern int WLD_ADD_KEY; //�������������.����
extern int WLD_ADD_TEXT; //�������������.�����

extern int WLD_INT_COMMAND;  // ��������.������� (LIST)
extern int WLD_INT_STOP;  // ��������.���� (INT)
extern int WLD_INT_MESSPLAYER;  // ��������.����� (STRING)
extern int WLD_INT_MESSVICTIM;  // ��������.������ (STRING)
extern int WLD_INT_MESSOTHER;  // ��������.��������� (STRING)
extern int WLD_INT_MESSROOM;  // ��������.������� (STRING)
extern int WLD_INT_SCRIPT;  // ��������.�������� (INT)

extern int WLD_EXIT_DIRECTION;  // �����.����������� (LIST)
extern int WLD_EXIT_ROOMNUMBER; // �����.������� (INT)
extern int WLD_EXIT_DESCRIPTION; // �����.�������� (STRING)
extern int WLD_EXIT_NAME;  // �����.���  (LIST)
extern int WLD_EXIT_ALIAS;  // �����.������� (STRING)
extern int WLD_EXIT_KEY;  // �����.����  (INT)
extern int WLD_EXIT_PROPERTIES; // �����.�������� (VECTOR)
extern int WLD_EXIT_QUALITY;         // �����.��������
extern int WLD_EXIT_TRAP;  // �����.������� (INT)
extern int WLD_EXIT_TRAP_CHANCE; // �����.�������.���� (INT)
extern int WLD_EXIT_TRAP_TYPEDAMAGE; // �����.�������.�����  (LIST)
extern int WLD_EXIT_TRAP_FORCEDAMAGE; // �����.�������.�����  (RANDOM)
extern int WLD_EXIT_TRAP_SAVE;  // �����.�������.�������
extern int WLD_EXIT_TRAP_MESS_CHAR; // �����.�������.�����
extern int WLD_EXIT_TRAP_MESS_ROOM; // �����.�������.�������
extern int WLD_EXIT_TRAP_MESS_SCHAR; // �����.�������.������
extern int WLD_EXIT_TRAP_MESS_SROOM; // �����.�������.��������
extern int WLD_EXIT_TRAP_MESS_KCHAR; // �����.�������.����_�����
extern int WLD_EXIT_TRAP_MESS_KROOM; // �����.�������.����_�������
extern int WLD_EXIT_SEX;  // �����.���

extern int WLD_DAM_CHANCE;  //�����������.����
extern int WLD_DAM_TYPE;  //�����������.���
extern int WLD_DAM_TYPEDAMAGE;  //�����������.�����
extern int WLD_DAM_SAVE;  //�����������.�������
extern int WLD_DAM_FORCEDAMAGE; //�����������.�����
extern int WLD_DAM_MESS_CHAR;  //�����������.�����
extern int WLD_DAM_MESS_ROOM;  //�����������.�������
extern int WLD_DAM_MESS_SCHAR;  //�����������.������
extern int WLD_DAM_MESS_SROOM;  //�����������.��������

extern int WLD_TRAP_DIRECTION;  //�������.�����������
extern int WLD_TRAP_CHANCE;  //�������.����
extern int WLD_TRAP_TYPE;  //�������.���
extern int WLD_TRAP_TYPEDAMAGE; //�������.�����
extern int WLD_TRAP_SAVE;  //�������.�������
extern int WLD_TRAP_FORCEDAMAGE; //�������.�����
extern int WLD_TRAP_MESS_CHAR;  //�������.�����
extern int WLD_TRAP_MESS_ROOM;  //�������.���������
extern int WLD_TRAP_MESS_SCHAR; //�������.������
extern int WLD_TRAP_MESS_SROOM; //�������.����������
extern int WLD_TRAP_MESS_ACT_C; //�������.������
extern int WLD_TRAP_MESS_ACT_R; //�������.����������
extern int WLD_TRAP_MESS_KCHAR; //�������.����_�����
extern int WLD_TRAP_MESS_KROOM; //�������.����_�������

extern int WLD_PORTAL_DIRECTION; //������.�����������
extern int WLD_PORTAL_TYPE;  //������.���
extern int WLD_PORTAL_TIME;  //������.�����
extern int WLD_PORTAL_ROOM;  //������.�������
extern int WLD_PORTAL_KEY;  //������.����
extern int WLD_PORTAL_DESCRIPTION; //������.��������
extern int WLD_PORTAL_ACTIVE;  //������.��������
extern int WLD_PORTAL_DEACTIVE; //������.����������
extern int WLD_PORTAL_MESS_CHAR; //������.�����
extern int WLD_PORTAL_MESS_ROOM; //������.���������
extern int WLD_PORTAL_WORK_TIME; //������.�����_������

extern int WLD_HOTEL;                  //���������
extern int WLD_HOTEL_TYPE;             //���������.���
extern int WLD_HOTEL_MASTER;           //���������.������
extern int WLD_HOTEL_CHAR;             //���������.������
extern int WLD_HOTEL_ROOM;             //���������.�������
extern int WLD_HOTEL_RETURN;           //���������.��������

extern int WLD_FD_ROOM;  //�������.�������
extern int WLD_FD_DIR;   //�������.�����������
extern int WLD_FD_TIME;  //�������.�����
extern int WLD_FD_PERIOD;  //�������.������
extern int WLD_FD_DAMAGE;  //�������.�����������
extern int WLD_FD_DAM_TYPE;  //�������.�����������.���
extern int WLD_FD_DAM_FORCEDAMAGE; //�������.�����������.����
extern int WLD_FD_DAM_SAVETYPE; //�������.�����������.������
extern int WLD_FD_DAM_SAVE;  //�������.�����������.����������
extern int WLD_FD_MESS_MCHAR;  //�������.������_��������
extern int WLD_FD_MESS_MROOM;  //�������.������_�������
extern int WLD_FD_MESS_EXCHAR;  //�������.����_��������
extern int WLD_FD_MESS_EXROOM;  //�������.����_�������
extern int WLD_FD_MESS_ENCHAR;  //�������.������_��������
extern int WLD_FD_MESS_ENROOM;  //�������.������_�������
extern int WLD_FD_MESS_KCHAR;  //�������.����_��������
extern int WLD_FD_MESS_KROOM;  //�������.����_�������

extern int WLD_PERIOD;   //�������������
extern int WLD_PRD_START;  //�������������.������
extern int WLD_PRD_STOP;  //�������������.�����
extern int WLD_PRD_WEATHER;  //�������������.������
extern int WLD_PRD_OBJECT;  //�������������.�������
extern int WLD_PRD_MONSTER;  //�������������.������
extern int WLD_PRD_SRLOCATION;  //�������������.��������
extern int WLD_PRD_SPLOCATION;  //�������������.��������
extern int WLD_PRD_SRZONE;  //�������������.�����������
extern int WLD_PRD_SPZONE;  //�������������.�����������

extern CWld *Wld;

/* ����������� ��� �������� ���� � �������� (/lib/misc/world_loot)           */
/*****************************************************************************/

class CWlt : public CParser {
    public:
        CWlt();
        ~CWlt();
        bool Initialization(void);
};

//world loot ������� (/lib/misc/world_loot)
extern int WRL_LOOT;   //�������
extern int WRL_RACE;   //�������.���� LIST(14)
extern int WRL_TYPE;   //��� LIST(49)
extern int WRL_LEVEL;   //������� STRING
extern int WRL_SEX;   //��� LIST(11)
extern int WRL_CLASS;   //����� STRLIST(13)
extern int WRL_GOD;   //��� LIST(28)
extern int WRL_AGE;   //������� STRLIST(52)
extern int WRL_OBJECT;   //������� INT
extern int WRL_SHANCE;   //���� INT (1...1000)

extern CWlt Wlt;

#endif
