#ifndef XHELP_H
#define XHELP_H

#include "parser.h"
#include "parser_const.h"

extern int HELP_NUMBER; //����� �������
extern int HELP_TOPIC;
extern int HELP_TITLE;  //��������� (������)
extern int HELP_ALIAS;  //�������� (������)
extern int HELP_TYPE;  //��� (����)
extern int HELP_CONTENT; //���������� (������)
extern int HELP_FORMAT; //������ ������� (������)
extern int HELP_LINKS;  //���� (������)

class CHelp : public CParser {
    public:
        CHelp();
        ~CHelp();
        bool Initialization(void);
};

#endif
