#include "data.h"
#include "rules.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int c = count_args(argv[1]);
	if(c == -1) {
		printf("%s: Nie mogę czytać pliku %s", argv[0], argv[1]);
		return 1;
	}
	printf("Wczytano tyle zmiennych: %d.\n", c);
	data_t *data = load_data(argv[1], c);
	int i, j = 0;
	for(i = 0 ; i < c; i++)
		printf("Nazwa: %s Wartość: %c\n", data[i].name, data[i].value);
	int r = count_rules(argv[2]);
	if(r == -1) {
		printf("%s: Nie mogę czytać pliku %s", argv[0], argv[2]);
		return -1;
	}
	printf("Wczytano tyle reguł: %d.\n", r);
	rule_t *rules = load_rules(argv[2], r);
	for(i = 0 ; i < r ; i++) {
		do {
			printf("Nazwa: %s Operator: %s\n", rules[i].com[j].name, rules[i].com[j].ope);
			j++;
		} while(strcmp(rules[i].com[j-1].ope, "=>") != 0);
		printf("Rezultat: %s Operator: %s\n", rules[i].res.name, rules[i].res.ope);
	}
	return 0;
}
