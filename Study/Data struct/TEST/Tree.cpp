#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode* create(int data)
{
    TreeNode *newNode = (TreeNode *)calloc(sizeof(TreeNode));
    newNode->data = data;
    return newNode;
}

void insert(TreeNode*& root, int data )
{
    TreeNode *newNode = create(data);
    if (!root) {
        root = newNode;
        return;
    }
    TreeNode* current = root;
    TreeNode* parent = current;
    while (current) {
        if (data < current->data ) {            
            parent = current;
            current = current->left;
            continue;
        }
        if (data > current->data ) {            
            parent = current;
            current = current->right;
            continue;
        }
        // data == current->data
        free(newNode);
        return;
    }
    current = newNode;
    assert( parent != nullptr);
    if (parent->data < data)
        parent->right = current;
    else
        parent->left = current;
}

void display(TreeNode* root)
{
    if (!root) return;
    display(root->left);
    printf( "%d ", root-> data);
    display(root->right);
}

int main()
{
    int test_set[] = { 5, 4, 1, 7, 8, 2 };
    TreeNode *root = nullptr;

    for (int i=0; i< 6; i++ )
    {
        insert(root, test_set[i]);
    }

    display(root);

    return 0;

}