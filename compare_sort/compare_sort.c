/* Compares given sorting algorithms */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

typedef struct {
	double best_time;
	double avg_time;
	double worst_time;
	double memory_used;
} Result;

/* function prototypes */
void getvars(int *size_max, int *dsize);
void random(int *arr, int size);
Result bubble_sort();

int main(void)
{
	int i;
	int size, size_max, dsize;
	int arr[MAX];

	for (i = 0; i < MAX; ++i) {
		arr[i] = -1;
	}

	srand((int)time(NULL));

	getvars(&size_max, &dsize);

	for (size = dsize; size <= size_max; size += dsize) {
		random(arr, size);

		/*
		bubble_sort(arr, size);
		quick();
		insert();
		...
		*/
	}


	return 0;
}

void getvars(int *size_max, int *dsize)
{
	printf("배열에 저장할 숫자의 최대 개수를 입력하세요(10000 이하): \n");
	printf("0을 입력하면 종료합니다. \n");
	for (;;) {
		scanf("%d", size_max);

		if (*size_max < 0) {
			printf("0 이상의 정수를 입력해 주세요. \n");
			continue;
		}
		else if (*size_max > 10000) {
			printf("입력한 숫자가 너무 큽니다. \n");
			continue;
		}
		else if (*size_max == 0) {
			exit(0);
		}
		else {
			break;
		}
	}
	printf("\n배열에 저장할 숫자의 개수의 증가량을 입력하세요: \n");
	printf("0을 입력하면 종료합니다. \n");
	for (;;) {
		scanf("%d", dsize);

		if (*dsize < 0) {
			printf("0 이상의 정수를 입력해 주세요. \n");
			continue;
		}
		else if (*dsize >= *size_max) {
			printf("최대 개수보다 작은 값을 입력해 주세요. \n");
			continue;
		}
		else if (*dsize == 0) {
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

Result bubble_sort()
{
	Result bubble;


	return bubble;
}