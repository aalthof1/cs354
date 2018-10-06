/* getmem.c - getmem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char  	*getmem(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent * prptr;	/* Pointer to current process	*/
	struct	memblk	*prev, *curr, *leftover;

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}
	prptr = &proctab[currpid];

	nbytes = (uint32) roundmb(nbytes);	/* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL) {			/* Search free list	*/

		if (curr->mlength == nbytes) {	/* Block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;
//			if(currpid != 0) {
//				prptr = &proctab[currpid];
//				struct memstruct currmemstruct = prptr->memory;
//				struct memstruct mem;
//				mem.next = NULL;
//				mem.blkaddr = (char*)curr;
//				mem.nbytes = (int)nbytes;
//				while(currmemstruct.next != NULL) {
//					currmemstruct = *(currmemstruct.next);
//				}
//				currmemstruct.next = &mem;
//			}
			restore(mask);
			return (char *)(curr);

		} else if (curr->mlength > nbytes) { /* Split big block	*/
			leftover = (struct memblk *)((uint32) curr +
					nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;
//			if(currpid != 0) {
//				prptr = &proctab[currpid];
//				struct memstruct* currmemstruct = &(prptr->memory);
//				struct memstruct mem;
//				mem.next = NULL;
//				mem.blkaddr = (char*)curr;
//				mem.nbytes = (int)nbytes;
//				while(currmemstruct->next != NULL) {
//					currmemstruct = currmemstruct->next;
//				}
//				currmemstruct->next = &mem;
//				kprintf("in getmem=%d\n",mem.blkaddr);
//			}
			restore(mask);
			return (char *)(curr);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
