#include "AVLTreeNode.h"

AVLTreeNode::AVLTreeNode()
{
    data = height = 0;
    left = right = nullptr;
}

AVLTreeNode::AVLTreeNode(int data)
{
    this->data = data;
    height = 0;
    left = right = nullptr;
}
