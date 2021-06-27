#include <stdio.h>
#include <string.h>
#define MAX 40

typedef struct node{
	char x[MAX];
	struct node *firstChild;
	struct node *nextSibling;
}NODE;

NODE *newNode(char name[]){
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	strcpy(temp->x, name);
	temp->firstChild = NULL;
	temp->nextSibling = NULL;
	
	if(strcmp(temp->x, name) == 0){
		return temp;
	}
	else{
		printf("Error.\n");
	}
}

NODE *mkdir(NODE *root, char name[]){
	if(root == NULL){
		printf("Error.\n");
		return NULL;
	}
	
	if(root->firstChild == NULL){
		root->firstChild = newNode(name);
		return root;	
	}
	
	else{
		// add sibling
		NODE *temp;
		temp = root->firstChild;
		if(strcmp(temp->x, name) == 0){
			printf("Cannot create folder with the same name.\n");
			return temp;
		}
	
		while(temp->nextSibling != NULL){
			temp = temp->nextSibling;
			if(strcmp(temp->x, name) == 0){
				printf("Cannot create folder with the same name.\n");
				return root;
			}
		}
	
		temp->nextSibling = newNode(name);
		return root;
	}
}

void *dir(NODE *root){
	
	printf("Contents of directory %s :\n", root->x);
	
	if(root->firstChild  != NULL){
		root = root->firstChild;
		
		while(root->nextSibling != NULL){
			printf("\t%s\n", root->x);
			root = root->nextSibling;
		}
		
		printf("\t%s\n", root->x);
	}
	else{
		printf("Directory %s is empty.\n", root->x);
	}
}

NODE *chdir(NODE *root, char name[]){
	
	if(root == NULL){
		printf("Error.\n");
		return NULL;
	}
	
	if(root->firstChild == NULL){
		return root;
	}
	else{
		NODE *temp = root->firstChild;
		
		if(strcmp(temp->x, name) == 0){
			return temp;
		}
		else{
			while(temp->nextSibling != NULL){
				temp = temp->nextSibling;
				if(strcmp(temp->x, name) == 0){
					return temp;
				}
			}
			
			if(temp->nextSibling == NULL){
				printf("There is no file with this name.\n");
				return root;
			}
		}
	}	
}

void *rmdir(NODE *root, char name[]){
	NODE *temp = root;
	NODE *tut;
	temp = temp->firstChild;
	
	if(strcmp(temp->x, name) == 0){
		if(temp->firstChild != NULL){
			printf("Cannot delete folder. The directory is not empty.\n");
		}
		else{
			tut = temp;
			if(temp->nextSibling != NULL){
				root->firstChild = temp->nextSibling;	
			}
			else{
				free(tut->firstChild);
			}
		}
	}
	
	else{
		
		if(temp->nextSibling != NULL){
			tut = temp;
			temp = temp->nextSibling;
			
			while(strcmp(temp->x, name) != 0 && temp->nextSibling != NULL){
				tut = temp;
				temp = temp->nextSibling;
			}
			
			if(temp->nextSibling == NULL && strcmp(temp->x, name) != 0){
				printf("This directory not exist.\n");
			}
			else{
				if(temp->firstChild == NULL){
					tut->nextSibling = temp->nextSibling;
					free(temp);
				}
				else{
					printf("Cannot delete folder. The directory is not empty.\n");
				}
			}
		}
		else{
			printf("This directory not exist.\n");
		}
	}
	
}

void count(NODE *root){
	NODE *temp = root;
	int count = 1;
	
	temp = temp->firstChild;
	
	while(temp->nextSibling != NULL){
		temp = temp->nextSibling;
		count ++;
	}
	
	printf("%d\n", count);
}

NODE *chdirUp(NODE *root, NODE *tut){
	NODE *sakla;
	int girdi = 0;
	while(tut != root){
		girdi = 1;
		sakla = tut;
		tut = tut->firstChild;
		
		if(tut == root){
			break;
		}
		
		while(tut->nextSibling != NULL){
			tut = tut->nextSibling;
			if(tut->x == root){
				break;
			}
		}
	}
	
	if(girdi == 0){
		printf("%s\n", tut->x);
		return tut;
	}
	
	printf("%s\n", sakla->x);
	return sakla;
}


int main(){
    char dizi[50];
    char *komut, *name;
    int tut=1;

	NODE *tree = newNode("root");
	NODE *tut2 = tree;
	printf("Please select a command.\n\n");
	printf("Available commands : ");
	printf("\n\tmkdir\n\tchdir\n\trmdir\n\tdir\n\tcount\n\n");
	
	while(tut == 1){
		printf(">");
		
		gets(dizi);
		
		komut = strtok(dizi, " ");
	    name = strtok(NULL, " ");
	
	    if(strcmp(komut, "mkdir") == 0){
			mkdir(tree, name);
		}
		
		else if(strcmp(komut, "chdir") == 0){
			if(strcmp(name, "..") == 0){
				tree = chdirUp(tree, tut2);
				printf("\n%s\n", tree);
				printf("%s\n", tut2);
			}
			else{
				tree = chdir(tree, name);
				printf("%s\n", tree->x);
			}
		}
		
		else if(strcmp(komut, "dir") == 0){
			dir(tree);
		}
		
		else if(strcmp(komut, "rmdir") == 0){
			rmdir(tree, name);
			
		}
		
		else if(strcmp(komut, "count") == 0){
			count(tree);
		}
		
		else{
			printf("Incorrect command.\n");	
		}
	}
	
	return 0;
}
