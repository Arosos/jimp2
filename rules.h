#ifndef RULES_H
#define RULES_H

#include <stdbool.h>

#define MAXR 3
#define MAXC 10
#define MAXN 10
#define MAXO 3

typedef struct {
	bool neg;
	char name[MAXN];
	char ope[MAXO];
} part_t;

typedef struct {
	part_t com[MAXC];
	part_t res;
} rule_t;

int count_rules(char* fname);

rule_t *load_rules(char *fname, int n);

char *del_first(char *string);

#endif
