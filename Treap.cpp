#include "Treap.h"
#include <cmath>
#include <iostream>
#include <algorithm>

int Treap::GetMaxDepth(TreapNode *&p) {
    if (!p)
        return 0;
    return 1 + std::max(GetMaxDepth(p->left), GetMaxDepth(p->right));
}

std::pair<TreapNode *, TreapNode *> Treap::Split(TreapNode *&t,
                                                 int lambda) {
    if (t == nullptr)
        return std::make_pair(nullptr, nullptr);
    if (t->key <= lambda) {
        auto split_res = Split(t->right, lambda);
        t->right = split_res.first;
        split_res.first = t;
        return split_res;
    } else {
        auto split_res = Split(t->left, lambda);
        t->left = split_res.second;
        split_res.second = t;
        return split_res;
    }
}

TreapNode *Treap::Merge(TreapNode *&t1, TreapNode *&t2) {
    if (t1 == nullptr)
        return t2;
    if (t2 == nullptr)
        return t1;
    if (t1->priority < t2->priority) {
        t1->right = Merge(t1->right, t2);
        return t1;
    } else {
        t2->left = Merge(t1, t2->left);
        return t2;
    }
}

bool Treap::Find(TreapNode *&t, int key) {
    if (t == nullptr)
        return false;
    if (t->key == key)
        return true;
    if (t->key > key)
        return Find(t->left, key);
    return Find(t->right, key);
}

void Treap::InsertNode(TreapNode *&t, int key) {
    if (Find(t, key))
        return;
    auto split_res = Split(t, key);
    TreapNode *node = new TreapNode(key);
    auto merge_res = Merge(split_res.first, node);
    start = Merge(merge_res, split_res.second);
}

void Treap::RemoveNode(TreapNode *&t, int key) {
    if (!t)
        return;
    if (t->key > key) {
        RemoveNode(t->left, key);
    } else if (t->key < key) {
        RemoveNode(t->right, key);
    } else {
        TreapNode *p_l = t->left, *p_r = t->right;
        delete t;
        t = Merge(p_l, p_r);
    }
}

Treap::Treap() {
    start = nullptr;
}

void Treap::Draw(sf::RenderWindow &window,
                 sf::Font &font,
                 sf::Vector2f mouse_pos,
                 TreapNode *p,
                 TreapNode *parent,
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
