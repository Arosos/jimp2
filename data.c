#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int BUFFSIZE = 8192;

int a;

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

data_t *reload_data(data_t *data, rule_t *rules, int d, int r) {
	int i, j, k;
	bool b = false;
	for(j = 0 ; j < r ; j++)
		for(k = 0 ; strcmp(rules[j].com[k-1].ope, "=>") != 0 ; k++) {
			for(i = 0 ; i < d ; i++) {
				b = false;
				if(strcmp(rules[j].com[k].name, data[i].name) == 0)
					break;
				else
					b = true;
			}
			if(b) {
				strcpy(data[d].name, rules[j].com[k].name);
				data[d].value = '?';
				d++;
			}
		}
	for(j = 0 ; j < r ; j++) {
		for(i = 0 ; i < d ; i++) {
			b = false;
			if(strcmp(rules[j].res.name, data[i].name) == 0)
				break;
			else
				b = true;
		}
		if(b) {
			strcpy(data[d].name, rules[j].res.name);
			data[d].value = '?';
			d++;
		}
	}
	a = d;
	return data;
}

int return_args_number() {
	return a;
}
