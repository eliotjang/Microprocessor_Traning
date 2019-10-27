// queue.c
#include "queue.h"

#define QI_SIZE 128
#define QO_SIZE 128

static char qi[QI_SIZE], qo[QO_SIZE];
static int fi, ri, fo, ro;

void q_init()
{
	fi = ri = fo = ro = 0;
}

int qi_insert(char ch)
{
	if((ri+1) % QI_SIZE == fi)
		return(0);	//full
	ri = (ri+1) % QI_SIZE;
	qi[ri] = ch;
	return(1);
}

int qi_delete()
{
	if(ri == fi)
		return(0);	//empty
	fi = (fi+1) % QI_SIZE;
	return(qi[fi]);
}

int qo_insert(char ch)
{
	if((ro+1) % QO_SIZE == fo)
		return(0);	//full
	ro = (ro+1) % QO_SIZE;
	qo[ro] = ch;
	return(1);
}

int qo_delete()
{
	if(ro == fo)
		return(0);	//empty
	fo = (fo+1) % QO_SIZE;
	return(qo[fo]);
}
