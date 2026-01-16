#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>


Dictionary create()
{
	Dictionary rjecnik = (Dictionary)malloc(sizeof(Word));//AlociraS u memoriju prostor vel jednog Word
	rjecnik->count = 0;
	rjecnik->next = NULL;//pocetni
	rjecnik->word = NULL;

	return rjecnik;
}//stvaras praznu povezanu listu s dummy 
//cvorom na pocetku (olaksava umetanje na pocetak).

void add(Dictionary dict, char* str)
{

	Dictionary p = dict; //pret
	Dictionary n = dict->next; //tren cvor, prvi stvarni element

	Dictionary novi = (Dictionary)malloc(sizeof(Word));
	novi->word = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(novi->word, str);
	novi->count = 1;

	while (n != NULL)
	{
		if (strcmp(n->word, str) == 0)
		{
			n->count++;
			free(novi->word);
			free(novi);
			return;

		}
		else if (strcmp(n->word, str) > 0)
		{
			novi->next = n;
			p->next = novi;
			return;
		} 
		n = n->next;
		p = p->next;

	}
	p->next = novi;
	novi->next = NULL;

}


void print(Dictionary dict)
{
	dict = dict->next;//presk dum
	while (dict != NULL)
	{
		printf("%s - Broj:%d\n", dict->word, dict->count);
		dict = dict->next;
	}
}

void destroy(Dictionary dict)
{

	while (dict != NULL)
	{
		Dictionary temp;
		temp = dict;
		dict = dict->next;
		free(temp->word);
		free(temp);
	}
}


int filter(Word* w)

{
	if ((w->count > 5 && w->count < 10) && strlen(w->word) > 3)
	{
		return 1;
	}
	else
		return 0;
}

Dictionary filterDictionary(Dictionary indict, int(*filter)(Word* w))
{
	Dictionary p = indict; //pret
	Dictionary n = indict->next;//tren

	while (n != NULL)
	{
		if (filter(n) == 1)
		{
			p = p->next;
			n = n->next;
		}
		else
		{
			p->next = n->next;
			free(n->word);
			free(n);
			n = p->next;
		}
	}
	return indict;
}
