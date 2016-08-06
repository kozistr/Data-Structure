#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	char num;
	struct _node *next;
} node;

node *nBuf[3];

void Initializing(void) {
	for (char i = 0; i < 2; i++) {
		nBuf[i] = (node *)malloc(sizeof(node));
		nBuf[i]->next = nBuf[1 - i];
	}
}

void Put(int n) {
	nBuf[2] = (node *)malloc(sizeof(node));
	nBuf[2]->num = n;
	
	if (nBuf[0]->next == nBuf[1]) {
		nBuf[0]->next = nBuf[2];
		nBuf[2]->next = nBuf[1];
		nBuf[1]->next = nBuf[2];
	}

	else {
		nBuf[1]->next->next = nBuf[2];
		nBuf[2]->next = nBuf[1];
		nBuf[1]->next = nBuf[2];
	}
}

void Get(void) {
	if (nBuf[0]->next == nBuf[1])
		printf("\nQueue Empty!\n");

	else {
		node *del = nBuf[0]->next;
		nBuf[0]->next = del->next;
		printf("\nGet() -> %d", del->num);
		free(del);
	}
}

void Display(void) {
	printf("\nQueue State");

	if (nBuf[0]->next != nBuf[1]) {
		printf("\nend -> ");
		for (node *ptr = nBuf[0]; ptr->next != nBuf[1]; ptr = ptr->next)
			printf("%d -> ", ptr->next->num);
		printf("start");
	}

	else if (nBuf[0]->next == nBuf[1])
		printf("Queue Empty!\n");
}

int main(int argc, char *argv[]) {
	Initializing();
	
	Put(1);
	Put(2);
	Put(3);
	Display();

	Get();
	Get();
	Display();

	getchar();
}
