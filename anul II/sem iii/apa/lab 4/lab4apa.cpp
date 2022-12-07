#include <iostream>
#include <time.h>

using namespace std;

#define max 500 //nr maxim de varfuri
#define inf 99999 // in loc de +00

int phi[3] = {20, 50, 100}; // cat de tare graful sa fie (in procente (20%, 50%, 100%))
int nrVarf[3] = {10, 50, 100}; // nr de varfuri :/
int iterFloyd, iterDij; //nr de iteratii pentru floyd si dijkastra

//fucntia pentru a reseta graful si iteratiile :/ (nu degeaba reset se numeste :/ )
void reset(int graf[max][max]){
	iterFloyd = iterDij = 0; // iteratiilor li se atribuie 0

	for(int i = 0; i < max; i++) // aista e for
		for(int j = 0; j < max; j++) // si aista e for
			graf[i][j] = 0; // initializeaza graful cu 0 
}

//funcia pentru a crea graful :/
void grafCreate(int graf[max][max], int nrVarf,int dens){
	for(int i = 0; i < nrVarf; i++)	 // inca un for
		for(int j = 0; j < nrVarf; j++)	 // si aici e for
			if(j > i){
				//iful pentru a da valori la muchiile ce se afla mai sus de diagonala principala (undei 1 in matricea de mai jos)

				//  0  1  1  1 1
				// -1  0  1  1 1
				// -1 -1  0  1 1
				// -1 -1 -1  0 1
				// -1 -1 -1 -1 0

				int r = rand() % 100 + 1; //ia un nr random de la 1 la 100;
				if(r <= phi[dens]){ //daca r e mai mic de phi ales(dens e densitatea, se alege in main(detalii la dens tot acolo)), pe positia [i][j] nu se atribuie nimic
					r = rand() % 10000 + 1; 
					graf[i][j] = r;// lui [i][j] i se atrubui r care e un nr rand de la 0 pana la 10000
				}
			} else if(i > j){
				graf[i][j] = graf[j][i]; // se indeplineste muchiile mai jos de diagonala principala(se oglindeste valorile de deasupra diagonalei principale sub diagonala principala)
			}
}

//printeaza graful :/
void printGraf(int graf[max][max], int nrVarf){
	for(int i = 0; i < nrVarf; i++){ // aici iar e for
		for(int j = 0; j < nrVarf; j++) // si aici tot e for :/
			cout << graf[i][j] << " "; //afiseaza valoarea de pe positia [i][j] :/
		cout << endl; //trece din rand nou :/
	}
}

//=====================================================Floyd============================================================
void floyd(int graph[max][max], int size){
	int D[max][max];// matricea ce va contine lungimea celui mai scurt drum intre fiecare pereche de varfuri


	//randurile de mai jos atribuie fiecarui zerou ce nu se afla pe diagonala principala inf(9999) 

	//era asa
	// 0 2 0 1
	// 2 0 3 0
	// 0 3 0 1
	// 1 0 1 0

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++){
			iterFloyd++;
			if(i != j && graph[i][j] == 0){
				iterFloyd++;
				D[i][j] = inf;
			}else{
				iterFloyd++;
				D[i][j] = graph[i][j];
			}
		}

	// sa facut asa
	//   0   2 inf   1
	//   2   0   3 inf 
	// inf   3   0   1
	//   1 inf   1   0

	//pentru a intelege mai zbs cum asta lucreaza cel mai zbs in yt vidosic de uitat :/
	for(int k = 0; k < size; k++)
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++){
				iterFloyd++;
				D[i][j] = min(D[i][j], D[i][k]+D[k][j]); iterFloyd++; // lui D[i][j](costul minim pana la [i][j]) i se atribuie costul minim dintre cel care deja exista si cel care trece prin k
			}

	cout << "Numarul de iteratii(f) : " << iterFloyd << endl;
}

//===============================Dijkastra==============================================
int minCost(int cost[max], bool visited[max], int size){
	int min = inf;
	int minIndex = 0;

	for(int i = 0; i < size; i++){ // trece prin toate varfurile
		iterDij++;
		if(visited[i] == false && cost[i] <= min){ // daca varful nu a fost vizitat si costul e mai mic sau egal cu min
			iterDij++;
			//in randurile de mai jos se tine minte valoarea celui mai mic cost si pozitia lui
			min = cost[i]; 
			minIndex = i;
		}
	}

	return minIndex; // se returneaza pozitia varfului cu cel mai mic cost care inca nu a fost vizitat
}

void dijkastra(int graph[max][max],int start, int size){
	int cost[size]; // pentru costul pana la varf 
	bool visited[size]; //pentru a sti daca varful a fost vizitat

	for(int i = 0; i < size; i++){
		visited[i] = false;
		cost[i] = inf;
	}

	cost[start] = 0; // incepe din varful start (se da in main)

	for(int i = 0; i < size - 1; i++){
		int min = minCost(cost,visited, size);// se ia varful cu cel mai mic cost si care inca nui visitat
		visited[min] = true; // varful min se marcheaza ca vizitat
		for(int j = 0; j < size; j++){
			iterDij++;
			if(!visited[j] && graph[min][j] != 0 // daca varful nu a fost vizitat si valoarea este diferita de 0
				&& cost[min] != inf //daca costul varfului e diferit de inf(9999)
				&& (cost[min] + graph[min][j] < cost[j])) { // daca din min costul pana la j e mai mic atunci costul pana la j se schimba
				iterDij++;
				cost[j] = cost[min] + graph[min][j]; // aici costul se schimba
			}
		}
	}

	cout << "Numarul de iteratii(d) : " << iterDij << endl;
}

int main(){
	srand(time(NULL));
	int graf[max][max];


	// densitatea pentru phi
	/*
		0 - rar (20%)
		1 - mediu (50%)
		2 - dens (100%)
	*/

	for(int i = 0; i < 3; i++) // for pentru a schomba numarul de varfuri
		for(int j = 0; j < 3; j++){ // for pentru a schimba densitatea
			switch(j){
				case 0 : 
					cout << "Graf rar cu " << nrVarf[i] << " varfuri." << endl;
					break;
				case 1 : 
					cout << "Graf mediu cu " << nrVarf[i] << " varfuri." << endl;
					break;
				case 2 : 
					cout << "Graf dens cu " << nrVarf[i] << " varfuri." << endl;
					break;
			}

			reset(graf); // reseteaza graful
			grafCreate(graf,nrVarf[i],j); // creeeaza graful
			//printGraf(graf, nrVarf[i]);
			dijkastra(graf, 0, nrVarf[i]); // dijkastra :/
			floyd(graf, nrVarf[i]); // floyd :/

			cout << endl; // rand nou :/
		}

	return 0;
}
