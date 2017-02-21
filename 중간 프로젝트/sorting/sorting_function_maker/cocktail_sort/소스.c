#include <stdio.h>

#define size 10

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void cocktail_sorting(int*arr) {		//���� �ʿ�, ������
	int i, j;

	for (i = size; i >= 0; i--) {
		for (j = size - i; j < i - 1; j++) {
			if (arr[j] > arr[j + 1]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(&arr[j], &arr[j + 1]);
			}
		}

		for (j = i - 1; j > size - i; j--) {
			if (arr[j] < arr[j - 1]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(&arr[j], &arr[j - 1]);
			}
		}
	}

	return;
}

int main() {
	int arr[size] = { 10,9,8,7,6,5,4,3,2,1 };

	cocktail_sorting(arr);

	return 0;
}