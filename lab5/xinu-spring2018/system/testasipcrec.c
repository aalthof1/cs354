/* testasipcrec.c  --  testasipcrec */

#include <xinu.h>

/*--------------------------------------------------------------------
 * testasipcrec - test receiving process for the asynchronis IPC
	implementation with callbacks
 *------------------------------------------------------------------*/

umsg32 mbuf = 0;

void testasipcrec() {
	if(cbreg(&callback) != OK) {
		kprintf("cb registration failed!\n");
		return;
	}
	sleepms(100);
	kprintf("message %d received\n",mbuf);
	sleepms(100);
	kprintf("message %d received\n",mbuf);
	sleepms(100);
	kprintf("message %d received\n",mbuf);
	sleepms(100);
	kprintf("message %d received\n",mbuf);
}
