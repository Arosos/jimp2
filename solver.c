#include "data.h"
#include "rules.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char kon(char value1, char value2) {
        if(value1 == '1' && value2 == '1')
                return '1';
        else
                return '0';
}

char alt(char value1, char value2) {
        if(value1 == '1' || value2 == '1')
                return '1';
        else
                return '0';
}

char neg(char value) {
	if(value == '0')
		return '1';
	else
		return '0';
}

bool forward_chaining(data_t *data, rule_t *rules, char *s, int d, int r) {
	int i, j, k;
	bool b;
	char solution, first, second;
	for(i = 0 ; i < d ; i++) {
                if(strcmp(data[i].name, s) == 0 && data[i].value == '0')
                        return false;
                else if(strcmp(data[i].name, s) == 0 && data[i].value == '1')
                        return true;
        }
	for(i = 0 ; i < r ; i++) {
		rule_t rule;
		j = 0;
		strcpy(rule.res.name, rules[i].res.name);
		do {
			rule.com[j].neg = rules[i].com[j].neg;
			strcpy(rule.com[j].name, rules[i].com[j].name);
			strcpy(rule.com[j].ope, rules[i].com[j].ope);
			for(k = 0 ; k < d ; k++) {
				if(strcmp(rule.com[j].name, data[k].name) == 0)
					rule.com[j].value = data[k].value;
				if(strcmp(rule.res.name, data[k].name) == 0)
					rule.res.value = data[k].value;
			}
			j++;
		} while(strcmp(rule.com[j-1].ope, "=>") != 0);
		if(rule.res.value == '?') {
			j = 0;
			b = false;
			do {
				if(rule.com[j].value == '?') {
					b = true;
					break;
				}
				j++;
			} while(strcmp(rule.com[j-1].ope, "=>") != 0);
			if(!b) {
				if(rule.com[0].neg)
					solution = neg(rule.com[0].value);
				else
					solution = rule.com[0].value;
				j = 0;
				do {
					if(strcmp(rule.com[j].ope, "&&") == 0) {
						first = solution;
						if(rule.com[j+1].neg)
							second = neg(rule.com[j+1].value);
						else
							second = rule.com[j+1].value;
						solution = kon(first, second);
					}
					else if(strcmp(rule.com[j].ope, "||") == 0) {
                                                first = solution;
                                                if(rule.com[j+1].neg)
                                                        second = neg(rule.com[j+1].value);
                                                else
                                                        second = rule.com[j+1].value;
                                                solution = alt(first, second);
                                        }
					j++;
				} while(strcmp(rule.com[j-1].ope, "=>") != 0);
				rule.res.value = solution;
				if(strcmp(rule.res.name, s) == 0 && rule.res.value == '1')
						return true;
				for(j = 0 ; j < d ; j++) {
					if(strcmp(rule.res.name, data[j].name) == 0) {
						data[j].value = rule.res.value;
						break;
					}
				}
			}
		}
	}
	if(solution == '0')
		return false;
	else
		return true;
}

int find_rule(data_t *data, rule_t *rules, int d, int r) {
	int i, j, k, b = -1;
	bool *co, re, h;
	co = malloc(sizeof(bool));
	for(i = 0 ; i < r ; i++) {
		j = 0;
		do {
			h = true;
			for(k = 0 ; k < d ; k++) {
				co[j] = false;
				if(strcmp(rules[i].com[j].name, data[k].name) == 0 && data[k].value == '?')
					break;
				else
					co[j] = true;
			}
			if(co[j] == false)
				h = false;
			j++;
		} while(strcmp(rules[i].com[j-1].ope, "=>") != 0);
		for(k = 0 ; k < d ; k++) {
			re = false;
			if(strcmp(rules[i].res.name, data[k].name) == 0 && data[k].value == '?')
				re = true;
		}
		if(re && h)
			return i;
	}
	return r;
}

/*bool solve(data_t *data, rule_t *rules, char *s, int d, int r) {
	bool solution, co, re, result;
	int i, j, k;
	char value1, value2;
	for(i = 0 ; i < d ; i++) {
		if(strcmp(data[i].name, s) == 0 && data[i].value == '0') {
			solution = false;
			return solution;
		}
		else if(strcmp(data[i].name, s) == 0 && data[i].value == '1') {
			solution = true;
			return solution;
		}
	}
	for(i = 0 ; i < r ; i++) {
		for(k = 0 ; k < d ; k++) {
			if(strcmp(rules[i].com[0].name, data[k].name) == 0
		}
	}
	for(i = 0 ; i < r ; i++) {
		co = false;
		re = false;
		j = 0;
		do {
			for(k = 0 ; k < d ; k++)
				if(strcmp(rules[i].com[j].name, data[k].name) == 0 && data[k].value != '?')
					co = true;
			j++;
		} while(strcmp(rules[i].com[j-1].name, "=>") != 0);
		for(k = 0 ; k < d ; k++)
			if(strcmp(rules[i].res.name, data[k].name) == 0 && data[k].value == '?')
				re = true;
		if(co && re)
			do {
				j = 0;
				for(k = 0 ; k < d ; k++)
					if(strcmp(rules[i].com[j].name, data[k].name) == 0) {
						value1 = data[k].value;
						value2 = data[k+1].value;
						if(strcmp(rules[i].com[j].ope, "||") == 0)
							result = alt(value1, value2);
						else if(strcmp(rules[i].com[j].ope, "&&") == 0)
							result = kon(value1, value2);
					}
				j++;
			} while(strcmp(rules[i].com[j-1].name, "=>") != 0);
		for(k = 0 ; k < d ; k++)
			if(strcmp(rules[i].res.name, data[k].name) == 0 && result)
				data[k].value = '1';
			else
				data[k].value = '0';
	}
	for(k = 0 ; k < d ; k++)
		if(strcmp(s, data[k].name) == 0 && data[k].value == '0')
			solution = false;
		else if(strcmp(s, data[k].name) == 0 && data[k].value == '1')
			solution = true;
	return solution;
}*/
