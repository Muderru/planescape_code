#ifndef XTEMPL_H
#define XTEMPL_H
#include "parser.h"
#include "parser_const.h"

/*****************************************************************************/
/* ����������� ��� �������� ����� �������� ������� ��������                  */
/*****************************************************************************/

class CArmTmp : public CParser {
    public:
        CArmTmp();
        ~CArmTmp();
        bool Initialization(void);
};

extern CArmTmp ArmTmp;

// ����������� �������� ����������
extern int A_NUMBER;  //������
extern int A_NAME;    //��������
extern int A_DESC;    //
extern int A_ALIAS; //�������������
extern int A_TYPE;    //���
extern int A_PTYPE;   //������
extern int A_WEIGHT;    //���
extern int A_MATERIAL;  //��������
extern int A_PRICE;     //����
extern int A_AC;        //�����
extern int A_ARM0;      //��������
extern int A_ARM1;      //��������
extern int A_ARM2;      //��������
extern int A_CLASS;     //�����
extern int A_WEAR; //������������
extern int A_SPEED; //��������

extern int A_MAT_TYPE;  //���
extern int A_MAT_VAL; //����������
extern int A_MAT_MAIN;  //��������

extern int A_P0; //��������
extern int A_P1; //��������
extern int A_P2; //��������


/*****************************************************************************/
/* ����������� ��� �������� ����� �������� ������� ��������                  */
/*****************************************************************************/

class CWeapTmp : public CParser {
    public:
        CWeapTmp();
        ~CWeapTmp();
        bool Initialization(void);
};

extern CWeapTmp WeapTmp;

// ����������� �������� ����������

extern int W_NUMBER; //������
extern int W_NAME; //��������
extern int W_DESC; //��������
extern int W_ALIAS; //�������������
extern int W_TYPE; //���
extern int W_MESS; //���������
extern int W_HIT; //����
extern int W_HIT_TYPE; //����.���
extern int W_HIT_DAM; //����,����
extern int W_WEIGHT; //���
extern int W_PRICE; //����
extern int W_SPEED; //��������
extern int W_CRITIC; //�����������
extern int W_MATERIAL; //��������
extern int W_MAT_TYPE;  //��������.���
extern int W_MAT_VAL; //��������.����������
extern int W_MAT_MAIN;  //��������.��������
extern int W_WEAR; //�������������

class CMissTmp : public CParser {
    public:
        CMissTmp();
        ~CMissTmp();
        bool Initialization(void);
};

extern CMissTmp MissTmp;

extern int M_NUMBER; //������
extern int M_NAME;      //��������
extern int M_ALIAS; //�������������
extern int M_DESC; //��������
extern int M_TYPE; //���
extern int M_HITS; //���
extern int M_HIT_TYPE; //����.���
extern int M_HIT_DAM; //����,����
extern int M_MATERIAL; //��������
extern int M_MAT_TYPE;  //��������.���
extern int M_MAT_VAL; //��������.����������
extern int M_MAT_MAIN;  //��������.��������

class CSetTmp : public CParser {
    public:
        CSetTmp();
        ~CSetTmp();
        bool Initialization(void);
};

extern CSetTmp SetTmp;

extern int S_NUMBER;  //�����
extern int S_OBJECTS;           //��������
extern int S_VARIANTE;  //�������
extern int S_VAR_COUNT; //�������.����������
extern int S_VAR_DESC; //�������.��������
extern int S_VAR_AFFECT; //�������.������
extern int S_VAR_APPLY; //�������.����������
extern int S_VAR_SKILL; //�������.������
extern int S_VAR_SCORE; //�������.����
extern int S_VAR_SCHAR; //�������.������
extern int S_VAR_SROOM; //�������.��������
extern int S_VAR_ECHAR; //�������.������
extern int S_VAR_EROOM; //�������.��������

class CHitMess : public CParser {
    public:
        CHitMess();
        ~CHitMess();
        bool Initialization(void);
};

extern CHitMess HitMess;

extern int MS_TYPE; //����
extern int MS_SUB_CHAR; //������������.�����
extern int MS_SUB_VICT; //������������.������
extern int MS_SUB_ROOM; //������������.�������
extern int MS_HIT_NONE;  //���������
extern int MS_HIT_WEAP; //��������
extern int MS_HWP_CHAR; //������������.�����
extern int MS_HWP_VICT; //������������.������
extern int MS_HWP_ROOM; //������������.�������

extern int MS_MISS_NONE; //���������
extern int MS_MISS_WEAP; //�����������
extern int MS_KILL_NONE; //���������
extern int MS_KILL_WEAP; //������������
extern int MS_ARM_NONE; //���������
extern int MS_ARM_WEAP; //������������
extern int MS_SKIN_NONE; //�������
extern int MS_SKIN_WEAP; //����������

#endif
