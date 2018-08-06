#ifndef PARSER_CONST_H
#define PARSER_CONST_H

struct CListConst_item {
    int key;
    char* text;
    CListConst_item* Next;
};

struct CListConst {
    int ID;
    CListConst_item* Item;
    CListConst_item* last;  // ����� ������ ��� ������
    CListConst* Next;
};

struct CVectorConst_item {
    char* key;
    char* text;
    CVectorConst_item* Next;
};

struct CVectorConst {
    int ID;
    CVectorConst_item* Item;
    CVectorConst_item* last; // ����� ������ ��� ������
    CVectorConst* Next;
};

class CParserConst {
        CVectorConst* VectorConst;
        CVectorConst* last_vector; // ����� ������ ��� ������
        CListConst* ListConst;
        CListConst* last_list;  // ����� ������ ��� ������
        int CurrentConst;
        bool ParseLine(char*);  // ��������� ������
        int line;
        bool NewParameter(int);
        bool ParseLineConf(char*, char*);
    public:
        CParserConst();
        ~CParserConst(); // ������������ ������ �� ������������� :)

        // ������ ������ ��� ��������
        bool ReadConst(const char*);

        void* GetList(int id);
        void* GetVector(int id);

        // ���������� ���������� ������.
        // �������� �� ���������� �� ������������
        void SetVector(int id, char*, char*);
        void SetList(int id, int, char*);

};

extern CParserConst ParserConst;

#endif
