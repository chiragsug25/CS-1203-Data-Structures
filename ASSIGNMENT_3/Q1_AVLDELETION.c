#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node* left;
    struct node* right;
    int height;
};

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get the height of a node
int getHeight(struct node* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(struct node* n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

// Function to create a new node with the given key
struct node* createNode(int key) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to perform a right rotation on the given node
struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;
    x->right = y;
    y->left = T2;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    return x;
}

// Function to perform a left rotation on the given node
struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    return y;
}

// Function to insert a key into the AVL tree
struct node* insert(struct node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    // Left Left Case
    if (bf > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (bf < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (bf > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (bf < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to find the node with the minimum key value in a given AVL tree
struct node* findMinNode(struct node* root) {
    struct node* current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with the given key from the AVL tree
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct node* temp = findMinNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    if (bf > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (bf < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to delete a node with the given key from the AVL tree
struct node* delete(struct node* root, int key) {
    return deleteNode(root, key);
}

// Function to perform a preorder traversal of the tree
void preOrder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function to perform an inorder traversal of the tree
void inOrder(struct node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Function to display the tree structure
void displayTree(struct node* root, int level) {
    if (root == NULL)
        return;

    displayTree(root->right, level + 1);
    printf("\n");

    for (int i = 0; i < level; i++)
        printf("   ");

    printf("%d\n", root->key);
    displayTree(root->left, level + 1);
}

int main() {
    struct node* root = NULL;

    // Insert some default elments into the AVL tree
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);

    int choice, key;

    while (1) {
        printf("AVL Tree Operations, there already exists an AVL tree with default elements and you can modify them or view:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display Tree\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                break;
            case 3:
                printf("AVL Tree (in-order):\n");
                inOrder(root);
                printf("\n");
                displayTree(root, 10);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

