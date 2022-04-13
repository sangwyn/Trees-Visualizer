#ifndef TREESSFML__AVLTREE_H_
#define TREESSFML__AVLTREE_H_

#include "AVLTreeNode.h"
#include <SFML/Graphics.hpp>

class AVLTree {
 private:
  int GetHeight(AVLTreeNode *&p);
  void RecalcHeight(AVLTreeNode *&p);
  int BalanceFactor(AVLTreeNode *&p);
  AVLTreeNode *RotateRight(AVLTreeNode *&p);
  AVLTreeNode *RotateLeft(AVLTreeNode *&p);
  AVLTreeNode *Balance(AVLTreeNode *&p);
  AVLTreeNode *FindMin(AVLTreeNode *&p);
  AVLTreeNode *RemoveMin(AVLTreeNode *&p);
  AVLTreeNode *FindMax(AVLTreeNode *&p);
  AVLTreeNode *RemoveMax(AVLTreeNode *&p);
 public:
  AVLTreeNode *start;
  AVLTreeNode *InsertNode(AVLTreeNode *&p, int key);
  AVLTreeNode *RemoveNode(AVLTreeNode *&p, int key);
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            AVLTreeNode *&p,
            AVLTreeNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  AVLTree();
};

#endif
