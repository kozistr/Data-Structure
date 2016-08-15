#include <stdio.h>
#include <stdlib.h>

#define tSize 100 // Tree Size

typedef struct _node {
	char data;
	struct _node *left;
	struct _node *right;
} node;

int tree = 0; // Init with 0 - Stack Initializing
node *nBuf[2]; // nBuf[0] for Head_Node, nBuf[1] for End_Node
node *nTree[3]; // nTree[0] for parent, nTree[1] for Left_Child, nTree[2] for Right_Child
node *Stack[tSize];

void InitNode(void) {
	for (char i = 0; i < 2; ++i)
		nBuf[i] = (node *)malloc(sizeof(node));

	for (char i = 0; i < 2; ++i) {
		nBuf[i]->left = nBuf[1]; // head_node->left = end_node, end_node->left = end_node
		nBuf[i]->right = nBuf[1]; // head_node->right = end_node, end_node->right = end_node
	}
}

void InitTree(void) {
	/* Now Path : parent */
	for (char i = 0; i < 3; ++i) {
		nTree[i] = (node *)malloc(sizeof(node));
		nTree[i]->data = 'A' + i; // parent : A, left_child : B, right_child : C
	}
	
	nTree[0]->left = nTree[1]; // parent->left = left_child
	nTree[0]->right = nTree[2]; // parent->right = right_child

	nBuf[0]->left = nTree[0]; // head->left = parent
	nBuf[0]->right = nTree[0]; // head->right = parent

	/* Now Path : parent->left_child */
	nTree[0] = nTree[0]->left;

	for (char i = 1; i < 3; ++i) {
		nTree[i] = (node *)malloc(sizeof(node));
		nTree[i]->data = 'C' + i; // parent->left_child->left->date = D, parent-left_child->rigth->date = E
		nTree[i]->left = nBuf[1]; // parent->left_child->left(right)->left = end_node
		nTree[i]->right = nBuf[1]; // parent->left_child->left(right)->right = end_node
	}

	nTree[0]->left = nTree[1]; // parent->left_child->left = left_child'
	nTree[0]->right = nTree[2]; // parent->rigth_child->right = right_child'
	
	/* Now Path : parent->right_child */
	nTree[0] = nBuf[0]->right->right;

	for (char i = 1; i < 3; ++i) {
		nTree[i] = (node *)malloc(sizeof(node));
		nTree[i]->data = 'E' + i; // parent->right_child->left->date = F, parent-right_child->rigth->date = G
		nTree[i]->left = nBuf[1]; // parent->right_child->left(right)->left = end_node
		nTree[i]->right = nBuf[1]; // parent->right_child->left(right)->right = end_node
	}

	nTree[0]->left = nTree[1];
	nTree[0]->right = nTree[2];
}

int IsStackEmpty(void) {
	if (tree == 0)
		return 1;
	else
		return 0;
}

void Push(node *ptr) {
	Stack[tree] = ptr;
	tree = (tree++) % tSize;
}

node *Pop(void) {
	if (!IsStackEmpty())
		return Stack[--tree];
	else
		printf("Stack is Empty!\n");
	return NULL;
}

void Display(node *ptr) {
	printf("%2c -> ", ptr->data);
}

void Recursive_Traverse(node *ptr) {
	if (ptr != nBuf[1]) {
		Recursive_Traverse(ptr->left);
		Display(ptr);
		Recursive_Traverse(ptr->right);
	}
}

void Stack_Traverse(node *ptr) {
	for (;;) {
		while (ptr != nBuf[1]) { // ptr isn't end_node
			Push(ptr);
			ptr = ptr->left;
		}

		if (!IsStackEmpty()) {
			ptr = Pop();
			Display(ptr);
			ptr = ptr->right;
		}

		else
			break;
	}
}

int main(int argc, char *argv[]) {
	InitNode();
	InitTree();

	printf("- In-Order Tree Traversal\n\n");

	printf("[*] Method : Recursive\n");
	Recursive_Traverse(nBuf[0]->left); // head_node->left => parent

	printf("\n[*] Method : Stack\n");
	Stack_Traverse(nBuf[0]->left); // head_node->left => parent
}
