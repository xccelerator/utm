#include <iostream>

using namespace std;

#define max 500
#define inf 99999

//Floyd
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
		for(int j = 0; j < size; j++)
			if(i != j && graph[i][j] == 0)
				D[i][j] = inf;
			else D[i][j] = graph[i][j];

	for(int k = 0; k < size; k++)
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
				D[i][j] = min(D[i][j], D[i][k]+D[k][j]);

	printPathFloyd(0,graph, D, size);
}

//Dijkastra
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
		if(visited[i] == false && cost[i] <= min){
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
		for(int j = 0; j <= size; j++){
			if(!visited[j] && graph[min][j] != 0 && cost[min] != max && (cost[min] + graph[min][j] < cost[j])){
				cost[j] = cost[min] + graph[min][j];
				path[j] = min;
			}
		}
	}

	printPathDijkastra(0, path, cost, size);
}

int main(){
	int graph[max][max] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
						 {4, 0, 8, 0, 0, 0, 0, 11,0},
						 {0, 8, 0, 7, 0, 4, 0, 0, 2},
						 {0, 0, 7, 0, 9, 14,0, 0, 0},
						 {0, 0, 0, 9, 0, 10,0, 0, 0},
						 {0, 0, 4, 14, 10,0,2, 0, 0},
						 {0, 0, 0, 0, 0, 2, 0, 1, 6},
						 {8, 11,0, 0, 0, 0, 1, 0, 7},
						 {0, 0, 2, 0, 0, 0, 6, 7, 0}};

	dijkastra(graph, 0,9);
	floyd(graph, 9);

	return 0;
}
