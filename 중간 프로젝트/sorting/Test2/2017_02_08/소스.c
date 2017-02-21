#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>      //�ݵ�� wincon.h ���� windows.h�� �־����. �ȱ׷��� ���� ��ź

//���� �Լ��� �߰��ϰ��� �� ���
//1. '���� �Լ�' ��Ͽ� �Լ��� �߰��� ��
//2. sorting_manager �� case ���� �߰��� ������ ó������ ����.
//3. sorting_names �迭�� �� �ڿ� �߰��� ������ �̸��� �� ��
//4. N_SORT�� ���� �����Ѵ�.

#define N_SORT 12
#define N_MENU 3
#define N_SETUP 3
#define wait_time 3000	//����Ʈ �� ���ù��� ���ð�

const char* sorting_names[N_SORT] = { "Bubble Sort","Shell Sort","Bogo Sort","Gnome Sort","Quick Sort","Merge Sort","Bitonic Sort","Heap Sort", "Selection Sort","Cocktail Sort", "Insertion Sort", "�޴��� ���ư���" };
const char* menu_names[N_MENU] = { "���� ���� ����","���� ����","���α׷� ����" };
const char* setup_names[N_SETUP] = { "���� �ӵ� ����", "������ �迭�� ũ�� ����", "�޴��� ���ư���" };

//size�� speed�� ������������� �����ϰ� �޾ƿñ�??
int size = 10;      //size ���������� ����
int speed = 5;      //sorting �ӵ� ���� (1200/speed)�� ����Ʈ


//�迭 ���� �Լ�
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
		if (arr[i][0] > arr[i + 1][0]) {      //������ �ȵǾ��� ��� 0 ����
			return 0;
		}
	}
	return 1;      //������ �Ǿ��� ��� 1 ����
}

void print(int** arr) {
	int i, j;
	system("cls");
	for (i = 0; i < size; i++)
	{
		if (arr[i][1] == 1)      //���� Ȯ�� ���� ������ ���
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			for (j = 0; j < arr[i][0]; j++) {
				//printf(" ��");
				//putch('��');
				putchar('��');
			}
			printf("\n");
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for (j = 0; j < arr[i][0]; j++) {
				//printf(" ��");
				//putch('��');
				putchar('��');
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
	arr[y][1] = 1;      //���� Ȯ������ �迭 ������ �� �ٲ�

	print(arr);			//����׷��� ���

	arr[x][1] = 0;
	arr[y][1] = 0;      //������� ����

	return;
}

void shuffle(int** arr) {		//�迭 �������� ����, �� ���ڴ� �ѹ����� ����
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

void copy_arr(int** arr, int** original) {      //arr�� �Ҵ� �� original �迭�� �� ����
	int i;

	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 2);
		arr[i][1] = 0;
		arr[i][0] = original[i][0];
	}
	return;
}

#pragma endregion


// ���� �Լ�
#pragma region

void bubble_sorting(int** arr) {
	int i, j;

	for (i = size; i >= 0; i--) {
		for (j = 0; j < i - 1; j++) {
			if (arr[j][0] > arr[j + 1][0]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(&arr[j][0], &arr[j + 1][0]);
			}
			chan_color(arr, j, j + 1);         //���� Ȯ������ j,j+1 �� �� �ٲٰ� ���
		}
	}

	return;
}

void shell_sorting(int** arr) {
	int i, j;

	for (i = size / 2; i > 0; i = i / 2) {      // i == gap
		for (j = 0; j < size; j++) {      //j == üũ�ϴ� ����
			int temp = j;

			if (temp + i < size) {      //temp + i �� ������ ���
				if (arr[temp][0] > arr[temp + i][0]) {      //temp�� temp + i�� �ڹٲ�� ������� 
					swap(&arr[temp][0], &arr[temp + i][0]);
					chan_color(arr, temp, temp + i);      //���� �ٲ� & ���
				}
				else {
					continue;
				}
			}
			while (temp - i >= 0 && arr[temp - i][0] > arr[temp][0]) {      //temp-i�� �����ϰ� temp�� temp-i�� ������ �ٲ������ ���
				swap(&arr[temp - i][0], &arr[temp][0]);
				chan_color(arr, temp, temp - i);      //���� �ٲ� & ��� & temp ����
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

int partition(int **arr, int p, int r)      //quick sort ���� ���
{
	int h, k;
	int pivot = arr[p][0]; // ���� ó���� ���� pivot
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
	return h;   // h�� ��ġ�� �����Ѵ�.
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
		if (arr[ai][0] <= arr[bi][0])//������ ũ�ų� ���� ��
		{
			temp[i] = arr[ai][0];//���� �迭�� ���Ҹ� ����
			chan_color(arr, ai, bi);
			ai++;
		}
		else
		{
			temp[i] = arr[bi][0];//���� �迭�� ���Ҹ� ����
			chan_color(arr, ai, bi);
			bi++;
		}
		i++;
	}
	while (ai < partition) //���� �迭�� ���� �͵��� ����
	{
		temp[i] = arr[ai][0];
		i++;
		ai++;
	}
	while (bi < r)//���� �迭�� ���� �͵��� ����
	{
		temp[i] = arr[bi][0];
		i++;
		bi++;
	}
	for (i = p; i < r; i++)
		arr[i][0] = temp[i];
}

void bitonicMerge(int **arr, int low, int cnt, int flag)         //bitonic sort ���� ���
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

void heapify(int **arr, int idx, int heap_size)            //heap sort ���� ���
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
void buildHeap(int **arr, int heap_size)						//heap sort ���� ���
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
			if (arr[j][0] > arr[j + 1][0]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(&arr[j][0], &arr[j + 1][0]);
			}
			chan_color(arr, j, j + 1);         //���� Ȯ������ j,j+1 �� �� �ٲٰ� ���
		}
		for (j = i - 1; j > size - i; j--) {
			if (arr[j][0] < arr[j - 1][0]) {      //ū���� ���ʿ� ���� ��� ��ġ �ٲ�
				swap(&arr[j][0], &arr[j - 1][0]);
			}
			chan_color(arr, j, j - 1);         //���� Ȯ������ j,j-1 �� �� �ٲٰ� ���
		}
	}

	return;
}

void insertion_sorting(int** arr) {
	printf("�� ���� ������\n");
}

#pragma endregion


//UI �Լ�
#pragma region

int example_maker(char* names[], int length) {		//���� ��� �Լ�
	int i, user = 0;
	int arrow = NULL;

	while (arrow != 13) {
		system("cls");
		printf("\n\n���ϴ� �׸��� �����ϼ���.\n\n");

		for (i = 0; i < length; i++) {
			if (i == user) {
				printf("��");
			}
			else {
				printf("  ");
			}
			printf("%s\n", names[i]);
		}

		arrow = getch();		//����Ű �޾ƿ��� �κ�

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
	printf("\n\n%s(��)�� �����ϼ̽��ϴ�.\n\n", names[user]);
	Sleep(wait_time);

	return user;
}

void sorting_manager() {		//���� �Լ� ȣ���ϴ� �Լ�

	//�ϵ��ڵ� �κ�

	int sort = 0, i, temp_bogo;
	int** original;      //���� ���� �� �迭

	original = (int**)malloc(sizeof(int*)*size);      //1���� �迭 ���� �Ҵ�, �� �迭�� original ����

	for (i = 0; i < size; i++) {
		original[i] = (int*)malloc(sizeof(int) * 2);
		original[i][1] = 0;
	}

	while (sort != N_SORT -1) {

		shuffle(original);      //original �迭 �������� ����

		int** arr = (int**)malloc(sizeof(int*)*size);;         //���� �� �迭, �Ź� ���� �Ҵ�, original�� ���纻
		copy_arr(arr, original);

		sort = example_maker(sorting_names, N_SORT);		//���� ���

		switch (sort) {
		case 0:
			print(arr);      //���� �� �迭 ����Ʈ
			bubble_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 1:
			print(arr);      //���� �� �迭 ����Ʈ
			shell_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 2:
			printf("\n\nBogo Sort�� �ð��� �ſ�ſ� ���� �ɸ��� ����� �� �� ���ɼ��� �ſ� Ů�ϴ�.\n\n");
			printf("���� �غ��Ŵٸ� �������� �迭�� ũ�⸦ 4���Ϸ� �����Ͻñ� �����մϴ�.\n\n");
			printf("���� ��ġ�� ���, �ƹ�Ű�� ���� ������ �ߴܽ�ų �� �ֽ��ϴ�.");
			Sleep(wait_time);
			print(arr);      //���� �� �迭 ����Ʈ
			temp_bogo = bogo_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			if (temp_bogo) {
				printf("\n\n���ÿϷ�!");
			}
			else {
				printf("\n\n�����ߴ�!");
			}
			Sleep(wait_time);
			break;
		case 3:
			print(arr);      //���� �� �迭 ����Ʈ
			gnome_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 4:
			print(arr);      //���� �� �迭 ����Ʈ
			quick_sorting(arr, 0, size - 1);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 5:
			print(arr);      //���� �� �迭 ����Ʈ
			merge_sorting(arr, 0, size);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 6:
			if ((size == 2) || (size == 4) || (size == 8) || (size == 16) || (size == 32)) {
				print(arr);      //���� �� �迭 ����Ʈ
				bitonic_sorting(arr, 0, size, 1);
				print(arr);      //���� �� �迭 ����Ʈ
				printf("\n\n���ÿϷ�!");
			}
			else {
				printf("\n\nBitonic Sort�� �迭�� ũ�Ⱑ 2�� �������϶��� ��� �����մϴ�.\n");
				printf("�������� �迭�� ũ�⸦ �����ϰ� ��� �� �ּ���.\n");
			}
			Sleep(wait_time);
			break;
		case 7:
			print(arr);      //���� �� �迭 ����Ʈ
			heap_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 8:
			print(arr);      //���� �� �迭 ����Ʈ
			select_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 9:
			printf(arr);      //���� �� �迭 ����Ʈ
			cocktail_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 10:
			printf(arr);      //���� �� �迭 ����Ʈ
			insertion_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		}

		for (i = 0; i < size; i++) {      //2�����迭 �Ҵ� ����
			free(arr[i]);
		}
		free(arr);
	}

	return;
}

void setup() {		//���� ���� ó�� �Լ�
	int user = NULL, temp;

	while (user != N_SETUP - 1) {
		user = example_maker(setup_names, N_SETUP);

		switch (user) {
		case 0:
			do {
				system("cls");
				printf("\n\n���� �ӵ��� %d�Դϴ�.\n\n", speed);
				printf("1~12�� �� �߿� ���ϴ� �ӵ��� �Է��ϼ���\n\nŬ���� ���ļӵ��� �����ϴ� : ");
				scanf("%d", &temp);
				if (temp < 0 || temp > 13) {
					printf("\n\n1�̻� 12������ ���� �Է� ���ּ���.\n");
					Sleep(wait_time);
				}
			} while (temp < 0 || temp > 13);

			speed = temp;

			printf("\n\n������ �ӵ��� %d(��)�� ����Ǿ����ϴ�.", speed);
			Sleep(wait_time);
			break;
		case 1:
			do {
				system("cls");
				printf("\n\n���� �迭�� ũ��� %d�Դϴ�.\n\n", size);
				printf("3~27�� �� �߿� ���ϴ� �迭�� ũ�⸦ �Է��ϼ��� : ");
				scanf("%d", &temp);
				if (temp < 3 || temp > 27) {
					printf("\n\n3�̻� 27������ ���� �Է� ���ּ���.\n");
					Sleep(wait_time);
				}
			} while (temp < 3 || temp > 27);

			size = temp;

			printf("\n\n�迭�� ũ�Ⱑ %d(��)�� ����Ǿ����ϴ�.", size);
			Sleep(wait_time);
			break;
		}
	}

	return;
}

void menu() {		//�⺻ �޴� ó�� �Լ�
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

void start() {		// �Ǵ�� ���� �κ� ó�� �Լ�
	printf("\n\n2016 C.A.P.S ����ȸ ��ǰ\n\n");
	printf("�ڷᱸ�� �� �ǽ� - Sorting\n\n");
	Sleep(wait_time);

	menu();

	return;
}

#pragma endregion


int main() {

	start();

	printf("\n\n���α׷��� ���� �˴ϴ�.\n\n�����մϴ�.\n\n");

	return 0;
}