/* $Id: schedulerlist.h,v 1.1.2.1.28.4 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 * based on idea by NoFate, 2001
 */
#ifndef SCHEDULERLIST_H
#define SCHEDULERLIST_H

#include <list>

#include "dlobject.h"

class SchedulerTask;

/**
 * @short ������� ������� ��� ������������� ������� � ����������
 * @see Scheduler
 * @see SchedulerQueue
 */

typedef ::Pointer<SchedulerTask> SchedulerTaskPointer;

class SchedulerList : public std::list<SchedulerTaskPointer>, public virtual DLObject
{
public:
    typedef ::Pointer<SchedulerList> Pointer;

    SchedulerList();
    virtual ~SchedulerList();

    void put( SchedulerTaskPointer pointer );
    void tick( );
    /** �������� ����� ��� ������ ��������� ���� */
    void slay( SchedulerTaskPointer& task );
    /** �������� ����� ��� ������ � ���� ���������� */
    void slayInstance( SchedulerTaskPointer& task );

};

#endif
