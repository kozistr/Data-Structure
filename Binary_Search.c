#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX 100

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
		int num = rand() % 200 + 1;

		if (!IsNumExist(num, i)) {
			buf[i] = num;
			++i;
		}
	}
}

int binary_search(int n) {
	int right = MAX, left = 0, mid = 0;
	
	while (right >= left) {
		mid = (right + left) / 2;

		if (n < buf[mid])
			right = mid - 1;

		else
			left = mid - 1;

		if (n == buf[mid])
			return mid;
	}

	return -1;
}
void quick_sort(int *data, int left, int right) {
	if (right > left) {
		int num = data[right];

		int i = left - 1;
		int j = right;

		for (;;) {
			while (data[++i] < num);
			while (data[--j] > num);
			if (i >= j) break;

			swap(data[i], data[j]);
		}

		swap(data[i], data[right]);

		quick_sort(data, left, i - 1);
		quick_sort(data, i + 1, right);
	}
}

void main(int argc, char *argv[]) {
	printf("- Binary Search Algorithm\n\n");

	printf("[+] Generating Random Numbers\n");
	gen_rand();
	display();

	printf("\n[+] Sorting\n");
	quick_sort(buf, 0, MAX - 1);
	display();

	printf("\n[+] Searching\n");
	int n = buf[rand() % MAX + 1];
	printf("  [*] %d at %d\n", n, binary_search(n));
}
