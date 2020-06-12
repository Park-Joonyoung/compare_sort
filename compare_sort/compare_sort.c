/* Compares given sorting algorithms */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000
#define BEST_TIME_FORMAT "�ּ�(ms): %3g \n"
#define AVG_TIME_FORMAT "���(ms): %3g \n"
#define WORST_TIME_FORMAT "�־�(ms): %3g \n"

typedef struct {
	double best_time;
	double avg_time;
	double worst_time;
	double memory_used;
} Result;

/* function prototypes */
void getvars(int *size, int *repeat);
void init(Result *bubble_ptr);
void random(int *arr, int size);
void print_all(Result bubble);
void bubble_sort(Result *bubble_ptr, int *arr, int size, int repeat);

int main(void)
{
	int size, repeat; getvars(&size, &repeat);
	int arr[MAX];
	Result bubble;
	Result *bubble_ptr = &bubble;

	init(bubble_ptr);

	srand((int)time(NULL));

	random(arr, size);

	bubble_sort(bubble_ptr, arr, size, repeat);
	/*
	quick();
	insert();
	...
	*/

	print_all(bubble);

	return 0;
}

void init(Result *bubble_ptr)
{
	bubble_ptr->best_time = 0.0;
	bubble_ptr->avg_time = 0.0;
	bubble_ptr->worst_time = 0.0;
}

void getvars(int *size, int *repeat)
{
	printf("�迭�� ������ ������ �ִ� ������ �Է��ϼ���(%d ����). \n", MAX);
	printf("0�� �Է��ϸ� �����մϴ�. \n");
	for (;;) {
		scanf("%d", size);

		if (*size < 0) {
			printf("0 �̻��� ������ �Է��� �ּ���. \n");
			continue;
		}
		else if (*size > MAX) {
			printf("%d ������ ������ �Է��� �ּ���. \n", MAX);
			continue;
		}
		else if (*size == 0) {
			exit(0);
		}
		else {
			break;
		}
	}
	printf("\n�� ���� ���� ���� �ݺ��� Ƚ���� �Է��ϼ���: \n");
	printf("0�� �Է��ϸ� �����մϴ�. \n");
	for (;;) {
		scanf("%d", repeat);

		if (*repeat < 0) {
			printf("0 �̻��� ������ �Է��� �ּ���. \n");
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

void print_all(Result bubble)
{
	printf("Bubble Sort \n");
	printf(BEST_TIME_FORMAT, bubble.best_time);
	printf(AVG_TIME_FORMAT, bubble.avg_time);
	printf(WORST_TIME_FORMAT, bubble.worst_time);
}

void bubble_sort(Result *bubble_ptr, int *arr, int size, int repeat)
{
	double t_i, t_f;
	double time[MAX];							// the array stores time taken during sorting elements
	int i, j, k, temp;
	double t_sum = 0.0;

	for (i = 0; i < repeat; ++i) {
		t_i = clock();
		/******************************************************************/

		for (j = size - 1; j > 0; --j) {
			for (k = 0; k < j; ++k) {
				if (arr[k] > arr[k + 1]) {
					temp = arr[k];
					arr[k] = arr[k + 1];
					arr[k + 1] = temp;
				}
			}
		}

		/******************************************************************/
		t_f = clock();
		time[i] = (double)t_f - t_i;
	}

	bubble_ptr->best_time = bubble_ptr->worst_time = time[0];
	for (i = 0; i < repeat; ++i) {
		t_sum += time[i];
		bubble_ptr->avg_time = t_sum / (double) repeat;
		if (bubble_ptr->best_time > time[i]) {
			bubble_ptr->best_time = time[i];
		}
		if (bubble_ptr->worst_time < time[i]) {
			bubble_ptr->worst_time = time[i];
		}
	}
}