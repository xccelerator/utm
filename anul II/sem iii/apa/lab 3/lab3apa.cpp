#include <iostream>
#include <time.h>

#define max 10000

using namespace std;

const int INF = 10000;

int phi[3] = {20, 50, 100};
int nrVarf[3] = {10, 15, 20};

int parent[max] = { 0 }, visited[max] = { 0 };
int grafPrim[max][max],grafKrusk[max][max];
int iterPrim = 0, iterKrusk = 0;

void printGraf(int nrVarf){
	cout << endl << "===========Graful============" << endl;

	for(int i = 0; i < nrVarf; i++){
		for(int j = 0; j < nrVarf; j++)
			if(grafPrim[i][j] != 10000)
				cout << grafPrim[i][j] << " ";
			else cout << "0 ";
		cout << endl;
	}
}

void reset(){
	iterPrim = iterKrusk = 0;

	for(int i = 0; i < max; i++){
		visited[i] = 0;
		parent[i] = 0;
		for(int j = 0; j  < max; j++){
			grafPrim[i][j] = 0;
			grafKrusk[i][j] = 0;
		}
	}
}

void grafCreate(int nrVarf,int dens){
	for(int i = 0; i < nrVarf; i++)	
		for(int j = 0; j < nrVarf; j++)	
			if(j > i){
				int r = rand() % 100 + 1;
				if(r <= phi[dens]){
					r = rand() % 10000 + 1;
					grafPrim[i][j] = r;
					grafKrusk[i][j] = r;
				}
			} else if(i > j){
				grafPrim[i][j] = grafPrim[j][i];
				grafKrusk[i][j] = grafKrusk[j][i];
			}

	for(int i = 0; i < nrVarf; i++)
		for(int j = 0; j < nrVarf; j++)
			if(!grafPrim[i][j] && i != j){
				grafPrim[i][j] = INF;
				grafKrusk[i][j] = INF;
			}
}

//============================PRIM==========================

void prim(int nrVarf){
	int n = 0;
	int u,v, min;
	visited[0] = 1;

	while(n < nrVarf - 1){
		iterPrim++;
		min = INF;

		u = v = 0;

		for(int i = 0; i < nrVarf; i++){
			iterPrim++;
			if(visited[i]){
				iterPrim++;
				for(int j = 0; j < nrVarf; j++){
					iterPrim++;
					if(!visited[j] && grafPrim[i][j] && i != j){
						iterPrim++;
						if(min > grafPrim[i][j]){
							iterPrim++;
							min = grafPrim[i][j];
							u = i; 
							v = j;
						}
					}
				}
			}
		}

		visited[v] = 1;
		n++;

	}
	cout << endl << "Numarul de iteratii(p) : " << iterPrim << endl;
}

//===============================KRUSKAL==========================

int find(int i){
	while(parent[i]){
		i = parent[i];
		iterKrusk++;
	}
	return i;
}

void UNION(int x, int y){
	iterKrusk++;
	if(x != y)
		parent[y] = x;
}

void kruskal(int nrVarf){
	int u,v,x,y,n=0,min;

	while(n < nrVarf - 1){
		iterKrusk++;
		min = INF;

		for(int i = 0; i < nrVarf; i++){
			iterKrusk++;
			for(int j = 0; j < nrVarf; j++){
				iterKrusk++;
				if(grafKrusk[i][j] < min && i != j){
					iterKrusk++;
					min = grafKrusk[i][j];
					x = i;
					y = j;
				}
			}
		}
		u = find(x);
		v = find(y);

		UNION(u,v);

		grafKrusk[x][y] = grafKrusk[y][x] = INF;

		n++;
	}

	cout << "Numarul de iteratii(k) : " << iterKrusk << endl;
}

int main(){
	srand(time(NULL));

	/*
		0 - rar
		1 - mediu
		2 - dens
	*/

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			switch(j){
				case 0 : 
					cout << "Graf rar cu " << nrVarf[i] << " varfuri.";
					break;
				case 1 : 
					cout << "Graf mediu cu " << nrVarf[i] << " varfuri.";
					break;
				case 2 : 
					cout << "Graf dens cu " << nrVarf[i] << " varfuri.";
					break;
			}

			reset();
			grafCreate(nrVarf[i],j);
			printGraf(nrVarf[i]);
			prim(nrVarf[i]);
			kruskal(nrVarf[i]);

			cout << endl;
		}

	return 0;
}
