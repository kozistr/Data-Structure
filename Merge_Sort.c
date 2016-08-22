#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define swap(a, b) ((&(a) == &(b))? a : ( a ^= b, b ^=a, a ^= b))

int buf[MAX];

int IsNumExist(int num, int index) {
	for (int i = 0; i < index; ++i) {
		if (buf[i] == num)
			return 1;
	}

	return 0;
}

void display(void) {
	for (int i = 1; i <= MAX; (i % 10 == 0) ? printf("%3d\n", buf[i - 1]) : printf("%3d ", buf[i - 1]), ++i);
}
void gen_rand(void) {
	srand((unsigned)time(0));

	for (int i = 0; i < MAX;) {
		int num = rand() % MAX + 1;

		if (!IsNumExist(num, i)) {
			buf[i] = num;
			++i;
		}
	}
}

void merge_sort(int *data, int left, int right) {
	int i, j;
	if (right > left) {
		int middle = (right + left) / 2;

		merge_sort(data, left, middle);
		merge_sort(data, middle + 1, right);

		for (i = middle + 1; i > left; --i)
			tmp[i - 1] = data[i - 1];

		for (j = middle; j < right; ++j)
			tmp[right + middle - j] = data[j + 1];

		for (int k = left; k <= right; ++k)
			data[k] = (tmp[i] < tmp[j]) ? tmp[++i] : tmp[--j];
	}
}

void main(int argc, char *argv[]) {
	printf("- Merge Sort Algorithm\n\n");

	printf("[+] Generating Random Numbers\n");
	gen_rand();
	display();

	printf("\n[+] Sorting\n");
	merge_sort(buf, 0, MAX - 1);
	display();
}
