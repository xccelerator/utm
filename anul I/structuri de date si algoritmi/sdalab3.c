#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

struct tree{
	int value;
	struct tree *right, *left;
};

void add(struct tree **head, int value){
	if((*head) == NULL){
		(*head) = (struct tree*)malloc(sizeof(struct tree));
		(*head) -> value = value;
		(*head) -> right = (*head) -> left = NULL;
		return;
	}

	if((*head) -> value < value)
		add(&(*head) -> right,value);

	if((*head) -> value > value)
		add(&(*head) -> left,value);
}

//preordine
void printTreePr(struct tree *head){
	if(head != NULL){
		printf("%d ", head -> value);
		printTreePr(head -> left);
		printTreePr(head -> right);
	}
}

//inordine
void printTreeIn(struct tree *head){
	if(head != NULL){
		printTreeIn(head -> left);
		printf("%d ", head -> value);
		printTreeIn(head -> right);
	}
}

//postordine
void printTreePo(struct tree *head){
	if(head != NULL){
		printTreePo(head -> left);
		printTreePo(head -> right);
		printf("%d ", head -> value);
	}
}

void afisare(struct tree *head){
	if(!head){
		printf("Arborele este NULL\n");
		return;
	}

	printf("Afisare preordine: \n");
	printTreePr(head);

	printf("\nAfisare inordine: \n");
	printTreeIn(head);

	printf("\nAfisare postordine: \n");
	printTreePo(head);

	printf("\n");
}

int heightOfTree(struct tree *head){
	if(head == NULL)
		return 0;

	int left = heightOfTree(head -> left);
	int right = heightOfTree(head -> right);

	if(left >= right)
		return left + 1;
	else return right + 1;
}

struct tree* search(struct tree *head, int value){
	if(head == NULL || head -> value == value)
		return head;

	if(value > head -> value)
		return search(head -> right,value);

	if(value < head -> value)
		return search(head -> left,value);
}

void printLeaf(struct tree *head){
	if(head != NULL){
		if(head -> left == NULL && head -> right == NULL)
			printf("%d ", head -> value);
		printLeaf(head -> left);
		printLeaf(head -> right);
	}
}

int heightOfNode(struct tree *head, int value){
	struct tree* temp = search(head, value);
	return heightOfTree(temp);
}

int depthNode(struct tree *head, int value, int depth){
	if(head == NULL)
		return 0;

	if(head -> value == value)
		return depth;

	int tmp = depthNode(head -> left, value, depth + 1);

	if(tmp != 0)
		return tmp;

	tmp = depthNode(head -> right, value, depth + 1);

	return tmp;
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

void aleator(struct tree **head, int num){
	for(int i = 0; i < num; i++) 
		add(&(*head), rand() % 22 + 10);
}

void menu(){
	printf("1. Calcularea adancimii arborelui.\n");
	printf("2. Cautarea unui nod in baza unei chei de cautare.\n");
	printf("3. Calcularea adancimii unui nod.\n");
	printf("4. Calcularea inaltimii unui nod.\n");
	printf("5. Afisarea tuturor frunzelor.\n");
	printf("6. Curatirea elementelor.\n");
	printf("7. Adauga elemente.\n");
	printf("0. Iesire din program.\n");
}

int main(){
	struct tree *head = NULL;
	int num, option, find;
	srand(time(NULL));

	printf("\nheight : %d \n",heightOfNode(head, 5));
	printf("\ndepth : %d \n",depthNode(head, 5, 1));

	printf("\nLeaf\n");
	printLeaf(head);

	system("cls");
	printf("Dati numarul de elemente:");
	scanf("%d",&num);

	aleator(&head, num);

	do{
		system("cls");
		afisare(head);
		printf("\n");
		menu();
		printf("\nAlegeti optiunea:");
		scanf("%d",&option);

		switch(option){
			case 1:
				printf("\nAdancimea arborelui este : %d", heightOfTree(head));
			break;

			case 2:
				printf("Dati valoarea care doriti sa o cautati: ");
				scanf("%d",&find);
				struct tree *tmp = search(head, find);
				if(tmp != NULL){
					printf("Nodul: ");
					printTreeIn(tmp);
				}else printf("Valoare data nu a fost intalnita in arbore!");
			break;

			case 3:
				printf("Alegeti nodul adancimea caruia doriti sa o calculati: ");
				scanf("%d",&num);
				printf("Adancimea nodului este: %d", depthNode(head,num,1));
			break;

			case 4:
				printf("Alegeti nodul inaltimea caruia doriti sa o calculati: ");
				scanf("%d", &num);
				printf("Inltimea nodului este: %d", heightOfNode(head,num));
			break;

			case 5:
				printf("Frunzele arborelui sunt: ");
				printLeaf(head);
			break;

			case 6:
				clearTree(&head);
				printf("Stejarul a fost curatit cu succes!");
			break;

			case 7:
				printf("Dati numarul de elemente:");
				scanf("%d",&num);
				aleator(&head, num);
			break;

			case 0:
				deleteTree(&head);
				printf("Memoria arborelui a fost eliberata cu succes!");
			break;
		}

		printf("\nPress any key to continue...");
		_getch();
	}while(option != 0);

	return 0;
}
