#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#define SIZE 10

void print(int** arr) {
	int i = 0;
	system("cls");
	for (i = 0; i < SIZE; i++)
	{
		if (arr[i][1] == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%3d ", arr[i][0]);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("%3d ", arr[i][0]);
		}
		if (i % 10 == 9 || i == SIZE - 1)
			printf("\n");
	}
	Sleep(600);
}

void swap(int* a, int* b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void chan_color(int** arr, int x, int y) {
	arr[x][0] = 1;
	arr[y][0] = 1;      //현재 확인중인 배열 원소의 색 바꿈

	print;

	arr[x][0] = 0;
	arr[y][0] = 0;      //원래대로 돌림
}

void shell_sorting(int** arr, int size) {
	int i, j;

	for (i = size / 2; i > 0; i = i / 2) {		// i == gap
		for (j = 0; j < size; j++) {		//j == 체크하는 원소
			int temp = j;

			if (temp + i < size) {		//temp + i 가 존재할 경우

				if (arr[temp]>arr[temp + i]) {		//temp와 temp + i가 뒤바뀌어 있을경우 
					swap(arr[temp], arr[temp + i]);
					chan_color(arr, temp, temp + i);		//순서 바꿈 & 출력 & temp 낮춤
					temp -= i;
				}
				else {
					chan_color(arr, temp, temp + i);		//출력
					continue;
				}
			}
			while (temp -i >=0 && arr[temp-i]<arr[temp]) {		//temp-i가 존재하고 temp와 temp-i의 순서가 바뀌어있을 경우
				swap(arr[temp - i], arr[temp]);
				chan_color(arr, temp, temp + i);		//순서 바꿈 & 출력 & temp 낮춤
				temp -= i;
			}
		}
	}
}

int main() {
	int i, size = SIZE;
	int** arr = (int*)malloc(sizeof(int*)*size);

	for (i = 0; i < size; i++) {      //이차원배열 동적할당
		*arr[i] = (int)malloc(sizeof(int) * 2);
		arr[i][1] = 0;      //색값 초기화
	}

	for (i = 1; i <= SIZE; i++) {
		arr[i][i - 1] = i;
	}

	print(arr);      //배열 상태 출력

	shell_sorting(arr, size);      //sort

	return 0;      //프로그램 종료
}