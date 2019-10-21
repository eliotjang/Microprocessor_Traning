
struct node {
	char data[8];
	struct node *link;
};
// 구조체는 반드시 헤더파일에 선언


void insert_node_head(struct node *np);
void insert_node_tail(struct node *np);
void insert_node_ascn(struct node *np);
void free_node(struct node *np);
void tour_list();
void free_list();

struct node *get_node();
