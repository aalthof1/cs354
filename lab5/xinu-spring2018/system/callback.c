/* callback.c  --  callback */

#include <xinu.h>

/*-------------------------------------------------------------------
 *  callback - sample callback that receives a message and prints
	it
 *-----------------------------------------------------------------*/

int32 callback() 
{
	extern umsg32 mbuf;
	mbuf = receive();
	kprintf("Message %d received by callback for process %d\n",mbuf,currpid);
	return OK;
}
