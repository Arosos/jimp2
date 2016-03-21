#ifndef RULES_H
#define RULES_H

#include <stdbool.h>

typedef struct {
	bool neg;
	char *name;
	bool var;
	char *ope;
} part_t;

typedef struct {
	part_t *com;
	part_t res;
} rule_t;

void loadRules (rule_t *rules, char *fname);

void delFirst(char *string);

#endif
