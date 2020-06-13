/* MEMO*/
/*
 *  다른 sort 알고리즘 추가하기
 *
 *
 *
 */

/* Compares given sorting algorithms */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000
#define BEST_TIME_FORMAT "최선(ms): %g \n"
#define AVG_TIME_FORMAT "평균(ms): %g \n"
#define WORST_TIME_FORMAT "최악(ms): %g \n"

typedef struct {
	double best_time;
	double avg_time;
	double worst_time;
} Result;

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
void quick(int *arr, int size);
void merge(int *arr, int size);
void heap(int *arr, int size);

int main(void)
{
	enum { BUBBLE, SELECTION, INSERTION, QUICK, MERGE, HEAP };
	int i = 0;
	int size, repeat; getvars(&size, &repeat);
	int arr[MAX];
	Result sort[6];

	for (i = BUBBLE; i <= HEAP; ++i) {
		init(&sort[i]);
	}

	srand((int)time(NULL));

	random(arr, size);

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
	printf("배열에 저장할 숫자의 최대 개수를 입력하세요(%d 이하). \n", MAX);
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
	enum { BUBBLE, SELECTION, INSERTION, QUICK, MERGE, HEAP };
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
	enum { BUBBLE, SELECTION, INSERTION, QUICK, MERGE, HEAP };
	double t_i, t_f;
	double time[MAX];							// the array stores time taken during sorting elements
	int i;
	double t_sum = 0.0;

	for (i = 0; i < repeat; ++i) {
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
			quick(arr, size);
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

void selection(int *arr, int size) {

}

void insertion(int *arr, int size) {

}

void quick(int *arr, int size) {

}

void merge(int *arr, int size) {

}

void heap(int *arr, int size) {

}