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
			ret = dequeue(fblev->queue_head);
			if(isempty(fblev->queue_head)) {
				fblev->status = 0;
			}
			return ret;
		}
	}
	return ret;
}
