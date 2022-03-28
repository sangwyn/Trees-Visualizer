#ifndef TREESSFML__AVLTREENODE_H_
#define TREESSFML__AVLTREENODE_H_

class AVLTreeNode {
 public:
  int data, height;
  AVLTreeNode *left, *right;
  AVLTreeNode();
  AVLTreeNode(int data);
};

#endif
