#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bfs.c"

struct elev{
	int key;
	char *nume;
	char *prenume;
	float notaMedie;
};

struct tree{
	struct elev data;
	struct tree *left, *right;
};

void add(struct tree **head, int key, char *nume, char *prenume, float notaMedie){
	if(!(*head)){
		*head = (struct tree*)malloc(sizeof(struct tree));
		(*head) -> data.key = key;
		(*head) -> data.notaMedie = notaMedie;
		(*head) -> data.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
		strcpy((*head) -> data.nume, nume);
		(*head) -> data.prenume = (char*)malloc((strlen(prenume) + 1) * sizeof(char));
		strcpy((*head) -> data.prenume, prenume);
		(*head) -> left =  (*head) -> right = NULL;
		return;
	}

	if((*head) -> data.key < key)
		add(&(*head) -> right, key, nume, prenume, notaMedie);


	if((*head) -> data.key > key)
		add(&(*head) -> left, key, nume, prenume, notaMedie);
}

void printIn(struct tree *head){
	if(head){
		printIn(head -> left);
		printf("%d %s %s %.2f\n", head -> data.key, head -> data.nume, head -> data.prenume, head -> data.notaMedie);
		printIn(head -> right);
	}
}

void printPre(struct tree *head){
	if(head){
		printf("%d %s %s %.2f\n", head -> data.key, head -> data.nume, head -> data.prenume, head -> data.notaMedie);
		printPre(head -> left);
		printPre(head -> right);
	}
}

void printPost(struct tree *head){
	if(head){
		printPost(head -> left);
		printPost(head -> right);
		printf("%d %s %s %.2f\n", head -> data.key, head -> data.nume, head -> data.prenume, head -> data.notaMedie);
	}
}

void afisare(struct tree *head){
	if(!head)
		return;

	printf("Afisarea Preordine:\n");
	printPre(head);

	printf("\nAfisarea Inordine:\n");
	printIn(head);

	printf("\nAfisarea Postordine:\n");
	printPost(head);
}

struct tree * search(struct tree *head, int key){
	if(!head || head -> data.key == key)
		return head;

	if(key > head -> data.key)
		return search(head -> right, key);

	if(key < head -> data.key)
		return search(head -> left, key);
}

void BFS(struct tree *head){
	struct list * vizitate = NULL;
	struct list * asteptare = NULL;
	struct list * temp = NULL;
	struct tree * tempTree = NULL;

	append(&asteptare, head);

	do{
		temp = vizitate;
		vizitate = asteptare;
		asteptare = temp;

		struct list *tempList = NULL;

		while(tempList = popFirst(&vizitate)){
			tempTree = tempList -> node;
			free(tempList);

			if(tempTree){
				if(tempTree -> left)
					append(&asteptare, tempTree -> left);
				if(tempTree -> right)
					append(&asteptare, tempTree -> right);
				printf("%d %s %s %.2f\n", tempTree -> data.key, tempTree -> data.nume, tempTree -> data.prenume, tempTree -> data.notaMedie);
			}
		}
		printf("\n");
	}while(asteptare);

	deleteList(&vizitate);
	deleteList(&asteptare);
}

void DFS(struct tree *head){
	if(head){
		printf("%d %s %s %.2f\n", head -> data.key, head -> data.nume, head -> data.prenume, head -> data.notaMedie);
		DFS(head -> left);
		DFS(head -> right);
	}
}

void mirrorTree(struct tree **head){
	if(!(*head))
		return;

	struct tree *temp;

	mirrorTree(&(*head) -> left);
	mirrorTree(&(*head) -> right);

	temp = (*head) -> left;
	(*head) -> left = (*head) -> right;
	(*head) -> right = temp;
}



int main(){
	struct tree *head = NULL;

	add(&head, 8, "dragos123", "cojocari5", 7.55);
	add(&head, 6, "dragos22", "cojocari3", 6.57);
	add(&head, 4, "dragos22", "cojocari3", 6.57);
	add(&head, 2, "dragos22", "cojocari3", 6.57);
	add(&head, 1, "dragos", "cojocari", 5.55);
	add(&head, 5, "dragos123", "cojocari5", 7.55);
	add(&head, 3, "dragos22", "cojocari3", 6.57);

	printIn(head);
	mirrorTree(&head);
	printf("\n");
	printIn(head);

/*
	afisare(head);

	struct tree *temp = search(head, 6);
	if(temp)
		printf("\n%d %s %s %.2f", temp -> data.key, temp -> data.nume, temp -> data.prenume, temp -> data.notaMedie);
	else printf("\nElevul cu cheia data nu a fost gasit.");

	struct list *temp= NULL;
	append(&temp, head -> right);
	append(&temp, head);
	append(&temp, head -> left);

	struct tree *tempTree;
	struct list *foo = NULL;

	printf("\nBFS\n");
	BFS(head);

	printf("\nDFS\n");

	DFS(head);

*/
	return 0;
}
