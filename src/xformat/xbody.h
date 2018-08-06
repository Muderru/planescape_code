#ifndef XBODY_H
#define XBODY_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"


/*****************************************************************************/
/* ����������� ��� �������� ������ �������� ��� ��� (body) */
/*****************************************************************************/

class CBody : public CParser {
    public:
        CBody();
        ~CBody();
        bool Initialization(void);
};

class CProf : public CParser {
    public:
        CProf();
        ~CProf();
        bool Initialization(void);
};

// ����������� �������� ����������
extern int TBD_RACE;  //����
extern int TBD_HEALTH;  //��������
extern int TBD_BODY;  //����
extern int TBD_BODY_POSITION; //����.�������
extern int TBD_BODY_SNAME; //����.�����������
extern int TBD_BODY_NAME; //����.��������
extern int TBD_BODY_CHANCE; //����.���������
extern int TBD_BODY_KDAM; //����.���������
extern int TBD_AC; //����.�����
extern int TBD_ARM0; //����.��������
extern int TBD_ARM1; //����.��������
extern int TBD_ARM2; //����.��������
extern int TBD_FIRE;
extern int TBD_COLD;
extern int TBD_ELECTRO;
extern int TBD_ACID;
extern int TBD_POISON;
extern int TBD_XAOS;
extern int TBD_ORDER;
extern int TBD_POSITIVE;
extern int TBD_NEGATIVE;

extern int TCL_CLASS;  //���������
extern int TCL_ADDSTR;  //���������� ����
extern int TCL_ADDCON;
extern int TCL_ADDDEX;
extern int TCL_ADDINT;
extern int TCL_ADDWIS;
extern int TCL_ADDCHA;  //���������� �������
extern int TCL_HEALTH;
extern int TCL_MANA;
extern int TCL_KFORT;
extern int TCL_KREFL;
extern int TCL_KWILL;
extern int TCL_HROLL;
extern int TCL_AC;
extern int TCL_ARM0;
extern int TCL_ARM1;
extern int TCL_ARM2;

extern int TBD_BODY_WEAPON; //������
extern int TBD_BWP_NAME; //������.��������
extern int TBD_BWP_SEX;  //������.���

extern CBody tBody;
extern CProf tProf;

#endif
