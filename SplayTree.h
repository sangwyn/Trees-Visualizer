#ifndef TREESSFML__SPLAYTREE_H_
#define TREESSFML__SPLAYTREE_H_

#include "SplayTreeNode.h"
#include <SFML/Graphics.hpp>

class SplayTree {
 private:
  SplayTreeNode *RightRotate(SplayTreeNode *&root);
  SplayTreeNode *LeftRotate(SplayTreeNode *&root);
 public:
  SplayTreeNode *start;
  int GetMaxDepth(SplayTreeNode *&p);
  SplayTreeNode *Splay(SplayTreeNode *&root, int key);
  SplayTreeNode *InsertNode(SplayTreeNode *&p, int key);
  SplayTreeNode *RemoveNode(SplayTreeNode *&p, int key);
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            SplayTreeNode *&p,
            SplayTreeNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  SplayTree();
};

#endif
