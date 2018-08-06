#ifndef XSAVE_H
#define XSAVE_H
#include "parser.h"
#include "parser_const.h"


/*****************************************************************************/
/* ����������� ��� ������/������ ������ ��������� ����� (savedata)           */
/*****************************************************************************/

class CRent : public CParser {
    public:
        CRent();
        ~CRent();
        bool Initialization(void);
};

extern int RENT_NUMBER;
extern int RENT_NAME;
extern int RENT_TYPE;
extern int RENT_TIME;
extern int RENT_ROOM;
extern int RENT_QUALITY;


class CPet : public CParser {
    public:
        CPet();
        ~CPet();
        bool Initialization(void);
};

extern int PET_NUMBER; //�����
extern int PET_GUID; //������
extern int PET_NAME;   //���
extern int PET_RACE;   //����
extern int PET_TYPE; //���
extern int PET_SPELL; //����������
extern int PET_TIME; //�����
extern int PET_CLASS;
extern int PET_CLASS_TYPE; //���������.�����
extern int PET_CLASS_LEVEL; //���������.�������
extern int PET_HIT;  //������
extern int PET_MOVE;  //���������
extern int PET_MANA;  //�����
extern int PET_EXP;  //����
extern int PET_LIKES;  //������
extern int PET_SKILLS;  //������

class CVarSave : public CParser {
    public:
        CVarSave();
        ~CVarSave();
        bool Initialization(void);
};

extern int VARS_NUMBER;  //����������
extern int VARS_NAME;  //��������
extern int VARS_VALUE;  //��������
extern int VARS_TIME;  //�����

#endif 
