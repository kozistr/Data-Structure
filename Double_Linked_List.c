#include <stdio.h>
#include <stdlib.h>

/* Double Linked List */
typedef struct _node {
	char ch;
	struct _node *prev;
	struct _node *next;
} node;

char chs[6] = {'A', 'B', 'D', 'E', 'F', 'G'};
node *nBuf[6]; // nBuf[0] = head, nBuf[5] = end

void Initializing(void) {
	for (int i = 0; i < 6; i++) {
		nBuf[i] = (node *)malloc(sizeof(node));
		nBuf[i]->ch = chs[i];
		nBuf[i]->prev = (i == 0) ? nBuf[i] : nBuf[i - 1];
		if (i != 0)	nBuf[i - 1]->next = nBuf[i];
	}
	nBuf[5]->next = nBuf[5];
}

void InsertNode(node *ptr) {
	node *id;
	for (id = nBuf[0]->next; id != nBuf[5]; id = id->next)
		if (id->ch < ptr->ch && id->next->ch > ptr->ch)
			break;

	ptr->next = id->next;
	id->next->prev = ptr;
	id->next = ptr;
	ptr->prev = id;
}

void DeleteNode(node *ptr) {
	node *id, *del;
	for (id = nBuf[0]; id != nBuf[5]; id = id->next)
		if (id->next->ch == ptr->ch) {
			del = id->next;
			break;
		}

	id->next = id->next->next;
	id->next->next->prev = id;
	free(del);
}

int main(int argc, char *argv[]) {
	node *ptr, *C;

	Initializing(); // Init Double Linked List Settings
	
	printf("Before Inserting 'Node C'\n");
	
	ptr = nBuf[0];
	for (int i = 0; i < 6; i++) {
		printf("%2c", ptr->ch);
		ptr = ptr->next;
	}

	/* Configure Node C */
	C = (node *)malloc(sizeof(node));
	C->ch = 'C';
	
	/* Insert 'Node C' into 'Node nBuf' */
	InsertNode(C);

	printf("\nAfter Inserting 'Node C'\n");

	ptr = nBuf[0];
	for (int i = 0; i < 7; i++) {
		printf("%2c", ptr->ch);
		ptr = ptr->next;
	}

	/* Delete 'Node C' from 'Node nBuf' */
	DeleteNode(C);

	printf("\nAfter Deleting 'Node C'\n");

	ptr = nBuf[0];
	for (int i = 0; i < 6; i++) {
		printf("%2c", ptr->ch);
		ptr = ptr->next;
	}
}
