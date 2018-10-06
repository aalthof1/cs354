/* sigcbreg.c  --  sigcbreg */

#include <xinu.h>

/*---------------------------------------------------------------------
 * cbreg - specify a user space callback function to be executed in
	it's context when a signal is received
 *-------------------------------------------------------------------*/

syscall sigcbreg(
	uint16 ssig,	/* signal to register callback for */
	int (* fnp)(void), /* pointer to the function to set as callback */
	uint32 tmarg	/* time argument for XSIGXTM */
	)
{
	intmask mask;	/* interrupt mask */
	struct procent *prptr;	/* pointer to current process */
	
	mask = disable();

	/* check for invalid conditions */
	if(ssig < XSIGRCV || ssig > XSIGXTM) {
		restore(mask);
		return SYSERR;
	}
	if(fnp == NULL) {
		restore(mask);
		return SYSERR;
	}
	if(ssig == XSIGXTM && tmarg < 0) {
		restore(mask);
		return SYSERR;
	}
	
	prptr = &proctab[currpid];
	if(ssig == XSIGRCV) { /* if signal is XSIGRCV */
		/* add the function to the process table entry */
		prptr->prhascb = 1;
		prptr->fptr = fnp;
	} else if(ssig == XSIGCHL) { /* if signal is XSIGCHL */
		/* add function to the process table entry to */
		prptr->prhascb1 = 1;
		prptr->fptr1 = fnp;
	} else if(ssig == XSIGXTM) { /* if signal is XSIGXTM */
		/* add function to process table entry */
		prptr->prhascb2 = 1;
		prptr->fptr2 = fnp;
		prptr->prtmarg = tmarg;
		prptr->prxtmsighand = 0;
	}

	restore(mask);
	return OK;	
}
