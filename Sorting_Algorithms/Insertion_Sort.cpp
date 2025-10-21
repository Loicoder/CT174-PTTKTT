#include <stdio.h>

typedef int key_type;
typedef float another_type;

typedef struct {
	key_type key;
	another_type another_field;
}data_type;

void readFile(data_type arr[], int* n) {
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if (f!=NULL) {
		while (!feof(f)) {
			fscanf(f, "%d %f", &arr[i].key, &arr[i].another_field);
			i++;
		}
	}
	else {
		printf("loi doc file.");
		return;	
	}
	fclose(f);
	*n = i;
}

void printScreen(data_type arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%3d	%3d	%.2f\n", i+1, arr[i].key, arr[i].another_field);
	}
}

void insertionSort(data_type arr[], int n) {
	for (int i = 1; i < n; i++) {
		int j = i;
		while ((arr[j].key < arr[j-1].key)&&(j>0)) {
			data_type tmp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = tmp;
			j--;
		}
	}
}

int main() {
	data_type arr[100];
	int size;
	
	// doc du lieu tu file
	readFile(arr, &size);
	
	// ten thuat toan
	printf("***********insertion sort***********\n");
	
	// du lieu chua sap xep
	printf("du lieu chua duoc sap xep:\n");
	printScreen(arr, size);
	
	// thuat toan sap xep
	insertionSort(arr, size);
	
	// du lieu da sap xep
	printf("du lieu da duoc sap xep:\n");
	printScreen(arr, size);
	
}
