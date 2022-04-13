#ifndef TREESSFML__RBTREENODE_H_
#define TREESSFML__RBTREENODE_H_

#include <SFML/Graphics.hpp>

class RBTreeNode {
 private:
 private:
  sf::CircleShape sprite;
  sf::Text text;
  sf::Font font;
 public:
  int data;
  bool red;
  RBTreeNode *left, *right, *parent;
  void SetPosition(sf::Vector2f pos);
  sf::Vector2f GetPosition();
  void SetColor(bool red);
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            RBTreeNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  RBTreeNode(int data = 0);
};

#endif
