#ifndef _CPU_H
#define _CPU_H

#define REG_COUNT

typedef enum
{
	A,
	B,
	C,
	D,
	E,
	H,
	L

} register_t;

struct cpu
{
	unsigned char *pc;
	unsigned char  R[REG_COUNT];
};

#endif
