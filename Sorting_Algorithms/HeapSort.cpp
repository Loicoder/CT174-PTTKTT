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

void swap(data_type* a, data_type* b) {
	data_type tmp = *a;
	*a = *b;
	*b = tmp;	
}

void pushDown(data_type arr[], int start, int end) {
	int r = start;
	
	while (r <= (end-1)/2) {
		if (end == 2*r + 1) {
			if (arr[r].key > arr[end].key) {
				swap(&arr[r], &arr[end]);
			}
				r = end;	// phai bo r = end ra ngoai if vi neu khong, vong lap chi dung khi arr[r].key > arr[end].key
		} 
		else if ((arr[r].key > arr[2*r+1].key) && (arr[2*r+1].key <= arr[2*r+2].key)) {
			swap(&arr[r], &arr[2*r+1]);
			r = 2*r+1;
		} 
		else if ((arr[r].key > arr[2*r+2].key) && (arr[2*r+2].key<arr[2*r+1].key)) {
			swap(&arr[r], &arr[2*r+2]);
			r = 2*r+2;
		}
		else {
			r = end;
		}
	}
	
}	

void heapSort(data_type arr[], int n) {
	for (int i = (n-2)/2; i >= 0; i--) {
		pushDown(arr, i, n-1);
	}
	for (int i = n-1; i >= 2; i--) {
		swap(&arr[0], &arr[i]);
		pushDown(arr, 0, i-1);
	}
	swap(&arr[0], &arr[1]);
}

int main() {
	data_type arr[100];
	int size;
	
	// doc du lieu tu file
	readFile(arr, &size);
	
	// ten thuat toan
	printf("***********heap sort***********\n");
	
	// du lieu chua sap xep
	printf("du lieu chua duoc sap xep:\n");
	printScreen(arr, size);
	
	// thuat toan sap xep
	heapSort(arr, size);
	
//	 du lieu da sap xep
	printf("du lieu da duoc sap xep:\n");
	printScreen(arr, size);
	
}

