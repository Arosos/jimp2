#include "data.h"
#include "rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, char **argv)
{
	char *s = argv[3];
	printf("Poszukiwana wartość: %s\n", s);
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
		j = 0;
		printf("Reguła #%d:\n", i+1);
		do {
			printf("Neg: %s Nazwa: %s Operator: %s\n", rules[i].com[j].neg ? "true" : "false", rules[i].com[j].name, rules[i].com[j].ope);
			j++;
		} while(strcmp(rules[i].com[j-1].ope, "=>") != 0);
		printf("Rezultat: %s Operator: %s\n", rules[i].res.name, rules[i].res.ope);
	}
	data = reload_data(data, rules, c, r);
	c = return_args_number();
	bool database = check_database(data, c);
	if(database) {
		printf("%s: Baza danych jest niespójna. Kończę działanie programu.\n", argv[0]);
		return 1;
	}
	printf("Po uwzględnieniu nieznanych zmiennych z reguł, jest tyle argumentów: %d.\n", c);
	for(i = 0 ; i < c ; i++)
                printf("Nazwa: %s Wartość: %c\n", data[i].name, data[i].value);
/*	int d = find_rule(data, rules, c, r);
	printf("%d\n", d);
	bool solution = solve(data, rules, s, c, r);
	if(solution)
		printf("%s = true\n", s);
	else
		printf("%s = false\n", s);
*/	return 0;
}
