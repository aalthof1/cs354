/* sendblk.c  --  sendblk */

#include <xinu.h>

/*---------------------------------------------------------------------
 *  sendblk - blocking version of the send system call. if sendblk
 *	tries to send to a process that already has a message waiting
 *	the process that called sendblk blocks and it's message is
 *	added to a queue until the recieving process calls recieve and
 *	the message is set to the recievers prmsg procent field
 *-------------------------------------------------------------------*/

syscall sendblk(
		pid32	pid,		/* ID of recipient process	*/
		umsg32	msg		/* Contents of message		*/
	)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct procent *prptr;		/* Ptr to process' table entry	*/
	struct procent *currptr;	/* Ptr to current process	*/
	#ifdef DEBUG
	kprintf("ONE\n");
	#endif
	mask = disable();
	prptr = &proctab[pid];
	#ifdef DEBUG
	kprintf("prstate=%d\n",prptr->prstate);
	#endif
	if(isbadpid(pid)) {
		#ifdef DEBUG
		kprintf("ISBADPID\n");
		#endif
		restore(mask);
		return SYSERR;
	}
	#ifdef DEBUG
	kprintf("TWO\n");
	#endif
	/* if recieving process does not have a message, send	*/
	if(prptr->prhasmsg == FALSE) {
//		restore(mask);
		return send(pid,msg);
	}
	#ifdef DEBUG
	kprintf("THREE\n");
	#endif
	
	currptr = &proctab[currpid];

	/* update process table for recieving process */
	if(prptr->sendqueue == 0) {
		prptr->sendqueue = newqueue();
		#ifdef DEBUG
		kprintf("queue: %d\n",prptr->sendqueue);
		#endif
	}
	prptr->rcpblkflag = 1;
	pid32 enq = enqueue(currpid,prptr->sendqueue);
	#ifdef DEBUG
	kprintf("enq=%d\n",enq);
	#endif

	/* update process table for sending process */
	currptr->sendblkflag = 1;
	currptr->sendblkmsg = msg;
	currptr->sendblkrcp = pid;
	currptr->prstate = PR_SNDBLK;
	resched(); /* block until message is sent */

	restore(mask);
	return OK;

}










