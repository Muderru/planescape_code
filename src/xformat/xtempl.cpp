/**************************************************************************
    ��� "����� ����" (�) 2002-2004 ������ �������
    �������� ���������� ���������
 **************************************************************************/

#include "xtempl.h"
#include "parser_id.h"


// ����������� �������� ����������
int A_NUMBER;  //�����
int A_NAME;    //��������
int A_DESC;    //
int A_ALIAS;
int A_TYPE;    //���
int A_PTYPE;   //������
int A_WEIGHT;    //���
int A_MATERIAL;  //��������
int A_PRICE;     //����
int A_AC;        //�����
int A_ARM0;      //��������
int A_ARM1;      //��������
int A_ARM2;      //��������
int A_CLASS;     //�����
int A_WEAR;  //�������������
int A_SPEED; //��������

//��������
int A_MAT_TYPE;  //���
int A_MAT_VAL; //����������
int A_MAT_MAIN;  //��������

int A_P0; //��������
int A_P1; //��������
int A_P2; //��������

///////////////////////////////////////////////////////////////////////////////
CArmTmp::CArmTmp() {
}

CArmTmp::~CArmTmp() {
}
///////////////////////////////////////////////////////////////////////////////

CArmTmp ArmTmp;

bool CArmTmp::Initialization(void) {
    A_NUMBER = Proto->AddItem(TYPE_INT, "������");
    A_NAME  = Proto->AddItem(TYPE_STRING, "��������");
    A_ALIAS = Proto->AddItem(TYPE_STRING, "�������������", false);
    A_DESC  = Proto->AddItem(TYPE_STRING, "��������", false);
    A_TYPE  = Proto->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_TYPE_ARMOR));
    A_PTYPE = Proto->AddItem(TYPE_LIST, "������", false, ParserConst.GetList(LIST_PTYPE_ARMOR));
    A_WEIGHT = Proto->AddItem(TYPE_INT, "���", false);
    A_PRICE = Proto->AddItem(TYPE_INT, "����", false);
    A_AC  = Proto->AddItem(TYPE_INT, "�����", false);
    A_ARM0  = Proto->AddItem(TYPE_INT, "��������", false);
    A_ARM1  = Proto->AddItem(TYPE_INT, "��������", false);
    A_ARM2  = Proto->AddItem(TYPE_INT, "��������", false);
    A_CLASS = Proto->AddItem(TYPE_LIST, "�����", false, ParserConst.GetList(LIST_TYPE_ACLASS));
    A_SPEED = Proto->AddItem(TYPE_INT, "��������", false);
    A_WEAR  = Proto->AddItem(TYPE_VECTOR, "�������������", false,
                             ParserConst.GetVector(VEC_OBJ_WEAR));

    A_P0  = Proto->AddItem(TYPE_INT, "��������", false);
    A_P1  = Proto->AddItem(TYPE_INT, "��������", false);
    A_P2  = Proto->AddItem(TYPE_INT, "��������", false);

    A_MATERIAL = Proto->AddItem(TYPE_STRUCT, "��������", true);
    CItemProto *mat = Proto->GetItem(A_MATERIAL);
    A_MAT_TYPE = mat->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_MATERIAL_TYPE));
    A_MAT_VAL = mat->AddItem(TYPE_INT, "����������", true);
    A_MAT_MAIN    = mat->AddItem(TYPE_INT, "��������", false);

    return CheckInit();
}

/******************************************************************************/
int W_NUMBER; //������
int W_NAME; //��������
int W_DESC; //��������
int W_ALIAS; //�������������
int W_TYPE; //���
int W_MESS; //���������
int W_HIT; //����
int W_HIT_TYPE; //����.���
int W_HIT_DAM; //����,����
int W_WEIGHT; //���
int W_PRICE; //����
int W_SPEED; //��������
int W_CRITIC; //�����������
int W_MATERIAL; //��������
int W_MAT_TYPE;  //��������.���
int W_MAT_VAL; //��������.����������
int W_MAT_MAIN;  //��������.��������
int W_WEAR; //�������������
///////////////////////////////////////////////////////////////////////////////
CWeapTmp::CWeapTmp() {
}

CWeapTmp::~CWeapTmp() {
}
///////////////////////////////////////////////////////////////////////////////

CWeapTmp WeapTmp;

bool CWeapTmp::Initialization(void) {
    W_NUMBER = Proto->AddItem(TYPE_INT, "������");
    W_NAME  = Proto->AddItem(TYPE_STRING, "��������");
    W_ALIAS  = Proto->AddItem(TYPE_STRING, "��������������", false);
    W_DESC  = Proto->AddItem(TYPE_STRING, "��������", false);
    W_ALIAS = Proto->AddItem(TYPE_STRING, "�������������");
    W_TYPE  = Proto->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_WEAPON_SKILLS));
    W_MESS  = Proto->AddItem(TYPE_LIST, "���������", true, ParserConst.GetList(LIST_WEAPON_TYPE));
    W_HIT  = Proto->AddItem(TYPE_STRUCT, "����", true);
    CItemProto *hit = Proto->GetItem(W_HIT);
    W_HIT_TYPE = hit->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_DAMAGE));
    W_HIT_DAM = hit->AddItem(TYPE_STRING, "�����", true);
    W_WEIGHT = Proto->AddItem(TYPE_INT, "���");
    W_PRICE = Proto->AddItem(TYPE_INT, "���������");
    W_SPEED = Proto->AddItem(TYPE_INT, "��������");
    W_CRITIC = Proto->AddItem(TYPE_INT, "�����������");
    W_MATERIAL = Proto->AddItem(TYPE_STRUCT, "��������", true);
    CItemProto *mat = Proto->GetItem(W_MATERIAL);
    W_MAT_TYPE = mat->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_MATERIAL_TYPE));
    W_MAT_VAL = mat->AddItem(TYPE_INT, "����������", true);
    W_MAT_MAIN    = mat->AddItem(TYPE_INT, "��������", false);
    W_WEAR  = Proto->AddItem(TYPE_VECTOR, "�������������", true, ParserConst.GetVector(VEC_OBJ_WEAR));

    return CheckInit();
}

/**************************************************************************/
int M_NUMBER;    //������
int M_NAME;      //��������
int M_ALIAS; //�������������
int M_DESC; //��������
int M_TYPE; //���
int M_HITS; //����
int M_HIT_TYPE; //����.���
int M_HIT_DAM; //����,����
int M_MATERIAL; //��������
int M_MAT_TYPE;  //��������.���
int M_MAT_VAL; //��������.����������
int M_MAT_MAIN;  //��������.��������

CMissTmp::CMissTmp() {
}

CMissTmp::~CMissTmp() {
}
///////////////////////////////////////////////////////////////////////////////

CMissTmp MissTmp;

bool CMissTmp::Initialization(void) {
    M_NUMBER = Proto->AddItem(TYPE_INT, "������", true);
    M_NAME  = Proto->AddItem(TYPE_STRING, "��������", true);
    M_ALIAS = Proto->AddItem(TYPE_STRING, "�������������", false);
    M_DESC  = Proto->AddItem(TYPE_STRING, "��������", false);
    M_TYPE  = Proto->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_MISSILE));
    M_HITS  = Proto->AddItem(TYPE_STRUCT, "����", true);
    CItemProto *hit = Proto->GetItem(M_HITS);
    M_HIT_TYPE = hit->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_DAMAGE));
    M_HIT_DAM = hit->AddItem(TYPE_STRING, "�����", true);

    M_MATERIAL = Proto->AddItem(TYPE_STRUCT, "��������", true);
    CItemProto *mat = Proto->GetItem(M_MATERIAL);
    M_MAT_TYPE = mat->AddItem(TYPE_LIST, "���", true, ParserConst.GetList(LIST_MATERIAL_TYPE));
    M_MAT_VAL = mat->AddItem(TYPE_INT, "����������", true);
    M_MAT_MAIN    = mat->AddItem(TYPE_INT, "��������", false);

    return CheckInit();
}

/***************************************************************************/
int S_NUMBER;  //�����
int S_IDENT;           //�������������
int S_OBJECTS;           //��������
int S_VARIANTE;  //�������
int S_VAR_COUNT; //�������.����������
int S_VAR_DESC;  //�������.��������
int S_VAR_AFFECT; //�������.������
int S_VAR_APPLY; //�������.����������
int S_VAR_SKILL; //�������.������
int S_VAR_SCORE; //�������.����
int S_VAR_SCHAR; //�������.������
int S_VAR_SROOM; //�������.��������
int S_VAR_ECHAR; //�������.������
int S_VAR_EROOM; //�������.��������

CSetTmp::CSetTmp() {
}

CSetTmp::~CSetTmp() {
}
///////////////////////////////////////////////////////////////////////////////

CSetTmp SetTmp;

bool CSetTmp::Initialization(void) {
    S_NUMBER = Proto->AddItem(TYPE_INT, "�����", true);
    S_IDENT = Proto->AddItem(TYPE_STRING, "�������������", false);
    S_OBJECTS = Proto->AddItem(TYPE_SCRIPT, "��������", true);
    S_VARIANTE = Proto->AddItem(TYPE_STRUCT, "�������", true);
    CItemProto *varnt = Proto->GetItem(S_VARIANTE);
    S_VAR_COUNT = varnt->AddItem(TYPE_INT, "����������", true);
    S_VAR_DESC  = varnt->AddItem(TYPE_STRING, "��������", false);
    S_VAR_AFFECT = varnt->AddItem(TYPE_VECTOR, "������", false, ParserConst.GetVector(VEC_MOB_AFF));
    S_VAR_APPLY = varnt->AddItem(TYPE_STRLIST, "����������", false, ParserConst.GetList(LIST_APPLY));
    S_VAR_SKILL = varnt->AddItem(TYPE_STRLIST, "������", false, ParserConst.GetList(LIST_SKILLS));
    S_VAR_SCORE = varnt->AddItem(TYPE_STRING, "����", false);
    S_VAR_SCHAR = varnt->AddItem(TYPE_STRING, "������", false);
    S_VAR_SROOM = varnt->AddItem(TYPE_STRING, "��������", false);
    S_VAR_ECHAR = varnt->AddItem(TYPE_STRING, "������", false);
    S_VAR_EROOM = varnt->AddItem(TYPE_STRING, "��������", false);

    return CheckInit();
}

/////////////////////////////////////////////////////////////////////////////

int MS_TYPE;  //����
int MS_SUB_CHAR;  //������������.�����
int MS_SUB_VICT;  //������������.������
int MS_SUB_ROOM;  //������������.�������
int MS_HIT_NONE;   //���������
int MS_HIT_WEAP;  //��������
int MS_HWP_CHAR;  //������������.�����
int MS_HWP_VICT;  //������������.������
int MS_HWP_ROOM;  //������������.�������
int MS_MISS_NONE; //���������
int MS_MMN_CHAR;  //������������.�����
int MS_MMN_VICT;  //������������.������
int MS_MMN_ROOM;  //������������.�������

int MS_MISS_WEAP; //�����������
int MS_KILL_NONE; //���������
int MS_KILL_WEAP; //������������
int MS_ARM_NONE;  //���������
int MS_ARM_WEAP;  //������������
int MS_SKIN_NONE; //�������
int MS_SKIN_WEAP; //����������

CHitMess::CHitMess() {
}

CHitMess::~CHitMess() {
}
///////////////////////////////////////////////////////////////////////////////
CHitMess HitMess;

bool CHitMess::Initialization(void) {
    MS_TYPE = Proto->AddItem(TYPE_LIST, "���������", true, ParserConst.GetList(LIST_MOB_HIT));

    MS_HIT_NONE = Proto->AddItem(TYPE_STRUCT, "���������", true);
    CItemProto *mhn = Proto->GetItem(MS_HIT_NONE);
    MS_SUB_CHAR = mhn->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = mhn->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = mhn->AddItem(TYPE_STRING, "�������", true);

    MS_HIT_WEAP = Proto->AddItem(TYPE_STRUCT, "��������", true);
    CItemProto *mhw = Proto->GetItem(MS_HIT_WEAP);
    MS_HWP_CHAR = mhw->AddItem(TYPE_STRING, "�����", true);
    MS_HWP_VICT = mhw->AddItem(TYPE_STRING, "������", true);
    MS_HWP_ROOM = mhw->AddItem(TYPE_STRING, "�������", true);

    MS_MISS_NONE = Proto->AddItem(TYPE_STRUCT, "���������", true);
    CItemProto *mmn = Proto->GetItem(MS_MISS_NONE);
    MS_MMN_CHAR = mmn->AddItem(TYPE_STRING, "�����", true);
    MS_MMN_VICT = mmn->AddItem(TYPE_STRING, "������", true);
    MS_MMN_ROOM = mmn->AddItem(TYPE_STRING, "�������", true);

    MS_MISS_WEAP = Proto->AddItem(TYPE_STRUCT, "������������", true);
    CItemProto *mmw = Proto->GetItem(MS_MISS_WEAP);
    MS_SUB_CHAR = mmw->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = mmw->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = mmw->AddItem(TYPE_STRING, "�������", true);

    MS_KILL_NONE = Proto->AddItem(TYPE_STRUCT, "���������", true);
    CItemProto *mkn = Proto->GetItem(MS_KILL_NONE);
    MS_SUB_CHAR = mkn->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = mkn->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = mkn->AddItem(TYPE_STRING, "�������", true);

    MS_KILL_WEAP = Proto->AddItem(TYPE_STRUCT, "������������", true);
    CItemProto *mkw = Proto->GetItem(MS_KILL_WEAP);
    MS_SUB_CHAR = mkw->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = mkw->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = mkw->AddItem(TYPE_STRING, "�������", true);

    MS_ARM_NONE = Proto->AddItem(TYPE_STRUCT, "���������", true);
    CItemProto *man = Proto->GetItem(MS_ARM_NONE);
    MS_SUB_CHAR = man->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = man->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = man->AddItem(TYPE_STRING, "�������", true);

    MS_ARM_WEAP = Proto->AddItem(TYPE_STRUCT, "������������", true);
    CItemProto *maw = Proto->GetItem(MS_ARM_WEAP);
    MS_SUB_CHAR = maw->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = maw->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = maw->AddItem(TYPE_STRING, "�������", true);

    MS_SKIN_NONE = Proto->AddItem(TYPE_STRUCT, "�������", true);
    CItemProto *msn = Proto->GetItem(MS_SKIN_NONE);
    MS_SUB_CHAR = msn->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = msn->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = msn->AddItem(TYPE_STRING, "�������", true);

    MS_SKIN_WEAP = Proto->AddItem(TYPE_STRUCT, "����������", true);
    CItemProto *msw = Proto->GetItem(MS_SKIN_WEAP);
    MS_SUB_CHAR = msw->AddItem(TYPE_STRING, "�����", true);
    MS_SUB_VICT = msw->AddItem(TYPE_STRING, "������", true);
    MS_SUB_ROOM = msw->AddItem(TYPE_STRING, "�������", true);

    return CheckInit();
}

