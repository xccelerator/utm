#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int n){
	int *arr = (int*)malloc(n * sizeof(int));
	if(arr == NULL){
		printf("\nNu sa primit de alocat memoria.\n");
		return;
	}
	int temp;

	for(int i = 0; i < n; i++)
		arr[i] = rand() % n;

	/*
	printf("Tabloul nesortat:\n");
	for(int i = 0; i < n; i++)
		printf("%d ",arr[i]);
	*/

	clock_t begin = clock();

	for(int i = 0; i < n - 1; i++)
		for(int j = 0; j < n - i - 1; j++)
			if(arr[j] > arr[j + 1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}

	clock_t end = clock();

	printf("Tabloul a fost sortat in %f secunde.\n\n", (float)(end - begin) / CLOCKS_PER_SEC);

	/*
	printf("\nTabloul sortat:\n");
	for(int i = 0; i < n; i++)
		printf("%d ",arr[i]);
	*/
	free(arr);
}

void merge(int arr[], int l, int m, int r){
	int n1 = m - l + 1; 
	int n2 = r - m;

	int L[n1], R[n2];

	for(int i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for(int i = 0; i < n2; i++)
		R[i] = arr[m + 1 + i];

	int i = 0, j = 0, k = l;

	while(i < n1 && j < n2){
		if(L[i] <= R[j])
			arr[k] = L[i++];
		else arr[k] = R[j++];

		k++;
	}

	while(i < n1)
		arr[k++] = L[i++];

	while(j < n2)
		arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r){
	if(l < r){
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void mergeSortFunc(int n){
	int *arr = (int*)malloc(n * sizeof(int));
	if(arr == NULL){
		printf("\nNu sa primit de alocat memoria.\n");
		return;
	}
	int temp;

	for(int i = 0; i < n; i++)
		arr[i] = rand() % n;

	/*
	printf("Tabloul nesortat:\n");
	for(int i = 0; i < n; i++)
		printf("%d ",arr[i]);
	*/

	clock_t begin = clock();

	mergeSort(arr, 0, n - 1);

	clock_t end = clock();

	printf("Tabloul a fost sortat in %f secunde.\n\n", (float)(end - begin) / CLOCKS_PER_SEC);

	/*
	printf("\nTabloul sortat:\n");
	for(int i = 0; i < n; i++)
		printf("%d ",arr[i]);
	*/
	free(arr);
}

int linearSearch(int num, int n, int arr[]){
	for(int i = 0; i < n; i++)
		if(arr[i] == num)
			return i + 1;

	return 0;
}

void linearSearchFunc(int n){
	int *arr = (int*)malloc(n * sizeof(int));
	if(arr == NULL){
		printf("\nNu sa primit de alocat memoria.\n");
		return;
	}

	for(int i = 0; i < n; i++)
		arr[i] = rand() % n;

	clock_t begin = clock();

	int pos = linearSearch(-1 ,n,arr);

	clock_t end = clock();

	if(pos)
		printf("\nElementul a fost gasit pe pozitia %d.\n", pos - 1);
	else printf("\nElementul dat nu a fost gasit.\n");


	printf("Timpul de executie: %f secunde.\n\n", (float)(end - begin) / CLOCKS_PER_SEC);

	free(arr);
}

int binarySearch(int arr[], int left, int right, int x){
	if(right >= left){
		int mid = left + (right - left) / 2;

		if(arr[mid] == x)
			return mid + 1;

		if(arr[mid] > x)
			return binarySearch(arr, left, mid - 1, x);

		return binarySearch(arr, mid + 1, right, x);
	}

	return 0;
}

void binarySearchFunc(int n){
	int *arr = (int*)malloc(n * sizeof(int));
	if(arr == NULL){
		printf("\nNu sa primit de alocat memoria.\n");
		return;
	}

	for(int i = 0; i < n; i++)
		arr[i] = rand() % n;

	mergeSort(arr, 0, n - 1);

	clock_t begin = clock();

	int pos = binarySearch(arr, 0, n - 1, -1);

	clock_t end = clock();

	if(pos)
		printf("\nElementul a fost gasit pe pozitia %d.\n",pos - 1);
	else printf("\nElementul nu a fost gasit in tabel.\n");


	printf("Timpul de executie: %f secunde.\n\n", (float)(end - begin) / CLOCKS_PER_SEC);
}

int main(){
	srand(time(NULL));
	printf("---------------Algoritmii de sortare---------------\n");

	printf("\nMerge sort cu 100 elemente:\n");
	mergeSortFunc(100);
	printf("Merge sort cu 1000 elemente:\n");
	mergeSortFunc(1000);
	printf("Merge sort cu 10000 elemente:\n");
	mergeSortFunc(10000);
	printf("Merge sort cu 100000 elemente:\n");
	mergeSortFunc(100000);

	printf("Bubble sort cu 100 elemente:\n");
	bubbleSort(100);
	printf("Bubble sort cu 1000 elemente:\n");
	bubbleSort(1000);
	printf("Bubble sort cu 10000 elemente:\n");
	bubbleSort(10000);
	printf("Bubble sort cu 100000 elemente:\n");
	bubbleSort(100000);

	printf("--------------------------------------------\n");

	int n = 500000;

	printf("\n\n------------Algoritmii de cautare------------\n");
	printf("\nLinear search:");
	linearSearchFunc(n);
	printf("Binary search:");
	binarySearchFunc(n);
	printf("---------------------------------------------");

	return 0;
}
