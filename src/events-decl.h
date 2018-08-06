#ifndef EVENTS_DECL_H
#define EVENTS_DECL_H

#define AEVENT(function) void (function)(struct event_param_data *params)

#define STOP_NONE 0
#define STOP_HIDDEN 1
#define STOP_ALL 255

/***********************************************************************************************************************/
/* �������� ������� ���������� �������� */
/***********************************************************************************************************************/

struct event_item_data {
    int time;   //����� ��������� ������� (� ��������)
    int ctime;   //�������� ����� �������, ��������� ��� � �������
    int stopflag;   //���� ���� �������
    bool show_meter;  //���������� actor� ������ ��������� �������
    bool saved;   //���� ������ ������� � actor (true - ����������)
    struct event_param_data *params;
    int script;   //������ �������� ������� ��������� ��� �������
    AEVENT(*func);   //�������� ��������� ������� ��������� ��� �������

    struct event_item_data *next;
};

struct event_param_data {

    struct char_data *actor;      //�������� ������� (�������� ��� ������) ����� ���� NULL
    struct char_data *victim; //����������� ������� (�������� ��� ������) ����� ���� NULL
    struct obj_data *object; //������� ������� (������ � ����) ����� ���� NULL
    int stopflag;   //���� ���� �������
    bool show_meter;  //���������� actor� ������ ��������� �������
    bool saved;   //���� ������ ������� � actor (true - ����������)
    int narg[4];   //������ int-���������� ��� �������� ������
    const char *sarg;   //��������� ��������
    const char *action;   //������ ������� ������������ � actor � ������� ��� ���������� �������
    const char *status;   //������ ������� ������������ � actor � ����� ��� ���������� �������
    const char *vaction;  //������ ������� ������������ � victim � ������� ��� ���������� �������
    const char *vstatus;  //������ ������� ������������ � victim � ����� ��� ���������� �������
    const char *raction;  //������ ������� ������������ � ������� victim (��� actor) ��� ���������� �������
    const char *rstatus;  //������ ������� ������������ � �������
    const char *sto_actor;  //������ ��������� actor ��� ������ �������
    const char *sto_victim;  //������ ��������� victim ��� ������ �������
    const char *sto_room;  //������ ��������� � ������� actor ��� ������ �������
    const char *bto_actor;  //������ ��������� actor ��� ���������� �������
    const char *bto_victim;  //������ ��������� victim ��� ���������� �������
    const char *bto_room;  //������ ��������� � ������� actor ��� ���������� �������
};

extern struct event_item_data *events_list;

#endif
