#ifndef TREESSFML__SPLAYTREENODE_H_
#define TREESSFML__SPLAYTREENODE_H_

#include <SFML/Graphics.hpp>

class SplayTreeNode {
 private:
  sf::CircleShape sprite;
  sf::Text text;
 public:
  int data;
  SplayTreeNode *left, *right;
  sf::Vector2f GetPosition();
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            SplayTreeNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  SplayTreeNode(int data = 0);
};

#endif
