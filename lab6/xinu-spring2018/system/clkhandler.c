/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;

	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	struct procent * prptr = &proctab[currpid];
	if(prptr->prhascb2) {
		if(clktime-prptr->prstarttime >= prptr->prtmarg) {
//			kprintf("yep\n");
			if(prptr->prfirstsig == XSIGXTM || prptr->prsecondsig == XSIGXTM
				|| prptr->prthirdsig == XSIGXTM) {
				//do nothing
			} else if (prptr->prfirstsig == 0) {
//				kprintf("******************FIRST***********************");
				prptr->prfirstsig = XSIGXTM;
			} else if (prptr->prsecondsig == 0) {
//				kprintf("******************SECOND***********************");
				prptr->prsecondsig = XSIGXTM;
			} else if (prptr->prthirdsig == 0) {
//				kprintf("******************THIRD***********************");
				prptr->prthirdsig = XSIGXTM;
			}
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
