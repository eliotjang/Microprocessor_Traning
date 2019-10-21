
struct node {
	char data[8];
	struct node *link;
};

struct task {
	void (*fun)(void*);
	char arg[8];
};

struct timer {
	int time;
	struct task task;
	struct timer *link;
};

struct timer *get_timer()
{
	struct timer *tp;

	tp = (struct timer *)malloc(sizeof(*tp));
	return(tp);
}
// 구조체는 반드시 헤더파일에 선언

extern struct timer *Thead;

void insert_node_head(struct node *np);
void insert_node_tail(struct node *np);
void insert_node_ascn(struct node *np);
void free_node(struct node *np);
void tour_list();
void free_list();
void inset_timer(struct task *tskp, int ms);
struct timer *get_timer();
void tour_timer(), free_timer();

struct node *get_node();
