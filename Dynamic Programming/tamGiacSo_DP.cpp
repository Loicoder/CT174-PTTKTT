#include <stdio.h>
#include <stdlib.h>
#define size 50

typedef struct {
	int giaTri;
	int index;
}Element;

void readFile(int* n, int tam_giac[][size]) {
	FILE *f;
	f = fopen("tam_giac_so.txt", "r");
	int i=0, j;
	if (f != NULL) {
		while (!feof(f)) {
			for (int j = 0; j <= i; j++) {
				fscanf(f, "%d", &tam_giac[i][j]);
			}
			i++;
		}
	}
	else {
		printf("Loi doc file!");
		return;
	}
	*n=i;
	fclose(f);
}

void inTamGiac(int tam_giac[][size], int n) {    
	printf("TAM GIAC SO da cho la\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d ", tam_giac[i][j]);
		}
		printf("\n");
	}
}

int max(int index_i, int index1, int index2, int index3, int tam_giac[][size]) {
	int max = tam_giac[index_i][index1];
	int index = index1;
	if (tam_giac[index_i][index2] > max) {
		max = tam_giac[index_i][index2];
		index = index2;
	}
	if (tam_giac[index_i][index3] > max) {
		max = tam_giac[index_i][index3];
		index = index3;
	}
	return index;
}

void taoTamGiac(Element PA[][size], int n, int tam_giac[][size]) {
	// khoi tao gia tri cho 2 hang dau truoc de truy hoi
	PA[0][0].giaTri = tam_giac[0][0];
	PA[0][0].index = 0;
	PA[1][0].giaTri = tam_giac[1][0]+PA[0][0].giaTri;
	PA[1][0].index = 0;
	PA[1][1].giaTri = tam_giac[1][1]+PA[0][0].giaTri;
	PA[1][1].index = 0;
	for (int i = 2; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0) { // cot dau tien
				if (tam_giac[i-1][0] > tam_giac[i-1][1]) {
					PA[i][0].giaTri = PA[i-1][0].giaTri+tam_giac[i][j];
					PA[i][0].index = 0;
				}
				else {
					PA[i][0].giaTri = PA[i-1][1].giaTri+tam_giac[i][j];
					PA[i][0].index = 1;
				}
			}
			else if (j == i) { // hang cheo cuoi
				PA[i][j].giaTri = PA[i-1][j-1].giaTri+tam_giac[i][j];
				PA[i][j].index = j-1;
			}
			else if (j == i-1) { // hang cheo trong 
				if (tam_giac[i-1][j-1] > tam_giac[i-1][j]) {
					PA[i][j].giaTri = PA[i-1][j-1].giaTri+tam_giac[i][j];
					PA[i][j].index = j-1;
				}
				else {
					PA[i][j].giaTri = PA[i-1][j].giaTri+tam_giac[i][j];
					PA[i][j].index = j;
				}
			}
			else { // TH binh thuong
				int index = max(i-1, j-1, j, j+1, tam_giac);
				PA[i][j].giaTri = PA[i-1][index].giaTri+tam_giac[i][j];
				PA[i][j].index = index;
			}
		}
	}
}

void inPA(Element PA[][size], int n) {
	printf("TAM GIAC SO da tinh la\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d ", PA[i][j].index);
		}
		printf("\n");
	}
}

int maxDongCuoi(Element PA[][size], int n) {
	int max = PA[n-1][0].giaTri;
	int max_index = 0;
	for (int i = 1; i < n; i++) {
		if (PA[n-1][i].giaTri > max) {
			max = PA[n-1][i].giaTri;
			max_index = i;
		}
	}	
	
	return max_index;
}

void inDuongDi(int F[], int n, Element PA[][size]) {
	printf("Dap an la duong di qua cac so: ");
	for (int i = 0; i < n-1; i++) {
		printf("%d => ", F[i]);
	}
	printf("%d\n", F[n-1]);
	printf("Tong quy trinh la: %d", PA[n-1][maxDongCuoi(PA, n)].giaTri);
}

void traBang(Element PA[][size], int n, int tam_giac[][size], int F[]) {
	F[n-1] = tam_giac[n-1][maxDongCuoi(PA, n)];
	int indexPath = PA[n-1][maxDongCuoi(PA, n)].index;
	for (int i = n-2; i >= 0; i--) {
		F[i] = tam_giac[i][indexPath];
		indexPath = PA[i][indexPath].index;
	}
}

int main() {
	printf("Giai bai toan TAM GIAC SO bang QUY HOACH DONG\n");
	int bang[size][size];
	Element PA[size][size];
	int n;
	
	
	readFile(&n, bang);
	int F[n];
	inTamGiac(bang, n);
	taoTamGiac(PA, n, bang);
	inPA(PA, n);
	traBang(PA, n, bang, F);
	inDuongDi(F, n, PA);
	return 0;
}
