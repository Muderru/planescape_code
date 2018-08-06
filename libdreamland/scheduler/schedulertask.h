/* $Id: schedulertask.h,v 1.1.2.2.10.3 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
/***************************************************************************
                          schedulertask.h  -  description
                             -------------------
    begin                : Wed May 30 2001
    copyright            : (C) 2001 by Igor S. Petrenko
    email                : nofate@europe.com
 ***************************************************************************/

#ifndef SCHEDULERTASK_H
#define SCHEDULERTASK_H

#include "dlobject.h"
#include "pointer.h"

class SchedulerPriorityMap;

/**
 * @short ������ ��� ������������
 * @author Igor S. Petrenko
 * @see Scheduler
 */
struct SchedulerTask : public virtual DLObject
{
    typedef ::Pointer<SchedulerTask> Pointer;
    typedef ::Pointer<SchedulerPriorityMap> SchedulerPriorityMapPointer;

    /** ���������� ����� ������������ ������ */
    virtual void before( );
    /** ��������� ������ */ 
    virtual void run( );
    /** ���������� ����� ������������ ������ */
    virtual void after( );
    /** �������� ���� � list */
    virtual void putInto( SchedulerPriorityMapPointer& list );
    virtual int getPriority( ) const = 0;
};


#endif
