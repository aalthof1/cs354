/* xts-enqueue.c  -  xts_enqueue */

#include <xinu.h>

/*--------------------------------------------------------------------
 *  xts_enqueue - used for timesharing scheduler, enqueues the PID to
	the appropriate priority level
 *------------------------------------------------------------------*/

int xts_enqueue(
		pid32 pid,  /* pid of the process being added */
	        pri16 prio  /* prioriity level of the process */
		)
{
	if(prio < 0 || prio > 59) { /* prio value invalid */
		return -1;
	}

	/* feedback level of priority */

	struct xts_multifb * fblev = &xts_ready[prio];

	/* try to enqueue the pid to the queue */

	int ret = enqueue(pid,fblev->queue_head);

	if(ret == SYSERR) { /* enqueue fails */
		return -1;
	} else { /* enqueue successful */
		fblev->status = 1;
		return 0;
	}
}
