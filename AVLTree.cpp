#include "AVLTree.h"
#include <cmath>
#include <iostream>

void AVLTree::SmallTurnRight(AVLTreeNode* &a)
{
    AVLTreeNode* b = a->right;
    a->right = b->left;
    b->left = a;
    a = b;
}

void AVLTree::BigTurnRight(AVLTreeNode* &a)
{
    AVLTreeNode* b = a->right;
    AVLTreeNode* c = b->left;
    a->right = c->left;
    b->left = c->right;
    c->left = a;
    c->right = b;
    a = c;
}

void AVLTree::SmallTurnLeft(AVLTreeNode* &a)
{
    AVLTreeNode* b = a->left;
    a->left = b->right;
    b->right = a;
    a = b;
}

void AVLTree::BigTurnLeft(AVLTreeNode* &a)
{
    AVLTreeNode* b = a->left;
    AVLTreeNode* c = b->right;
    a->left = c->right;
    b->right = c->left;
    c->right = a;
    c->left = b;
    a = c;
}

void AVLTree::Balance(AVLTreeNode* &a)
{
    if (a->right->height > a->left->height)
    {
        AVLTreeNode* b = a->right;
        AVLTreeNode* c = b->left;
        AVLTreeNode* r = b->right;
        if (c->height <= r->height)
            SmallTurnRight(a);
        else
            BigTurnRight(a);
    }
    else
    {
        AVLTreeNode* b = a->left;
        AVLTreeNode* c = b->left;
        AVLTreeNode* r = b->right;
        if (c->height >= r->height)
            SmallTurnLeft(a);
        else
            BigTurnLeft(a);
    }
}

AVLTreeNode* AVLTree::FindMin(AVLTreeNode* &p)
{
    if (p->left == nullptr)
        return p;
    return FindMin(p->left);
}

AVLTreeNode* AVLTree::FindMax(AVLTreeNode* &p)
{
    if (p->right == nullptr)
        return p;
    return FindMax(p->right);
}

void AVLTree::InsertNode(AVLTreeNode* &p, int node)
{
    if (p == nullptr)
    {
        p = new AVLTreeNode(node);
        return;
    }
    if (node > p->data)
        InsertNode(p->right, node);
    else if (node < p->data)
        InsertNode(p->left, node);
    else
        std::cout << "EQUAL NODES FOUND\n";
    ++p->height;
    int l_height = 0, r_height = 0;
    if (p->left != nullptr)
        l_height = p->left->height;
    if (p->right != nullptr)
        r_height = p->right->height;
    if (abs(r_height - l_height) > 1)
        Balance(p);
}

void AVLTree::RemoveNode(AVLTreeNode* &p, int node)
{
    if (p->data > node)
    {
        RemoveNode(p->left, node);
        --p->height;
        if (abs(p->left->height - p->right->height) > 1)
            Balance(p);
        return;
    }
    if (p->data < node)
    {
        RemoveNode(p->right, node);
        --p->height;
        if (abs(p->left->height - p->right->height) > 1)
            Balance(p);
        return;
    }
    bool left = true;
    bool found = false;
    if (p->left != nullptr)
        found = true;
    if (p->right != nullptr)
    {
        if (p->left == nullptr || p->left != nullptr && p->right->height > p->left->height)
        {
            found = true;
            left = false;
        }
    }
    if (!found)
        std::cout << "NO ELEM FOUND\n";
    AVLTreeNode* q = nullptr;
    if (left)
        q = FindMax(p->left);
    else
        q = FindMin(p->right);
    p->data = q->data;
    delete q;
}

AVLTree::AVLTree()
{
    start = nullptr;
}