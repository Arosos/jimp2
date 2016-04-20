#ifndef DATA_H
#define DATA_H

#define MAX 2

typedef struct {
	char name[MAX];
	char value;
} data_t;

int count_args(char *filename);

data_t *load_data(char *filename, int n);

#endif
