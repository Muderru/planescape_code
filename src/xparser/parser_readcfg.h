#ifndef PARSER_READCFG_H
#define PARSER_READCFG_H

#define FIELD_CONST  1
#define FIELD_STRING 2
#define FIELD_STRUCT 3
#define FIELD_NONE  0
#define FIELD_ERROR  -1
#define FIELD_NC  4

#define CR    0x0A

class CReadCfg {
        int fd;
        int NumLine;
        char *Buffer;

        char *ReadBuffer;
        int ReadSize;
        int ReadPos;

        char GetChar(void);
        void BackChar(void);
        ///////////////////////////////////////////////////////////////////////////
        // ��������� ���������� ����
        // �����:   1 - ���������
        //     2 - ��������� ���������
        //     3 - ���������
        //     4 - ����� ������� (:)
        //     0 - ������ �� �������
        //    -1 - ������. �� ����������� ��������� ��� ���������
        int GetField(bool &NextLine, char *dst);

    public:
        CReadCfg();
        ~CReadCfg();

        bool StartRead(const char*);
        void StartRead(char*, int);
        int GetLine(void);
        void SetActiveBuffer(char*);
        ///////////////////////////////////////////////////////////////////////////
        // �������� ������� � ����������
        // ���������� ��� ��������� ��� ������
        // FIELD_CONST - ���������
        // FIELD_STRING - ��������� ��������� (����� � ��������)
        // FIELD_STRUCT - ��������� (����� � ������� �������)
        // FIELD_NONE - ������ (����� ������ ���� ��� ��������� ������ �����)
        // FIELD_ERROR - ������
        int GetCommand(char *comm, char *param);
};

#endif
