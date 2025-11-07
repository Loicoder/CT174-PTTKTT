#include <stdio.h>
#include <stdlib.h>
#define size 30

typedef struct {
	int start, end;
	float length;
	bool is_used;
} Line;

void readFile(Line arr[][size], int* n) {
	FILE* f;
	f = fopen("TSP.txt", "r");
	if (f == NULL) {
		printf("Khong the doc file!");
		return;
	}
	
	fscanf(f, "%d", n);
	
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n;j++) {
			fscanf(f, "%f", &arr[i][j].length);
			arr[i][j].start = i;
			arr[i][j].end = j;
			arr[i][j].is_used = false;
		}
	}
	fclose(f);
}

void printMartrix(Line arr[][size], int n) {
	printf("MA TRAN DA DOC DUOC TU FILE LA:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n;j++) {
			printf("%c%c = %.2f     ", arr[i][j].start+'a', arr[i][j].end+'a', arr[i][j].length);
		}
		printf("\n");
	}
}

float minLine(Line arr[][size], int n) {
	float Lmin = 3.40282e+38;
	for (int i = 0; i<n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j].is_used == false && arr[i][j].length < Lmin) {
				Lmin = arr[i][j].length;
			}
		}
	}
	return Lmin;
}

bool isCircle(Line tmp[], int city, int next) {
	bool res = false;
	int index = 0;
	while (index < city && res == false) {
		if (next == tmp[index].start) {
			res = true;
		}
		else index++;
	}
	
	return res;
}

void updateRes(Line arr[][size], int n, float TGT, float *GNNTT, Line tmp[], Line res[]) {
	tmp[n-1] = arr[tmp[n-2].end][tmp[0].start];
	TGT = TGT + tmp[n-1].length;
	if (TGT < *GNNTT) {
		*GNNTT = TGT;
		for (int i = 0; i < n; i++) {
			res[i] = tmp[i];
		}
	}
	
}

void Branch_Bound(Line arr[][size], int n, int city, int current_city, float* TGT, float* CD, float* GNNTT, Line tmp[], Line res[]) {
	for (int j = 0; j < n; j++) {
		
		if (current_city != j && arr[current_city][j].is_used == false && isCircle(tmp, city, j)==false) {
			*TGT = *TGT + arr[current_city][j].length;
			*CD = *TGT + (n-city)*minLine(arr, n);
			
			if (*CD < *GNNTT) {
				tmp[city] = arr[current_city][j];
				arr[current_city][j].is_used = true;
				arr[j][current_city].is_used = true;
			
				if (city == (n-2)) {
					updateRes(arr, n, *TGT, GNNTT, tmp, res);
				}
				else {
					Branch_Bound(arr, n, city+1, j, TGT, CD, GNNTT, tmp, res);
				}
			}
			
			*TGT = *TGT - arr[current_city][j].length;
			arr[current_city][j].is_used = false;
			arr[j][current_city].is_used = false;
			// khong can tinh lai can duoi vi no khong anh huong toi nut tiep theo
		}
	}
	
} 

void printScreen(Line res[], float GNN, int n) {
	printf("BAI TOAN TSP GIAI BANG NHANH CAN\n");
	printf("PHUONG AN TIM DUOC:\n");
	for (int i = 0; i < n; i++) {
		printf("%c%c : %.2f\n", res[i].start + 'a', res[i].end + 'a', res[i].length);
	}
	printf("CHU TRINH TIM DUOC LA: ");
	for (int i = 0; i < n; i++) {
		printf("%c -> ", res[i].start+'a');
	}
	printf("%c\n", res[0].start+'a');
	printf("TONG GIA TRI CUA CHU TRINH TREN LA: %.2f", GNN);
	
}

int main() {
	Line arr[size][size];
	int n;
	// doc file du lieu
	readFile(arr, &n);
	Line res[n];
	Line tmp[n];
	char start_city, again;
	
	// in ma tran da doc ra man hinh
	printMartrix(arr, n);
	
	// vong lap cho den khi nao nguoi dung muon dung
	do {
		fflush(stdin); // don sach bo nho dem
		
		// nhap thanh pho bat dau
		printf("Nhap diem xuat phat (a->%c): ", n-1+'a');
		scanf("%c", &start_city);
		
		// nhanh can
		float TGT = 0, CD = 0, GNNTT = 3.40282e+38;
		Branch_Bound(arr, n, 0, start_city - 'a', &TGT, &CD, &GNNTT, tmp, res);
		
		// in ket qua ra man hinh
		printScreen(res, GNNTT, n);
		
		// tiep tuc hay dung chuong trinh
		fflush(stdin);
		printf("\nTiep tuc?(y/n): ");
		scanf("%c", &again);
	}	
	while (again == 'y' || again == 'Y');
	return 0;
}
