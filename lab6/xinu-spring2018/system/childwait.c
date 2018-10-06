/* childwait.c - childwait */

#include <xinu.h>

/*----------------------------------------------------------------------
 * childwait - called by parent process, returns pid of child process
 * that has terminated. If no child process has terminated the calling
 * process blocks until a child terminates or returns SYSERR if there
 * are no child processes
 *----------------------------------------------------------------------
 */

pid32 childwait()
{
	intmask mask;	/* interrupt mask */
	struct procent * prptr;	/* pointer to process table entry */

	mask = disable();
	prptr = &proctab[currpid];
	if(prptr->prchlnum == 0) {
		restore(mask);
		return SYSERR;
	}
	if(prptr->prchldterm != 0) {
		restore(mask);
		pid32 temp = prptr->prchldterm;
		prptr->prchldterm = 0;
		return temp;
	}
	kprintf("in childwait blocking\n");
	prptr->prstate = PR_CHLDWAIT;
	resched();
	pid32 temp = prptr->prchldterm;
	prptr->prchldterm = 0;
	restore(mask);
	return temp;
}
