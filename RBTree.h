#ifndef TREESSFML__RBTREE_H_
#define TREESSFML__RBTREE_H_

#include "RBTreeNode.h"

class RBTree {
 private:
  sf::RectangleShape nil_sprite;
  sf::Text nil_text;
  void FixInsert(RBTreeNode *&root, RBTreeNode *&p);
  void FixDelete(RBTreeNode *&root, RBTreeNode *&p);
  void RightRotate(RBTreeNode *&root, RBTreeNode *&p);
  void LeftRotate(RBTreeNode *&root, RBTreeNode *&p);
 public:
  RBTreeNode *start;
  int GetMaxDepth(RBTreeNode *&p);
  RBTreeNode *BSTInsert(RBTreeNode *&root, RBTreeNode *&p);
  void InsertNode(RBTreeNode *&root, int key);
  RBTreeNode *FindMin(RBTreeNode *&p);
  RBTreeNode *FindMax(RBTreeNode *&p);
  void RemoveNode(RBTreeNode *&root, int key);
  void DrawNil(sf::RenderWindow &window,
               sf::Font &font,
               RBTreeNode *&parent,
               int depth,
               int max_depth,
               bool left);
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            RBTreeNode *p,
            RBTreeNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  RBTree();
};

#endif
