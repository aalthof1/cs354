/* sigcbunreg.c  --  sigcbunreg */

#include <xinu.h>

/*-------------------------------------------------------------------------------------------------
 * sigcbunreg - unregister a registered callback function for a specified signal
 *-------------------------------------------------------------------------------------------------
 */

syscall sigcbunreg(
			uint16 ssig	/* signal to unregister callback for */
		)
{
	intmask mask;			/* interrupt mask */
	struct procent * prptr;		/* pointer to process */

	mask = disable();	
	if(ssig < XSIGRCV || ssig > XSIGXTM) { /* ssig value is invalid */
		restore(mask);
		return SYSERR;
	}
	
	prptr = &proctab[currpid];
	if(ssig == XSIGRCV) {
		prptr->prhascb = 0;
		prptr->fptr = NULL;
	} else if(ssig == XSIGCHL) {
		prptr->prhascb1 = 0;
		prptr->fptr1 = NULL;
	} else if(ssig == XSIGXTM) {
		prptr->prhascb2 = 0;
		prptr->fptr2 = NULL;
	}
	restore(mask);
	return OK;
}
