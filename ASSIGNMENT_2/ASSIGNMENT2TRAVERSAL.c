#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary tree
struct node {
    int key;
    struct node *left, *right;
};

// Function to create a new node with a given key
struct node* createNode(int k) {
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->key = k;
    temp->left = temp->right = NULL;
    return temp;
}

// Fuction to perform an inorder traversal of the binary tree
void inorder(struct node *root) {
    struct node *stack[100];
    int top = -1;
    struct node *p = root;

    // Loop until all nodes are traversed
    while (p != NULL || top != -1) {
        // Traverse to the leftmost node
        while (p != NULL) {
            stack[++top] = p;
            p = p->left;
        }
        // Backtrack from the empty subtree and visit the node
        // at the top of the stack
        p = stack[top--];
        printf("%d ", p->key);
        // We have visted the node and its left subtree. Now,
        // it's right subtree's turn
        p = p->right;
    }
}

int main() {
    // Create a binary tree
    struct node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // Perform inorder traversal
    inorder(root);

    return 0;
}
