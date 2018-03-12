#define XTS_PRIOLEV 60

struct xts_tab {
	int xts_quantum;	// new time slice
	int xts_tqexp;		// new priority: CPU-intensive
	int xts_slpret;		// new priority: I/O-intensive
};

struct xts_multifb {
	int status;
	qid16 queue_head;
	qid16 queue_tail;
};

extern struct xts_multifb xts_ready[];
extern struct xts_tab xts_conf[];
