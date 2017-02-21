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
	arr[y][0] = 1;      //���� Ȯ������ �迭 ������ �� �ٲ�

	print;

	arr[x][0] = 0;
	arr[y][0] = 0;      //������� ����
}

void shell_sorting(int** arr, int size) {
	int i, j;

	for (i = size / 2; i > 0; i = i / 2) {		// i == gap
		for (j = 0; j < size; j++) {		//j == üũ�ϴ� ����
			int temp = j;

			if (temp + i < size) {		//temp + i �� ������ ���

				if (arr[temp]>arr[temp + i]) {		//temp�� temp + i�� �ڹٲ�� ������� 
					swap(arr[temp], arr[temp + i]);
					chan_color(arr, temp, temp + i);		//���� �ٲ� & ��� & temp ����
					temp -= i;
				}
				else {
					chan_color(arr, temp, temp + i);		//���
					continue;
				}
			}
			while (temp -i >=0 && arr[temp-i]<arr[temp]) {		//temp-i�� �����ϰ� temp�� temp-i�� ������ �ٲ������ ���
				swap(arr[temp - i], arr[temp]);
				chan_color(arr, temp, temp + i);		//���� �ٲ� & ��� & temp ����
				temp -= i;
			}
		}
	}
}

int main() {
	int i, size = SIZE;
	int** arr = (int*)malloc(sizeof(int*)*size);

	for (i = 0; i < size; i++) {      //�������迭 �����Ҵ�
		*arr[i] = (int)malloc(sizeof(int) * 2);
		arr[i][1] = 0;      //���� �ʱ�ȭ
	}

	for (i = 1; i <= SIZE; i++) {
		arr[i][i - 1] = i;
	}

	print(arr);      //�迭 ���� ���

	shell_sorting(arr, size);      //sort

	return 0;      //���α׷� ����
}