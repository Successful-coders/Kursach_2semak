#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string>
#include <algorithm>
#include <locale.h>
using namespace std;
FILE *file;


string towns[40];
int i = 0;
int path=0 ,bestpath = 0, k=0;

struct Way {
	char begin[15]="0";
	char end[15]="0";
	int distance=0;
};

void AddList(string begin, string end, int dis, int **Distance) {
	int mark = 0;
	int k = 0, m = 0;
	for (int j = 0; j < i; j++)
	{
		if (begin == towns[j]) {
			mark = 1;
			m = j;
		}
	}

	for (int j = 0; j < i; j++)
	{
		if (end == towns[j]) {
			if (mark == 1) {
				mark = 3;
				k = j;
			}
			else {
				mark = 2;
				k = j;
			}
		}
	}

	if (mark == 1) {
		towns[i] = end;
		Distance[m][i] = dis;
		i++;
	}
	if (mark == 2) {
		towns[i] = begin;
		Distance[i][k] = dis;
		i++;
	}

	if (mark == 3) {
		if (Distance[m][k] < dis) {
			Distance[m][k] = dis;
		}
	}


	if ( mark == 0) {
		towns[i] = begin;
		i++;
		towns[i] = end;
		Distance[i - 1][i] = dis;
 		i++;
	}
	
}

void ReadTowns(int **Distance) {
	char symbol;
	Way *Inf;
	Inf = new Way;

	fscanf(file, "%s %s", Inf->begin, Inf->end);
	fscanf_s(file, "%i", &Inf->distance);
	AddList(Inf->begin, Inf->end, Inf->distance, Distance);
	symbol = fgetc(file);
	if (symbol == '\n') ReadTowns(Distance);
	if (symbol == EOF) return ;
}

int FindIndexTown(string f, int index, int n) {
	for (int k = 0; k < n; k++)
	{
		if (f == towns[k]) {
			index = k;
			return k;
		}
	}

	return -1;

}

void DFS(int indexBegin, int indexEnd, int **Distance, int *Visited, int n) {

	if (indexBegin == indexEnd) {
		k++;
		return;
	}
	Visited[indexBegin] = 1;
	for (int j = 0; j < n  ; j++)
	{
		if (Distance[indexBegin][j]) {
			if (Visited[j] == 0) {
				path += Distance[indexBegin][j];
				bestpath = max(bestpath, path);
				DFS(j, indexEnd, Distance, Visited, n);
				path -= Distance[indexBegin][j];
			}
		}
	}
	Visited[indexBegin] = 0;
}

int **Incialization(int **Distance, int n) {
	for (int j = 0; j <n; j++)
	Distance[j] = (int*)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++)
		{

			Distance[j][k] = 0;
		}

	}
	return Distance;
}

void main() {
	fopen_s(&file, "input.txt", "r");
	setlocale(LC_ALL, "Russian");
	int n=0;
	fscanf_s(file, "%i", &n);
	int *Visited = (int*)malloc(n * sizeof(int));
	int **Distance = (int**)malloc(n * sizeof(int*));

	Distance = Incialization(Distance, n);
	char fbegin[15], fend[15];
	int bindex = -1, eindex = -1;

	ReadTowns(Distance);

	printf_s("Система дорог представлена в виде матрицы весов, следующим образом:\n");
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++) {
			printf_s("%i ", Distance[j][k]);
		}
		printf_s("\n");
	}

	printf_s("Введите город из которого нужно найти максимальный путь: ");
	scanf("%s", fbegin);
	printf_s("Начальный город: %s", fbegin);
	bindex = FindIndexTown(fbegin, bindex, n);
	if (bindex == -1) {

		printf_s("\nТакого города в данной системе не существует!");
	}
	else {

		printf_s("\nВведите город в который нужно найти максимальный путь: ");
		scanf("%s", fend);
		printf_s("Конечный город: %s", fend);
		eindex = FindIndexTown(fend, eindex, n);
		if (eindex == -1) {
			printf_s("\nТакого города в данной системе не существует!");
		}
		else{
			for (int i = 0; i < n; i++)
			{
				Visited[i] = 0;
			}

			DFS(bindex, eindex, Distance, Visited, n);

			if (k == 0) {
				printf_s("\nПути между этими городами не существует!");
			}
			else
			{
				printf_s("\nМаксимальный путь из начального города в конечный:%i", bestpath);
			}

		}
	}
	_getch();
}