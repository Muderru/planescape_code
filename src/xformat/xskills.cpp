/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xskills.h"
#include "parser_id.h"


// ����������� �������� ����������
int SKL_NUMBER;  //������
int SKL_NAME;   //��������
int SKL_ALIAS;  //�������������
int SKL_USELESS; //������������� (���������)
int SKL_USE_CLASS; //���������
int SKL_USE_TEMPL; //��������
int SKL_USE_PRACT; //����������
int SKL_USE_LEVEL; //�������
int SKL_USE_EFFECT; //�������������
int SKL_MISS_ATTACK; //������ (���������)
int SKL_MA_CHAR;
int SKL_MA_VICT;
int SKL_MA_ROOM;
int SKL_HIT_ATTACK; //���������
int SKL_HA_CHAR;
int SKL_HA_VICT;
int SKL_HA_ROOM;
int SKL_DTH_ATTACK; //������
int SKL_DA_CHAR;
int SKL_DA_VICT;
int SKL_DA_ROOM;
int SKL_NHS_ATTACK; //������������
int SKL_NA_CHAR;
int SKL_NA_VICT;
int SKL_NA_ROOM;
int SKL_ARM_ATTACK; //����������
int SKL_AM_CHAR;
int SKL_AM_VICT;
int SKL_AM_ROOM;
int SKL_ARM2_ATTACK; //������������
int SKL_A2_CHAR;
int SKL_A2_VICT;
int SKL_A2_ROOM;
int SKL_TMPL;
int SKL_TM_CHAR;
int SKL_TM_VICT;
int SKL_TM_ROOM;
int SKL_TMPS;
int SKL_TS_CHAR;
int SKL_TS_VICT;
int SKL_TS_ROOM;

///////////////////////////////////////////////////////////////////////////////
CSkl::CSkl() {
}

CSkl::~CSkl() {
}
///////////////////////////////////////////////////////////////////////////////

CSkl Skl;

bool CSkl::Initialization(void) {
    SKL_NUMBER = Proto->AddItem(TYPE_INT, "������");
    SKL_NAME = Proto->AddItem(TYPE_STRING, "��������");
    SKL_ALIAS = Proto->AddItem(TYPE_STRING, "�������������");
    SKL_USELESS = Proto->AddItem(TYPE_STRUCT, "�������������");
    CItemProto *skuse = Proto->GetItem(SKL_USELESS);
    SKL_USE_CLASS = skuse->AddItem(TYPE_LIST, "���������", true, ParserConst.GetList(LIST_CLASS));
    SKL_USE_TEMPL  = skuse->AddItem(TYPE_LIST, "��������", true, ParserConst.GetList(LIST_GODS));
    SKL_USE_PRACT = skuse->AddItem(TYPE_INT, "����������");
    SKL_USE_LEVEL  = skuse->AddItem(TYPE_INT, "�������");
    SKL_USE_EFFECT = skuse->AddItem(TYPE_INT, "�������������");
    SKL_MISS_ATTACK = Proto->AddItem(TYPE_STRUCT, "������");
    CItemProto *mMis = Proto->GetItem(SKL_MISS_ATTACK);
    SKL_MA_CHAR = mMis->AddItem(TYPE_STRING, "��������");
    SKL_MA_VICT = mMis->AddItem(TYPE_STRING, "������");
    SKL_MA_ROOM = mMis->AddItem(TYPE_STRING, "�������");
    SKL_HIT_ATTACK = Proto->AddItem(TYPE_STRUCT, "���������");
    CItemProto *mHit = Proto->GetItem(SKL_HIT_ATTACK);
    SKL_HA_CHAR = mHit->AddItem(TYPE_STRING, "��������");
    SKL_HA_VICT = mHit->AddItem(TYPE_STRING, "������");
    SKL_HA_ROOM = mHit->AddItem(TYPE_STRING, "�������");
    SKL_DTH_ATTACK = Proto->AddItem(TYPE_STRUCT, "������");
    CItemProto *mDth = Proto->GetItem(SKL_DTH_ATTACK);
    SKL_DA_CHAR = mDth->AddItem(TYPE_STRING, "��������");
    SKL_DA_VICT = mDth->AddItem(TYPE_STRING, "������");
    SKL_DA_ROOM = mDth->AddItem(TYPE_STRING, "�������");
    SKL_NHS_ATTACK = Proto->AddItem(TYPE_STRUCT, "������������");
    CItemProto *mNhs = Proto->GetItem(SKL_NHS_ATTACK);
    SKL_NA_CHAR = mNhs->AddItem(TYPE_STRING, "��������");
    SKL_NA_VICT = mNhs->AddItem(TYPE_STRING, "������");
    SKL_NA_ROOM = mNhs->AddItem(TYPE_STRING, "�������");
    SKL_ARM_ATTACK = Proto->AddItem(TYPE_STRUCT, "����������");
    CItemProto *mArm = Proto->GetItem(SKL_ARM_ATTACK);
    SKL_AM_CHAR = mArm->AddItem(TYPE_STRING, "��������");
    SKL_AM_VICT = mArm->AddItem(TYPE_STRING, "������");
    SKL_AM_ROOM = mArm->AddItem(TYPE_STRING, "�������");
    SKL_ARM2_ATTACK = Proto->AddItem(TYPE_STRUCT, "������������");
    CItemProto *mA2 = Proto->GetItem(SKL_ARM2_ATTACK);
    SKL_A2_CHAR = mA2->AddItem(TYPE_STRING, "��������");
    SKL_A2_VICT = mA2->AddItem(TYPE_STRING, "������");
    SKL_A2_ROOM = mA2->AddItem(TYPE_STRING, "�������");

    /* SKL_TMPL = Proto->AddItem(TYPE_STRUCT,"������");
     CItemProto *tm = Proto->GetItem(SKL_TMPL);
      SKL_TM_CHAR = tm->AddItem(TYPE_STRING,"��������");
      SKL_TM_VICT = tm->AddItem(TYPE_STRING,"������");
      SKL_TM_ROOM = tm->AddItem(TYPE_STRING,"�������");

     SKL_TMPS = Proto->AddItem(TYPE_STRUCT,"������_������");
     CItemProto *ts = Proto->GetItem(SKL_TMPS);
      SKL_TS_CHAR   = ts->AddItem(TYPE_STRING,"��������");
      SKL_TS_VICT   = ts->AddItem(TYPE_STRING,"������");
      SKL_TS_ROOM   = ts->AddItem(TYPE_STRING,"�������"); */

    return CheckInit();
}

