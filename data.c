#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFSIZE = 8192;

int count_args(char *filename) {
	FILE *in = fopen(filename, "r");
	if (in == NULL) {
		printf("Nie mogę czytać pliku %s.\n", filename);
		return -1;
	}
	int c = 0;
	char buff[BUFFSIZE];
	while(fgets(buff, BUFFSIZE, in) != NULL)
		c++;
	return c;
}

data_t *load_data(char *filename, int n) {
	FILE *in = fopen(filename, "r");
	data_t *data = (data_t*)malloc(n*sizeof(data_t));
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
