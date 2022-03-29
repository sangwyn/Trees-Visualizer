#ifndef TREESSFML__AVLTREENODE_H_
#define TREESSFML__AVLTREENODE_H_

#include <SFML/Graphics.hpp>

class AVLTreeNode {
 private:
  sf::CircleShape sprite;
  sf::Text text;
  sf::Font font;
 public:
  int data, height;
  AVLTreeNode *left, *right;
  AVLTreeNode(int data = 0);
  void SetPosition(sf::Vector2f pos);
  void Draw(sf::RenderWindow &window);
};

#endif
