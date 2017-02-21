#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>

void swap(int* a, int* b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void print(int** arr, int size) {
	int i, j;
	system("cls");
	for (i = 0; i <size; i++)
	{
		if (arr[i][1] == 1)		//���� Ȯ�� ���� ������ ���
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			for (j = 0; j < arr[i][0]; j++) {
				printf("�� ");
			}
			printf("\n");
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for (j = 0; j < arr[i][0]; j++) {
				printf("�� ");
			}
			printf("\n");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	Sleep(600);
}

void chan_color(int** arr, int x, int y, int size) {
	arr[x][1] = 1;
	arr[y][1] = 1;      //���� Ȯ������ �迭 ������ �� �ٲ�

	print(arr,size);

	arr[x][1] = 0;
	arr[y][1] = 0;      //������� ����
}

void bubble_sorting(int** arr, int size) {
	int i, j;

	for (i = size; i >= 0; i--) {
		for (j = 0; j < i - 1; j++) {
			if (arr[j][0] > arr[j + 1][0]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(arr[j], arr[j + 1]);
			}
			chan_color(arr,j,j+1,size);			//���� Ȯ������ j,j+1 �� �� �ٲٰ� ���
		}
	}
}

void shell_sorting(int** arr, int size) {
	int i, j;

	for (i = size / 2; i > 0; i = i / 2) {		// i == gap
		for (j = 0; j < size; j++) {		//j == üũ�ϴ� ����
			int temp = j;

			if (temp + i < size) {		//temp + i �� ������ ���
				if (arr[temp][0] > arr[temp + i][0]) {		//temp�� temp + i�� �ڹٲ�� ������� 
					swap(arr[temp], arr[temp + i]);
					chan_color(arr, temp, temp + i, size);		//���� �ٲ� & ���
				}
				else {
					continue;
				}
			}
			while (temp - i >= 0 && arr[temp - i][0]>arr[temp][0]) {		//temp-i�� �����ϰ� temp�� temp-i�� ������ �ٲ������ ���
				swap(arr[temp - i], arr[temp]);
				chan_color(arr, temp, temp - i, size);		//���� �ٲ� & ��� & temp ����
				temp -= i;
			}
		}
	}
}

void shuffle(int **) {

}

void choose_sort(int** arr, int size) {
	int sort;

	while(1) {
		system("cls");
		printf("���ϴ� ���� ����� �����ϼ���\n");
		printf("1. Bubble Sort\n2. Shell Sort\n3. ����\n\n");

		scanf("%d", &sort);

		switch (sort) {
		case 1:
			printf("Bubble Sort�� �����ϼ̽��ϴ�.\n");
			Sleep(1200);
			print(arr, size);		//���� �� �迭 ����Ʈ
			bubble_sorting(arr,size);
			print(arr, size);		//���� �� �迭 ����Ʈ
			return;
		case 2:
			printf("Shell Sort�� �����ϼ̽��ϴ�.\n");
			Sleep(1200);
			print(arr, size);		//���� �� �迭 ����Ʈ
			shell_sorting(arr,size);
			print(arr, size);		//���� �� �迭 ����Ʈ
			return;
		case 3:
			printf("���α׷��� �����մϴ�.\n");
			Sleep(1200);
			return;
		default:
			printf("���� �߸� �Է��ϼ̽��ϴ�.\n �ٽ� �Է��ϼ���.\n");
			Sleep(1200);
			break;
		}
	}
}

int main() {
	int** arr;
	int size = 10, sort;
	int i, j;

	//����ڷκ��� ���� ����, �迭�� ũ�� �޾ƿ;���
	//UI ����

	arr = (int**)malloc(sizeof(int*)*size);		//2���� �迭 ���� �Ҵ�
	
	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 2);
		arr[i][0] = size - i;		//�迭�� �� �Է� or �������� �޾ƿ���
	}

	choose_sort(arr,size);	//���� ��� ���� �� �����Լ� ȣ��

	for (i = 0; i < size; i++) {		//2�����迭 �Ҵ� ����
		free(arr[i]);
	}
	free(arr);

	return 0;
}