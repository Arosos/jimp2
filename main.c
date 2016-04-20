#include "data.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int c = count_args(argv[1]);
	if(c == -1)
		return 1;
	printf("c=%d\n", c);
	data_t *data = load_data(argv[1], c);
	int i;
	for(i = 0 ; i < c; i++)
		printf("%s %c\n", data[i].name, data[i].value);
	return 0;
}
