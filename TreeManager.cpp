#include "TreeManager.h"
#include <iostream>
#include <vector>
#include "Globals.h"

void TreeManager::InsertNode(int key) {
    avl_tree.start = avl_tree.InsertNode(avl_tree.start, key);
    if (couldnt_insert)
        return;
    rb_tree.InsertNode(rb_tree.start, key);
    treap.InsertNode(treap.start, key);
    splay_tree.start = splay_tree.InsertNode(splay_tree.start, key);
    splay_tree.start = splay_tree.Splay(splay_tree.start, key);
}

void TreeManager::RemoveNode(int key) {
    avl_tree.start = avl_tree.RemoveNode(avl_tree.start, key);
    rb_tree.RemoveNode(rb_tree.start, key);
    treap.RemoveNode(treap.start, key);
    splay_tree.start = splay_tree.RemoveNode(splay_tree.start, key);
}

void TreeManager::SetTreeType(const std::string &tree_type) {
    current_tree_type = tree_type;
}

void TreeManager::DrawTree(sf::RenderWindow &window,
                           sf::Font &font,
                           sf::Vector2f mouse_pos) {
    if (selected_key)
        delete selected_key;
    selected_key = nullptr;
    std::vector<sf::Text> all_text;
    std::vector<sf::CircleShape> all_sprites;
    if (current_tree_type == "avl") {
        if (avl_tree.start == nullptr)
            return;
        avl_tree.Draw(window,
                      font,
                      mouse_pos,
                      avl_tree.start,
                      nullptr,
                      0,
                      avl_tree.start->height,
                      all_text,
                      all_sprites);
    } else if (current_tree_type == "rb") {
        if (rb_tree.start == nullptr)
            return;
        rb_tree.Draw(window,
                     font,
                     mouse_pos,
                     rb_tree.start,
                     nullptr,
                     0,
                     rb_tree.GetMaxDepth(rb_tree.start) + 1,
                     all_text,
                     all_sprites);
    } else if (current_tree_type == "treap") {
        if (treap.start == nullptr)
            return;
        treap.Draw(window,
                   font,
                   mouse_pos,
                   treap.start,
                   nullptr,
                   0,
                   treap.GetMaxDepth(treap.start),
                   all_text,
                   all_sprites);
    } else if (current_tree_type == "splay") {
        if (splay_tree.start == nullptr)
            return;
        splay_tree.Draw(window,
                        font,
                        mouse_pos,
                        splay_tree.start,
                        nullptr,
                        0,
                        splay_tree.GetMaxDepth(splay_tree.start),
                        all_text,
                        all_sprites);
    } else {
        std::cout << "NO SUCH TYPE EXISTS\n";
    }
    for (int i = 0; i < all_text.size(); ++i) {
        window.draw(all_sprites[i]);
        window.draw(all_text[i]);
    }
}

