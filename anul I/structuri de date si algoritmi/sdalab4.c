#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	if(*head == NULL){
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
		printf("%d %s %s %.2f\n", head -> data.key, head -> data.nume, head -> data.prenume, head -> data.notaMedie);
		printIn(head -> left);
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
		printf("%d %s %s %.2f\n", head -> data.key, head -> data.nume, head -> data.prenume, head -> data.notaMedie);
		printPost(head -> left);
		printPost(head -> right);
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

int main(){
	struct tree *head = NULL;

	add(&head, 3, "dragos22", "cojocari3", 6.57);
	add(&head, 1, "dragos", "cojocari", 5.55);
	add(&head, 4, "dragos123", "cojocari5", 7.55);
	add(&head, 5, "dragos22", "cojocari3", 6.57);
	add(&head, 2, "dragos123", "cojocari5", 7.55);

	afisare(head);

	return 0;
}
