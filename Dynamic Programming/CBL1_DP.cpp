#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char tenDV[20];
	int GT, TL, PA;
} DoVat;

typedef int bang[50][100];

DoVat* readFile(int* n, int* w) {
	FILE* f = fopen("CBL13_DP.txt", "r");
	
	// doc w dau file
	fscanf(f, "%d", w);
	int i = 0;
	DoVat* dsdv = (DoVat*)malloc(sizeof(DoVat));
	while (fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV)==3) {
		dsdv[i].PA = 0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
	
	
}

void printFile(DoVat dsdv[], int n, int w) {
	printf("trong luong toi da cua balo la: %d\n", w);
	printf("|------------------|-----|-----|\n");
	printf("|%18s|%5s|%5s|\n", "    Ten Do Vat    ", " TL  ", " GT  ");
	printf("|------------------|-----|-----|\n");
	for (int i = 0; i < n; i++) {
		printf("|%-18s|%-5d|%-5d|\n", dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT);
	}
	printf("|------------------|-----|-----|\n");
}

void createTable(bang F, bang X, DoVat dsdv[], int n, int w) {
	// dien dong dau tien cua bang
	for (int v = 0; v <= w; v++) {
		X[0][v] = v/dsdv[0].TL;
		F[0][v] = X[0][v]*dsdv[0].GT;
	}
	
	// dien cac dong con lai
	int Fmax, Xmax, yk, xk, k;
	for (k = 1; k < n; k++) {
		for (int v = 0; v <= w; v++) {
			yk = v/dsdv[k].TL;
			Xmax = 0;
			Fmax = F[k-1][v];
			for (xk = 1; xk <= yk; xk++) {
				if (F[k-1][v-xk*dsdv[k].TL]+xk*dsdv[k].GT > Fmax) {
					Fmax = F[k-1][v-xk*dsdv[k].TL]+xk*dsdv[k].GT;
					Xmax = xk;
				}
			}
			F[k][v] = Fmax;
			X[k][v] = Xmax;
		}
	}
}

void printTable(bang F, bang X, int n, int w) {
	printf("\nBang quy hoach dong\n");
	for (int k = 0; k < n; k++)	 {
		printf("|%d", k+1);
		for (int v = 0; v <= w; v++) {
			printf("|%2d %2d", F[k][v], X[k][v]);
		}
		printf("|\n");
	}
}

void searchTable(bang F, bang X, int n, int w, DoVat dsdv[]) {
	int v = w; //pa toi uu nam cuoi vi khi do trong luong balo duoc dung nhieu nhat
	for (int k = n-1; k>=0; k--) {
		dsdv[k].PA = X[k][v];
		v -= X[k][v]*dsdv[k].TL;
	}
}

void printResult(DoVat dsdv[], int n) {
	int TGT = 0, TTL = 0;
	printf("\nBai toan CBL1 giai bang thuat toan quy hoach dong\n");
	printf("|--------------------|-----|-----|-----|-----|\n");
	printf("|%20s|%5s|%5s|%5s|%5s|\n", "     Ten Do Vat     ", " TL  ", " GT  ", " PA  ", " TGT ");
	printf("|--------------------|-----|-----|-----|-----|\n");
	for (int i = 0; i < n; i++) {
		printf("|%20s|%5d|%5d|%5d|%5d|\n", dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].PA, dsdv[i].PA*dsdv[i].GT);
		TGT += dsdv[i].GT*dsdv[i].PA;
		TTL += dsdv[i].TL*dsdv[i].PA;
	}
	printf("|--------------------|-----|-----|-----|-----|\n");
	printf("Tong gia tri thu duoc la: %d\n", TGT);
	printf("Tong trong luong balo la: %d", TTL);
	
}
int main() {
	int w, n;
	DoVat* dsdv = readFile(&n, &w);
	bang F, X;
	printFile(dsdv, n, w);
	createTable(F, X, dsdv, n, w);
	printTable(F, X, n, w);
	searchTable(F, X, n, w, dsdv);
	printResult(dsdv, n);
	return 0;
}

