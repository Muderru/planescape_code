#ifndef XSKILLS_H
#define XSKILLS_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� ������ (spells) */
/*****************************************************************************/

class CSkl : public CParser {
    public:
        CSkl();
        ~CSkl();
        bool Initialization(void);
};


// ����������� �������� ����������
extern int SKL_NUMBER;  //������
extern int SKL_NAME;   //��������
extern int SKL_ALIAS;  //�������������
extern int SKL_USELESS; //������������� (���������)
extern int SKL_USE_CLASS; //���������
extern int SKL_USE_TEMPL; //��������
extern int SKL_USE_PRACT; //����������
extern int SKL_USE_LEVEL; //�������
extern int SKL_USE_EFFECT; //�������������
extern int SKL_MISS_ATTACK; //������ (���������)
extern int SKL_MA_CHAR;
extern int SKL_MA_VICT;
extern int SKL_MA_ROOM;
extern int SKL_HIT_ATTACK; //���������
extern int SKL_HA_CHAR;
extern int SKL_HA_VICT;
extern int SKL_HA_ROOM;
extern int SKL_DTH_ATTACK; //������
extern int SKL_DA_CHAR;
extern int SKL_DA_VICT;
extern int SKL_DA_ROOM;
extern int SKL_NHS_ATTACK; //������������
extern int SKL_NA_CHAR;
extern int SKL_NA_VICT;
extern int SKL_NA_ROOM;
extern int SKL_ARM_ATTACK; //����������
extern int SKL_AM_CHAR;
extern int SKL_AM_VICT;
extern int SKL_AM_ROOM;
extern int SKL_ARM2_ATTACK; //������������
extern int SKL_A2_CHAR;
extern int SKL_A2_VICT;
extern int SKL_A2_ROOM;
extern int SKL_TMPL;
extern int SKL_TM_CHAR;
extern int SKL_TM_VICT;
extern int SKL_TM_ROOM;
extern int SKL_TMPS;
extern int SKL_TS_CHAR;
extern int SKL_TS_VICT;
extern int SKL_TS_ROOM;

extern CSkl Skl;

#endif
