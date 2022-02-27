#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct student{
	char *nume;
	char *prenume;
	float notaMedie;
};

struct list{
	struct student head;
	struct list* next;
};

const char nume[][20] = {"Dragos","Ecaterina","Catalin","Doru","Nichita","Mihail","Nicu","Eduard","Nicoleta","Vova"};
const char prenume[][20] = {"Cojocari","Popa","Plesu","Apareci","Furuncea","Lukashuk","Druta","Robovol","Bors","Vozian"};

void append(struct list **head, char *name, char *surname, float nMed){
	struct list *newStudent = (struct list*)malloc(sizeof(struct list));
	struct list *last = *head;

	newStudent -> head.nume = (char*)malloc((strlen(name) + 1)*sizeof(char));
	strcpy(newStudent -> head.nume, name); 

	newStudent -> head.prenume = (char*)malloc((strlen(surname) + 1)*sizeof(char));
	strcpy(newStudent -> head.prenume, surname);

	newStudent -> head.notaMedie = nMed;

	newStudent -> next = NULL;

	if(*head == NULL){
		*head = newStudent;
		return;
	}

	while(last -> next != NULL){
		last = last -> next;
	}

	last -> next = newStudent;
}

void aleator(struct list **head, int num){
	srand(time(NULL));

	for(int i = 0; i < num; i++){
		append(&(*head), nume[rand() % 10], prenume[rand() % 10], ((5 * ((float)rand() / RAND_MAX)) + 5));
	}
}


void push(struct list **stud, char *name, char *surname, float nMed){
	struct list *newStudent = (struct list*)malloc(sizeof(struct list));

	newStudent -> head.nume = (char*)malloc((strlen(name) + 1)*sizeof(char));
	strcpy(newStudent -> head.nume, name); 

	newStudent -> head.prenume = (char*)malloc((strlen(surname) + 1)*sizeof(char));
	strcpy(newStudent -> head.prenume, surname);

	newStudent -> head.notaMedie = nMed;

	newStudent -> next = *stud;
	(*stud) = newStudent;
}

void afisare(struct list *stud){
	int i = 1;
	if(stud== NULL){
		printf("Lista este Nula\n");
		return;
	}

	while(stud != NULL){
		printf("%d) %s %s %0.2f\n", i++, stud -> head.nume, stud -> head.prenume, stud -> head. notaMedie);
		stud = stud -> next;
	}
}

void find(struct list *stud){
	int option, i = 1, nota;
	char str[20];

	printf("\n1.Nume 2.Prenume\n");
	printf("Alegeti campul dupa care doriti sa indepliniti cautarea:");
	scanf("%d",&option);
	switch(option){
		case 1:
			printf("Dati numele care va fi cautat in lista:");
			fflush(stdin);
			scanf("%s",&str);

			while(stud != NULL){
				if(!strcmp(stud -> head.nume, str)){
					printf("Prima aparitie a numelui %s se intalneste pe pozitia %d.\n", str, i);
					return;
				}
				i++;
				stud = stud -> next;
			}

			printf("Persoana cu numele dat nu a fost gasit in lista.");
		break;

		case 2:
			printf("Dati prenumele care va fi cautat in lista:");
			fflush(stdin);
			scanf("%s",&str);

			while(stud != NULL){
				if(!strcmp(stud -> head.prenume, str)){
					printf("Prima aparitiei a persoanei cu familia \"%s\" se intalneste pe pozitia %d. \n", str, i);
					return;
				}
				i++;
				stud = stud -> next;
			}

			printf("Persoana cu prenumele dat nu a fost gasit in lista.");
		break;
	}
}

void sort(struct list **head){
	struct list *curentStudent = *head, *index = NULL;
	struct student temp;

	while(curentStudent != NULL){
		index = curentStudent -> next;

		while(index != NULL){
			if(strcmp(curentStudent -> head.nume, index -> head.nume) > 0){
				temp = curentStudent -> head;
				curentStudent -> head = index -> head;
				index -> head = temp;
			}

			index = index -> next;
		}
		curentStudent = curentStudent -> next;
	}
}

void insertPos(struct list **head, char *nume, char *prenume, float nMed, int pos){
	struct list *curent= *head;
	struct list *temp = (struct list*)malloc(sizeof(struct list));
	int curentPos = 1;

	srand(time(NULL));

	temp -> head.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(temp -> head.nume, nume);

	temp -> head.prenume= (char*)malloc((strlen(prenume) + 1) * sizeof(char));
	strcpy(temp -> head.prenume, prenume);

	temp -> head.notaMedie = nMed;

	if(pos == 1){
		push(&(*head), nume, prenume, nMed);
		return;
	}

	while(curentPos != pos - 1){
		curent = curent -> next;
		curentPos++;
	}

	temp -> next = curent -> next;
	curent -> next = temp;
}

void deletePos(struct list **head, int pos){
	struct list *temp = *head, *temp2;
	if(pos == 1){
		(*head) = (*head) -> next;
		free(temp -> head.nume);
		free(temp -> head.prenume);
		free(temp);
		return;
	}

	int curentPos = 1;
	while(curentPos != pos - 1){
		temp = temp -> next;
		curentPos++;
	}

	temp2 = temp -> next;
	temp -> next = temp -> next -> next;

	free(temp2 -> head.nume);
	free(temp2 -> head.prenume);
	free(temp2);
}

void clear(struct list **head){
	struct list *temp;

	while((*head) != NULL){
		temp = *head;
		(*head) = (*head) -> next;

		free(temp -> head.nume);
		free(temp -> head.prenume);
		free(temp);
	}
}

void deleteList(struct list **head){
	clear(&(*head));
	free(*head);
}

void inversList(struct list **head){
	struct list *temp = *head, *invList = NULL;

	while(temp != NULL){
		push(&invList, temp -> head.nume, temp -> head.prenume, temp -> head.notaMedie);
		temp = temp -> next;
	}

	deleteList(&(*head));
	(*head) = invList;
}

void menu(){
	printf("1. Citirea aleatorie a studentilor.\n");
	printf("2. Afisarea pozitiei unde se afla primul element dorit\n");
	printf("3. Curatirea listei\n");
	printf("4. Sortarea elementelor\n");
	printf("5. Inserarea unui element nou la capatul listei\n");
	printf("6. Inserarea unui element nou la inceputul listei\n");
	printf("7. Inserarea unui element la o pozitie X in cadrul listei\n");
	printf("8. Stergerea unui element de pe o pozitie x din cadrul listei\n");
	printf("9. Inversarea ordinei elementelor din lista\n");
	printf("0. Eliberarea memoriei listei\n");
}

int main(){
	struct list *stud = NULL;
	int num, option, pos;
	char str[30];

	srand(time(NULL));

	system("cls");
	printf("Dati numarul de elevi:");
	scanf("%d",&num);

	aleator(&stud,num);

	do{
		system("cls");
		afisare(stud);
		printf("\n");
		menu();
		printf("Alegeti optiunea:");
		fflush(stdin);
		scanf("%d",&option);

		switch(option){
			case 1:
				printf("\nDati numarul de studenti:");
				scanf("%d",&num);
				aleator(&stud, num);
			break;

			case 2:
				find(stud);
			break;

			case 3:
				clear(&stud);
				printf("Lista a fost curatita cu succes!");
			break;

			case 4:
				sort(&stud);
			break;

			case 5:
				append(&stud, nume[rand() % 10], prenume[rand() % 10], ((5 * ((float)rand() / RAND_MAX)) + 5));
			break;

			case 6:
				push(&stud, nume[rand() % 10], prenume[rand() % 10], ((5 * ((float)rand() / RAND_MAX)) + 5));
			break;

			case 7:
				printf("\nDati pozitia pe care va fi inserat elementul nou:");
				scanf("%d",&pos);
				insertPos(&stud, nume[rand() % 10], prenume[rand() % 10], ((5 * ((float)rand() / RAND_MAX)) + 5), pos);
			break;

			case 8:
				printf("\nDati pozitia de pe care va fi eliminat elementul:");
				scanf("%d",&pos);
				deletePos(&stud, pos);
			break;

			case 9:
				inversList(&stud);
			break;

			case 0:
				deleteList(&stud);
				printf("\nLista stearsa cu succes\n");
			break;
		}

		printf("\nPress any key to continue...");
		getch();
	}while(option != 0);

	return 0;
}
