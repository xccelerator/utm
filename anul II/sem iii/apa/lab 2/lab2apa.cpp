#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int it_quick, it_merge, it_bubble;
 
// BUBBLE SORT
void bubbleSort(int arr[], int n){
	int sortat;
	do{
		sortat = 1;
		for(int i = 0; i < n-1; i++){
			if(arr[i] > arr[i+1]){
				sortat = 0;
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
			it_bubble++;
		}
	}while(sortat == 0);
}

// MERGE SORT
void merge(int arr[], int l, int m, int r){
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for(int i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for(int i = 0; i < n2; i++)
		R[i] = arr[m + 1 + i];

	it_merge = it_merge + n1 + n2;

	int i = 0, j = 0, k = l;

	while(i < n1 && j < n2){
		if(L[i] <= R[j])
			arr[k++] = L[i++];
		else arr[k++] = R[j++];
		it_merge++;
	}

	while(i < n1){
		arr[k++] = L[i++];
		it_merge++;
	}

	while(j < n2){
		arr[k++] = R[j++];
		it_merge++;
	}

	it_merge++;
}

void mergeSort(int arr[], int l, int r){
	if(l < r){
		it_merge++;
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

// QUICK SORT
void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high]; 
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
		it_quick++;
    }
    swap(&arr[i + 1], &arr[high]);
	it_quick++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high){
    if (low < high) {
		it_quick++;
        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
void printArray(int arr[], int size){
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
 
void arrDesc(int arr[], int size){
	for(int i = size; i > 0; i--)
		arr[size - i] = i;
}

void arrCresc(int arr[], int size){
	for(int i = 0; i < size; i++)
		arr[i] = i;
}

void arrAleator(int arr[], int size){
	for(int i = 0; i < size; i++)
		arr[i] = rand() % size; 
}

void arrCopy(int arr1[], int arr2[], int size){
	for(int i = 0; i < size; i++)
		arr2[i] = arr1[i];
}

int main(){
	ofstream fin_c("crescator.out");
	ofstream fin_d("descrescator.out");
	ofstream fin_a("aleatoriu.out");
	int n;
	int arrTemp[1000],arr[1000];
	int num[12] = {10, 50, 100, 200 ,300,400, 500,600, 700, 800, 900, 1000};
	srand(time(NULL));

	//crescator

	for(int i = 0; i < 12; i++){
		it_bubble = 0;
		arrCresc(arr,num[i]);
		bubbleSort(arr,num[i]);
		if(i != 11)
			fin_c << it_bubble << " ";
	}
	fin_c << it_bubble;

	fin_c << endl;

	for(int i = 0; i < 12; i++){
		it_quick= 0;
		arrCresc(arr,num[i]);
		quickSort(arr,0, num[i] - 1);
		if(i != 11)
			fin_c << it_quick<< " ";
	}
	fin_c << it_quick;

	fin_c << endl;

	for(int i = 0; i < 12; i++){
		it_merge= 0;
		arrCresc(arr,num[i]);
		mergeSort(arr,0, num[i] - 1);
		if(i != 11)
			fin_c << it_merge << " ";
	}
	fin_c << it_merge;

	//descrescator

	for(int i = 0; i < 12; i++){
		it_bubble = 0;
		arrDesc(arr,num[i]);
		bubbleSort(arr,num[i]);
		if(i != 11)
			fin_d << it_bubble << " ";
	}
	fin_d << it_bubble;

	fin_d << endl;

	for(int i = 0; i < 12; i++){
		it_quick= 0;
		arrDesc(arr,num[i]);
		quickSort(arr,0, num[i] - 1);
		if(i != 11)
			fin_d << it_quick<< " ";
	}
	fin_d << it_quick;

	fin_d << endl;

	for(int i = 0; i < 12; i++){
		it_merge= 0;
		arrDesc(arr,num[i]);
		mergeSort(arr,0, num[i] - 1);
		if(i != 11)
			fin_d << it_merge << " ";
	}
	fin_d << it_merge;

	//aleator

	arrAleator(arrTemp, num[12]);
	for(int i = 0; i < 12; i++){
		it_bubble = 0;
		arrCopy(arrTemp, arr, num[i]);
		bubbleSort(arr,num[i]);
		if(i != 11)
			fin_a << it_bubble << " ";
	}
	fin_a << it_bubble;

	fin_a << endl;

	for(int i = 0; i < 12; i++){
		it_quick= 0;
		arrCopy(arrTemp, arr, num[i]);
		quickSort(arr,0,num[i] - 1);
		if(i != 11)
			fin_a << it_quick<< " ";
	}
	fin_a << it_quick;

	fin_a << endl;

	for(int i = 0; i < 12; i++){
		it_merge= 0;
		arrCopy(arrTemp, arr, num[i]);
		mergeSort(arr,0,num[i] - 1);
		if(i != 11)
			fin_a << it_merge<< " ";
	}
	fin_a << it_merge;

    return 0;
}
