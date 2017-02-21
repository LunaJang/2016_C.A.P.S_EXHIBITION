#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#define SIZE 10

void print(int** arr) {
	int i,j,cnt;
	system("cls");
	for (i = 0; i < SIZE; i++)
	{
		if (arr[i][1] == 1)
		{
			cnt = arr[i][0];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

			for (j = 0; j < cnt; j++) {
				printf("��");
			}
			printf("\n");
		}
		else
		{
			cnt = arr[i][0];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			for (j = 0; j < cnt; j++) {
				printf("��");
			}
			printf("\n");
		}
	}
	Sleep(600);		// 600 == 1��
}

void swap(int* a, int* b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sorting(int** arr, int size) {
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < i - 1; j++) {
			if (arr[j][0] < arr[j + 1][0]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(arr[j], arr[j + 1]);
			}
			arr[j][0] = 1;
			arr[j + 1][0] = 1;      //���� Ȯ������ �迭 ������ �� �ٲ�

			print(arr);

			arr[j][0] = 0;
			arr[j + 1][0] = 0;      //������� ����
		}
	}
}

int main() {
	int i;
	int** arr;
	arr= (int**)malloc(sizeof(int*) * SIZE);

	for (i = 0; i < SIZE; i++) {      //�������迭 �����Ҵ�
		*arr[i] = (int*)malloc(sizeof(int) * 2);
		arr[i][1] = 0;      //���� �ʱ�ȭ
	}
	for (i = 1; i <= SIZE; i++) {
		arr[i-1][0] = i;
	}

	print(arr);      //�迭 ���� ���

	bubble_sorting(arr, SIZE);      //sort

	return 0;      //���α׷� ����
}