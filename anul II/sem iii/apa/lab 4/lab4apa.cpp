#include <iostream>
#include <time.h>

using namespace std;

#define max 500
#define inf 99999

int phi[3] = {20, 50, 100};
int nrVarf[3] = {10, 15, 20};
int iterFloyd, iterDij;

void reset(int graf[max][max]){
	iterFloyd = iterDij = 0;

	for(int i = 0; i < max; i++)
		for(int j = 0; j < max; j++)
			graf[i][j] = 0;
}

void grafCreate(int graf[max][max], int nrVarf,int dens){
	for(int i = 0; i < nrVarf; i++)	
		for(int j = 0; j < nrVarf; j++)	
			if(j > i){
				int r = rand() % 100 + 1;
				if(r <= phi[dens]){
					r = rand() % 10000 + 1;
					graf[i][j] = r;
				}
			} else if(i > j){
				graf[i][j] = graf[j][i];
			}
}

void printGraf(int graf[max][max], int nrVarf){
	for(int i = 0; i < nrVarf; i++){
		for(int j = 0; j < nrVarf; j++)
			cout << graf[i][j] << " ";
		cout << endl;
	}
}

//=====================================================Floyd============================================================
void printPathFloyd(int start, int graphInit[max][max], int graphFloyd[max][max], int size){
	int k;
	int path[size];

	cout << "=================Floyd:=====================" << endl;

	for(int i = 0; i < size; i++){
		if(i != start){
			for(int j = 0; j < size; j++)
				path[j] = 0;

			k = 0;
			path[k] = start;
			k+=1;

			while(path[k - 1] != i){
				int curr = path[k - 1];
				int optim = start;

				for(int j = 0; j < size; j++)
					if(graphInit[curr][j] != 0)
						if((graphFloyd[curr][i] - graphFloyd[curr][j] == graphFloyd[j][i]) && (graphFloyd[j][i] <= graphFloyd[optim][i]))
							optim = j;

				path[k] = optim;
				k+=1;
			}
			cout << "Costul:" << start << "->" << i << "=" << graphFloyd[start][i] << endl;

			cout << "Drumul:[";
			for(int j = 0; j < k-1; j++)
				cout << path[j] << "->";
			cout << i << "]" << endl << endl;
		}
	}
}

void floyd(int graph[max][max], int size){
	int D[max][max];

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

	for(int k = 0; k < size; k++)
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++){
				iterFloyd++;
				D[i][j] = min(D[i][j], D[i][k]+D[k][j]); iterFloyd++;
			}

	cout << "Numarul de iteratii(f) : " << iterFloyd << endl;
	//printPathFloyd(0,graph, D, size);
}

//===============================Dijkastra==============================================
void printPathDijkastra(int start, int path[max], int cost[max], int size){
	int k = 0;
	cout << "=================Dijkastra:=====================" << endl;
	for(int i = 0; i < size ; i++){
		if(i != start){
			cout << "Costul:" << start << "->" << i << "=" << cost[i] << endl;

			int ord[size];
			k = 0;

			for(int j = 0; j < size; j++)
				ord[j] = 0;

			ord[k] = i;
			k+=1;

			while(ord[k - 1] != start){
				ord[k] = path[ord[k - 1]];
				k+=1;
			}

			cout << "Drumul:" << start << "->" << i << "=["; 
			for(int j = k - 1; j > 0; j--)
				cout << ord[j] << "->";
			cout << ord[0] << "]" << endl << endl;
		}
	}
}

int minCost(int cost[max], bool visited[max], int size){
	int min = inf;
	int minIndex = 0;

	for(int i = 0; i < size; i++){
		iterDij++;
		if(visited[i] == false && cost[i] <= min){
			iterDij++;
			min = cost[i];
			minIndex = i;
		}
	}

	return minIndex;
}

void dijkastra(int graph[max][max],int start, int size){
	int cost[size];
	int path[size];
	bool visited[size];

	for(int i = 0; i < size; i++){
		visited[i] = false;
		cost[i] = inf;
	}

	cost[start] = 0;

	for(int i = 0; i < size - 1; i++){
		int min = minCost(cost,visited, size);
		visited[min] = true;
		for(int j = 0; j < size; j++){
			iterDij++;
			if(!visited[j] && graph[min][j] != 0 
				&& cost[min] != max 
				&& (cost[min] + graph[min][j] < cost[j])) {
				iterDij++;
				cost[j] = cost[min] + graph[min][j];
				path[j] = min;
			}
		}
	}

	cout << "Numarul de iteratii(d) : " << iterDij << endl;
	//printPathDijkastra(0, path, cost, size);
}

int main(){
	srand(time(NULL));
	int graf[max][max];

	/*
		0 - rar
		1 - mediu
		2 - dens
	*/

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
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

			reset(graf);
			grafCreate(graf,nrVarf[i],j);
			//printGraf(graf, nrVarf[i]);
			dijkastra(graf, 0, nrVarf[i]);
			floyd(graf, nrVarf[i]);

			cout << endl;
		}

	return 0;
}
