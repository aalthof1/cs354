/* xts_proichk.c  -  xts_priochk */

#include <xinu.h>

/*------------------------------------------------------------------
 * xts_priochk  -- returns the highest priority level of ready 
 * processes
 *-----------------------------------------------------------------*/

pri16 xts_priochk(void)
{
	int i = 59;
	for (; i >= 0; i--) {
		struct xts_multifb * fblev = &xts_ready[i];
		if(fblev->status == 1) {
			return i;
		}
	}	
}
