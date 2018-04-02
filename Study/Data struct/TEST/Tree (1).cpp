#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int T;

typedef struct treeNode {
	T                   data;
	struct treeNode*    left;
	struct treeNode*    right;
} TreeNode;

TreeNode* createNode(T data)
{
	TreeNode* newNode = (TreeNode *)malloc(sizeof(treeNode) * 1);
	newNode->data = data;
	newNode->left = nullptr;
	newNode->right = nullptr;

	return newNode;
}

enum TraversalType { InOrder, PreOrder, PostOrder };

TreeNode* emptyNode = nullptr;

void printTree(TreeNode* current, TraversalType type = InOrder)
{
	if (!current) return;
	if (type == PreOrder) printf("%d ", current->data);
	printTree(current->left, type);
	if (type == InOrder) printf("%d ", current->data);
	printTree(current->right, type);
	if (type == PostOrder) printf("%d ", current->data);
}

void insert(TreeNode*& current, T data)
{
	if (!current) {
		current = createNode(data);
		return;
	}
	if (current->data == data) return; // do nothing
	if (data < current->data) {
		insert(current->left, data);
		return;
	}
	// else data > current->data
	insert(current->right, data);
}

TreeNode*& find(const TreeNode*& current, T data)
{
	if (!current) return emptyNode;
	if (current->data == data) return const_cast<TreeNode*&>(current);
	if (data < current->data) return find( const_cast<const TreeNode*&>(current->left), data);
	return find(const_cast<const TreeNode*&>(current->right), data);
}

TreeNode*& leftmost(TreeNode*& current)
{
	if (!current) return emptyNode;
	if (!current->left) return current;
	return leftmost(current->left);
}

TreeNode*& rightmost(TreeNode*& current)
{
	if (!current) return emptyNode;
	if (!current->right) return current;
	return rightmost(current->right);
}

void removeNode(TreeNode*& node)
{
	if (!node->left && !node->right) {
		free( node );
		node = nullptr;
		return;
	}
	if (!node->left || !node->right) {
		TreeNode *temp = nullptr;
		if ( node->left) {
			temp = node->left;
			node->data = node->left->data;
			node->right = node->left->right;
			node->left = node->left->left;
			free(temp);
			return;
		}
		temp = node->right;
		node->data = node->right->data;
		node->left = node->right->left;
		node->right = node->right->right;
		free(temp);
		return;
	}
	TreeNode*& r = rightmost(node->left);
	TreeNode*& l = leftmost(node->right);
	assert(r && l);
	TreeNode*& candidate = ( node->data - r->data > l->data - node->data) ? l : r;
	node->data = candidate->data;
	removeNode(candidate);
}

void remove(TreeNode*& root, T data)
{
	TreeNode*& to_be_removed = find(const_cast<const TreeNode*&>(root), data);
	if (to_be_removed == emptyNode) return;
	removeNode(to_be_removed);
}

void removeTree(TreeNode*& root)
{
	while (root) {
		printf("removing %d\n", root->data);
		remove(root, root->data);

		printf("InOrder: "); printTree(root);
		printf(", PreOrder: ");	printTree(root, PreOrder);
		printf("\n");
	}
}

int main()
{
	T data[] = { 5, 0, 10, -5, -8, -3, -4, -2 };

	TreeNode* root = nullptr;

	for (auto datum : data) insert(root, datum);
		
	printf("InOrder: "); printTree(root); 
	printf(", PreOrder: ");	printTree(root, PreOrder); 
	printf("\n");

	remove(root,0);

	printf("InOrder: "); printTree(root);
	printf(", PreOrder: ");	printTree(root, PreOrder);
	printf("\n");

	removeTree(root);

	return 0;
}