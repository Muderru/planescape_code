#ifndef XMATERIAL_H
#define XMATERIAL_H
#include "parser.h"
#include "parser_const.h"

/*****************************************************************************/
/* ����������� ��� �������� ����� ���������                                  */
/*****************************************************************************/

class CMaterial : public CParser {
    public:
        CMaterial();
        ~CMaterial();
        bool Initialization(void);
};

// ����������� �������� ����������
extern int MAT_NUMBER; //�������� (����)
extern int MAT_DESCRIPTION;
extern int MAT_NAME; //�������� (��������)
extern int MAT_WEIGHT; //���
extern int MAT_COST; //����
extern int MAT_DURAB; //���������
extern int MAT_AC; //�����
extern int MAT_ARM0; //�������
extern int MAT_ARM1; //�������
extern int MAT_ARM2; //�������
extern int MAT_HITX;
extern int MAT_HITY;
extern int MAT_HITZ;
extern int MAT_ALIAS;
extern int MAT_TYPE;
extern int MAT_HITS;
extern int MAT_FIRE;
extern int MAT_COLD;
extern int MAT_ELECTRO;
extern int MAT_ACID;
extern int MAT_INCLUDE; //���������

#endif
