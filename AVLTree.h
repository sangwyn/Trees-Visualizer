#ifndef TREESSFML__AVLTREE_H_
#define TREESSFML__AVLTREE_H_

#include "AVLTreeNode.h"

class AVLTree {
 private:
  void SmallTurnRight(AVLTreeNode *&a);
  void BigTurnRight(AVLTreeNode *&a);
  void SmallTurnLeft(AVLTreeNode *&a);
  void BigTurnLeft(AVLTreeNode *&a);
  void Balance(AVLTreeNode *&a);
 public:
  AVLTreeNode *start;
  AVLTreeNode *FindMin(AVLTreeNode *&p);
  AVLTreeNode *FindMax(AVLTreeNode *&p);
  void InsertNode(AVLTreeNode *&p, int node);
  void RemoveNode(AVLTreeNode *&p, int node);
  AVLTree();
};

#endif
