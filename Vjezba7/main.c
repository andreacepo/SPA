#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "bstree.h"

int readWord(FILE* fd, char* buffer)
{
	int c;

	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

int main()
{
	int wc;
	FILE* fd;
	char buffer[1024];
	BSTree bst = NewBSTree();

	// Kreiraj stablo
	fd = fopen("liar.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file.\n");
		return 1;
	}

	wc = 0;
	while (readWord(fd, buffer))
	{
		AddNode(&bst, _strdup(buffer));
		wc++;
	}
	fclose(fd);

	// Ispisi stablo, visinu i broj cvorova
	PrintBSTree(bst);
	printf("\nH = %d, N = %d\n", BSTHeight(bst), wc);


	


	// Snimi stablo u datoteku
	fd = fopen("stablo.txt", "wt");
	if (fd == NULL)
	{
		printf("Error opening file for writing.\n");
		DeleteBSTree(bst);
		return 1;
	}
	SaveBSTree(bst, fd);
	fclose(fd);

	// Izbrisi stablo
	DeleteBSTree(bst);

	// Ucitaj stablo iz datoteke
	fd = fopen("stablo.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file for reading.\n");
		return 1;
	}
	bst = LoadBSTree(fd);
	fclose(fd);
	

	// Ispisi visinu i izbrisi
	/*printf("\nH = %d\n", BSTHeight(bst));*/
	DeleteBSTree(bst);

	return 0;
}
