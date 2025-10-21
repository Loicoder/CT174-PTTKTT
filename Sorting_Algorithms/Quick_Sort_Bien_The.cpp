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

int find_pivot(data_type arr[], int l, int r) {
	int first_key;
	int k = l+1;
	first_key = arr[l].key;
	while (k <= r && arr[k].key == first_key) k++;
	if (k > r) return -1;
	else {
		if (arr[k].key < first_key) return k;
	}
	return l;
}

int partition(data_type arr[], int start, int end, int pivot) {
	int left = start, right = end;
	while (left <= right) {
		while (arr[left].key <= pivot) left++;
		while (arr[right].key > pivot) right--;
		
		if (left < right) {
			data_type tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
			
		}
	}
	return left;
}

void quickSort(data_type arr[], int l, int r) {
	int pivot, pivot_index, partition_point;
	pivot_index = find_pivot(arr, l, r);
	if (pivot_index != -1) {
		pivot = arr[pivot_index].key;
		partition_point = partition(arr, l, r, pivot);
		quickSort(arr, l, partition_point-1);
		quickSort(arr, partition_point, r);
	}
	
}

int main() {
	data_type arr[100];
	int size;
	
	// doc du lieu tu file
	readFile(arr, &size);
	
	// ten thuat toan
	printf("***********quick sort***********\n");
	
	// du lieu chua sap xep
	printf("du lieu chua duoc sap xep:\n");
	printScreen(arr, size);
	
	// thuat toan sap xep
	quickSort(arr, 0, size-1);
//	partition(arr, 0, size-1, 10);
	
//	 du lieu da sap xep
	printf("du lieu da duoc sap xep:\n");
	printScreen(arr, size);
	
}
