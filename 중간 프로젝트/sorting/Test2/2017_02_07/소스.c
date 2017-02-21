#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>      //�ݵ�� wincon.h ���� windows.h�� �־����. �ȱ׷��� ���� ��ź

#define N_SORT 9
#define N_MENU 3
#define N_SETUP 3
#define wait_time 3000

const char* sorting_names[N_SORT] = { "Bubble Sort","Shell Sort","Bogo Sort","Gnome Sort","Quick Sort","Merge Sort","Bitonic Sort","Heap Sort","�޴��� ���ư���" };
const char* menu_names[N_MENU] = { "���� ���� ����","���� ����","���α׷� ����" };
const char* setup_names[N_SETUP] = { "���� �ӵ� ����", "������ �迭�� ũ�� ����", "�޴��� ���ư���" };

int size = 10;      //size ���������� ����
int speed = 5;      //sorting �ӵ� ���� (1200/speed)�� ����Ʈ



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
	for (i = 0; i <size; i++)
	{
		if (arr[i][1] == 1)      //���� Ȯ�� ���� ������ ���
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
	Sleep(1200 / speed);

	return;
}
void chan_color(int** arr, int x, int y) {
	arr[x][1] = 1;
	arr[y][1] = 1;      //���� Ȯ������ �迭 ������ �� �ٲ�

	print(arr);

	arr[x][1] = 0;
	arr[y][1] = 0;      //������� ����

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
void copy_arr(int** arr, int** original) {      //�Ҵ� �� �� �迭 ����
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
			while (temp - i >= 0 && arr[temp - i][0]>arr[temp][0]) {      //temp-i�� �����ϰ� temp�� temp-i�� ������ �ٲ������ ���
				swap(&arr[temp - i][0], &arr[temp][0]);
				chan_color(arr, temp, temp - i);      //���� �ٲ� & ��� & temp ����
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
	return h;   // h�� ��ġ�� �����Ѵ�.
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
		if (arr[ai][0] <= arr[bi][0])//������ ũ�ų� ���� ��
		{
			temp[i] = arr[ai][0];//���� �迭�� ���Ҹ� ����
			arr[ai][1] = 1;
			arr[bi][1] = 1;
			print(arr);
			arr[ai][1] = 0;
			arr[bi][1] = 0;
			ai++;
		}
		else
		{
			temp[i] = arr[bi][0];//���� �迭�� ���Ҹ� ����
			arr[ai][1] = 1;
			arr[bi][1] = 1;
			print(arr);
			arr[ai][1] = 0;
			arr[bi][1] = 0;
			bi++;
		}
		i++;
	}
	while (ai < partition) //���� �迭�� ���� �͵��� ����
	{
		temp[i] = arr[ai][0];
		/*arr[ai][1] = 1;
		print(arr);
		arr[ai][1] = 0;*/
		i++;
		ai++;
	}
	while (bi < r)//���� �迭�� ���� �͵��� ����
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

void bitonicMerge(int **arr, int low, int cnt, int flag)         //bitonic sort ���� ���
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

void heapify(int **arr, int idx, int max)            //heap sort ���� ���
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
void buildHeap(int **arr) {      //heap sort ���� ���
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
	printf("\n\n%s�� �����ϼ̽��ϴ�.\n\n", names[user]);
	Sleep(wait_time);

	return user;
}

void sorting_manager() {

	int sort = 0, i;
	int** original;      //���� ���� �� �迭

	original = (int**)malloc(sizeof(int*)*size);      //1���� �迭 ���� �Ҵ�, �� �迭�� original ����

	for (i = 0; i < size; i++) {
		original[i] = (int*)malloc(sizeof(int) * 2);
		original[i][1] = 0;
	}

	while (sort != 8) {

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
			//�ð� �����ɸ� ���
			print(arr);      //���� �� �迭 ����Ʈ
			bogo_sorting(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 3:
			print(arr);      //���� �� �迭 ����Ʈ
			gnome_sort(arr);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 4:
			print(arr);      //���� �� �迭 ����Ʈ
			quick_sort(arr, 0, size - 1);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 5:
			print(arr);      //���� �� �迭 ����Ʈ
			merge_sort(arr, 0, size);
			print(arr);      //���� �� �迭 ����Ʈ
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 6:
			//�迭 ũ����� ���������� ���
			//print(arr);      //���� �� �迭 ����Ʈ
			//bitonic_sort(arr);
			//print(arr);      //���� �� �迭 ����Ʈ
			printf("���� �� ������� \n");
			printf("\n\n���ÿϷ�!");
			Sleep(wait_time);
			break;
		case 7:
			print(arr);      //���� �� �迭 ����Ʈ
			heap_sort(arr);
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

void setup() {
	int user = NULL, temp;

	while (user != 2) {
		user = example_maker(setup_names, N_SETUP);

		switch (user) {
		case 0:
			do {
				system("cls");
				printf("\n\n���� �ӵ��� %d�Դϴ�.\n", speed);
				printf("1~12�� �� �߿� ���ϴ� �ӵ��� �Է��ϼ���\nŬ���� ���ļӵ��� �����ϴ� : ");
				scanf("%d", &temp);
				if (temp < 0 || temp > 13) {
					printf("3�̻� 60������ ���� �Է� ���ּ���.\n");
				}
			} while (temp < 0 || temp > 13);

			speed = temp;

			printf("������ �ӵ��� %d�� ����Ǿ����ϴ�.", speed);
			Sleep(wait_time);
			break;
		case 1:
			do {
				system("cls");
				printf("\n\n���� �迭�� ũ��� %d�Դϴ�.\n", size);
				printf("3~60�� �� �߿� ���ϴ� �迭�� ũ�⸦ �Է��ϼ��� : ");
				scanf("%d", &temp);
				if (temp < 3 || temp > 60) {
					printf("3�̻� 60������ ���� �Է� ���ּ���.\n");
				}
			} while (temp < 3 || temp > 60);

			size = temp;

			printf("�迭�� ũ�Ⱑ %d�� ����Ǿ����ϴ�.", size);
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
	printf("\n\n2016 C.A.P.S ����ȸ ��ǰ\n\n");
	printf("�ڷᱸ�� �� �ǽ� - Sorting\n\n");
	Sleep(wait_time);

	menu();

	return;
}

int main() {

	start();

	return 0;
}