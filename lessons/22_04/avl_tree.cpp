#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void printTitle(const string& title) {
    cout << "\n=== " << title << " ===\n";
}

// Вертикальный вывод
void printPretty(Node* root, int level = 0, char prefix = ' ') {
    if (!root) return;
    if (root->right) printPretty(root->right, level + 1, '/');
    cout << string(level * 4, ' ') << prefix << "-- " << root->key << endl;
    if (root->left) printPretty(root->left, level + 1, '\\');
}

Node* rotateRight(Node* y) {
    if (!y || !y->left) return y;

    printTitle("ПРАВОЕ ВРАЩЕНИЕ");
    printPretty(y);

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    printTitle("ПОСЛЕ ПРАВОГО ВРАЩЕНИЯ");
    printPretty(x);

    return x;
}

Node* rotateLeft(Node* x) {
    if (!x || !x->right) return x;

    printTitle("ЛЕВОЕ ВРАЩЕНИЕ");
    printPretty(x);

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    printTitle("ПОСЛЕ ЛЕВОГО ВРАЩЕНИЯ");
    printPretty(y);

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node{key, nullptr, nullptr, 1};

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    // RR
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Балансировки
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

bool search(Node* node, int key) {
    if (!node) return false;
    if (key == node->key) return true;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

int main() {
    Node* root = nullptr;
    for (int i = 1; i <= 8; i++)
        root = insert(root, i);

    cout << "\n\nДерево до удаления:\n";
    printPretty(root);

    root = deleteNode(root, 1);
    cout << "\nДерево после удаления 1:\n";
    printPretty(root);

    return 0;
}
