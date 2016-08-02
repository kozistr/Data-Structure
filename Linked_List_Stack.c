#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *next;
} node;

node *nBuf[3];

void InitializeStack(void) {
	nBuf[0] = (node *)malloc(sizeof(node));
	nBuf[2] = (node *)malloc(sizeof(node));
	nBuf[0]->next = nBuf[2];
	nBuf[2]->next = nBuf[2];
}

void Push(int n) {
	nBuf[1] = (node *)malloc(sizeof(node));
	nBuf[1]->data = n;
	nBuf[1]->next = nBuf[0]->next;
	nBuf[0]->next = nBuf[1];
}

void Pop(void) {
	nBuf[1] = nBuf[0]->next;
	nBuf[0]->next = nBuf[0]->next->next;
	free(nBuf[1]);
}

void Display(void) {
	printf("head -> ");
	for (node *ins = nBuf[0]->next; ins != nBuf[2]; ins = ins->next)
		printf("%d -> ", ins->data);
	printf("end\n");
}

int main(int argc, char *argv[]) {
	InitializeStack();

	Push(1);
	Push(2);
	Push(3);
	Display();

	Pop();
	Pop();
	Display();
}
