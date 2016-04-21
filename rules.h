#ifndef RULES_H
#define RULES_H

#include <stdbool.h>

#define MAXR 3

typedef struct {
	bool neg;
	char *name;
	char *ope;
} part_t;

typedef struct {
	part_t *com;
	part_t res;
} rule_t;

int count_rules(char* fname);

rule_t *load_rules(char *fname);

char *del_first(char *string);

#endif
