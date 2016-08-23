#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX 20000
#define swap(a, b) ((&(a) == &(b))? a : ( a ^= b, b ^=a, a ^= b))

int buf[MAX], tmp[MAX];

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

void insert_sort(void) {
	for (int i = 0; i < MAX; ++i) {
		int tmp = buf[i];

		int j = i;
		while (buf[j - 1] > tmp && j > 0) {
			buf[j] = buf[j - 1];
			--j;
		}

		buf[j] = tmp;
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
void bubble_sort(void) {
	for (int i = MAX - 1; i >= 0; --i) {
		for (int j = 1; j <= i; ++j) {
			if (buf[j - 1] > buf[j])
				swap(buf[j - 1], buf[j]);
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
	time_t log[6][2]; // Logging each algorithms' elapsed time
	/* algorithms */
	char *name[] = { "Bubble", "Insert", "Select", "Shell", "Quick" };
	LPVOID func[] = { bubble_sort, insert_sort, select_sort, shell_sort, };
	
	printf("- Sorting Algorithm BenchMark\n\n");

	printf("[+] Generating Random Numbers\n");
	//gen_rand(); <- Could it be called just one time without allocating another same size array.
	printf("\n[+] Sorting\n");
	
	for (int i = 0; i < 4; ++i) {
		gen_rand();
		printf("   [*] %s Sort : \n", name[i]);
		log[i][0] = clock();
		FARPROC proc = (FARPROC)func[i]; proc();
		log[i][1] = clock() - log[i][0];
		printf("\tElapsed Time : %fs\n", (float)log[i][1] / (CLOCKS_PER_SEC));
	}

	gen_rand();
	printf("   [*] Quick Sort : \n");
	log[4][0] = clock();
	quick_sort(buf, 0, MAX - 1);
	log[4][1] = clock() - log[4][0];
	printf("\tElapsed Time : %fs\n", (float)log[4][1] / (CLOCKS_PER_SEC));
	
	gen_rand();
	printf("   [*] Merge Sort : \n");
	log[5][0] = clock();
	merge_sort(buf, 0, MAX - 1);
	log[5][1] = clock() - log[5][0];
	printf("\tElapsed Time : %fs\n", (float)log[5][1] / (CLOCKS_PER_SEC));
}
