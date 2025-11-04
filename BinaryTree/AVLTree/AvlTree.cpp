#include <iostream>
#include <algorithm>
using namespace std;

// Node structure
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        height = 1;
        left = right = NULL;
    }
};

// ---------- Helper Functions ----------

// Function to get height of a node
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get balance factor
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to update height after any change
void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// ---------- Rotations ----------

// Right rotation (LL case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation (RR case)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// ---------- Rebalancing Function ----------
Node* rebalance(Node* node) {
    updateHeight(node);

    int balance = getBalance(node);

    // Left heavy
    if (balance > 1) {
        // Left-Left case
        if (getBalance(node->left) >= 0)
            return rightRotate(node);
        // Left-Right case
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // Right heavy
    if (balance < -1) {
        // Right-Right case
        if (getBalance(node->right) <= 0)
            return leftRotate(node);
        // Right-Left case
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node; // Balanced
}

// ---------- Insert Function ----------
Node* insert(Node* node, int key) {
    if (node == NULL)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // duplicates not allowed

    return rebalance(node);
}

// ---------- Inorder Traversal ----------
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// ---------- Main Function ----------
int main() {
    Node* root = NULL;

    // Inserting nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder traversal of AVL tree: ";
    inorder(root);
    cout << endl;

    return 0;
}
z 
