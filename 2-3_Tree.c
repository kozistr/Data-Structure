#include <stdio.h>
#include <stdlib.h>

#define tree 100

typedef struct _node {
	char lData; // Left Data
	char rData; // Right Data
	struct _node *left;
	struct _node *mid;
	struct _node *right;
} node;

int front, rear;
node *head;
node *parent;
node *Queue[tree];

void InitializeQueue(void) {
	front = rear = 0;
}
void InitializeTree(void) {
	head = (node *)malloc(sizeof(node));
	head->left = head;
	head->mid = head;
	head->right = head;
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
	printf("%d ", ptr->lData);

	if (ptr->rData != -1) {
		printf("%d ", ptr->rData);
	}

	printf("-> ");
}

node *split_node(node *tmp, node *ptr) {
	node *_ptr = (node *)malloc(sizeof(node));
	_ptr->rData = -1;
	_ptr->left = head;
	_ptr->mid = head;
	_ptr->right = head;

	if (tmp->lData < ptr->lData) {
		if (ptr->lData < tmp->rData) {
			_ptr->lData = tmp->rData;
			tmp->rData = -1;
		}

		else {
			_ptr->lData = ptr->lData;
			ptr->lData = tmp->rData;
			tmp->rData = -1;
		}
	}

	else {
		_ptr->lData = tmp->rData;
		tmp->rData = ptr->lData;
		ptr->lData = tmp->lData;
		tmp->lData = tmp->rData;
		tmp->rData = -1;
	}

	ptr->left = tmp;
	ptr->mid = _ptr;

	return ptr;
}
void InsertNode(int data) {
	int flag = 0;

	if (head->right == head) { //  Configure 'Starting Node'
		node *ptr = (node *)malloc(sizeof(node));
		ptr->lData = data;
		ptr->rData = -1;
		ptr->left = head;
		ptr->mid = head;
		ptr->right = head;

		/* Configure head node -> head node to 'Start Node' */
		head->left = ptr;
		head->mid = ptr;
		head->right = ptr;
	}

	else { // If not...
		node *tmp = head->left;
		parent = head;

		for (;;) {
			if (tmp->lData < data) {
				if (tmp->rData == -1)
					break;

				else {
					if (tmp->left == head) {
						flag = 1;
						break;
					}

					else {
						if (tmp->rData < data) {
							if (tmp->mid == head)
								break;

							else {
								parent = tmp;
								tmp = tmp->mid;
							}
						}

						else {
							if (tmp->mid == head)
								break;

							else {
								parent = tmp;
								tmp = tmp->mid;
							}
						}
					}
				}
			}

			else {
				if (tmp->left == head) {
					if (tmp->rData == -1)
						flag = 0;
					else
						flag = 1;
					break;
				}

				else {
					parent = tmp;
					tmp = tmp->left;
				}
			}
		}

		if (tmp->rData == -1 && flag == 0) {
			if (tmp->lData < data)
				tmp->rData = data;

			else {
				tmp->rData = tmp->lData;
				tmp->lData = data;
			}
		}

		else if (flag > 0) {
			/* Configure node for Inserting */
			node *ptr = (node *)malloc(sizeof(node));
			ptr->lData = data;
			ptr->rData = -1;
			ptr->left = head;
			ptr->mid = head;
			ptr->right = head;

			if (flag == 1) {
				parent->left = split_node(tmp, ptr);
				tmp = parent->left;

				if (parent->rData == -1) {
					parent->rData = parent->lData;
					parent->lData = tmp->lData;
					parent->right = parent->mid;
					parent->mid = tmp->mid;
					parent->left = tmp->left;
				}
			}
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

		if (ptr->mid != head)
			Put(ptr->mid);

		if (ptr->right != head)
			Put(ptr->right);
	}
}

void main(int argc, char *argv[]) {
	InitializeTree();

	printf("- 2-3 Tree Algorithm\n\n");

	InsertNode(10);
	InsertNode(30);
	Level_Traverse(head->left);
	printf("\n====================================\n");

	InsertNode(25);
	InsertNode(7);
	Level_Traverse(head->left);
	printf("\n====================================\n");

	InsertNode(15);
	Level_Traverse(head->left);
	printf("\n====================================\n");

	InsertNode(5);
	InsertNode(23);
	Level_Traverse(head->left);
	printf("\n====================================\n");
}
