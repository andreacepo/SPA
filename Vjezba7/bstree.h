#define _CRT_SECURE_NO_WARNINGS
#ifndef TREE_H
#define TREE_H
#include <string.h>



typedef struct Node {
	char* word;
	struct Node* left, *right;
} Node;


typedef Node* BSTree;

BSTree NewBSTree();

void AddNode(BSTree* bst, char* word);

int BSTHeight(BSTree bst);

void PrintBSTree(BSTree bst);

void SaveBSTree(BSTree bst, FILE* fd);

void DeleteBSTree(BSTree bst);

BSTree LoadBSTree(FILE* fd);

//moje


#endif
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef TREE_H
#define TREE_H
#include <string.h>



typedef struct Node {
	char* word;
	struct Node* left, *right;
} Node;


typedef Node* BSTree;

BSTree NewBSTree();

void AddNode(BSTree* bst, char* word);

int BSTHeight(BSTree bst);

void PrintBSTree(BSTree bst);

void SaveBSTree(BSTree bst, FILE* fd);

void DeleteBSTree(BSTree bst);

BSTree LoadBSTree(FILE* fd);

//moje


#endif
#pragma once
