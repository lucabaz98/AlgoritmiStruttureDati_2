#include <iostream>
#include <sstream>

using namespace std;


class AVL {
    int key;
    AVL *left, *right;
    int height;
    string stringKey;
public:
    int getHeight(AVL *);

    AVL(int, string);

    AVL *rightRotate(AVL *);

    AVL *leftRotate(AVL *);

    int getBalanceFactor(AVL *N);

    void preOrder(AVL *);

    AVL *insert(AVL *, int, string);

    AVL *find(AVL *, int);

    string getStringKey(AVL *);

    void destroy(AVL *);
};

int max(int a, int b);


int AVL::getHeight(AVL *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVL::AVL(int value, string stringValue) {
    this->key = value;
    this->stringKey = stringValue;
    left = nullptr;
    right = nullptr;
    height = 1;
}

AVL *AVL::rightRotate(AVL *y) {
    AVL *x = y->left;
    AVL *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVL *AVL::leftRotate(AVL *x) {
    AVL *y = x->right;
    AVL *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int AVL::getBalanceFactor(AVL *node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVL *AVL::insert(AVL *root, int value, string stringValue) {
    if (root == nullptr)
        return (new AVL(value, stringValue));
    if (value < root->key)
        root->left = insert(root->left, value, stringValue);
    else if (value > root->key)
        root->right = insert(root->right, value, stringValue);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
        if (value < root->left->key) {
            return rightRotate(root);
        } else if (value > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (value > root->right->key) {
            return leftRotate(root);
        } else if (value < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

AVL *AVL::find(AVL *root, int value) {
    if ((root == nullptr) || ((root->key) == value)) {
        return root;
        //cout << root->stringKey;
    } else if (value < (root->key)) {
        return find(root->left, value);
    } else {
        return find(root->right, value);
    }
}

void AVL::preOrder(AVL *root) {
    if (root != nullptr) {
        cout << root->key << ":" << root->stringKey << ":" << root->height << " ";
        preOrder(root->left);
        preOrder(root->right);
    } else {
        cout << "NULL ";
    }
}

string AVL::getStringKey(AVL *root) {
    return root->stringKey;
}

void AVL::destroy(AVL *root) {
    if (root == nullptr)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
    root = nullptr;
}