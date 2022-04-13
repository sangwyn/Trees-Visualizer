#include "AVLTree.h"
#include "Globals.h"
#include <cmath>
#include <iostream>
#include <algorithm>

AVLTree::AVLTree() {
    start = nullptr;
}

int AVLTree::GetHeight(AVLTreeNode *&p) {
    return p ? p->height : 0;
}

void AVLTree::RecalcHeight(AVLTreeNode *&p) {
    p->height = 1 + std::max(GetHeight(p->left), GetHeight(p->right));
}

int AVLTree::BalanceFactor(AVLTreeNode *&p) {
    return GetHeight(p->right) - GetHeight(p->left);
}

AVLTreeNode *AVLTree::RotateRight(AVLTreeNode *&p) {
    AVLTreeNode *q = p->left;
    p->left = q->right;
    q->right = p;
    RecalcHeight(p);
    RecalcHeight(q);
    return q;
}

AVLTreeNode *AVLTree::RotateLeft(AVLTreeNode *&p) {
    AVLTreeNode *q = p->right;
    p->right = q->left;
    q->left = p;
    RecalcHeight(p);
    RecalcHeight(q);
    return q;
}

AVLTreeNode *AVLTree::Balance(AVLTreeNode *&p) {
    RecalcHeight(p);
    if (BalanceFactor(p) == 2) {
        if (BalanceFactor(p->right) < 0) {
            p->right = RotateRight(p->right);
        }
        return RotateLeft(p);
    } else if (BalanceFactor(p) == -2) {
        if (BalanceFactor(p->left) > 0) {
            p->left = RotateLeft(p->left);
        }
        return RotateRight(p);
    }
    return p;
}

AVLTreeNode *AVLTree::InsertNode(AVLTreeNode *&p, int key) {
    if (!p)
        return (new AVLTreeNode(key));
    if (key < p->data) {
        p->left = InsertNode(p->left, key);
    } else if (key > p->data) {
        p->right = InsertNode(p->right, key);
    } else {
        couldnt_insert = true;
    }
    return Balance(p);
}

AVLTreeNode *AVLTree::FindMin(AVLTreeNode *&p) {
    return p->left ? FindMin(p->left) : p;
}

AVLTreeNode *AVLTree::RemoveMin(AVLTreeNode *&p) {
    if (!p->left)
        return p->right;
    p->left = RemoveMin(p->left);
    return Balance(p);
}

AVLTreeNode *AVLTree::FindMax(AVLTreeNode *&p) {
    return p->right ? FindMax(p->right) : p;
}

AVLTreeNode *AVLTree::RemoveMax(AVLTreeNode *&p) {
    if (!p->right)
        return p->left;
    p->right = RemoveMax(p->right);
    return Balance(p);
}

AVLTreeNode *AVLTree::RemoveNode(AVLTreeNode *&p, int key) {
    if (!p)
        throw key;
    if (key < p->data) {
        p->left = RemoveNode(p->left, key);
    } else if (key > p->data) {
        p->right = RemoveNode(p->right, key);
    } else {
        AVLTreeNode *q = p->left;
        AVLTreeNode *r = p->right;
        delete p;
        if (!r)
            return q;
        if (!q)
            return r;
        if (GetHeight(q) > GetHeight(r)) {
            AVLTreeNode *max = FindMax(q);
            max->left = RemoveMax(q);
            max->right = r;
            return Balance(max);
        } else {
            AVLTreeNode *min = FindMin(r);
            min->right = RemoveMin(r);
            min->left = q;
            return Balance(min);
        }
    }
    return Balance(p);
}

void AVLTree::Draw(sf::RenderWindow &window,
                   sf::Font &font,
                   sf::Vector2f mouse_pos,
                   AVLTreeNode *&p,
                   AVLTreeNode *parent,
                   int depth,
                   int max_depth,
                   std::vector<sf::Text> &all_text,
                   std::vector<sf::CircleShape> &all_sprites) {
    if (!p)
        return;
    Draw(window, font, mouse_pos, p->left, p, depth + 1, max_depth, all_text, all_sprites);
    p->Draw(window, font, mouse_pos, parent, depth, max_depth, all_text, all_sprites);
    Draw(window, font, mouse_pos, p->right, p, depth + 1, max_depth, all_text, all_sprites);
}
