#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char ten[25];
	float TL, GT, DG;
	int PA;
}Dovat;

Dovat* readData(float * W, int* size) {
	FILE *f;
	f = fopen("CBL1.txt", "r");
	int i = 0;
	Dovat* dsdv = (Dovat*)malloc(sizeof(Dovat));
	
	if (f!= NULL) {
		fscanf(f, "%f", W);
		while (fscanf(f, "%f %f %[^\n]", &dsdv[i].TL, &dsdv[i].GT, dsdv[i].ten) == 3) {
		    dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		    dsdv[i].PA = 0;
		    i++;
		    dsdv = (Dovat*)realloc(dsdv, sizeof(Dovat) * (i + 1));
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

void createFirstNode(float* TGT, float* GLNTT,float *CT, float donGiaMax, float W) {
	*TGT = 0.0;
	*GLNTT = 0.0;
	*CT	= W*donGiaMax;
}

void updateBestChoice(Dovat arr[], int size, int tmp[],float TGT, float* GLNTT) { //do khong thay doi TGT nen khong can contro
	if (TGT > *GLNTT) {
		*GLNTT = TGT;
		for (int i = 0; i < size; i++) {
			arr[i].PA = tmp[i];
		}
	}
}

void branchBound(Dovat arr[], int size, int indexDoVat, float* W, float* TGT, float* CT, float* GLNTT, int tmp[]) {
	
	
	int xk = *W/arr[indexDoVat].TL;
	
	for (int i = xk; i >= 0; i--) {
		// tinh gia tri cho nut trong
		*TGT += i*arr[indexDoVat].GT;
		*W -= i*arr[indexDoVat].TL;
		*CT = *TGT + (*W)*arr[indexDoVat+1].DG;
		
		if (*CT > *GLNTT) {
			tmp[indexDoVat] = i;
			if (*W == 0 || indexDoVat==size-1) { // toi nut la hoac balo day
				updateBestChoice(arr, size, tmp, *TGT, GLNTT);
			}
			else {
				branchBound(arr, size, indexDoVat+1, W, TGT, CT, GLNTT, tmp); //xet tiep nut con
			}
		}
		// hoan tra gia tri ban dau
		tmp[indexDoVat] = 0;  //den cuoi cung khong co phuong an tot se tu dong = 0
		*TGT -= i*arr[indexDoVat].GT;
		*W += i*arr[indexDoVat].TL;
		// khong can tinh can tren vi no phu thuoc tgt va w		
	}
	
}

void printScreen(Dovat arr[], int size, float w) {
	printf("Bai toan CLB1 dung NHANH CAN\n");
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "        Ten do vat       ", "Gia tri", "Phuong An", "Tong GT");
	printf("|---|-------------------------|---------|---------|----------|\n");	
	int trongLuong = 0;
	float TGT = 0;
	for (int i = 0; i < size; i++) {
		trongLuong += arr[i].TL*arr[i].PA;
		TGT += arr[i].GT*arr[i].PA;
		printf("|%-3d|%-25s|%-9.2f|%-9d|%-10.2f|\n", i+1, arr[i].ten, arr[i].GT, arr[i].PA, arr[i].GT*arr[i].PA);
	}
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("Tong trong luong balo: %d\n", trongLuong);
	printf("Tong gia tri balo: %.2f", TGT);
}

int main() {
	int size;
	float w;
	
	//load file du lieu
	Dovat* dsdv = readData(&w, &size);  
	//sap xep
	InsertionSort(dsdv, size);
	// set up nhanh can
	float TGT, CT, GLNTT;
	int tmp[size]; //mang luu phuong an tam thoi
	createFirstNode(&TGT, &GLNTT, &CT, dsdv[0].DG, w); //branchBound dang de quy nen khong duoc de vao
	// nhanh can
	branchBound(dsdv, size, 0, &w, &TGT, &CT, &GLNTT, tmp);
	// in ra man hinh
	printScreen(dsdv, size, w);
	return 0;
}
