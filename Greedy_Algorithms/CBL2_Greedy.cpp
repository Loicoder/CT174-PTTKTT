#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char ten[25];
	float TL, GT, DG;
	int PA, SL;
}Dovat;

Dovat* readData(float* W, int* size) {
	FILE *f;
	f = fopen("CBL2.txt", "r");
	int i = 0;
	Dovat* dsdv = (Dovat*)malloc(sizeof(Dovat));
	
	if (f!= NULL) {
		fscanf(f, "%f", W);
		while (fscanf(f, "%f %f %d %[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, dsdv[i].ten) == 4) { //khong dung feof vi no chi 
			dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;										//dung lai khi khong doc duoc nua
			dsdv[i].PA = 0;															//thanh ra se doc them mot dong
			i++;
			dsdv = (Dovat*)realloc(dsdv, sizeof(Dovat)*(i+1));
		}
	}
	else {
		printf("Loi doc file du lieu!");
	}
	*size = i;
	fclose(f);
	return dsdv;
}

void InsertionSort(Dovat arr[], int size) {
	for (int i = 1; i < size; i++) {
		int j = i;
		while ((j>0)&&(arr[j].DG>arr[j-1].DG)) {
			Dovat tmp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = tmp;
			j--;
		}
	}
}

void Greedy(Dovat res[], int w, int size) {
	int i = 0;
	while (w!=0&&i<size) {
		res[i].PA = w/res[i].TL;
		if (res[i].PA > res[i].SL) res[i].PA = res[i].SL;
		w -= res[i].PA*res[i].TL;
		i++;
	}	
}

void printScreen(Dovat arr[], int size, float w) {
	printf("Bai toan CLB2 dung THAM AN\n");
	printf("|---|-------------------------|---------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-9s|%-10s|\n", "STT", "        Ten do vat       ", "So luong", "Gia tri", "Phuong An", "Tong GT");
	printf("|---|-------------------------|---------|---------|---------|----------|\n");	
	int trongLuong = 0;
	float TGT = 0;
	for (int i = 0; i < size; i++) {
		trongLuong += arr[i].TL*arr[i].PA;
		TGT += arr[i].GT*arr[i].PA;
		printf("|%-3d|%-25s|%-9d|%-9.2f|%-9d|%-10.2f|\n", i+1, arr[i].ten, arr[i].SL, arr[i].GT, arr[i].PA, arr[i].GT*arr[i].PA);
	}
	printf("|---|-------------------------|---------|---------|---------|----------|\n");
	printf("Tong trong luong balo: %d\n", trongLuong);
	printf("Tong gia tri balo: %.2f", TGT);
}

int main() {
	int size;
	float w;
	
	//load file du lieu
	Dovat* dsdv = readData(&w, &size); 
//	printScreen(dsdv, size, w); 
	//sap xep
	InsertionSort(dsdv, size);
	// tham an
	Greedy(dsdv, w, size); 
	// in ra man hinh
	printScreen(dsdv, size, w);
	return 0;
}
