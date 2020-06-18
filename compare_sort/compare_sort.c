/* Compares given sorting algorithms */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000
#define BEST_TIME_FORMAT "최선(ms): %f \n"
#define AVG_TIME_FORMAT "평균(ms): %f \n"
#define WORST_TIME_FORMAT "최악(ms): %f \n"

/* structs */
typedef struct {
	double best_time;
	double avg_time;
	double worst_time;
} Result;

/* external variables */
enum { BUBBLE, SELECTION, INSERTION, QUICK, MERGE, HEAP };

/* function prototypes */
void getvars(int *size, int *repeat);
void init(Result *sort_ptr);
void random(int *arr, int size);
void print_all(Result *sort);
void do_sort(Result *sort_ptr, int sort_name, int *arr, int size, int repeat);
/* algorithms */
void bubble(int *arr, int size);
void selection(int *arr, int size);
void insertion(int *arr, int size);
void quick(int *arr, int left, int right);
/********************* merge sort *********************/
void merge(int *arr, int size);
void do_split(int *temp, int start, int end, int *arr);
void do_merge(int *arr, int start, int middle, int end, int *temp);
void copy_array(int *arr, int start, int end, int *temp);
/********************** heap sort *********************/
void heap(int *arr, int size);
void heapify(int *arr, int size, int i);
void swap(int *a, int *b);

int main(void)
{
	int i = 0;
	int size, repeat; getvars(&size, &repeat);
	int arr[MAX];
	Result sort[6];

	for (i = BUBBLE; i <= HEAP; ++i) {
		init(&sort[i]);
	}

	srand((int)time(NULL));

	for (i = BUBBLE; i <= HEAP; ++i) {
		do_sort(&sort[i], i, arr, size, repeat);
	}

	print_all(sort);

	return 0;
}

void init(Result *sort_ptr)
{
	sort_ptr->best_time = 0.0;
	sort_ptr->avg_time = 0.0;
	sort_ptr->worst_time = 0.0;
}

void getvars(int *size, int *repeat)
{
	printf("배열에 저장할 숫자의 개수를 입력하세요(%d 이하). \n", MAX);
	printf("0을 입력하면 종료합니다. \n");
	for (;;) {
		scanf("%d", size);

		if (*size < 0) {
			printf("0 이상의 정수를 입력해 주세요. \n");
			continue;
		}
		else if (*size > MAX) {
			printf("%d 이하의 정수를 입력해 주세요. \n", MAX);
			continue;
		}
		else if (*size == 0) {
			exit(0);
		}
		else {
			break;
		}
	}
	printf("\n한 번의 실험 동안 반복할 횟수를 입력하세요: \n");
	printf("0을 입력하면 종료합니다. \n");
	for (;;) {
		scanf("%d", repeat);

		if (*repeat < 0) {
			printf("0 이상의 정수를 입력해 주세요. \n");
			continue;
		}
		else if (*repeat == 0) {
			exit(0);
		}
		else {
			break;
		}
	}
}

void random(int *arr, int size)
{
	int i;

	for (i = 0; i < size; ++i) {
		arr[i] = rand();
	}
}

void print_all(Result *sort)
{
	char *sort_name[6] = {"Bubble", "Selection", "Insertion", "Quick", "Merge", "Heap"};
	int i;

	for (i = BUBBLE; i <= HEAP; ++i) {
		printf("%s Sort \n", sort_name[i]);
		printf(BEST_TIME_FORMAT, sort[i].best_time);
		printf(AVG_TIME_FORMAT, sort[i].avg_time);
		printf(WORST_TIME_FORMAT, sort[i].worst_time);
	}
	
}

void do_sort(Result *sort_ptr, int sort_name, int *arr, int size, int repeat)
{
	double t_i, t_f;
	double time[MAX];							// the array stores time taken during sorting elements
	int i;
	double t_sum = 0.0;

	for (i = 0; i < repeat; ++i) {
		random(arr, size);

		t_i = clock();
		
		switch (sort_name) {
		case BUBBLE:
			bubble(arr, size);
			break;
		case SELECTION:
			selection(arr, size);
			break;
		case INSERTION:
			insertion(arr, size);
			break;
		case QUICK:
			quick(arr, 0, size - 1);
			break;
		case MERGE:
			merge(arr, size);
			break;
		case HEAP:
			heap(arr, size);
			break;
		default:
			printf("유효하지 않은 알고리즘이 전달되었습니다. \n");
			exit(-1);
		}

		t_f = clock();
		time[i] = (double)t_f - t_i;
	}

	sort_ptr->best_time = sort_ptr->worst_time = time[0];
	for (i = 0; i < repeat; ++i) {
		t_sum += time[i];
		sort_ptr->avg_time = t_sum / (double) repeat;
		if (sort_ptr->best_time > time[i]) {
			sort_ptr->best_time = time[i];
		}
		if (sort_ptr->worst_time < time[i]) {
			sort_ptr->worst_time = time[i];
		}
	}
}

void bubble(int *arr, int size)
{
	int i, j, temp;

	for (i = size - 1; i > 0; --i) {
		for (j = 0; j < i; ++j) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void selection(int *arr, int size)
{
	int i, j, min_index, temp;

	for (i = 0; i < size - 1; ++i) {
		min_index = i;

		for (j = i + 1; j < size; ++j) {
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}

		temp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = temp;
	}
}

void insertion(int *arr, int size)
{
	int i, j, temp;

	for(i = 1; i <= size - 1; ++i) {
		j = i;

		while (j > 0 && arr[j] < arr[j - 1]) {
			temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;

			--j;
		}
	}
}

void quick(int *arr, int left, int right)
{
	int i = left, j = right;
	int pivot = arr[(left + right) / 2];
	int temp;

	while (i <= j) {
		while (arr[i] < pivot) {
			++i;
		}
		while (arr[j] > pivot) {
			--j;
		}

		if (i <= j) {
			if (i != j) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}

			++i; --j;
		}
	}

	if (left < j) {
		quick(arr, left, j);
	}
		
	if (i < right) {
		quick(arr, i, right);
	}
}

/********************* merge sort *********************/

void merge(int *arr, int size)
{
	int temp[MAX];

	copy_array(arr, 0, size, temp);
	do_split(temp, 0, size, arr);
}

void do_split(int *temp, int start, int end, int *arr)
{
	int middle;

	if (end - start < 2) {
		return;
	}
	middle = (end + start) / 2;
	do_split(arr, start, middle, temp);
	do_split(arr, middle, end, temp);

	do_merge(temp, start, middle, end, arr);
}

void do_merge(int *arr, int start, int middle, int end, int *temp)
{
	int i, j, k;

	i = start, j = middle;
	for (k = start; k < end; ++k) {
		if (i < middle && (j >= end || arr[i] <= arr[j])) {
			temp[k] = arr[i];
			i = i + 1;
		}
		else {
			temp[k] = arr[j];
			j = j + 1;
		}
	}
}

void copy_array(int *arr, int start, int end, int *temp)
{
	int i;

	for (i = start; i < end; ++i) {
		temp[i] = arr[i];
	}
}

/********************** heap sort *********************/

void heap(int *arr, int size)
{
	int i;

	for (i = size / 2 - 1; i >= 0; --i)
		heapify(arr, size, i);

	for (i = size - 1; i >= 0; --i) {
		swap(&arr[0], &arr[i]);

		heapify(arr, i, 0);
	}
}

void heapify(int *arr, int size, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && arr[left] > arr[largest]) {
		largest = left;
	}
		

	if (right < size && arr[right] > arr[largest]) {
		largest = right;
	}

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, size, largest);
	}
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}