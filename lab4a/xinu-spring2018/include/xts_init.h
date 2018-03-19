#define XTS_PRIOLEV 60

struct xts_tab {
	int xts_quantum;	//new time slice
	int xts_tqexp;		//new priority: CPU-intensive
	int xts_slpret;		//new priority: I/O-intensive
};

struct xts_multifb {
	int status;		//binary: 0 means empty, 1 is nonempty
	qid16 queue_head;	//head of the queue
	qid16 queue_tail;	//tail of the queue
};

extern struct xts_multifb xts_ready[];
extern struct xts_tab xts_conf[];
