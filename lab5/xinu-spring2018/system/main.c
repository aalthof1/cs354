/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
//	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
//	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
//	kprintf("\n...creating a shell\n");
//	recvclr();
//	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

//	while (TRUE) {
//		receive();
//		sleepms(200);
//		kprintf("\n\nMain process recreating shell\n\n");
//		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
//	}

	pid32 testrec = create(testreceive, 2048, 10, "testrec", 0);
	struct procent * prptr = &proctab[testrec];
	#ifdef DEBUG
	kprintf("testrec created with pid %d and state %d\n",testrec,prptr->prstate);
	#endif
	resume(testrec);
	resume(create(testsendblk, 2048, 16, "testsb1", 1, testrec));
	resume(create(testsendblk, 2048, 15, "testsb2", 1, testrec));
	resume(create(testsendblk, 2048, 15, "testsb3", 1, testrec));
	resume(create(testsendblk, 2048, 15, "testsb4", 1, testrec));
	
	return OK;
}
