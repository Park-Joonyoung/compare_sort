/* Compares given O(nlogn) sorting algorithms */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000000
#define TIME_FORMAT "%d번째 수행 시간(ms): %f \n"
#define AVG_TIME_FORMAT "평균(ms): %f \n"

/* external variables */
enum { QUICK, MERGE, HEAP };

/* function prototypes */
void getvars(int *size, int *repeat);
void random(int *arr, int size);
void do_sort(int sort_name, int *arr, int size, int repeat);
/* algorithms */
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
	int *arr = (int *)malloc(sizeof(int)*MAX);
	FILE *fp = fopen("nlogn.txt", "wt");

	srand((int)time(NULL));

	fprintf(fp, "배열의 원소의 개수: %d\n", size);
	fprintf(fp, "반복 횟수: %d\n", repeat);
	fclose(fp);
	for (i = QUICK; i <= HEAP; ++i) {
		do_sort(i, arr, size, repeat);
	}

	free(arr);
	return 0;
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

	printf("\n한 번의 실험 동안 반복할 횟수를 입력하세요. \n");
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

void do_sort(int sort_name, int *arr, int size, int repeat)
{
	char *sort_txt[3] = { "Quick", "Merge", "Heap" };
	double t_i, t_f, dt;
	int i;
	double t_sum = 0.0, t_avg;
	FILE *fp = fopen("nlogn.txt", "at");

	fprintf(fp, "\n\n");
	fprintf(fp, "%s sort 실행 시작\n", sort_txt[sort_name]);
	for (i = 0; i < repeat; ++i) {
		random(arr, size);

		t_i = clock();

		switch (sort_name) {
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
		dt = (double)t_f - t_i;
		fprintf(fp, TIME_FORMAT, i + 1, dt);
		t_sum += dt;
	}
	t_avg = t_sum / repeat;
	fprintf(fp, AVG_TIME_FORMAT, t_avg);

	fclose(fp);
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
	int *temp = (int *)malloc(sizeof(int)*MAX);

	copy_array(arr, 0, size, temp);
	do_split(temp, 0, size, arr);
	free(temp);
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