#include "RBTree.h"
#include "Globals.h"
#include <iostream>
#include <algorithm>

int RBTree::GetMaxDepth(RBTreeNode *&p) {
    if (!p)
        return 0;
    return 1 + std::max(GetMaxDepth(p->left), GetMaxDepth(p->right));
}

void RBTree::RightRotate(RBTreeNode *&root, RBTreeNode *&p) {
    RBTreeNode *p_left = p->left;
    p->left = p_left->right;
    if (p->left)
        p->left->parent = p;
    p_left->parent = p->parent;
    if (!p->parent)
        root = p_left;
    else if (p == p->parent->left)
        p->parent->left = p_left;
    else
        p->parent->right = p_left;

    p_left->right = p;
    p->parent = p_left;
}

void RBTree::LeftRotate(RBTreeNode *&root, RBTreeNode *&p) {
    RBTreeNode *p_right = p->right;
    p->right = p_right->left;
    if (p->right)
        p->right->parent = p;
    p_right->parent = p->parent;
    if (!p->parent)
        root = p_right;
    else if (p == p->parent->left)
        p->parent->left = p_right;
    else
        p->parent->right = p_right;

    p_right->left = p;
    p->parent = p_right;
}

void RBTree::FixInsert(RBTreeNode *&root, RBTreeNode *&p) {
    RBTreeNode *parent = nullptr, *grandparent = nullptr;
    while (p != root && p->red && p->parent->red) {
        parent = p->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            RBTreeNode *uncle = grandparent->right;
            if (uncle && uncle->red) {
                grandparent->SetColor(true);
                parent->SetColor(false);
                uncle->SetColor(false);
                p = grandparent;
            } else {
                if (p == parent->right) {
                    LeftRotate(root, parent);
                    p = parent;
                    parent = p->parent;
                }
                RightRotate(root, grandparent);
                std::swap(parent->red, grandparent->red);
                p = parent;
            }
        } else {
            RBTreeNode *uncle = grandparent->left;
            if (uncle && uncle->red) {
                grandparent->SetColor(true);
                parent->SetColor(false);
                uncle->SetColor(false);
                p = grandparent;
            } else {
                if (p == parent->left) {
                    RightRotate(root, parent);
                    p = parent;
                    parent = p->parent;
                }
                LeftRotate(root, grandparent);
                std::swap(parent->red, grandparent->red);
                p = parent;
            }
        }
    }
    root->SetColor(false);
}

RBTreeNode *RBTree::BSTInsert(RBTreeNode *&root, RBTreeNode *&p) {
    if (!root)
        return p;
    if (p->data < root->data) {
        root->left = BSTInsert(root->left, p);
        root->left->parent = root;
    } else if (p->data > root->data) {
        root->right = BSTInsert(root->right, p);
        root->right->parent = root;
    }
    return root;
}

void RBTree::InsertNode(RBTreeNode *&root, int key) {
    RBTreeNode *p = new RBTreeNode(key);
    root = BSTInsert(root, p);
    FixInsert(root, p);
}

RBTreeNode *RBTree::FindMin(RBTreeNode *&p) {
    if (!p)
        return nullptr;
    return p->left ? FindMin(p->left) : p;
}

RBTreeNode *RBTree::FindMax(RBTreeNode *&p) {
    if (!p)
        return nullptr;
    return p->right ? FindMax(p->right) : p;
}

void RBTree::FixDelete(RBTreeNode *root, RBTreeNode *p) {
    RBTreeNode *parent = nullptr, *sibling = nullptr, *s_l = nullptr,
        *s_r = nullptr;
    while (p != root) {
        parent = p->parent;
        if (p == parent->left)
            sibling = parent->right;
        else
            sibling = parent->left;
        s_l = sibling->left;
        s_r = sibling->right;

        if (p == parent->left) {
            if (sibling->red) {
                sibling->SetColor(false);
                parent->SetColor(true);
                LeftRotate(root, parent);

                parent = p->parent;
                if (p == parent->left)
                    sibling = parent->right;
                else
                    sibling = parent->left;
                s_l = sibling->left;
                s_r = sibling->right;
            }
            if (!parent->red && !sibling->red && (!s_l || !s_l->red)
                && (!s_r || !s_r->red)) {
                sibling->SetColor(true);
                p = parent;
                continue;
            }
            if (parent->red && !sibling->red && (!s_l || !s_l->red)
                && (!s_r || !s_r->red)) {
                parent->SetColor(false);
                sibling->SetColor(true);
                return;
            }
            if (!sibling->red) {
                if (s_l && s_l->red) {
                    s_l->SetColor(false);
                    sibling->SetColor(true);
                    RightRotate(root, sibling);
                    sibling = s_l;
                    s_l = sibling->left;
                    s_r = sibling->right;
                }
                if (s_r && s_r->red) {
                    sibling->SetColor(parent->red);
                    parent->SetColor(false);
                    s_r->SetColor(false);
                    LeftRotate(root, parent);
                    return;
                }
            }
        } else {
            if (sibling->red) {
                sibling->SetColor(false);
                parent->SetColor(true);
                RightRotate(root, parent);

                parent = p->parent;
                if (p == parent->left)
                    sibling = parent->right;
                else
                    sibling = parent->left;
                s_l = sibling->left;
                s_r = sibling->right;
            }
            if (!parent->red && !sibling->red && (!s_l || !s_l->red)
                && (!s_r || !s_r->red)) {
                sibling->SetColor(true);
                p = parent;
                continue;
            }
            if (parent->red && !sibling->red && (!s_l || !s_l->red)
                && (!s_r || !s_r->red)) {
                parent->SetColor(false);
                sibling->SetColor(true);
                return;
            }
            if (!sibling->red) {
                if (s_r && s_r->red) {
                    s_r->SetColor(false);
                    sibling->SetColor(true);
                    LeftRotate(root, sibling);
                    sibling = s_r;
                    s_l = sibling->left;
                    s_r = sibling->right;
                }
                if (s_l && s_l->red) {
                    sibling->SetColor(parent->red);
                    parent->SetColor(false);
                    s_l->SetColor(false);
                    RightRotate(root, parent);
                    return;
                }
            }
        }
    }
    start = p;
//    root->SetColor(false);
}

void RBTree::RemoveNode(RBTreeNode *&root, int key) {
    if (!root)
        return;
    if (root->data > key) {
        RemoveNode(root->left, key);
    } else if (root->data < key) {
        RemoveNode(root->right, key);
    } else {
        if (root == start && !root->left && !root->right) {
            start = nullptr;
            delete root;
            root = nullptr;
            return;
        }

        RBTreeNode *m = FindMin(root->right);
        if (!m)
            m = FindMax(root->left);

        if (!m) {
            m = root;
        }
        root->data = m->data;
        if (m->red) {
            if (m->parent) {
                if (m == m->parent->left)
                    m->parent->left = nullptr;
                else
                    m->parent->right = nullptr;
            }
            delete m;
            m = nullptr;
            return;
        }
        if (m->left) {
            if (m->parent) {
                if (m == m->parent->left)
                    m->parent->left = m->left;
                else
                    m->parent->right = m->left;
            }
            m->left->parent = m->parent;
            m->left->SetColor(false);
            delete m;
            m = nullptr;
            return;
        }
        if (m->right) {
            if (m->parent) {
                if (m == m->parent->left)
                    m->parent->left = m->right;
                else
                    m->parent->right = m->right;
            }
            m->right->parent = m->parent;
            m->right->SetColor(false);
            delete m;
            m = nullptr;
            return;
        }

        FixDelete(start, m);
        if (m->parent) {
            if (m == m->parent->left)
                m->parent->left = nullptr;
            else
                m->parent->right = nullptr;
        }
        delete m;
        m = nullptr;
    }
}

RBTree::RBTree() {
    start = nullptr;

    nil_text.setString("NIL");
    nil_text.setFillColor(kBlackNodeTextColor);

    nil_sprite.setFillColor(kBlackNodeColor);
    nil_sprite.setOutlineColor(kUnselectedColor);
    nil_sprite.setOutlineThickness(2);
    nil_sprite.setSize({2 * kRadius, 2 * kRadius});
    nil_sprite.setOrigin(kRadius, kRadius);

    nil_text.setOrigin(nil_text.getGlobalBounds().width / 2,
                       nil_text.getGlobalBounds().height / 2);
    nil_text.setPosition(nil_sprite.getPosition());
}

void RBTree::DrawNil(sf::RenderWindow &window,
                     sf::Font &font,
                     RBTreeNode *&parent,
                     int depth,
                     int max_depth,
                     bool left) {
//    nil_sprite.setSize({2 * kRadius * max_depth * 0.4f,
//                        2 * kRadius * max_depth * 0.4f});
    nil_text.setOrigin(nil_text.getGlobalBounds().width / 2,
                       nil_text.getGlobalBounds().height / 2);
    nil_text.setFont(font);
    sf::Vector2f base_pos = parent->GetPosition();
    float delta_x = pow(2, max_depth - depth) * kRadius;
//    delta_x *= max_depth * 0.4f;
    float delta_y = kVertDistance;
    delta_y *= max_depth * kVertIncrease;
    if (!left) {
        nil_sprite.setPosition(
            base_pos.x + delta_x,
            base_pos.y + delta_y);
    } else {
        nil_sprite.setPosition(
            base_pos.x - delta_x,
            base_pos.y + delta_y);
    }
    sf::VertexArray rib(sf::Lines);
    rib.append(base_pos);
    rib.append(nil_sprite.getPosition());
    rib[0].color = rib[1].color = kUIColor;
    window.draw(rib);

    nil_text.setOrigin(nil_text.getGlobalBounds().width / 2,
                       nil_text.getGlobalBounds().height / 2);
    nil_text.setPosition(nil_sprite.getPosition());
    while (
        !nil_sprite.getGlobalBounds().contains({nil_text.getGlobalBounds().left,
                                                nil_text.getGlobalBounds().top})
            ||
                !nil_sprite.getGlobalBounds().contains({nil_text.getGlobalBounds().left
                                                            + nil_text.getGlobalBounds().width,
                                                        nil_text.getGlobalBounds().top
                                                            + nil_text.getGlobalBounds().height})) {
        nil_text.setCharacterSize(nil_text.getCharacterSize() - 1);
        nil_text.setOrigin(nil_text.getGlobalBounds().width / 2,
                           nil_text.getGlobalBounds().height / 2);
        nil_text.setPosition(nil_sprite.getPosition());
    }
//    nil_text.setOrigin(nil_text.getGlobalBounds().width / 2,
//                       nil_text.getGlobalBounds().height / 2);
//    nil_text.setPosition(nil_sprite.getPosition());
//    while (nil_sprite.getGlobalBounds().contains({nil_text.getGlobalBounds().left,
//                                              nil_text.getGlobalBounds().top}) &&
//        nil_sprite.getGlobalBounds().contains({nil_text.getGlobalBounds().left
//                                               + nil_text.getGlobalBounds().width,
//                                           nil_text.getGlobalBounds().top
//                                               + nil_text.getGlobalBounds().height})) {
//        nil_text.setCharacterSize(nil_text.getCharacterSize() + 1);
//        nil_text.setOrigin(nil_text.getGlobalBounds().width / 2,
//                           nil_text.getGlobalBounds().height / 2);
//        nil_text.setPosition(nil_sprite.getPosition());
//    }
//    nil_text.setCharacterSize(nil_text.getCharacterSize() - 1);

    window.draw(nil_sprite);
    window.draw(nil_text);
}

void RBTree::Draw(sf::RenderWindow &window,
                  sf::Font &font,
                  sf::Vector2f mouse_pos,
                  RBTreeNode *p,
                  RBTreeNode *parent,
                  int depth,
                  int max_depth,
                  std::vector<sf::Text> &all_text,
                  std::vector<sf::CircleShape> &all_sprites) {
    if (!p) {
        return;
    }
    if (p->left)
        Draw(window,
             font,
             mouse_pos,
             p->left,
             p,
             depth + 1,
             max_depth,
             all_text,
             all_sprites);
    else
        DrawNil(window, font, p, depth + 1, max_depth, true);
    p->Draw(window,
            font,
            mouse_pos,
            parent,
            depth,
            max_depth,
            all_text,
            all_sprites);
    if (p->right)
        Draw(window,
             font,
             mouse_pos,
             p->right,
             p,
             depth + 1,
             max_depth,
             all_text,
             all_sprites);
    else
        DrawNil(window, font, p, depth + 1, max_depth, false);
}
