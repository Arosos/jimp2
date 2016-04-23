#include "rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 10

const int BUFFSIZER = 8192;

int count_rules(char *filename) {
        FILE *in = fopen(filename, "r");
        if (in == NULL)
                return -1;
        int c = 0;
        char buff[BUFFSIZER];
        while(fgets(buff, BUFFSIZER, in) != NULL)
                c++;
        return c;
}

rule_t *load_rules(char *filename, int n)
{
	FILE *in = fopen(filename, "r");
	rule_t *rules = malloc(sizeof(rule_t)*n);
	int i, j = 0;
	char buff[BUFFSIZER];
	for(i = 0 ; fgets(buff, BUFFSIZER, in) != NULL ; i++) {
		rules[i].com = (part_t*)malloc(MAXC*sizeof(part_t));
		rules[i].com[0].name = (char*)malloc(10);
                rules[i].com[0].ope = (char*)malloc(3);
                rules[i].res.name = (char*)malloc(10);
                rules[i].res.ope = (char*)malloc(3);
		char *token = strtok(buff, " \n");
		rules[i].com[0].name = token;
		while((token = strtok(NULL, " \n")) != NULL) {
/*			rules[i].com[j].name = (char*)malloc(10);
                	rules[i].com[j].ope = (char*)malloc(3);
*/			if(strcmp(token, "&&") == 0 || strcmp(token, "||") == 0 || strcmp(token, "=>") == 0) {
				if(strcmp(token, "=>") == 0) {
					rules[i].com[j].ope = token;
					token = strtok(NULL, " \n");
					rules[i].res.name = token;
					rules[i].res.ope = NULL;
					break;
				}
				else
					rules[i].com[j].ope = token;
			j++;
			}
			else
				rules[i].com[j].name = token;
		}
	}
	fclose(in);
	return rules;
}

void delFirst(char *string)
{
	int i;
	char *final;
	for(i = 1 ; i < strlen(string) ; i++)
		final[i-1] = string[i];
	string = final;
}
