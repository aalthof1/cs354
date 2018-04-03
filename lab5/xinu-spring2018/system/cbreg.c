/* cbreg.c  --  cbreg */

#include <xinu.h>

/*---------------------------------------------------------------------
 * cbreg - specify a user space callback function to be executed in
	it's context when a message is successfully received
 *-------------------------------------------------------------------*/

syscall cbreg(int (* fnp)(void) /* pointer to the function to set as callback */
	)
{
	intmask mask;	/* interrupt mask */
	struct procent *prptr;	/* pointer to current process */
	
	mask = disable();
	prptr = &proctab[currpid];
	if(prptr->prhascb) { /* if process already has a cb registered */
		restore(mask);
		return SYSERR;
	}
	/* add the function to the process table entry */
	prptr->prhascb = 1;
	prptr->fptr = fnp;

	restore(mask);
	return OK;	
}
