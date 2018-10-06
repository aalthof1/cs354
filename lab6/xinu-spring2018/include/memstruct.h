/* memstruct.h */
/* added by Aaron Althoff for lab 6 */

struct memstruct {
	struct memstruct * next;	/* next memstruct	*/
	char*	blkaddr;		/* address of block	*/
	int	nbytes;			/* size of block	*/
};
