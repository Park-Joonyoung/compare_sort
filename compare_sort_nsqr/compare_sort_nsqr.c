/* Compares given O(n^2) sorting algorithms */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000000
#define TIME_FORMAT "%d��° ���� �ð�(ms): %f \n"
#define AVG_TIME_FORMAT "���(ms): %f \n"

/* external variables */
enum { BUBBLE, SELECTION, INSERTION };

/* function prototypes */
void getvars(int *size, int *repeat);
void random(int *arr, int size);
void do_sort(int sort_name, int *arr, int size, int repeat);
/* algorithms */
void bubble(int *arr, int size);
void selection(int *arr, int size);
void insertion(int *arr, int size);

int main(void)
{
	int i = 0;
	int size, repeat; getvars(&size, &repeat);
	int *arr = (int *)malloc(sizeof(int)*MAX);
	FILE *fp = fopen("nsqr.txt", "wt");

	srand((int)time(NULL));

	fprintf(fp, "�迭�� ������ ����: %d\n", size);
	fprintf(fp, "�ݺ� Ƚ��: %d\n", repeat);
	fclose(fp);
	for (i = BUBBLE; i <= INSERTION; ++i) {
		do_sort(i, arr, size, repeat);
	}

	free(arr);
	return 0;
}

void getvars(int *size, int *repeat)
{
	printf("�迭�� ������ ������ ������ �Է��ϼ���(%d ����). \n", MAX);
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

	printf("\n�� ���� ���� ���� �ݺ��� Ƚ���� �Է��ϼ���. \n");
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

void do_sort(int sort_name, int *arr, int size, int repeat)
{
	char *sort_txt[3] = { "Bubble", "Selection", "Insertion" };
	double t_i, t_f, dt;
	int i;
	double t_sum = 0.0, t_avg;
	FILE *fp = fopen("nsqr.txt", "at");

	fprintf(fp, "\n\n");
	fprintf(fp, "%s sort ���� ����\n", sort_txt[sort_name]);
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
		default:
			printf("��ȿ���� ���� �˰����� ���޵Ǿ����ϴ�. \n");
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

	for (i = 1; i <= size - 1; ++i) {
		j = i;

		while (j > 0 && arr[j] < arr[j - 1]) {
			temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;

			--j;
		}
	}
}