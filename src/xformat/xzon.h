#ifndef XZON_H
#define XZON_H
#include "parser.h"
#include "parser_const.h"

/*****************************************************************************/
/* ����������� ��� �������� ������ �������� ���� (*.znx)                  */
/*****************************************************************************/

class CZon : public CParser {
    public:
        CZon();
        ~CZon();
        bool Initialization(void);
};

// ����������� �������� ����������
extern int ZON_NUMBER;  // ����
extern int ZON_NAME_MAJ;  // �������
extern int ZON_NAME_MIN;  // ��������
extern int ZON_AUTHOR;  // �����
extern int ZON_DESCRIPTION;  // ��������
extern int ZON_TYPE;   // ���
extern int ZON_TOP;   // ������
extern int ZON_RESET_TYPE;  // �����
extern int ZON_RESET_TIME;  // �����
extern int ZON_TIME;  // �����
extern int ZON_RECALL;  // ������
extern int ZON_COMMET;  // �����������
extern int ZON_MESTO;  // ��������������
extern int ZON_MESTO_PLANE; // ��������������.�����
extern int ZON_MESTO_WARD; // ��������������.�����

extern CZon Zon;

#endif
