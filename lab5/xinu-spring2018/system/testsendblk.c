/* testsndblk.c  --  testsendblk */

#include <xinu.h>

/*----------------------------------------------------------------------
 * testsendblk - test for the sendblk function. Calls sendblk with a
 *	print statement to determine order of execution
 *--------------------------------------------------------------------*/

void testsendblk(pid32 pid)
{
	#ifdef DEBUG
	kprintf("\nin sendblk with pid: %d, param=%d\n",currpid,pid);
	#endif
	int ret = sendblk(pid,currpid);
	#ifdef DEBUG
	kprintf("\nsent %d with ret=%d\n",currpid,ret);
	#endif
}
