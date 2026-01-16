
#define _CRT_SECURE_NO_WARNINGS
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define HCONST 3567892

HashTable* NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokazivaca)
	HashTable* dict = (HashTable*)malloc(sizeof(HashTable));
	dict->table = (Bin**)malloc(sizeof(Bin*) * size);//alokacija pretinaca
	if (dict->table == NULL)
	{
		return;
	}
	dict->size = size;
	dict->load = 0;
	for (int i = 0; i < size; i += 1)
	{
		dict->table[i] = NULL;//pretinci
	}
	return dict;

}
//svaki Bin* pokazuje na prvi cvor vezane liste
unsigned int hash(char* word)//od s stvara hash kod
{
	// od kljuca generira hash kod
	unsigned int key = 0;
	while (*word != '\0') //obraduje svaki znak
	{
		key = key * HCONST + *word;//komb zn u jedan broj
		word++;
	}
	return key;
}

void Insert(HashTable* ht, char* word)
{
	unsigned int idx = hash(word) % ht->size;//racunamo idx pretinca

	// Provjera da rijec vec ne postoji
	Bin* current = ht->table[idx];//prvi elem liste
	while (current) {// prolazi kroz vezanu listu 
		if (strcmp(current->word, word) == 0)
			return; 
		current = current->next;
	}

	// Kreira novi element
	Bin* tmp = (Bin*)malloc(sizeof(Bin));
	if (!tmp) return;

	tmp->word = _strdup(word); // kopira rijec
	if (!tmp->word) {//ako nije uspilo
		free(tmp);
		return;
	}

	// Ubacuje na pocetak liste
	tmp->next = ht->table[idx];
	ht->table[idx] = tmp;// stari prvi postaje drugi

	ht->load++;
}


int Get(HashTable* ht, char* word) //provjerava je li rijec postoji u tab
{
	//1 ako je, 0 ako nije
	unsigned int key = hash(word) % ht->size;
	Bin* item = ht->table[key];
	while (item != NULL)
	{
		if (strcmp(item->word, word) == 0)
		{
			return 1;
		}
		item = item->next;
	}
	return 0;
}

void DeleteTable(HashTable* ht)//oslobada memoriju cile tab
{
	if (!ht) return;

	for (int i = 0; i < ht->size; i++) {//kroz sve pretince
		Bin* current = ht->table[i];//prvi
		while (current) {
			Bin* tmp = current;
			current = current->next;

			free(tmp->word); // oslobodi kopiranu rijec
			free(tmp);
		}
	}

	free(ht->table);
	free(ht);
}
