/* $Id: schedulerprioritymap.h,v 1.1.4.1.10.3 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
#ifndef SCHEDULERPRIORITYMAP_H
#define SCHEDULERPRIORITYMAP_H

#include <map>

#include "dlobject.h"
#include "schedulerlist.h"

class SchedulerList;
class SchedulerTask;

/**
 * @short ��� �������� �������, ��������������� �� ����������
 * @see Scheduler
 * @see SchedulerQueue
 */
class SchedulerPriorityMap : public std::map<int, SchedulerList>, public virtual DLObject {
public:
	typedef ::Pointer<SchedulerPriorityMap> Pointer;
	typedef ::Pointer<SchedulerTask> SchedulerTaskPointer;

public:
	SchedulerPriorityMap();

	void tick( );
	/** �������� ����� ��� ������ ��������� ���� */
	void slay( SchedulerTaskPointer& task );
	/** �������� ����� ��� ������ � ���� ���������� */
	void slayInstance( SchedulerTaskPointer& task );
	/** ������� ������� ��������� */
	int getPriority( ) const;

private:
	int priority;
};

#endif
