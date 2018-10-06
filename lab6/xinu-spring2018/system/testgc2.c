/* testgc2.c - testgc2 */

#include <xinu.h>

/*----------------------------------------------------------------------
 * testgc2 - test for garbage collection
 *----------------------------------------------------------------------
 */

void testgc2() {
	struct procent * prptr = &proctab[currpid];
	struct memstruct mem = prptr->memory;
	kprintf("next=%d\tnbytes=%d\tblkaddr=%d\n",mem.next,mem.nbytes,mem.blkaddr);
	char* temp = getmem(120);
	kprintf("next=%d\tnbytes=%d\tblkaddr=%d\n",mem.next,mem.nbytes,mem.blkaddr);
	mem = *(mem.next);
	kprintf("next=%d\tnbytes=%d\tblkaddr=%d\n",mem.next,mem.nbytes,mem.blkaddr);
}
