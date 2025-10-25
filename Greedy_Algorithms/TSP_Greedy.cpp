#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	float giaTri;
	int start, end;
} Path;

Path* readData(int* city, int* size) {
	FILE *f;
	f = fopen("TSP_data.txt", "r");
	int k = 0;
	Path* paths = (Path*)malloc(sizeof(Path));
	
	if (f!= NULL) {
		fscanf(f, "%d", city);
		float tmp;
		for (int i = 0; i < *city; i++) {
			for (int j = 0; j < *city; j++) {
				if (j>=i) {
					fscanf(f, "%f", &tmp);
				}
				else {
					fscanf(f, "%f", &paths[k].giaTri);
					paths[k].start = j;
					paths[k].end = i;
					k++;
					paths = (Path*)realloc(paths, sizeof(Path)*(k+1)); 
				}
			}
		}
	}
	else {
		printf("Loi doc file du lieu!");
	}
	*size = k;
	fclose(f);
	return paths;
}

void InsertionSort(Path arr[], int size) {
	for (int i = 1; i < size; i++) {
		int j = i;
		while ((j>0)&&(arr[j].giaTri<arr[j-1].giaTri)) {
			Path tmp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = tmp;
			j--;
		}
	}
}

bool isThirdLevel(Path res[], int paths_count, Path new_path) {
	int count = 0;
	int i = 0;
	while (i < paths_count && count < 2) {
		if (new_path.start == res[i].start || new_path.start == res[i].end) {
			count++;
		}
		i++;
	}
	if (count == 2) { //da du 2 canh
		return true;
	}
	
	count = 0;
	i  = 0;
	while (i < paths_count && count < 2) {
		if (new_path.end == res[i].start || new_path.end == res[i].end) {
			count++;
		}
		i++;
	}
	if (count == 2) { //da du 2 canh
		return true;
	}
	
	return false;	
}

void init_forest(int forest[], int size) {
	for (int i = 0; i < size; i++) {
		forest[i] = i;
	}
}

int find_root(int forest[], int branch) {
	while (branch != forest[branch]) {
		branch = forest[branch];
	}	
	return branch;
}

bool isLinkBranch(int branch1, int branch2) {
	return (branch1 == branch2);
}

void update_forest(int forest[], int branch1, int branch2) {
	forest[branch1] = branch2;
}

void Greedy(Path arr[], int city, Path res[]) {
	int forest[city];
	init_forest(forest, city);
	int root_count = 0;
	int r1, r2;
	int i;
	// tao chu trinh co n-1 canh - con 1 canh cuoi
	for (i = 0; i < city*(city-1)/2 && root_count < city-1; i++) {
		r1 = find_root(forest, arr[i].start);
		r2 = find_root(forest, arr[i].end);
		if (!isLinkBranch(r1, r2) && !isThirdLevel(res, root_count, arr[i])) {
			res[root_count] = arr[i];
			root_count++;
			update_forest(forest, r1, r2);
		}
	}
	// them canh cuoi cung
	for ( ; i < city*(city-1)/2; i++) {
		r1 = find_root(forest, arr[i].start);
		r2 = find_root(forest, arr[i].end);
		if (isLinkBranch(r1, r2) && !isThirdLevel(res, root_count, arr[i])) {
			res[root_count] = arr[i];
			break;
		}
	}
}

void printScreen(Path arr[], int size) {
	printf("Bai toan TSP dung THAM AN\n");
	float gtChuTrinh = 0;
	for (int i =0; i < size; i++) {
		printf("%c ", arr[i].start+'a');
		gtChuTrinh += arr[i].giaTri;
	}
	printf("\ntong gia tri cua chu trinh tren la: %.2f", gtChuTrinh);
	
} 
int main() {
	int size;
	int city;
	// doc du lieu
	Path* paths = readData(&city, &size);
	Path* res = (Path*)malloc(sizeof(Path)*(city));
	// sorting
	InsertionSort(paths, size);
	// Greedy
	Greedy(paths, city, res);
	// in ket qua ra man hinh
	printScreen(res, city);
	return 0;
}
