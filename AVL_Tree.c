#include <stdio.h>
#include <stdlib.h>

#define tree 100

enum rotate { RR, LL, LR, RL };

typedef struct _node {
	char data;
	int balance;
	struct _node *left;
	struct _node *right;
} node;

int front, rear;
node *head, *big;
node *grand, *parent, *child;
node *Queue[tree];

void InitializeQueue(void) {
	front = rear = 0;
}
void InitializeTree(void) {
	head = (node *)malloc(sizeof(node));
	head->left = head;
	head->right = head;
	big = head;
}

int IsQueueEmpty(void) {
	if (rear == front)
		return 1;
	else
		return 0;
}

void Put(node *ptr) {
	Queue[rear] = ptr;
	rear = (rear++) % tree;
}
node *Get(void) {
	if (!IsQueueEmpty())
		return Queue[(front++) % tree];
	else
		printf("Queue is Empty!\n");
	return NULL;
}
void Display(node *ptr) {
	printf("%c -> ", ptr->data);
}

int IsBalance(void) {
	node *ptr = head->right;

	InitializeQueue();
	Put(ptr);

	while (!IsQueueEmpty()) {
		ptr = Get();

		if (ptr->balance > 1)
			return rotate::LL;

		else if (ptr->balance < -1)
			return rotate::RR;

		if (ptr->left != head)
			Put(ptr->left);

		if (ptr->right != head)
			Put(ptr->right);
	}

	return -1;
}

void RR_Rotate(void) {
	parent = grand->right;
	child = parent->right;

	if (grand->balance == -2) {
		big->right = parent;
		parent->left = grand;
		grand->left = head;
		grand->right = head;
	}

	++big->balance;
	parent->balance = 0;
	grand->balance = 0;
	child->balance = 0;
}
void LL_Rotate(void) {
	parent = grand->left;
	child = parent->left;

	if (grand->balance == 2) {
		big->left = parent;
		parent->right = grand;
		grand->left = head;
		grand->right = head;
	}

	--big->balance;

	parent->balance = 0;
	grand->balance = 0;
	child->balance = 0;
}
void LR_Rotate(void) {
	parent = grand->left;
	child = parent->left;

	if (grand->balance == -2) {
		big->right = parent;
		parent->left = grand;
		grand->left = head;
		grand->right = head;
	}

	++big->balance;
	parent->balance = 0;
	grand->balance = 0;
	child->balance = 0;
}
void RL_Rotate(void) {
	parent = grand->left;
	child = parent->left;

	if (grand->balance == -2) {
		big->left = parent;
		parent->right = grand;
		grand->left = head;
		grand->right = head;
	}

	--big->balance;
	parent->balance = 0;
	grand->balance = 0;
	child->balance = 0;
}

void InsertNode(char data) {
	/* Configure node for Inserting */
	node *ptr = (node *)malloc(sizeof(node));
	ptr->data = data;
	ptr->balance = 0;
	ptr->left = head;
	ptr->right = head;

	if (head->right == head) {
		head->left = ptr;
		head->right = ptr;
	}

	else {
		/* Initializing Tree node */
		grand = parent = head;
		child = head->right;

		/* Start with on the Top*/
		node *tmp = head->right;

		while (tmp != head) {
			child = tmp;

			big = grand;
			grand = parent;
			parent = child;

			if (child->data > ptr->data)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}

		child = ptr;

		if (parent->data > child->data) {
			parent->left = child;
			++parent->balance;

			if (grand != head)
				++grand->balance;
		}

		else {
			parent->right = child;
			--parent->balance;

			if (grand != head)
				--grand->balance;
		}

		switch (IsBalance()) {
		case rotate::RR:
			RR_Rotate(); break;
		case rotate::LL:
			LL_Rotate(); break;
		case rotate::LR:
			LR_Rotate(); break;
		case rotate::RL:
			RL_Rotate(); break;
		default:
			;
		}
	}
}
void Level_Traverse(node *ptr) {
	InitializeQueue();	
	Put(ptr);

	while (!IsQueueEmpty()) {
		ptr = Get();
		Display(ptr);

		if (ptr->left != head)
			Put(ptr->left);

		if (ptr->right != head)
			Put(ptr->right);
	}
}

void main(int argc, char *argv[]) {
	printf("- AVL Tree Algorithm\n");

	InitializeTree();
	printf("[*] RR Rotate Test\n");
	InsertNode('a');
	InsertNode('b');
	Level_Traverse(head->right);

	printf("\n========================\n");

	InsertNode('c');
	Level_Traverse(head->right);

	InitializeTree();
	printf("\n\n[*] LL Rotate Test\n");
	InsertNode('d');
	InsertNode('c');
	InsertNode('e');
	InsertNode('b');
	Level_Traverse(head->right);

	printf("\n========================\n");
	InsertNode('a');
	Level_Traverse(head->right);
}
