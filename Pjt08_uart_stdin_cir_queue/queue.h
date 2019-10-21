#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#define Q_size 8

static char q[Q_size];
static int f, r;

void q_init();

void q_insert(char ch);

int qi_insert(char ch);
int qi_delete();
int qo_insert(char ch);
int qo_delete();
