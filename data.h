#ifndef DATA_H
#define DATA_H

#include "rules.h"

#define MAX 10

typedef struct {
	char name[MAX];
	char value;
} data_t;

int count_args(char *filename);

data_t *load_data(char *filename, int n);

data_t *reload_data(data_t *data, rule_t *rules, int d, int r);

bool check_database(data_t*, int);

#endif
