#include <xinu.h>

int cb1(){
	kprintf("in cb for XSIGRCV\n");
	return 0;
}
int cb2(){
	kprintf("in cb for XSIGCHL\n");
	return 0;
}
int cb3(){
	kprintf("in cb for XSIGXTM\n");
	return 0;
}

void testchild() {
	kprintf("in suicidal function\n");
	sleepms(1000);
}

void testrcv() {
	kprintf("in sending function\n");
	struct procent * prptr = &proctab[currpid];
	send(prptr->prparent,88);
	sleepms(200);
	kprintf("killing sending function\n");
}

void testgc() {
	if(sigcbreg(XSIGRCV,&cb1,-1) != OK) {
		kprintf("cb1 failed\n");
	} else {
		kprintf("Success1\n");
	}	
	if(sigcbreg(XSIGCHL,&cb2,-1) != OK) {
		kprintf("cb2 failed\n");
	} else {
		kprintf("Success2\n");
	}
	if(sigcbreg(XSIGXTM,&cb3,1) != OK) {
		kprintf("cb3 failed\n");
	} else {
		kprintf("Success3\n");
	}
	struct procent * prptr = &proctab[currpid];
	pid32 child = create(testchild,1024,9,"testchild",0);
	resume(child);
	sleepms(1500);
	int i = 0;
	while(i<10000000){i++;}
//	pid32 ret = childwait();
//	if(child == ret) {
//		kprintf("BLOCKING SUCCESS\n");
//	} else {
//		kprintf("BLOCKING FAILED\n");
//	}
	sleepms(20);
	kprintf("exitting testgc\n");
}

