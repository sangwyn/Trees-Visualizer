#ifndef TREESSFML__TREEMANAGER_H_
#define TREESSFML__TREEMANAGER_H_

#include "AVLTree.h"
#include "RBTree.h"
#include "Treap.h"
#include "SplayTree.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class TreeManager {
 private:
  std::vector<int> keys;
  std::string current_tree_type = "avl";
  AVLTree avl_tree;
  RBTree rb_tree;
  Treap treap;
  SplayTree splay_tree;
 public:
  void InsertNode(int key);
  void RemoveNode(int key);
  void SetTreeType(const std::string &tree_type);
  void DrawTree(sf::RenderWindow &window, sf::Font &font, sf::Vector2f mouse_pos);
};

#endif
