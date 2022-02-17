#include <iostream>
using namespace std;

class BST {
    int key;
    string stringKey;
    BST *left, *right;

public:
    BST();

    BST(int, string);

    BST *insert(BST *root, int value, string sNumber);

    void preOrder(BST *);

    BST *find(BST *, int);

    string getStringKey(BST *);

    void destroy(BST *);
};

BST::BST() {
    key = 0;
    left = NULL;
    right = NULL;
    stringKey = "";
}

BST::BST(int value, string stringValue) {
    key = value;
    left = right = NULL;
    stringKey = stringValue;
}

BST *BST::insert(BST *root, int value, string stringValue) {
    if (!root) {
        return new BST(value, stringValue);
    }
    if (value > root->key) {
        root->right = insert(root->right, value, stringValue);
    } else {
        root->left = insert(root->left, value, stringValue);
    }
    return root;
}

void BST::preOrder(BST *root) {
    if (root != NULL) {
        cout << root->key << ":" << root->stringKey << " ";
        preOrder(root->left);
        preOrder(root->right);
    } else {
        cout << "NULL ";
    }
}

BST *BST::find(BST *root, int value) {
    if ((root == nullptr) || ((root->key) == value)) {
        return root;
        //cout << root->stringKey;
    } else if (value < (root->key)) {
        return find(root->left, value);
    } else {
        return find(root->right, value);
    }
}

string BST::getStringKey(BST *root) {
    return root->stringKey;
}

void BST::destroy(BST *root) {
    if (root == nullptr)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
    root = nullptr;
}
