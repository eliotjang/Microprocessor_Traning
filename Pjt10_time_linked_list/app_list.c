#include <stdio.h>
#include <stdlib.h>

#include "app_list.h"

extern struct node *Head = NULL;

struct timer *Thead = NULL;
void insert_timer(struct task *tskp, int ms)
{
	int	total;
	struct timer *tp, *cp, *pp;

	tp = get_timer();
	tp->task = *tskp;
	tp->time = ms;

	if (Thead == NULL) {
		Thead = tp, tp->link = NULL;
		return;
	}
	pp = NULL, total = 0;
	for (cp = Thead; cp; cp = cp->link) {
		total += cp->time;
		if(total >= ms)
			break;
		pp = cp;
	}
	if (pp == NULL) {
		cp->time -= tp->time;
		tp->link = cp, Thead = tp;
	else if (cp == NULL) {
		tp->time -= total;
		pp->link = tp;
		tp->link = NULL;
	}
	else {
		total -= cp->time;
		tp->time -= total;
		cp->time -= total;
		pp->link = tp;
		tp->link = cp;
	}
}

struct node *get_node()
{
	struct node *cp;

	cp = (struct node *)malloc(sizeof(struct node));
	return(cp);
}

void free_node(struct node *np)
{
	free(np);
}

void insert_node_head(struct node *np)
{
	if (!Head) {
		Head = np;
		np->link = NULL;
	}
	else {
		np->link = Head;
		Head = np;
	}
}

void insert_node_tail(struct node *np)
{
	struct node *cp;

	if(!Head)
		Head = np;
	else {
		for (cp = Head; cp->link != NULL; cp = cp->link)
			;
		cp->link = np;
	}
	np->link = NULL;
}

void insert_node_ascn(struct node *np)
{
	struct node *cp, *pp;
	if(!Head) {
		Head = np;
		np->link = NULL;
	}
	else {
		for (cp = Head, pp = NULL; cp != NULL && strcmp(cp->data,np->data)>1; pp = cp, cp = cp->link)
			;
		if (pp == NULL) {
			np->link = Head;
			Head = np;
		} else {
			//여기서 strcmp 필요할 듯
			np->link = pp->link;
			pp->link = np;
		}
	}
}

void tour_list()
{
	struct node *cp;
	printf("\n");
	for (cp = Head; cp != NULL; cp = cp->link)
		printf("-->%s", cp->data);
	printf("\n");
}

void free_list()
{
	struct node *cp;
	for ( ; Head != NULL ; ) {
		cp = Head;
		Head = cp->link;
		free_node(cp);
	}
}


void app_list(char *ap)
{
	char buf[8], how = 'a';
	struct node *np;

	if (ap) how = *ap;
	while(1) {
		printf("> ");
		if (fgets(buf, 8, stdin) == NULL) // 엔터가 붙어있다.
			break;
		np = get_node();
		strcpy(np->data, buf);
		switch(how) {
			case 'h' : insert_node_head(np); break;
			case 't' : insert_node_tail(np); break;
			default : insert_node_ascn(np);
		}
	}
	tour_list();
	free_list();
}
