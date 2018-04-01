/* testreceive.c  --  test receiving with sendblk */

#include <xinu.h>

/*---------------------------------------------------------------------
 * testreceive - tests receive by printing the order that things
	are received in
 *--------------------------------------------------------------------*/

void testreceive() {
	#ifdef DEBUG
	kprintf("\nin testreceive with pid: %d\n",currpid);
	#endif
	umsg32 firstmsg = receive();
	kprintf("\nreceived one: %d\n",firstmsg);
	#ifdef DEBUG
	struct procent * prptr = &proctab[currpid];
	qid16 qhead = prptr->sendqueue;
	pid32 next = firstid(qhead);
	kprintf("next pid = %d\n",next);
	#endif
	umsg32 secondmsg = receive();
	kprintf("\nreceived two\n");
	umsg32 thirdmsg = receive();
	kprintf("\nreceived three\n");
	umsg32 fourthmsg = receive();
	kprintf("\nreceived four\n");
	kprintf("\nmessages received in order: %d, %d, %d, %d\n",firstmsg,secondmsg,thirdmsg,fourthmsg);
}
