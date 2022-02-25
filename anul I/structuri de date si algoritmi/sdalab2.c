#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct elev{
	char *nume;
	struct elev *next
};

const char name[][16] = {"Dragos", "Roxana", "Sorin", "Maxim", "Catalin", "Cristian", "Vasile", "Stefan", "Ecaterina", "Iana", "Nichita"};

//adauga element nou la sfarsitul listei
void append(struct elev **head, char *name){
	struct elev *newElev = (struct elev*)malloc(sizeof(struct elev));
	struct elev *last = *head;

	newElev -> nume = (char*)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(newElev -> nume, name);

	newElev -> next = NULL;

	if(*head == NULL){
		*head = newElev;
		return;
	}

	while(last -> next != NULL)
		last = last -> next;

	last -> next = newElev;
}

//adauga element nou la inceputul listei
void push(struct elev **head, char *nume){
	struct elev *newElev = (struct elev*)malloc(sizeof(struct elev));

	newElev -> nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(newElev -> nume, nume);
	newElev -> next = *head;

	(*head) = newElev;
}

void aleator(struct elev **head, int num){
	srand(time(NULL));

	for(int i = 0; i < num; i++)
		append(&*head,name[rand() % 11]);
}


void afisare(struct elev *head){
	if(head == NULL){
		printf("Lista este Nula");
		return;
	}

	while(head != NULL){
		printf("%s\n", head -> nume);
		head = head -> next;
	}
}

void find(struct elev *head, char *nume){
	int i = 1;
	while(head != NULL){
		if(strcmp(head -> nume, nume) == 0){
			printf("\nPrima aparitie a elevului cu numele \"%s\" este pe pozitia %d\n", nume, i);
			return;
		}
		i++;
		head = head -> next;
	}

	printf("\nElev cu numele \"%s\" nu a fost gasit\n",nume);
}

void clear(struct elev **head){
	struct elev *temp = (struct elev*)malloc(sizeof(struct elev));
	while((*head) != NULL){
		temp = *head;
		(*head) = (*head) -> next;

		free(temp -> nume);
		free(temp);
	}
}

void deleteList(struct elev **head){
	clear(&*head);
	free(*head);
}

void sortList(struct elev **head){
	struct elev *curentElev = *head, *index = NULL;
	char temp[30];

	while(curentElev != NULL){
		index = curentElev -> next;

		while(index != NULL){
			if(strcmp(curentElev -> nume, index -> nume) > 0){
				strcpy(temp, curentElev -> nume);
				strcpy(curentElev -> nume, index -> nume);
				strcpy(index -> nume, temp);
			}
			index = index -> next;
		}
		curentElev = curentElev -> next;
	}
}

void insertPos(struct elev **head, char *nume, int pos){
	int i = 1;
	struct elev *temp = (struct elev*)malloc(sizeof(struct elev));
	struct elev* curent = *head, *prev;

	temp -> nume = (char*)malloc((strlen(nume) + 1)*sizeof(char));
	strcpy(temp -> nume, nume);
	temp -> next = NULL;


	if(pos == 1){
		push(&*head, nume);
		return;
	}

	while(i < pos){
		prev = curent;
		curent = curent -> next;
		i++;
	}

	temp -> next = curent;
	prev -> next = temp;
}

void deletePos(struct elev **head, int pos){
	int i = 1;
	struct elev *temp = *head, *prev;

	if(pos == 1){
		(*head) = (*head) -> next;
		free(temp);
		return;
	}

	while(i < pos){
		prev = temp;
		temp = temp -> next;
		i++;
	}

	prev -> next = temp -> next;
}

void inversList(struct elev **head){
	struct elev *invlist = NULL;
	struct elev *temp = *head;
	while(temp != NULL){
		push(&invlist, temp -> nume);
		temp = temp -> next; 
	}

	deleteList(&*head);
	(*head) = invlist;
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
	struct elev *head = NULL;
	int num, option, pos;
	char str[30];

	srand(time(NULL));

	system("cls");
	printf("Dati numarul de elevi:");
	scanf("%d",&num);

	aleator(&head,num);

	do{
		system("cls");
		afisare(head);
		printf("\n\n");
		menu();
		printf("\nAlegeti optiunea:");
		scanf("%d",&option);
		switch(option){
			case 1 : 
				printf("Dati numarul de elevi:");
				scanf("%d",&num);
				aleator(&head,num);
			break;

			case 2 : 
				strcpy(str,name[rand() % 11]);
				printf("Numele care urmeaza sa fie cautat in lista este %s\n",str);
				find(head, str);
			break;

			case 3 : 
				clear(&head);
				printf("Lista a fost curatita cu succes!\n");
			break;

			case 4 : 
				sortList(&head);
			break;

			case 5 : 
				strcpy(str,name[rand() % 11]);
				printf("Numele care urmeaza sa fie adaugat la capatul listei este %s\n",str);
				append(&head, str);
			break;

			case 6 :
				strcpy(str,name[rand() % 11]);
				printf("Numele care urmeaza sa fie adaugat la inceputul listei este %s\n",str);
				push(&head, str);
			break;

			case 7 : 
				printf("Dati pozitia pe care va fi adaugat elementul nou:");
				scanf("%d", &pos);
				strcpy(str,name[rand() % 11]);
				printf("Numele care urmeaza sa fie adaugat pe pozitia %d este %s\n",pos,str);
				insertPos(&head, str, pos);
			break;

			case 8 : 
				printf("Dati pozitia de pe care va fi sters elementul:");
				scanf("%d", &pos);
				deletePos(&head, pos);
			break;

			case 9 : 
				inversList(&head);
			break;


			case 0 : 
				deleteList(&head);
			break;
		}
		printf("\nApasati orice tasta.\n");
		getch();
	}while(option != 0);
	return 0;
}
