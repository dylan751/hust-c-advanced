#include<stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct name_num{
	char name[100], ID[10];
	struct name_num *left,*right;
}NN;

NN* makeNewNN(char* ID,char* name){
	NN* New=(NN*)malloc(sizeof(NN));
	strcpy(New->name,name);
	strcpy(New->ID,ID);
	New->left=New->right=NULL;
	return New;
}

void addNN(NN** root,NN* add){
	if(*root==NULL) *root=add;
	else if(atoi(add->ID)<atoi((*root)->ID)) addNN(&(*root)->left,add);
	else addNN(&(*root)->right,add);
}

void insertNN(NN** root,char* ID,char *name){
	NN* New=makeNewNN(ID,name);
	addNN(root,New);
}

NN* NN_search(NN* root,char* ID){
	if(root==NULL) return NULL;
	else if(strcmp(root->ID,ID)==0) return root;
	else if(atoi(ID)<atoi(root->ID)) return NN_search(root->left,ID);
	else return NN_search(root->right,ID);
}

void NN_name_print(NN* root){
	if(root!=NULL) printf("%s %s\n",root->ID,root->name);
}

void NN_print(NN* root){
	if(root==NULL) return;
	NN_print(root->left);
	NN_name_print(root);
	NN_print(root->right);
}

void NN_free(NN** root){
	if(*root==NULL) return;
	NN_free(&(*root)->left);
	NN_free(&(*root)->right);
	free(*root);
}