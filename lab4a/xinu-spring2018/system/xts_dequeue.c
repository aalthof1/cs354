/* xts_dequeue.c  -  xts_dequeue */

#include <xinu.h>

/*--------------------------------------------------------------------
 * xts_dequeue - dequeue highest priority process from ready queue
 *------------------------------------------------------------------*/

pid32 xts_dequeue(void) {
	int i = 59;
	pid32 ret = 0;
	for(;i>=0;i--) {
		struct xts_multifb * fblev = &xts_ready[i];
		if(fblev->status == 1) {
			#ifdef DEBUG
			kprintf("in xts_dequeue: i=%d\n",i);
			#endif
			ret = dequeue(queuetab[queuetab[fblev->queue_head].qnext].qkey);
			if(isempty(fblev->queue_head)) {
				fblev->status = 0;
			}
			#ifdef DEBUG
			kprintf("ret=%d\n",ret);
			#endif
			return ret;
		}
	}
	return ret;
}
