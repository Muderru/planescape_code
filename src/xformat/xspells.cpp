/**************************************************************************
    ��� "����� ����" (�) 2002-2003 ������ �������
    �������� ������ �������� ����
 **************************************************************************/

#include "xspells.h"
#include "parser_id.h"

// ����������� �������� ����������
int SPL_NUMBER; //����������
int SPL_NAME; //��������
int SPL_UNAME; //�������
int SPL_ALIAS; //�����������
int SPL_PROCEDURE; //���������
int SPL_SPHERE; //����� (�����)
int SPL_MANA; //����
int SPL_LEVEL; //�������
int SPL_SKILL; //������
int SPL_QUALITY; //�����
int SPL_DAMAGE; //�����
int SPL_TDAMAGE; //�����
int SPL_AGRO; //��������
int SPL_TARGET; //����
int SPL_POSITION; //���������
int SPL_LAG; //��������
int SPL_VLAG; //���������
int SPL_MEMORY; //�����������
int SPL_CONCENT; //������������
int SPL_SAVES; //����������
int SPL_SCORE; //����
int SPL_AFF_MESS; //��������
int SPL_SAY_MESS; //������������
int SPL_MESSAGES_AFFECT; //����������
int SPL_MESSAGES_DAMAGE;  //����������
int SPL_MESSAGES_OBJECT;  //����������

//���.��������� ��������
int SPL_AMESS_SCH; //������_�����
int SPL_AMESS_SRM; //������_�������
int SPL_AMESS_ECH; //�����_�����
int SPL_AMESS_ERM; //�����_�������

//���.��������� ������������
int SPL_SAY_CHAR; //�����
int SPL_SAY_VICTIM; //������
int SPL_SAY_ROOM; //�������
int SPL_SAY_ME;  //������
int SPL_SAY_MROOM; //��������

//���.��������� x���������
int SPL_MESSAGE_KIL_CHAR;   //����_�����
int SPL_MESSAGE_KIL_VICT;   //����_������
int SPL_MESSAGE_KIL_ROOM;   //����_�������
int SPL_MESSAGE_HIT_CHAR;   //����_�����
int SPL_MESSAGE_HIT_VICT;   //����_������
int SPL_MESSAGE_HIT_ROOM;   //����_�������
int SPL_MESSAGE_HIT_ME;     //����_������
int SPL_MESSAGE_HIT_MROM;   //����_��������
int SPL_MESSAGE_MIS_CHAR;   //������_�����
int SPL_MESSAGE_MIS_VICT;   //������_������
int SPL_MESSAGE_MIS_ROOM;   //������_�������
int SPL_MESSAGE_MIS_ME;     //������_������
int SPL_MESSAGE_MIS_MROM;   //������_��������
int SPL_MESSAGE_GOD_CHAR;   //����_�����
int SPL_MESSAGE_GOD_ME;     //����_������
int SPL_MESSAGE_GOD_VICT;   //����_������
int SPL_MESSAGE_GOD_ROOM;   //����_�������
int SPL_MESSAGE_GOD_MROM;   //����_��������
int SPL_MESSAGE_ARM_CHAR;
int SPL_MESSAGE_ARM_VICT;
int SPL_MESSAGE_ARM_ROOM;
int SPL_MESSAGE_AR2_CHAR;
int SPL_MESSAGE_AR2_VICT;
int SPL_MESSAGE_AR2_ROOM;

///////////////////////////////////////////////////////////////////////////////
CSpl::CSpl() {
}

CSpl::~CSpl() {
}
///////////////////////////////////////////////////////////////////////////////

CSpl Spl;

bool CSpl::Initialization(void) {
    SPL_NUMBER = Proto->AddItem(TYPE_INT, "����������");
    SPL_NAME = Proto->AddItem(TYPE_STRING, "��������");
    SPL_UNAME = Proto->AddItem(TYPE_STRING, "�������");
    SPL_ALIAS = Proto->AddItem(TYPE_STRING, "�����������");
    SPL_PROCEDURE = Proto->AddItem(TYPE_STRING, "���������");
    SPL_SPHERE = Proto->AddItem(TYPE_LIST, "�����", true, ParserConst.GetList(LIST_SPH_TYPES));
    SPL_MANA = Proto->AddItem(TYPE_INT, "����");
    SPL_LEVEL = Proto->AddItem(TYPE_INT, "�������");
    SPL_SKILL = Proto->AddItem(TYPE_INT, "������");
//SPL_QUALITY = Proto->AddItem(TYPE_INT,"�����");
    SPL_DAMAGE = Proto->AddItem(TYPE_RANDOM, "�����", false);
    SPL_TDAMAGE = Proto->AddItem(TYPE_LIST, "�����", false, ParserConst.GetList(LIST_DAMAGE));
    SPL_AGRO = Proto->AddItem(TYPE_VECTOR, "��������", false, ParserConst.GetVector(VEC_AGRO_TYPE));
    SPL_TARGET = Proto->AddItem(TYPE_VECTOR, "����", true, ParserConst.GetVector(VEC_SPELL_TARGET));
    SPL_POSITION = Proto->AddItem(TYPE_LIST, "���������", false, ParserConst.GetList(LIST_POSITIONS));
    SPL_LAG = Proto->AddItem(TYPE_INT, "��������", false);
    SPL_VLAG = Proto->AddItem(TYPE_INT, "���������", false);
    SPL_MEMORY = Proto->AddItem(TYPE_INT, "�����������", false);
    SPL_CONCENT = Proto->AddItem(TYPE_INT, "������������", false);
    SPL_SAVES = Proto->AddItem(TYPE_INT, "����������", false);
    SPL_SCORE = Proto->AddItem(TYPE_STRING, "����", false);
    SPL_AFF_MESS = Proto->AddItem(TYPE_STRUCT, "��������", false);
    CItemProto *aff = Proto->GetItem(SPL_AFF_MESS);
    SPL_AMESS_SCH = aff->AddItem(TYPE_STRING, "������_�����", false);
    SPL_AMESS_SRM = aff->AddItem(TYPE_STRING, "������_�������", false);
    SPL_AMESS_ECH = aff->AddItem(TYPE_STRING, "�����_�����", false);
    SPL_AMESS_ERM = aff->AddItem(TYPE_STRING, "�����_�������", false);

    SPL_SAY_MESS = Proto->AddItem(TYPE_STRUCT, "������������", false);
    CItemProto *say = Proto->GetItem(SPL_SAY_MESS);
    SPL_SAY_CHAR   = say->AddItem(TYPE_STRING, "�����", false);
    SPL_SAY_VICTIM = say->AddItem(TYPE_STRING, "������", false);
    SPL_SAY_ROOM   = say->AddItem(TYPE_STRING, "�������", false);
    SPL_SAY_ME     = say->AddItem(TYPE_STRING, "������", false);
    SPL_SAY_MROOM  = say->AddItem(TYPE_STRING, "��������", false);

    SPL_MESSAGES_AFFECT = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *maff = Proto->GetItem(SPL_MESSAGES_AFFECT);
    SPL_MESSAGE_KIL_CHAR = maff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_KIL_VICT = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_KIL_ROOM = maff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_HIT_CHAR = maff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_HIT_VICT = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_HIT_ROOM = maff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_HIT_ME   = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_HIT_MROM = maff->AddItem(TYPE_STRING, "����_��������", false);
    SPL_MESSAGE_MIS_CHAR = maff->AddItem(TYPE_STRING, "������_�����", false);
    SPL_MESSAGE_MIS_VICT = maff->AddItem(TYPE_STRING, "������_������", false);
    SPL_MESSAGE_MIS_ROOM = maff->AddItem(TYPE_STRING, "������_�������", false);
    SPL_MESSAGE_MIS_ME   = maff->AddItem(TYPE_STRING, "������_������", false);
    SPL_MESSAGE_MIS_MROM = maff->AddItem(TYPE_STRING, "������_��������", false);
    SPL_MESSAGE_GOD_CHAR = maff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_GOD_ME   = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_GOD_MROM = maff->AddItem(TYPE_STRING, "����_��������", false);
    SPL_MESSAGE_GOD_VICT = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_GOD_ROOM = maff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_ARM_CHAR = maff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_ARM_VICT = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_ARM_ROOM = maff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_AR2_CHAR = maff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_AR2_VICT = maff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_AR2_ROOM = maff->AddItem(TYPE_STRING, "����_�������", false);

    SPL_MESSAGES_DAMAGE = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *daff = Proto->GetItem(SPL_MESSAGES_DAMAGE);
    SPL_MESSAGE_KIL_CHAR = daff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_KIL_VICT = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_KIL_ROOM = daff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_HIT_CHAR = daff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_HIT_VICT = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_HIT_ROOM = daff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_HIT_ME   = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_HIT_MROM = daff->AddItem(TYPE_STRING, "����_��������", false);
    SPL_MESSAGE_MIS_CHAR = daff->AddItem(TYPE_STRING, "������_�����", false);
    SPL_MESSAGE_MIS_VICT = daff->AddItem(TYPE_STRING, "������_������", false);
    SPL_MESSAGE_MIS_ROOM = daff->AddItem(TYPE_STRING, "������_�������", false);
    SPL_MESSAGE_MIS_ME   = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_MIS_MROM = daff->AddItem(TYPE_STRING, "����_��������", false);
    SPL_MESSAGE_GOD_CHAR = daff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_GOD_VICT = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_GOD_ROOM = daff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_ARM_CHAR = daff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_ARM_VICT = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_ARM_ROOM = daff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_AR2_CHAR = daff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_AR2_VICT = daff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_AR2_ROOM = daff->AddItem(TYPE_STRING, "����_�������", false);

    SPL_MESSAGES_OBJECT = Proto->AddItem(TYPE_STRUCT, "����������", false);
    CItemProto *oaff = Proto->GetItem(SPL_MESSAGES_OBJECT);
    SPL_MESSAGE_KIL_CHAR = oaff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_KIL_VICT = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_KIL_ROOM = oaff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_HIT_CHAR = oaff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_HIT_VICT = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_HIT_ROOM = oaff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_HIT_ME   = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_HIT_MROM = oaff->AddItem(TYPE_STRING, "����_��������", false);
    SPL_MESSAGE_MIS_CHAR = oaff->AddItem(TYPE_STRING, "������_�����", false);
    SPL_MESSAGE_MIS_VICT = oaff->AddItem(TYPE_STRING, "������_������", false);
    SPL_MESSAGE_MIS_ROOM = oaff->AddItem(TYPE_STRING, "������_�������", false);
    SPL_MESSAGE_MIS_ME   = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_MIS_MROM = oaff->AddItem(TYPE_STRING, "����_��������", false);
    SPL_MESSAGE_GOD_CHAR = oaff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_GOD_VICT = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_GOD_ROOM = oaff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_ARM_CHAR = oaff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_ARM_VICT = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_ARM_ROOM = oaff->AddItem(TYPE_STRING, "����_�������", false);
    SPL_MESSAGE_AR2_CHAR = oaff->AddItem(TYPE_STRING, "����_�����", false);
    SPL_MESSAGE_AR2_VICT = oaff->AddItem(TYPE_STRING, "����_������", false);
    SPL_MESSAGE_AR2_ROOM = oaff->AddItem(TYPE_STRING, "����_�������", false);

    return CheckInit();
}

