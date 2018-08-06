/* $Id$
 *
 * ruffina, 2009
 */
#ifndef MUDSCHEDULER_H
#define MUDSCHEDULER_H

#include "scheduler.h"
#include "oneallocate.h"

enum {
    SCDP_STARTUP   =   100, // mud startup 
    SCDP_BOOT_START=   200, // boot db starts 
    SCDP_BOOT_END  =   300, // boot db finishes 
    SCDP_INITIAL   =  1000, // beginning of the loop
    SCDP_IOINIT	   =  2000, // descriptors initialization
    SCDP_IOPOLL	   =  3000, // poll descriptiors for input
    SCDP_IOREAD	   =  4000, // read from descriptors
    SCDP_IOWRITE   =  5000, // write to descriptors
    SCDP_HEARTBEAT =  6000, // autonomous game pulse
    SCDP_FINAL	   = 10000, // end of the loop
    SCDP_SHUTDOWN  = 20000, // mud shutdown
};

class MudScheduler : public Scheduler, public OneAllocate {
public:	
    MudScheduler( );
    virtual ~MudScheduler( );
    
    /** ��������� ������ ����� ������� */
    void putTaskInSecond( SchedulerTaskPointer task );
    /** ��������� ������ ����� time ������ */
    void putTaskInSecond( long time, SchedulerTaskPointer task );
    /** ��������� ������ ��� ������ ���� */
    void putTaskStartup( SchedulerTaskPointer task );
    /** ��������� ������ ��� shutdown */
    void putTaskShutdown( SchedulerTaskPointer task );
    
    /** ��������� ���� �� ������ ������ ���� � ��������� ������ */
    void tickStartup();
    /** ��������� ���� �� ������ shutdown � ��������� ������ */
    void tickShutdown();

protected:
    static const long SHUTDOWN_TIME;
    static const long STARTUP_TIME;
};

#endif
