/* sigcheck.c - sigcheck */

#include <xinu.h>

/*----------------------------------------------------------------------
 * sigcheck - checks if any signals have been received and handles them
 * in the correct order
 *----------------------------------------------------------------------
 */

syscall sigcheck()
{
	intmask mask;	/* interrupt mask */
	struct procent * prptr;	/* pointer to current process */
	int (* fnptr)();

	mask = disable();
	prptr = &proctab[currpid];
	while(prptr->prfirstsig != 0) {
		switch(prptr->prfirstsig) {
			case XSIGRCV:
				if(prptr->prhascb) {
					fnptr = prptr->fptr;
					restore(mask);
					(*fnptr)();
				}
				prptr->prfirstsig = prptr->prsecondsig;
				prptr->prsecondsig = prptr->prthirdsig;
				prptr->prthirdsig = 0;
				break;
			case XSIGCHL:
				if(prptr->prhascb1) {
					fnptr = prptr->fptr1;
					restore(mask);
					(*fnptr)();
				}
				prptr->prfirstsig = prptr->prsecondsig;
				prptr->prsecondsig = prptr->prthirdsig;
				prptr->prthirdsig = 0;
				break;
			case XSIGXTM:
				if(prptr->prhascb2) {
					fnptr = prptr->fptr2;
					restore(mask);
					(*fnptr)();
				}
				prptr->prfirstsig = prptr->prsecondsig;
				prptr->prsecondsig = prptr->prthirdsig;
				prptr->prthirdsig = 0;
				break;
			default:
				prptr->prfirstsig = prptr->prsecondsig;
				prptr->prsecondsig = prptr->prthirdsig;
				prptr->prthirdsig = 0;
		}
	}
	return OK;
}
