#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct elev{
	char *nume;
	char *prenume;
	float notaMedie;
}elev;

elev *elevi;
int n;
const char name[][16] = {"Dragos", "Roxana", "Sorin", "Maxim", "Catalin", "Cristian", "Vasile", "Stefan", "Ecaterina", "Iana", "Nichita"};
const char surname[][15] = {"Cojocari", "Arnaut", "Botnari", "Braguta", "Buza", "Capcanari", "Captarenco","Chiperi","Cornei", "Corobcinschii","Frunceac"};

void menu(){
	printf("\n1. Cautarea unui element dupa valoarea unui camp din structura si returnarea pozitiei unde se afla primul element gasit");
	printf("\n2. Stergerea unui element de pe o pozitie X");
	printf("\n3. Sortarea elementelor dupa un camp a structurii");
	printf("\n4. Inserarea unui element nou la pozitia X");
	printf("\n5. Inserarea unui element la sfarsitul tabloului");
	printf("\n6. Eliberarea memoriei");
	printf("\n7. Citirea aleatorie a elementelor tabloului");
	printf("\n0. Iesirea din program");
}

elev *creareTabel(){
	printf("Dati numarul de elevi: ");
	scanf("%d",&n);

	elev *students;
	students = (elev*)malloc(n*sizeof(elev));
	return students;
}

void aleator(){
	srand(time(NULL));
	char str[255];
	for(int i = 0; i < n; i++){
		strcpy(str, name[rand() % 11]);
		elevi[i].nume = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(elevi[i].nume, str);

		strcpy(str, surname[rand() % 11]);
		elevi[i].prenume = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(elevi[i].prenume, str);

		elevi[i].notaMedie = (5 * ((float)rand() / RAND_MAX)) + 5;
	}
}

void afisare(){
	printf("| Nr. | \tNume |  \tPrenume | Nota medie |\n");
	for(int i = 0; i < n; i++)
		printf("|%4d |%13s |%15s |%12.2f |\n", i + 1, elevi[i].nume, elevi[i].prenume, elevi[i].notaMedie);
}

void cautare(){
	int b = 1, i = 0;
	char str[255];

	printf("Dati numele elevuli care doriti sal cautati: ");
	fflush(stdin);
	gets(str);

	while(i != n && b != 0){
		if(strcmp(str,elevi[i].nume) == 0){
			b = 0;
			printf("| Nr. | \tNume |  \tPrenume | Nota medie |\n");
			printf("|%4d |%13s |%15s |%12.2f |\n", i + 1, elevi[i].nume, elevi[i].prenume, elevi[i].notaMedie);
		}
		i++;
	}

	if(b == 1)
		printf("\nNu a fost gasit elev cu astfel de nume!");

	printf("\n");
}

void stergere(){
	int x;
	printf("Dati numarul elementului care doriti sal stergeti: ");
	scanf("%d",&x);
	x--;

	for(int i = x; i < n-1; i++)
		elevi[i] = elevi[i+1];

	n--;
	elevi = (elev*)realloc(elevi,n*sizeof(elev));
}

void sort(){
	int sortat;
	do{
		sortat = 1;
		for(int i = 0; i < n-1; i++)
			if(elevi[i].notaMedie > elevi[i+1].notaMedie){
				sortat = 0;
				elev temp = elevi[i];
				elevi[i] = elevi[i+1];
				elevi[i+1] = temp;
			}
	}while(sortat == 0);
}

void insertEnd(){
	elev *tempElevi = realloc(elevi, ++n * sizeof(elev));
	char str[255];

	if(tempElevi){
		elevi = tempElevi;
		int pos = n - 1;
		strcpy(str, name[rand() % 11]);
		elevi[pos].nume = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(elevi[pos].nume, str);

		strcpy(str, surname[rand() % 11]);
		elevi[pos].prenume = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(elevi[pos].prenume, str);

		elevi[pos].notaMedie = (5 * ((float)rand() / RAND_MAX)) + 5;
	} else
		printf("Nu e posibil de inserat un element nou");
}

void inserare(int pos){
	elev *tempElevi = realloc(elevi, ++n * sizeof(elev));
	char str[255];

	elevi = tempElevi;
	for(int i = n-1; i >= pos; i--)
		elevi[i] = elevi[i-1];

	pos--;
	strcpy(str, name[rand() % 11]);
	elevi[pos].nume = (char*)malloc((strlen(str) + 1) * sizeof(char));
	strcpy(elevi[pos].nume, str);

	strcpy(str, surname[rand() % 11]);
	elevi[pos].prenume = (char*)malloc((strlen(str) + 1) * sizeof(char));
	strcpy(elevi[pos].prenume, str);

	elevi[pos].notaMedie = (5 * ((float)rand() / RAND_MAX)) + 5;
}

void elibMem(){
	for(int i = 0; i < n; i++){
		free(elevi[i].nume);
		free(elevi[i].prenume);
	}

	free(elevi);
	n = 0;
}

int main(){
	int option;
	int pos;
	system("cls");

	elevi = creareTabel();
	aleator();

	do{
		afisare();
		menu();
		printf("\nAlegeti optiunea: ");
		scanf("%d",&option);
		system("cls");
		switch(option){
			case 1 : cautare(); break;
			case 2 : stergere(); break;
			case 3 : sort(); break;
			case 4 :
				printf("Dati pozitia pe care doriti sa introduceti elementul nou: ");
				scanf("%d",&pos);
				inserare(pos);
			 break;
			case 5 : insertEnd(); break;
			case 6 : elibMem(); break;
			case 7 : aleator(); break;
		}
	}while(option);
	return 0;
}
