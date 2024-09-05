#ifndef _SCANNER_H
#define _SCANNER_H
#include "common.h"
#include "op.h"
#include "token_type.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_OP_ARGC 5

typedef struct op_meta op_meta;

struct op_meta
{
	char    *name;
	uint8_t  argc;
	opcode_t argv[MAX_OP_ARGC];
};

struct token
{
	opcode_t op;
	op_meta  meta;
};

typedef struct token   token;
typedef struct scanner scanner;
static scanner         scan;

token number(char **src);

#endif
