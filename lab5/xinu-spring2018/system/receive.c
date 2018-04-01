/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	/*Added by Aaron Althoff for lab 5*/
	if(prptr->rcpblkflag) {
		qid16 qhead = prptr->sendqueue;
		pid32 pid = dequeue(qhead);
		struct procent * prsnd = &proctab[pid];
		/* if queue is empty, set rcpblkflag to 0 */
		if(isempty(qhead)) {
			prptr->rcpblkflag = 0;
		}
		prptr->prhasmsg = 1;
		prptr->prmsg = prsnd->sendblkmsg;
		prsnd->sendblkflag = 0;
		prsnd->prstate = PR_READY;
	}
	/*--------------------------------*/
	restore(mask);
	return msg;
}
