#include "rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFSIZE = 8192;

void loadRules(rule_t *rules, char *fname)
{
	FILE *rule = fopen(fname, "r");
	int i, j;
	char *buff;
	for(i = 0 ; fgets(buff, BUFFSIZE, rule) != NULL ; i++)
	{
		strtok(buff, " ,.-");
		for(j = 0 ; buff != NULL ; j++)
		{
			if(strcmp(buff, "&&") == 0 || strcmp(buff, "||") == 0 || strcmp(buff, "=>") == 0)
			{
				if(strcmp(buff, "=>") == 0)
				{
					strtok(buff, " ,.-");
					if(buff[0] == '!')
					{
						rules[i].res.neg = true;
						delfirst(&buff);
						rules[i].res.name = buff;
					}
					else
					{
						rules[i].res.neg = false;
						rules[i].res.name = buff;
					}
				}
			}
			else if(buff[0] == '!')
			rules[i].com[j].neg = true;
			else if(buff[0] != '!')
			rules[i].com[j].neg = false;
			else
			rules[i].com[j].name = buff;
		}
	}
}

void delFirst(char *string)
{
	int i;
	char *final;
	for(i = 1 ; i < strlen(string) ; i++)
		final[i-1] = string[i];
	string = final;
}
