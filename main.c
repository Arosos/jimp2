#include "rules.h"

#include <stdio.h>
#include <stdlib.h>

const int BUFFSIZE = 8192;

int main (int argc, char **argv)
{
	char con = argv[1];
	FILE *data = fopen(argv[2], "r");
	if (data == NULL)
	{
		printf(stderr, "Nie mogę czytać pliku %s", argv[2]);
		return 1;
	}
	FILE *rule = fopen(argv[3], "r");
	if (rule == NULL)
        {
                printf(stderr, "Nie mogę czytać pliku %s", argv[3]);
                return 1;
        }
	printf("Wybrano wnioskowanie: %s", con);
	rule_t *rules;
	char buff[];
	return 0;
}
