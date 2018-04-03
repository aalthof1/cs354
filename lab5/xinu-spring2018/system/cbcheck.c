/* cbcheck.c  --  cbcheck */

#include <xinu.h>

/*-----------------------------------------------------------------------------------------------------------------------------------------------------
 *  cbcheck - function called by ctxsw to see if a function being switched into has a registered callback function and has recieved a message. if
	both are true it executes the callback function
 *---------------------------------------------------------------------------------------------------------------------------------------------------*/

void cbcheck() {
	intmask mask; /* interrupt mask */
	struct procent * prptr; /* pointer to the process table entry */
	#ifdef DEBUG
	kprintf("in cbcheck\n");
	#endif
	mask = disable();
	prptr = &proctab[currpid];
	if(prptr->prhasmsg && prptr->prhascb) {
		int (*ptr)() = prptr->fptr;
		restore(mask);
		(*ptr)();
	} else {
		restore(mask);
		return;
	}
}
