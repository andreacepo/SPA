#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "bstree.h"


BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}

void AddNode(BSTree* bst, char* word)
{
	if (*bst == NULL) {
		*bst = (BSTree)malloc(sizeof(Node));//rez mem za novi cvor
		(*bst)->word = _strdup(word);
		(*bst)->left = NULL;
		(*bst)->right = NULL;
		return;
	}
	if (strcmp(word, (*bst)->word) == 0) {//provjera duplikata
		free(word);
		return;
	}
	if (strcmp(word, (*bst)->word) < 0) {//fun se poziva dok se ne nade prazno mjesto
		AddNode(&((*bst)->left), word);
	}
	else {
		AddNode(&((*bst)->right), word);
	}

}

int BSTHeight(BSTree bst)//rek vis stabla
{
	if (bst == NULL) {
		return 0;
	}

	int leftHeight = BSTHeight(bst->left);
	int rightHeight = BSTHeight(bst->right);

	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}

	return 0;
}

void PrintBSTree(BSTree bst)//rijeci po abecedi(in)
{
	if (bst == NULL) {
		return;
	}

	PrintBSTree(bst->left);

	printf("%s\n", bst->word);

	PrintBSTree(bst->right);

}

void SaveBSTree(BSTree bst, FILE* fd)//u dat(pre)
{
	if (bst == NULL) {
		return;
	}

	fprintf(fd, "%s ", bst->word);

	SaveBSTree(bst->left, fd);

	SaveBSTree(bst->right, fd);

}

void DeleteBSTree(BSTree bst)//brise sve cvorove(post)
{
	if (bst == NULL) {
		return;
	}

	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);

	free(bst->word);
	free(bst);

}

BSTree LoadBSTree(FILE *fd)//cita ric po ric iz dat
{
	BSTree bst = NULL;
	char word[256];

	while (fscanf(fd, "%255s", word) == 1) {
		AddNode(&bst, _strdup(word));
	}

	return bst; //vraca novo
}







