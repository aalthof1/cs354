/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}


	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	/*-----------------Added by Aaron Althoff for lab 4-------------*/

	ptold->prcputot += clkmilli - ptold->prctxswbeg; /* update time process has been running */
	
	#ifdef DEBUG
	kprintf("\nin resched\n");
	kprintf("name:%s\tprio:%d\n",ptold->prname,ptold->prprio);
	#endif
	/* Update priority */

	struct xts_tab * oldprio = &xts_conf[ptold->prprio];
	if(preempt < oldprio->xts_quantum) { /* process does not use all of it's CPU time */
		if (ptold->prprio == 0) {}
		else if (ptold->prprio < 59) { /* do not update priority above max priority */
			ptold->prprio++;
		}
	} else { /* process uses all of it's CPU time */
		if (ptold->prprio == 0) {}
		else if (ptold->prprio > 1) { /* do not allow process to go below priority of 1 */
			ptold->prprio--;
		}
	}
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > xts_priochk()) { /* process has highest priority */
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		xts_enqueue(currpid, ptold->prprio); /* add pid to multifb table */
	}

	/*----------------------------------------------------------------*/

	/* Force context switch to highest priority ready process */
	currpid = xts_dequeue();
	ptnew = &proctab[currpid];
	#ifdef DEBUG
	kprintf("new - name:%s\tprio:%d\n",ptnew->prname,ptnew->prprio);
	#endif
	/*Added by Aaron Althoff for lab 4*/
	ptnew->prctxswbeg = clkmilli; /* update time process was ctxswed in */
	ptnew->prstate = PR_CURR;
	struct xts_tab * newprio = &xts_conf[ptnew->prprio];
	preempt = newprio->xts_quantum;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
