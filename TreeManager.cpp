#include "TreeManager.h"
#include <iostream>

void TreeManager::SetTreeType(const std::string &tree_type) {
    current_tree_type = tree_type;
}

void TreeManager::DrawTree(sf::RenderWindow &window) {
    if (current_tree_type == "avl") {

    } else {
        std::cout << "NO SUCH TYPE EXISTS\n";
    }
}

