#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

const char nume[][20] = {"Dragos","Ecaterina","Catalin","Doru","Nichita","Mihail","Nicu","Eduard","Nicoleta","Vova"};
const char prenume[][20] = {"Cojocari","Popa","Plesu","Apareci","Furuncea","Lukashuk","Druta","Robovol","Bors","Vozian"};
int currKey = 0;

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

void aleator(struct tree **head, int num){
	srand(time(NULL));
	int i;
	for(i = currKey; i <  currKey + num; i++){
		int key;
		add(&(*head), i + 1, nume[rand() % 10], prenume[rand() % 10], ((5 * ((float)rand() / RAND_MAX)) + 5));
	}
	currKey = i;
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
	if(!head){
		printf("Arborele nu are elemente!\n");
		return;
	}

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

//--------------------------BFS-----------------------------------
struct list{
	void *node;
	struct list *next;
};

void append(struct list **head, struct tree *node){
	struct list *temp = (struct list*)malloc(sizeof(struct list));
	temp -> node = node;
	temp -> next = NULL;

	if(!(*head))
		*head = temp;

	else {
		struct list *current = *head;
		while(current -> next)
			current = current -> next;

		current -> next = temp;
	}
}

struct list * popFirst(struct list **head){
	if(*head){
		struct list *temp = *head;
		(*head) = (*head) -> next;
		return temp;
	}
	return NULL;
}

void clearList(struct list **head){
	struct list *prev = NULL;
	while(*head){
		prev = *head;
		(*head) = (*head) -> next;

		free(prev);
	}
}

void deleteList(struct list **head){
	clearList(&(*head));
	free(*head);
}

void BFS(struct tree *head){
	struct list *vizitate = NULL, *asteptare = NULL, *temp = NULL;
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
//----------------------------------------------------------------

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

void deleteTree(struct tree **head){
	if(*head == NULL)
		return;

	deleteTree(&(*head) -> left);
	deleteTree(&(*head) -> right);

	free(*head);
}

void clearTree(struct tree **head){
	deleteTree(&(*head) -> left);
	deleteTree(&(*head) -> right);
	*head = NULL;
}


int index = 0;

void readIn(struct tree *head, struct elev arr[]){
	if(head){
		readIn(head -> left, arr);
		arr[index++] = head -> data;
		readIn(head -> right, arr);
	}
}

struct tree *balancedTree(struct elev arr[], int inceput, int sfarsit){
	if(inceput > sfarsit)
		return NULL;

	int mijloc = (inceput + sfarsit)/2;
	struct tree *temp = (struct tree*)malloc(sizeof(struct tree));

	temp -> data = arr[mijloc];
	temp -> left = balancedTree(arr, inceput, mijloc - 1);
	temp -> right = balancedTree(arr, mijloc + 1, sfarsit);

	return temp;
}

void menu(){
	printf("1.Adaugarea elementelor. \n");
	printf("2.Cautarea nodului in baza campului cheie de afisare a campurilor nodului gasit. \n");
	printf("3.Parcurgerea arborelui in largime(BFS). \n");
	printf("4.Balansarea arborelui. \n");
	printf("5.Oglindirea arborelui. \n");
	printf("6.Curatirea elementelor arborelui. \n");
	printf("0.Iesirea din program. \n");
}

int main(){
	struct tree *head = NULL;
	int num, option;

	srand(time(NULL));

	system("cls");
	printf("Dati numarul de elevi:");
	scanf("%d",&num);

	aleator(&head,num);
	struct elev *tempElev = (struct elev*)malloc(currKey * sizeof(struct elev));
	do{
		system("cls");
		afisare(head);
		printf("\n");
		menu();
		printf("Alegeti optiunea:");
		fflush(stdin);
		scanf("%d",&option);

		switch(option){
			case 1:
				printf("Dati numarul de elevi care vor urma a fi adaugati:");
				scanf("%d",&num);

				aleator(&head,num);
				tempElev = (struct elev*)realloc(tempElev, currKey * sizeof(struct elev));
			break;

			case 2:
				printf("\nDati cheia elementului care doriti sal cautati:");
				scanf("%d",&num);
				struct tree *temp = search(head, num);

				printIn(temp);
			break;

			case 3:
				printf("\nAfisarea parcurgerii arborelui in largime:\n");
				BFS(head);
			break;

			case 4:
				index = 0;
				readIn(head, tempElev);
				struct tree *balanceInAllThings = balancedTree(tempElev, 0, currKey - 1);
				printf("\nAfisarea BFS a arborelui balansat:\n");
				BFS(balanceInAllThings);

				printf("\nAfisarea inordine a arborelui balansat:\n");
				printIn(balanceInAllThings);
			break;

			case 5:
				mirrorTree(&head);
				printf("\nArborele a fost oglindit cu succes!\n");
			break;

			case 6:
				clearTree(&head);
				currKey = 0;
				printf("Arborele a fost curatit cu succes.");
			break;

			case 0:
				deleteTree(&head);
				printf("Arborele a fost sters cu succes.");
			break;
		}

		printf("\nPress any key to continue...");
		getch();
	}while(option != 0);

	return 0;
}
