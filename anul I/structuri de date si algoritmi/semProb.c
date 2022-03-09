#include <stdio.h>
#include <stdlib.h>

struct elev{
	int index;
	char *nume;
	char *prenume;
	float note[3];
	float notaMedie;
};

struct list{
	struct elev head;
	struct list *next;
};

int main(){
	struct list *elevi = NULL;

	return 0;
}
