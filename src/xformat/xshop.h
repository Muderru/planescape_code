#ifndef XSHOP_H
#define XSHOP_H
#include "parser.h"
#include "parser_const.h"


extern int SHOP_NUMBER; //�������
extern int SHOP_MOB;  //������
extern int SHOP_LIST;  //����

class CShop : public CParser {
    public:
        CShop();
        ~CShop();
        bool Initialization(void);
};

#endif
