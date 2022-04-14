#include "SplayTree.h"
#include <cmath>
#include <iostream>
#include <algorithm>

SplayTree::SplayTree() {
    start = nullptr;
}

int SplayTree::GetMaxDepth(SplayTreeNode *&p) {
    if (!p)
        return 0;
    return 1 + std::max(GetMaxDepth(p->left), GetMaxDepth(p->right));
}

SplayTreeNode *SplayTree::RightRotate(SplayTreeNode *&root) {
    SplayTreeNode *q = root->left;
    root->left = q->right;
    q->right = root;
    return q;
}

SplayTreeNode *SplayTree::LeftRotate(SplayTreeNode *&root) {
    SplayTreeNode *q = root->right;
    root->right = q->left;
    q->left = root;
    return q;
}

SplayTreeNode *SplayTree::Splay(SplayTreeNode *&root, int key) {
    if (!root || root->data == key)
        return root;
    if (root->data > key) {
        if (!root->left)
            return root;
        if (root->left->data > key) {
            root->left->left = Splay(root->left->left, key);
            root = RightRotate(root);
        } else if (root->left->data < key) {
            root->left->right = Splay(root->left->right, key);
            if (root->left->right) {
                root->left = LeftRotate(root->left);
            }
        }
        return root->left ? RightRotate(root) : root;
    } else {
        if (!root->right)
            return root;
        if (root->right->data > key) {
            root->right->left = Splay(root->right->left, key);
            if (root->right->left)
                root->right = RightRotate(root->right);
        } else if (root->right->data < key) {
            root->right->right = Splay(root->right->right, key);
            root = LeftRotate(root);
        }
        return root->right ? LeftRotate(root) : root;
    }
}

SplayTreeNode *SplayTree::InsertNode(SplayTreeNode *&p, int key) {
    if (!p)
        return (new SplayTreeNode(key));
    if (p->data > key)
        p->left = InsertNode(p->left, key);
    else
        p->right = InsertNode(p->right, key);
    return p;
}

SplayTreeNode *SplayTree::RemoveNode(SplayTreeNode *&p, int key) {
    p = Splay(p, key);
    SplayTreeNode *left = p->left, *right = p->right;
    SplayTreeNode *tmp;
    if (!left) {
        tmp = p;
        p = p->right;
    } else {
        tmp = p;
        p = Splay(p->left, key);
        p->right = tmp->right;
    }
    delete tmp;
    tmp = nullptr;
    return p;
}

void SplayTree::Draw(sf::RenderWindow &window,
                     sf::Font &font,
                     sf::Vector2f mouse_pos,
                     SplayTreeNode *&p,
                     SplayTreeNode *parent,
                     int depth,
                     int max_depth,
                     std::vector<sf::Text> &all_text,
                     std::vector<sf::CircleShape> &all_sprites) {
    if (!p)
        return;
    Draw(window,
         font,
         mouse_pos,
         p->left,
         p,
         depth + 1,
         max_depth,
         all_text,
         all_sprites);
    p->Draw(window,
            font,
            mouse_pos,
            parent,
            depth,
            max_depth,
            all_text,
            all_sprites);
    Draw(window,
         font,
         mouse_pos,
         p->right,
         p,
         depth + 1,
         max_depth,
         all_text,
         all_sprites);
}
