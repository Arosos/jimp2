#include "data.h"
#include "rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int BUFFSIZE = 8192;

int count_args(char *filename) {
	FILE *in = fopen(filename, "r");
	if (in == NULL)
		return -1;
	int c = 0;
	char buff[BUFFSIZE];
	while(fgets(buff, BUFFSIZE, in) != NULL)
		c++;
	return c;
}

data_t *load_data(char *filename, int n) {
	FILE *in = fopen(filename, "r");
	data_t *data = (data_t*)malloc(sizeof(data_t));
	if(data==NULL)
		return NULL;
	int i;
	char value;
	for(i = 0 ; i < n ; i++) {
		fscanf(in, "%s %c", data[i].name, &value);
		data[i].value = value;
	}
	fclose(in);
	return data;
}

/*data_t *reload_data(data_t *data, rule_t *rules, int d, int r) {
	data_t *ndata = malloc(sizeof(data_t));
	int i, j, k;
	char *name;
	bool b, c;
	for(i = 0 ; i < n ; i++) {
		name = data[i].name;
		bool *tb[r];
		b = false;
		for(j = 0 ; j < r ; j++) {
			for(k = 0 ; strcmp(rules[j].com[k].ope, "=>") != 0 ; k++) {
				if(strcmp(name, rules[j].com[k].name) == 0)
					tb[j][k] = true;
				else
					tb[j][k] = false;
				if(!tb[j][k])
				b = true;
			}
		}
	}
}*/
