#include <iostream>

using namespace std;

enum Color {
    RED, BLACK
};

class RBT {
private:
    int key;
    bool color;
    RBT *left, *right, *parent;
    string stringKey;

public:
    RBT(int, string);

    RBT *insert(RBT *, int, string);

    RBT *RBTInsert(RBT *, RBT *);

    void preOrder(RBT *);

    RBT *find(RBT *, int);

    void rotateLeft(RBT *&, RBT *&);

    void rotateRight(RBT *&, RBT *&);

    void fixViolation(RBT *&, RBT *&);

    string getStringKey(RBT *);

    void destroy(RBT *);
};

RBT::RBT(int value, string stringValue) {
    this->stringKey = stringValue;
    this->key = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

void RBT::preOrder(RBT *root) {
    if (root != nullptr) {
        string stringColor = root->color == RED ? "red" : "black";
        cout << root->key << ":" << root->stringKey << ":" << stringColor << " ";
        preOrder(root->left);
        preOrder(root->right);
    } else {
        cout << "NULL ";
    }
}

RBT *RBT::RBTInsert(RBT *root, RBT *pt) {
    if (root == nullptr)
        return pt;
    if (pt->key < root->key) {
        root->left = RBTInsert(root->left, pt);
        root->left->parent = root;
    } else if (pt->key > root->key) {
        root->right = RBTInsert(root->right, pt);
        root->right->parent = root;
    }
    return root;
}

RBT *RBT::insert(RBT *root, int value, string stringValue) {
    RBT *pt = new RBT(value, stringValue);
    root = RBTInsert(root, pt);
    fixViolation(root, pt);
    return root;
}

void RBT::rotateLeft(RBT *&root, RBT *&pt) {
    RBT *pt_right = pt->right;
    pt->right = pt_right->left;
    if (pt->right != nullptr)
        pt->right->parent = pt;
    pt_right->parent = pt->parent;
    if (pt->parent == nullptr)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;
    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBT::rotateRight(RBT *&root, RBT *&pt) {
    RBT *pt_left = pt->left;
    pt->left = pt_left->right;
    if (pt->left != nullptr)
        pt->left->parent = pt;
    pt_left->parent = pt->parent;
    if (pt->parent == nullptr)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;
    pt_left->right = pt;
    pt->parent = pt_left;
}

void RBT::fixViolation(RBT *&root, RBT *&pt) {
    RBT *parent_pt = nullptr;
    RBT *grand_parent_pt = nullptr;
    while ((pt != root) && (pt->color != BLACK) &&
           (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        if (parent_pt == grand_parent_pt->left) {
            RBT *uncle_pt = grand_parent_pt->right;
            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color,
                     grand_parent_pt->color);
                pt = parent_pt;
            }
        } else {
            RBT *uncle_pt = grand_parent_pt->left;
            if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color,
                     grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    root->color = BLACK;
}

RBT *RBT::find(RBT *root, int value) {
    if ((root == nullptr) || ((root->key) == value)) {
        return root;
    } else if (value < (root->key)) {
        return find(root->left, value);
    } else {
        return find(root->right, value);
    }
}

string RBT::getStringKey(RBT *root) {
    return root->stringKey;
}

void RBT::destroy(RBT *root) {
    if (root == nullptr)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
    root = nullptr;
}