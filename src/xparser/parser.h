#ifndef PARSER_H
#define PARSER_H

#include "parser_items.h"
#include "parser_types.h"

class CParser : public CItemStructList {
    protected:
        // ��������� ������������ �������������
        bool CheckInit(void);
        bool ReadData(void *Config, const char*);
    public:
        CParser();
        virtual ~CParser();
        virtual bool Initialization(void) = 0;
        // ������ �������
        bool ReadConfig(const char*);

        // ��������� ��������� � ����
        // ���������:
        // 1 - ��� �����
        // 2 - true   - �������� ���� � ������ ������
        //     false  - ���������� ������ � ������������ ����
        //              (���� ����� ������ ���, �� �� ��������� ������)
        bool SaveAll(const char*, bool);

};

#endif
