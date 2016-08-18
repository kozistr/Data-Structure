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

void select_sort(void) {
	for (int i = 0; i < MAX; ++i) {
		int min = i;

		for (int j = i; j < MAX; ++j)
			if (buf[j] < buf[min])
				min = j;

		swap(buf[min], buf[i]);
	}
}

void main(int argc, char *argv[]) {
	printf("- Selection Sort Algorithm\n\n");

	printf("[+] Generating Random Numbers\n");
	gen_rand();
	display();

	printf("\n[+] Sorting\n");
	select_sort();
	display();
}
