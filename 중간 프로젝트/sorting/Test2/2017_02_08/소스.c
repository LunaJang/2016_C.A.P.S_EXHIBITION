#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>      //반드시 wincon.h 위에 windows.h가 있어야함. 안그러면 에러 폭탄

//소팅 함수만 추가하고자 할 경우
//1. '소팅 함수' 목록에 함수를 추가한 후
//2. sorting_manager 의 case 문에 추가한 소팅의 처리문을 쓴다.
//3. sorting_names 배열의 맨 뒤에 추가한 소팅의 이름을 쓴 후
//4. N_SORT의 값을 수정한다.

#define N_SORT 12
#define N_MENU 3
#define N_SETUP 3
#define wait_time 3000	//프린트 된 지시문의 대기시간

const char* sorting_names[N_SORT] = { "Bubble Sort","Shell Sort","Bogo Sort","Gnome Sort","Quick Sort","Merge Sort","Bitonic Sort","Heap Sort", "Selection Sort","Cocktail Sort", "Insertion Sort", "메뉴로 돌아가기" };
const char* menu_names[N_MENU] = { "소팅 과정 보기","설정 변경","프로그램 종료" };
const char* setup_names[N_SETUP] = { "소팅 속도 변경", "소팅할 배열의 크기 변경", "메뉴로 돌아가기" };

//size랑 speed를 파일입출력으로 저장하고 받아올까??
int size = 10;      //size 전역변수로 설정
int speed = 5;      //sorting 속도 저장 (1200/speed)로 프린트


//배열 조작 함수
#pragma region

void swap(int* a, int* b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;

	return;
}

int isSorted(int** arr) {
	int i;

	for (i = 0; i < size - 1; i++) {
		if (arr[i][0] > arr[i + 1][0]) {      //소팅이 안되었을 경우 0 리턴
			return 0;
		}
	}
	return 1;      //소팅이 되었을 경우 1 리턴
}

void print(int** arr) {
	int i, j;
	system("cls");
	for (i = 0; i < size; i++)
	{
		if (arr[i][1] == 1)      //현재 확인 중인 원소일 경우
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			for (j = 0; j < arr[i][0]; j++) {
				//printf(" ■");
				//putch('■');
				putchar('■');
			}
			printf("\n");
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for (j = 0; j < arr[i][0]; j++) {
				//printf(" ■");
				//putch('■');
				putchar('■');
			}
			printf("\n");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	Sleep(900 / speed);

	return;
}

void chan_color(int** arr, int x, int y) {
	arr[x][1] = 1;
	arr[y][1] = 1;      //현재 확인중인 배열 원소의 색 바꿈

	print(arr);			//막대그래프 출력

	arr[x][1] = 0;
	arr[y][1] = 0;      //원래대로 돌림

	return;
}

void shuffle(int** arr) {		//배열 무작위로 섞음, 각 숫자는 한번씩만 등장
	int i;

	srand(time(NULL));

	for (i = 0; i < size; i++) {
		arr[i][0] = i + 1;
	}

	for (i = 1; i < size; i++) {
		swap(&arr[size - i][0], &arr[rand() % (size - i + 1)][0]);
	}

	return;
}

void copy_arr(int** arr, int** original) {      //arr의 할당 및 original 배열의 값 복사
	int i;

	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 2);
		arr[i][1] = 0;
		arr[i][0] = original[i][0];
	}
	return;
}

#pragma endregion


// 소팅 함수
#pragma region

void bubble_sorting(int** arr) {
	int i, j;

	for (i = size; i >= 0; i--) {
		for (j = 0; j < i - 1; j++) {
			if (arr[j][0] > arr[j + 1][0]) {      //큰값이 왼쪽에 있을 경우 위치 바꿈
				swap(&arr[j][0], &arr[j + 1][0]);
			}
			chan_color(arr, j, j + 1);         //현재 확인중인 j,j+1 의 색 바꾸고 출력
		}
	}

	return;
}

void shell_sorting(int** arr) {
	int i, j;

	for (i = size / 2; i > 0; i = i / 2) {      // i == gap
		for (j = 0; j < size; j++) {      //j == 체크하는 원소
			int temp = j;

			if (temp + i < size) {      //temp + i 가 존재할 경우
				if (arr[temp][0] > arr[temp + i][0]) {      //temp와 temp + i가 뒤바뀌어 있을경우 
					swap(&arr[temp][0], &arr[temp + i][0]);
					chan_color(arr, temp, temp + i);      //순서 바꿈 & 출력
				}
				else {
					continue;
				}
			}
			while (temp - i >= 0 && arr[temp - i][0] > arr[temp][0]) {      //temp-i가 존재하고 temp와 temp-i의 순서가 바뀌어있을 경우
				swap(&arr[temp - i][0], &arr[temp][0]);
				chan_color(arr, temp, temp - i);      //순서 바꿈 & 출력 & temp 낮춤
				temp -= i;
			}
		}
	}

	return;
}

int bogo_sorting(int** arr) {
	while (!isSorted(arr)) {
		shuffle(arr);
		print(arr);

		if (kbhit()) {
			getch();
			return 0;
		}
	}
	return 1;
}

void gnome_sorting(int **arr)
{
	int i;
	for (i = 0; i < size - 1;)
	{
		if (i < 0 || arr[i][0] <= arr[i + 1][0])
		{
			i++;
			continue;
		}
		swap(arr[i], arr[i + 1]);
		chan_color(arr, i, i + 1);
		i--;
	}
}

int partition(int **arr, int p, int r)      //quick sort 에서 사용
{
	int h, k;
	int pivot = arr[p][0]; // 가장 처음의 값이 pivot
	h = p;
	for (k = p + 1; k <= r; k++)
	{
		if (arr[k][0] < pivot)
		{
			h = h + 1;
			if (h != k)
			{
				swap(arr[h], arr[k]);
				chan_color(arr, h, k);
			}
		}
	}
	if (p != h)
	{
		swap(arr[p], arr[h]);
		chan_color(arr, p, h);
	}
	return h;   // h의 위치를 리턴한다.
}
void quick_sorting(int **arr, int p, int r)
{
	if (p < r) {
		int q = partition(arr, p, r);
		quick_sorting(arr, p, q - 1);
		quick_sorting(arr, q + 1, r);
	}
}

void merge_sorting(int **arr, int p, int r)
{
	int i = p;
	int temp[100] = { NULL };
	int partition = (r + p) / 2;
	int ai = p, bi = partition;
	if (r - p <= 1) return;
	merge_sorting(arr, p, partition);
	merge_sorting(arr, partition, r);
	while ((ai < partition) && (bi < r))
	{
		if (arr[ai][0] <= arr[bi][0])//뒤쪽이 크거나 같을 때
		{
			temp[i] = arr[ai][0];//앞쪽 배열의 원소를 대입
			chan_color(arr, ai, bi);
			ai++;
		}
		else
		{
			temp[i] = arr[bi][0];//뒤쪽 배열의 원소를 대입
			chan_color(arr, ai, bi);
			bi++;
		}
		i++;
	}
	while (ai < partition) //앞쪽 배열의 남은 것들을 대입
	{
		temp[i] = arr[ai][0];
		i++;
		ai++;
	}
	while (bi < r)//뒤쪽 배열의 남은 것들을 대입
	{
		temp[i] = arr[bi][0];
		i++;
		bi++;
	}
	for (i = p; i < r; i++)
		arr[i][0] = temp[i];
}

void bitonicMerge(int **arr, int low, int cnt, int flag)         //bitonic sort 에서 사용
{
	if (cnt > 1)
	{
		int split_length = cnt / 2;
		for (int i = low; i < low + split_length; i++)
		{
			//chan_color(arr, i, i + split_length);
			if (flag == 1)
			{
				if (arr[i][0] > arr[i + split_length][0])
				{
					swap(arr[i], arr[i + split_length]);
					chan_color(arr, i, i + split_length);
				}
			}
			else
			{
				if (arr[i][0] < arr[i + split_length][0])
				{
					swap(arr[i], arr[i + split_length]);
					chan_color(arr, i, i + split_length);
				}
			}
		}
		bitonicMerge(arr, low, split_length, flag);
		bitonicMerge(arr, low + split_length, split_length, flag);
	}
}
void bitonic_sorting(int **arr, int low, int cnt, int dir)
{
	if (cnt > 1)
	{
		int split_length = cnt / 2;
		bitonic_sorting(arr, low, split_length, 1);
		bitonic_sorting(arr, low + split_length, split_length, 0);
		bitonicMerge(arr, low, cnt, dir);
	}
}

void heapify(int **arr, int idx, int heap_size)            //heap sort 에서 사용
{
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	int largest;

	if ((left < heap_size) && (arr[left][0] > arr[idx][0]))
		largest = left;
	else
		largest = idx;

	if (right < heap_size)
	{
		chan_color(arr, right, largest);
		if ((arr[right][0] > arr[largest][0]))
			largest = right;
	}

	if (largest != idx)
	{
		swap(arr[idx], arr[largest]);
		chan_color(arr, idx, largest);
		heapify(arr, largest, heap_size);
	}
}
void buildHeap(int **arr, int heap_size)						//heap sort 에서 사용
{
	int idx;
	for (idx = size / 2 - 1; idx >= 0; idx--)
		heapify(arr, idx, heap_size);
}
void heap_sorting(int **arr)
{
	int last;
	int length = size;
	buildHeap(arr, length);
	for (last = length - 1; last > 0; last--)
	{
		swap(arr[0], arr[last]);
		length--;
		heapify(arr, 0, last);
	}
}

void select_sorting(int **arr)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (arr[i][0] >= arr[j][0])
			{
				swap(arr[i], arr[j]);
				chan_color(arr, i, j);
			}
		}
	}
}

void cocktail_sorting(int**arr) {
	int i, j;

	for (i = size; i >= 0; i--) {
		for (j = size - i; j < i - 1; j++) {
			if (arr[j][0] > arr[j + 1][0]) {      //큰값이 왼쪽에 있을 경우 위치 바꿈
				swap(&arr[j][0], &arr[j + 1][0]);
			}
			chan_color(arr, j, j + 1);         //현재 확인중인 j,j+1 의 색 바꾸고 출력
		}
		for (j = i - 1; j > size - i; j--) {
			if (arr[j][0] < arr[j - 1][0]) {      //큰값이 왼쪽에 있을 경우 위치 바꿈
				swap(&arr[j][0], &arr[j - 1][0]);
			}
			chan_color(arr, j, j - 1);         //현재 확인중인 j,j-1 의 색 바꾸고 출력
		}
	}

	return;
}

void insertion_sorting(int** arr) {
	printf("덜 만듬 ㅎㅎㅎ\n");
}

#pragma endregion


//UI 함수
#pragma region

int example_maker(char* names[], int length) {		//보기 출력 함수
	int i, user = 0;
	int arrow = NULL;

	while (arrow != 13) {
		system("cls");
		printf("\n\n원하는 항목을 선택하세요.\n\n");

		for (i = 0; i < length; i++) {
			if (i == user) {
				printf("▶");
			}
			else {
				printf("  ");
			}
			printf("%s\n", names[i]);
		}

		arrow = getch();		//방향키 받아오는 부분

		if (arrow == 224) {

			arrow = getch();

			switch (arrow) {
			case 72:
				if (user > 0) {
					user--;
				}
				break;
			case 80:
				if (user < length - 1) {
					user++;
				}
				break;
			}
		}
	}
	printf("\n\n%s(을)를 선택하셨습니다.\n\n", names[user]);
	Sleep(wait_time);

	return user;
}

void sorting_manager() {		//소팅 함수 호출하는 함수

	//하드코딩 부분

	int sort = 0, i, temp_bogo;
	int** original;      //소팅 전의 원 배열

	original = (int**)malloc(sizeof(int*)*size);      //1차원 배열 동적 할당, 원 배열인 original 생성

	for (i = 0; i < size; i++) {
		original[i] = (int*)malloc(sizeof(int) * 2);
		original[i][1] = 0;
	}

	while (sort != N_SORT -1) {

		shuffle(original);      //original 배열 무작위로 섞음

		int** arr = (int**)malloc(sizeof(int*)*size);;         //소팅 할 배열, 매번 새로 할당, original의 복사본
		copy_arr(arr, original);

		sort = example_maker(sorting_names, N_SORT);		//보기 출력

		switch (sort) {
		case 0:
			print(arr);      //정렬 전 배열 프린트
			bubble_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 1:
			print(arr);      //정렬 전 배열 프린트
			shell_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 2:
			printf("\n\nBogo Sort는 시간이 매우매우 오래 걸리며 결과를 못 볼 가능성이 매우 큽니다.\n\n");
			printf("굳이 해보신다면 설정에서 배열의 크기를 4이하로 설정하시길 권장합니다.\n\n");
			printf("보다 지치실 경우, 아무키나 눌러 소팅을 중단시킬 수 있습니다.");
			Sleep(wait_time);
			print(arr);      //정렬 전 배열 프린트
			temp_bogo = bogo_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			if (temp_bogo) {
				printf("\n\n소팅완료!");
			}
			else {
				printf("\n\n소팅중단!");
			}
			Sleep(wait_time);
			break;
		case 3:
			print(arr);      //정렬 전 배열 프린트
			gnome_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 4:
			print(arr);      //정렬 전 배열 프린트
			quick_sorting(arr, 0, size - 1);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 5:
			print(arr);      //정렬 전 배열 프린트
			merge_sorting(arr, 0, size);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 6:
			if ((size == 2) || (size == 4) || (size == 8) || (size == 16) || (size == 32)) {
				print(arr);      //정렬 전 배열 프린트
				bitonic_sorting(arr, 0, size, 1);
				print(arr);      //정렬 후 배열 프린트
				printf("\n\n소팅완료!");
			}
			else {
				printf("\n\nBitonic Sort는 배열의 크기가 2의 제곱수일때만 사용 가능합니다.\n");
				printf("설정에서 배열의 크기를 변경하고 사용 해 주세요.\n");
			}
			Sleep(wait_time);
			break;
		case 7:
			print(arr);      //정렬 전 배열 프린트
			heap_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 8:
			print(arr);      //정렬 전 배열 프린트
			select_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 9:
			printf(arr);      //정렬 전 배열 프린트
			cocktail_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 10:
			printf(arr);      //정렬 전 배열 프린트
			insertion_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		}

		for (i = 0; i < size; i++) {      //2차원배열 할당 해제
			free(arr[i]);
		}
		free(arr);
	}

	return;
}

void setup() {		//설정 변경 처리 함수
	int user = NULL, temp;

	while (user != N_SETUP - 1) {
		user = example_maker(setup_names, N_SETUP);

		switch (user) {
		case 0:
			do {
				system("cls");
				printf("\n\n현재 속도는 %d입니다.\n\n", speed);
				printf("1~12의 수 중에 원하는 속도를 입력하세요\n\n클수록 정렬속도가 빠릅니다 : ");
				scanf("%d", &temp);
				if (temp < 0 || temp > 13) {
					printf("\n\n1이상 12이하의 수를 입력 해주세요.\n");
					Sleep(wait_time);
				}
			} while (temp < 0 || temp > 13);

			speed = temp;

			printf("\n\n소팅의 속도가 %d(으)로 변경되었습니다.", speed);
			Sleep(wait_time);
			break;
		case 1:
			do {
				system("cls");
				printf("\n\n현재 배열의 크기는 %d입니다.\n\n", size);
				printf("3~27의 수 중에 원하는 배열의 크기를 입력하세요 : ");
				scanf("%d", &temp);
				if (temp < 3 || temp > 27) {
					printf("\n\n3이상 27이하의 수를 입력 해주세요.\n");
					Sleep(wait_time);
				}
			} while (temp < 3 || temp > 27);

			size = temp;

			printf("\n\n배열의 크기가 %d(으)로 변경되었습니다.", size);
			Sleep(wait_time);
			break;
		}
	}

	return;
}

void menu() {		//기본 메뉴 처리 함수
	int user = NULL;

	while (user != N_MENU - 1) {
		user = example_maker(menu_names, N_MENU);

		switch (user) {
		case 0:
			sorting_manager();
			break;
		case 1:
			setup();
			break;
		}
	}
	return;
}

void start() {		// 뽀대용 시작 부분 처리 함수
	printf("\n\n2016 C.A.P.S 전시회 작품\n\n");
	printf("자료구조 및 실습 - Sorting\n\n");
	Sleep(wait_time);

	menu();

	return;
}

#pragma endregion


int main() {

	start();

	printf("\n\n프로그램이 종료 됩니다.\n\n감사합니다.\n\n");

	return 0;
}