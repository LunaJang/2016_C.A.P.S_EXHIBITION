#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <time.h>
#define SIZE 8
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void print(int **arr)
{
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
void gnome_sort(int **arr, int size)
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
int partition(int **arr, int p, int r)
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
void bitonicMerge(int **arr, int low, int cnt, int flag)
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
void heapify(int **arr, int idx, int max)
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
void buildHeap(int **arr, int size) {
	int i;
	for (i = size / 2 - 1; i >= 0; i--)
		heapify(arr, i, size);
}
void heap_sort(int **arr, int size)
{
	int i;
	buildHeap(arr, size);
	for (i = size - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, 0, i);
	}
}
/*void shiftdown(int x, int i) // place element x in h[i] and let it
{
int c; // shift down
if (h[i * 2 + 1]>h[i * 2 + 2])
{
c = i * 2 + 2;
}
else
{
c = i * 2 + 1;
}
if (c > Size)
{
c = -1;
}
while (c != -1 && h[c] < x)
{
h[i] = h[c];
i = c;
if (h[i * 2 + 1]>h[i * 2 + 2])
{
c = i * 2 + 2;
}
else
{
c = i * 2 + 1;
}
if (c > Size)
{
c = -1;
}
}
h[i] = x;
}

int deleteMin() // delete minimum value from heap h[]
{
int x;
if (Size == 0)
return -1000;
else
{
x = h[0];
shiftdown(h[Size], 0);
return x;
}
}
void makeheap() // build a heap h from array S
{
int i;
for (i = 0; i < Size + 1; i++)
{
h[i] = S[i];
}
for (i = Size; i>-1; i--)
{
shiftdown(h[i], i);
}
}*/
int main()
{
	long seed = time(NULL);
	srand(seed);
	int i;
	int **input = (int*)malloc(sizeof(int*) * SIZE);
	for (i = 0; i < SIZE; i++)
	{
		input[i] = (int)malloc(sizeof(int) * 2);
		input[i][0] = rand() % 100 + 1;
		input[i][1] = 0;
	}
	print(input);
	//gnome_sort(input, SIZE);
	//print(input);
	//Sleep(1200);
	//quick_sort(input, 0, SIZE - 1);
	print(input);
	merge_sort(input, 0, SIZE);
}