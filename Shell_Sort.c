#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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
		int num = rand() % MAX + 1;

		if (!IsNumExist(num, i)) {
			buf[i] = num;
			++i;
		}
	}
}

void shell_sort(void) {
	int group;
	for (group = 0; group < MAX; group = 3 * group + 1);
	for (; group > 0; group /= 3) {
		for (int i = group; i < MAX; ++i) {
			int tmp = buf[i];

			int j = i;
			while (j >= group && buf[j - group] > tmp) {
				buf[j] = buf[j - group];
				j -= group;
			}

			buf[j] = tmp;
		}
	}
}

void main(int argc, char *argv[]) {
	printf("- Shell Sort Algorithm\n\n");

	printf("[+] Generating Random Numbers\n");
	gen_rand();
	display();

	printf("\n[+] Sorting\n");
	shell_sort();
	display();
}
