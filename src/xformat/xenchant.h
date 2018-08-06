#ifndef XENCHANT_H
#define XENCHANT_H
#include "parser.h"
#include "parser_const.h"
#include "parser_items.h"


/*****************************************************************************/
/*               */
/*****************************************************************************/

class CEnchant : public CParser {
    public:
        CEnchant();
        ~CEnchant();
        bool Initialization(void);
};


// ����������� �������� ����������
extern int ECH_NUMBER;  //�����������
extern int ECH_IDENTIFER; //��������������
extern int ECH_NAME;  //��������
extern int ECH_ALIAS;  //�������
extern int ECH_DESCRIPTION; //��������
extern int ECH_INCLUDE;  //������
extern int ECH_INC_TYPE; //���
extern int ECH_INC_COUNT; //����������
extern int ECH_OBJECT_TYPE; //�������
extern int ECH_WEAR_TYPE; //�������������
extern int ECH_APPLY;  //�������
extern int ECH_AFFECT;  //�������
extern int ECH_SKILL;  //������
extern int ECH_MINIMAL;  //�������
extern int ECH_MAXIMUM;  //��������
extern int ECH_ARM_CLASS; //�����
extern int ECH_WPN_TYPE; //������

extern CEnchant xEnchant;

#endif
