#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <avr/interrupt.h>
#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>

#define Q_size 256

#define QI_size 256
#define QO_size 256

static char q[Q_size];
static int f, r;

char qi[QI_size], qo[QO_size];
int fi,ri, fo, ro;

void q_init(){
	fi=ri=fo=ro=0;	
}

int qi_insert(char ch)
{
	if((ri+1)&QI_size ==fi)
		return (0);
	ri = (ri+1) % QI_size;
	qi[ri] = ch;
	return(1);
}
int qi_delete()
{
	if(ri==fi)
		return(0);
	fi = (fi+1)%QI_size;
	return(qi[fi]);
}

int qo_insert(char ch)
{
	if((ro+1)&QO_size ==fo)
		return (0);
	ro = (ro+1) % QO_size;
	qo[ro] = ch;
	return(1);
}
int qo_delete()
{
	if(ro==fo)
		return(0);
	fo = (fo+1)%QO_size;
	return(qo[fo]);
}
