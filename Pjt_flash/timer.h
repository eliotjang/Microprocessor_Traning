struct task {
	void (*fun)(void *);
	char arg[8];
};

struct timer {
	int time;
	struct task task;
	struct timer *link;
};

extern struct timer *Thread;
void insert_timer(struct task *tskp, int ms);
struct timer *get_timer();
void tour_timer();
void free_timer();
