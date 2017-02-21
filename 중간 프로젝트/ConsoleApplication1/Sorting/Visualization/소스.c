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
		if (arr[i][1] == 1)		//현재 확인 중인 원소일 경우
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			for (j = 0; j < arr[i][0]; j++) {
				printf("■ ");
			}
			printf("\n");
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for (j = 0; j < arr[i][0]; j++) {
				printf("■ ");
			}
			printf("\n");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	Sleep(600);
}

void chan_color(int** arr, int x, int y, int size) {
	arr[x][1] = 1;
	arr[y][1] = 1;      //현재 확인중인 배열 원소의 색 바꿈

	print(arr,size);

	arr[x][1] = 0;
	arr[y][1] = 0;      //원래대로 돌림
}

void bubble_sorting(int** arr, int size) {
	int i, j;

	for (i = size; i >= 0; i--) {
		for (j = 0; j < i - 1; j++) {
			if (arr[j][0] > arr[j + 1][0]) {      //큰값이 왼쪽에 있을 경우 위치 바꿈
				swap(arr[j], arr[j + 1]);
			}
			chan_color(arr,j,j+1,size);			//현재 확인중인 j,j+1 의 색 바꾸고 출력
		}
	}
}

void shell_sorting(int** arr, int size) {
	int i, j;

	for (i = size / 2; i > 0; i = i / 2) {		// i == gap
		for (j = 0; j < size; j++) {		//j == 체크하는 원소
			int temp = j;

			if (temp + i < size) {		//temp + i 가 존재할 경우
				if (arr[temp][0] > arr[temp + i][0]) {		//temp와 temp + i가 뒤바뀌어 있을경우 
					swap(arr[temp], arr[temp + i]);
					chan_color(arr, temp, temp + i, size);		//순서 바꿈 & 출력
				}
				else {
					continue;
				}
			}
			while (temp - i >= 0 && arr[temp - i][0]>arr[temp][0]) {		//temp-i가 존재하고 temp와 temp-i의 순서가 바뀌어있을 경우
				swap(arr[temp - i], arr[temp]);
				chan_color(arr, temp, temp - i, size);		//순서 바꿈 & 출력 & temp 낮춤
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
		printf("원하는 소팅 방법을 선택하세요\n");
		printf("1. Bubble Sort\n2. Shell Sort\n3. 종료\n\n");

		scanf("%d", &sort);

		switch (sort) {
		case 1:
			printf("Bubble Sort를 선택하셨습니다.\n");
			Sleep(1200);
			print(arr, size);		//정렬 전 배열 프린트
			bubble_sorting(arr,size);
			print(arr, size);		//정렬 전 배열 프린트
			return;
		case 2:
			printf("Shell Sort를 선택하셨습니다.\n");
			Sleep(1200);
			print(arr, size);		//정렬 전 배열 프린트
			shell_sorting(arr,size);
			print(arr, size);		//정렬 전 배열 프린트
			return;
		case 3:
			printf("프로그램을 종료합니다.\n");
			Sleep(1200);
			return;
		default:
			printf("값을 잘못 입력하셨습니다.\n 다시 입력하세요.\n");
			Sleep(1200);
			break;
		}
	}
}

int main() {
	int** arr;
	int size = 10, sort;
	int i, j;

	//사용자로부터 소팅 종류, 배열의 크기 받아와야함
	//UI 구현

	arr = (int**)malloc(sizeof(int*)*size);		//2차원 배열 동적 할당
	
	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 2);
		arr[i][0] = size - i;		//배열에 수 입력 or 랜덤으로 받아오기
	}

	choose_sort(arr,size);	//소팅 방법 선택 후 소팅함수 호출

	for (i = 0; i < size; i++) {		//2차원배열 할당 해제
		free(arr[i]);
	}
	free(arr);

	return 0;
}