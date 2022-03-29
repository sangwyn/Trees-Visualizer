#ifndef TREESSFML__TREEMANAGER_H_
#define TREESSFML__TREEMANAGER_H_

#include "AVLTree.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class TreeManager {
 private:
  std::vector<int> keys;
  AVLTree avl_tree;
  std::string current_tree_type = "avl";
 public:
  void SetTreeType(const std::string &tree_type);
  void DrawTree(sf::RenderWindow &window);
};

#endif
