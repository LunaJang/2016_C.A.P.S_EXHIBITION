#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>      //반드시 wincon.h 위에 windows.h가 있어야함. 안그러면 에러 폭탄

#define N_SORT 9
#define N_MENU 3
#define N_SETUP 3
#define wait_time 3000

const char* sorting_names[N_SORT] = { "Bubble Sort","Shell Sort","Bogo Sort","Gnome Sort","Quick Sort","Merge Sort","Bitonic Sort","Heap Sort","메뉴로 돌아가기" };
const char* menu_names[N_MENU] = { "소팅 과정 보기","설정 변경","프로그램 종료" };
const char* setup_names[N_SETUP] = { "소팅 속도 변경", "소팅할 배열의 크기 변경", "메뉴로 돌아가기" };

int size = 10;      //size 전역변수로 설정
int speed = 5;      //sorting 속도 저장 (1200/speed)로 프린트



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
	for (i = 0; i <size; i++)
	{
		if (arr[i][1] == 1)      //현재 확인 중인 원소일 경우
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
	Sleep(1200 / speed);

	return;
}
void chan_color(int** arr, int x, int y) {
	arr[x][1] = 1;
	arr[y][1] = 1;      //현재 확인중인 배열 원소의 색 바꿈

	print(arr);

	arr[x][1] = 0;
	arr[y][1] = 0;      //원래대로 돌림

	return;
}
void shuffle(int** arr) {
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
void copy_arr(int** arr, int** original) {      //할당 및 원 배열 복사
	int i;

	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 2);
		arr[i][1] = 0;
		arr[i][0] = original[i][0];
	}
	return;
}



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
			while (temp - i >= 0 && arr[temp - i][0]>arr[temp][0]) {      //temp-i가 존재하고 temp와 temp-i의 순서가 바뀌어있을 경우
				swap(&arr[temp - i][0], &arr[temp][0]);
				chan_color(arr, temp, temp - i);      //순서 바꿈 & 출력 & temp 낮춤
				temp -= i;
			}
		}
	}

	return;
}

void bogo_sorting(int** arr) {
	while (!isSorted(arr)) {
		shuffle(arr);
		print(arr);
	}
	return;
}

void gnome_sort(int **arr)
{
	int i;
	for (i = 0; i < size - 1;)
	{
		if (i < 0 || arr[i][0] <= arr[i + 1][0])
		{
			i++;
			continue;
		}
		arr[i][1] = 1;
		arr[i + 1][1] = 1;
		print(arr);
		swap(arr[i], arr[i + 1]);
		print(arr);
		arr[i][1] = 0;
		arr[i + 1][1] = 0;
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
				arr[h][1] = 1;
				arr[k][1] = 1;
				print(arr);
				arr[h][1] = 0;
				arr[k][1] = 0;
			}
		}
	}
	if (p != h)
	{
		swap(arr[p], arr[h]);
		arr[p][1] = 1;
		arr[h][1] = 1;
		print(arr);
		arr[p][1] = 0;
		arr[h][1] = 0;
	}
	return h;   // h의 위치를 리턴한다.
}
void quick_sort(int **arr, int p, int r)
{
	if (p < r) {
		int q = partition(arr, p, r);
		quick_sort(arr, p, q - 1);
		quick_sort(arr, q + 1, r);
	}
}

void merge_sort(int **arr, int p, int r)
{
	int i = p;
	int temp[100] = { NULL };
	int partition = (r + p) / 2;
	int ai = p, bi = partition;
	if (r - p <= 1) return;
	merge_sort(arr, p, partition);
	merge_sort(arr, partition, r);
	while ((ai < partition) && (bi < r))
	{
		if (arr[ai][0] <= arr[bi][0])//뒤쪽이 크거나 같을 때
		{
			temp[i] = arr[ai][0];//앞쪽 배열의 원소를 대입
			arr[ai][1] = 1;
			arr[bi][1] = 1;
			print(arr);
			arr[ai][1] = 0;
			arr[bi][1] = 0;
			ai++;
		}
		else
		{
			temp[i] = arr[bi][0];//뒤쪽 배열의 원소를 대입
			arr[ai][1] = 1;
			arr[bi][1] = 1;
			print(arr);
			arr[ai][1] = 0;
			arr[bi][1] = 0;
			bi++;
		}
		i++;
	}
	while (ai < partition) //앞쪽 배열의 남은 것들을 대입
	{
		temp[i] = arr[ai][0];
		/*arr[ai][1] = 1;
		print(arr);
		arr[ai][1] = 0;*/
		i++;
		ai++;
	}
	while (bi < r)//뒤쪽 배열의 남은 것들을 대입
	{
		temp[i] = arr[bi][0];
		/*arr[bi][1] = 1;
		print(arr);
		arr[ai][1] = 0;*/
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
			arr[i][1] = 1;
			arr[i + split_length][1] = 1;
			print(arr);
			arr[i][1] = 0;
			arr[i + split_length][1] = 0;
			if (flag == 1)
			{
				if (arr[i][0] > arr[i + split_length][0])
				{
					swap(arr[i], arr[i + split_length]);
					arr[i][1] = 1;
					arr[i + split_length][1] = 1;
					print(arr);
					arr[i][1] = 0;
					arr[i + split_length][1] = 0;
				}
			}
			else
			{
				if (arr[i][0] < arr[i + split_length][0])
				{
					swap(arr[i], arr[i + split_length]);
					arr[i][1] = 1;
					arr[i + split_length][1] = 1;
					print(arr);
					arr[i][1] = 0;
					arr[i + split_length][1] = 0;
				}
			}
		}
		bitonicMerge(arr, low, split_length, flag);
		bitonicMerge(arr, low + split_length, split_length, flag);
	}
}
void bitonic_sort(int **arr, int low, int cnt, int dir)
{
	if (cnt > 1)
	{
		int split_length = cnt / 2;
		bitonic_sort(arr, low, split_length, 1);
		bitonic_sort(arr, low + split_length, split_length, 0);
		bitonicMerge(arr, low, cnt, dir);
	}
}

void heapify(int **arr, int idx, int max)            //heap sort 에서 사용
{
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	int largest;
	if (left < max && (arr[left] > arr[idx]))
	{
		largest = left;
	}
	else
		largest = idx;

	if (right < max && (arr[right] > arr[largest]))
		largest = right;
	if (largest != idx)
	{
		swap(arr[idx], arr[largest]);
		heapify(arr, largest, max);
	}
}
void buildHeap(int **arr) {      //heap sort 에서 사용
	int i;
	for (i = size / 2 - 1; i >= 0; i--)
		heapify(arr, i, size);
}
void heap_sort(int **arr)
{
	int i;
	buildHeap(arr);
	for (i = size - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, 0, i);
	}
}



int example_maker(char* names[], int length) {
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

		arrow = getch();

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
	printf("\n\n%s를 선택하셨습니다.\n\n", names[user]);
	Sleep(wait_time);

	return user;
}

void sorting_manager() {

	int sort = 0, i;
	int** original;      //소팅 전의 원 배열

	original = (int**)malloc(sizeof(int*)*size);      //1차원 배열 동적 할당, 원 배열인 original 생성

	for (i = 0; i < size; i++) {
		original[i] = (int*)malloc(sizeof(int) * 2);
		original[i][1] = 0;
	}

	while (sort != 8) {

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
			//시간 오래걸림 경고
			print(arr);      //정렬 전 배열 프린트
			bogo_sorting(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 3:
			print(arr);      //정렬 전 배열 프린트
			gnome_sort(arr);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 4:
			print(arr);      //정렬 전 배열 프린트
			quick_sort(arr, 0, size - 1);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 5:
			print(arr);      //정렬 전 배열 프린트
			merge_sort(arr, 0, size);
			print(arr);      //정렬 후 배열 프린트
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 6:
			//배열 크기대한 조건있음을 경고
			//print(arr);      //정렬 전 배열 프린트
			//bitonic_sort(arr);
			//print(arr);      //정렬 후 배열 프린트
			printf("아직 덜 만들어짐 \n");
			printf("\n\n소팅완료!");
			Sleep(wait_time);
			break;
		case 7:
			print(arr);      //정렬 전 배열 프린트
			heap_sort(arr);
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

void setup() {
	int user = NULL, temp;

	while (user != 2) {
		user = example_maker(setup_names, N_SETUP);

		switch (user) {
		case 0:
			do {
				system("cls");
				printf("\n\n현재 속도는 %d입니다.\n", speed);
				printf("1~12의 수 중에 원하는 속도를 입력하세요\n클수록 정렬속도가 빠릅니다 : ");
				scanf("%d", &temp);
				if (temp < 0 || temp > 13) {
					printf("3이상 60이하의 수를 입력 해주세요.\n");
				}
			} while (temp < 0 || temp > 13);

			speed = temp;

			printf("소팅의 속도가 %d로 변경되었습니다.", speed);
			Sleep(wait_time);
			break;
		case 1:
			do {
				system("cls");
				printf("\n\n현재 배열의 크기는 %d입니다.\n", size);
				printf("3~60의 수 중에 원하는 배열의 크기를 입력하세요 : ");
				scanf("%d", &temp);
				if (temp < 3 || temp > 60) {
					printf("3이상 60이하의 수를 입력 해주세요.\n");
				}
			} while (temp < 3 || temp > 60);

			size = temp;

			printf("배열의 크기가 %d로 변경되었습니다.", size);
			Sleep(wait_time);
			break;
		}
	}

	return;
}

void menu() {
	int user = NULL, i;

	while (user != 2) {
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

void start() {
	printf("\n\n2016 C.A.P.S 전시회 작품\n\n");
	printf("자료구조 및 실습 - Sorting\n\n");
	Sleep(wait_time);

	menu();

	return;
}

int main() {

	start();

	return 0;
}