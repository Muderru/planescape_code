///////////////////////////////////////////////////////////////////////////////
//
//          ������������� ���������� ������ ������ ������������
//
// (�) 2003 ��������� �����
///////////////////////////////////////////////////////////////////////////////

#include "parser.h"
#include "parser_utils.h"
#include "parser_file.h"
#include "parser_readcfg.h"

///////////////////////////////////////////////////////////////////////////////
CParser::CParser() : CItemStructList() {
    Proto = new CItemProtoStruct("", true);
}
///////////////////////////////////////////////////////////////////////////////
CParser::~CParser() {
    delete Proto;
}
///////////////////////////////////////////////////////////////////////////////

bool CParser::ReadConfig(const char *name) {
    CReadCfg Config;
    log("������ ����� ������������ (%s)...", name);
    if (!Config.StartRead(name))
        return false;
    return ReadData(&Config, name);
}

bool CParser::ReadData(void *szConfig, const char* name) {
    CReadCfg *Config = (CReadCfg*)szConfig;
    char com[10000];
    char par[100000];
    // ��� ��������� ����� ��� ����, �� ���������� ������������
    // ��� Config. ������ �� Config->
    int ret = Config->GetCommand(com, par);  // ���
    if (ret == FIELD_NONE) {
        log("��������! ���� ����!");
        return true;
    }
    if (ret == FIELD_ERROR) {
        log("������ ������ ����� ������������");
        return false;
    }
    if (ret != FIELD_CONST) {
        // ���
        log("������ � ����� ������������ [FIELD_CONST]. ������ %d", Config->GetLine());
        return false;
    }
    if (strcmp(com, Proto->GetItem(0)->GetData()->Name) != 0) {
        log("������ �������� ������ ����: %s", Proto->GetItem(0)->GetData()->Name);
        // ���
        log("������ � ����� ������������. ������ %d", Config->GetLine());
        return false;
    }
    bool end = false;
    while (1) {
        //log("��������� �������� �������: %s %s", com, par);
        NewSubItem(); // ����� ����� ���������
        if (!(Item[Number-1]->AddParameter(ret, com, par))) {
            // ���
            log("������ � ����� ������������ []. ������ %d", Config->GetLine());
            return false;
        }

        while (1) {
            ret = Config->GetCommand(com, par);  // ���
            if (ret == FIELD_NONE) {
                end = true;
                break;
            }
            if (ret == FIELD_ERROR) {
                // ���
                log("������ � ����� ������������ [FIELD_ERROR]. ������ %d", Config->GetLine());
                return false;
            }
            if (strcmp(com, Proto->GetItem(0)->GetData()->Name) == 0)
                break;
            //log("���������: %d %s %s", ret, com, par);
            if (!(Item[Number-1]->AddParameter(ret, com, par))) {
                // ���
                log("������ � ����� ������������ [1]. ������ %d", Config->GetLine());
                return false;
            }
        }
        if (!(Item[Number-1]->GetStatus())) {
            log("������ � ����� ������������. ������ �� ��������. ������ %d", Config->GetLine());
            return false;
        }
        if (end)
            break;
    }
    log("������ ���������. �������: %d", Number);
    return true;
}

///////////////////////////////////////////////////////////////////////////////
bool CParser::CheckInit(void) {
    if (Proto == NULL) {
        log("������ �������������! �� ������ �������� ���������.");
        return false;
    }
    return Proto->CheckInit();
}
///////////////////////////////////////////////////////////////////////////////
bool CParser::SaveAll(const char *name, bool clr) {
    CParserFile file;
    if (!file.Open(name, clr))
        return false;
    for (int i = 0; i < Number; i ++) {
        file.StartLevel();
        Item[i]->SaveItem(&file);
    }
    file.Close();
    return true;
}
///////////////////////////////////////////////////////////////////////////////
