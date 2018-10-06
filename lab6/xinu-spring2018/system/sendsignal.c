/* sendsignal.c  -- sendsignal */

#include <xinu.h>

/*-------------------------------------------------------------------------------------------------
 * sendsignal - sends signal ssig to process with id pid
 *-------------------------------------------------------------------------------------------------
 */

syscall sendsignal(
			uint16 ssig,	/* Signal to send		*/
			pid32 pid	/* PID to send signal to	*/
		)
{
	intmask mask;		/* interrupt mask			*/
	struct procent * prptr;	/* Pointer to process table entry	*/

	mask = disable();
	if(isbadpid(pid)) {
		restore(mask);	
		return SYSERR;
	}
	if(ssig < XSIGRCV || ssig > XSIGXTM) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	restore(mask);
	return OK;
}
