#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int menhgia;
	char ten[25];
	int PA;
}Money;

Money* readData(int* size) {
	FILE *f;
	f = fopen("MenhGiaTien.txt", "r");
	int i = 0;
	Money* dslt = (Money*)malloc(sizeof(Money));
	
	if (f!= NULL) {
		while (!feof(f)) {
			fscanf(f, "%d %[^\n]", &dslt[i].menhgia, &dslt[i].ten);
			dslt[i].PA = 0;
			i++;
			dslt = (Money*)realloc(dslt, sizeof(Money)*(i+1));
		}
	}
	else {
		printf("Loi doc file du lieu!");
	}
	*size = i;
	fclose(f);
	return dslt;
}

void InsertionSort(Money arr[], int size) {
	for (int i = 1; i < size; i++) {
		int j = i;
		while ((j>0)&&(arr[j].menhgia>arr[j-1].menhgia)) {
			Money tmp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = tmp;
			j--;
		}
	}
}

int Greedy(Money* res, int tienRut, int size) {
	int i = 0;
	while(i<size&&tienRut!=0) {
		res[i].PA = tienRut/res[i].menhgia;
		tienRut -= res[i].PA*res[i].menhgia;
		i++;
	}
	return tienRut;
}

void printScreen(Money arr[], int size, int tienrut, int tienthieu) {
	printf("Bai toan ATM dung THAM AN\n");
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "        Loai tien        ", "Menh Gia", "So to", "Thanh tien");
	for (int i = 0; i < size; i++) {
		printf("|%-3d|%-25s|%-9d|%-9d|%-10d|\n", i+1, arr[i].ten, arr[i].menhgia, arr[i].PA, arr[i].menhgia*arr[i].PA);
	}
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("So tien can rut: %d\n", tienrut);
	printf("So tien da rut: %d", tienrut - tienthieu);
}

int main() {
	int size;
	int TienRut, tienConThieu;
	printf("Nhap so tien can rut: ");
	scanf("%d", &TienRut);
	
	//doc du lieu menh gia tien
	Money* res;
	res = readData(&size);
	
	//sap xep
	InsertionSort(res, size);
	
	//tham an
	tienConThieu = Greedy(res, TienRut, size);
	//in ra man hinh
	printScreen(res, size, TienRut, tienConThieu);
	return 0;
}
