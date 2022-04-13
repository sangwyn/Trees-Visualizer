#ifndef TREESSFML__AVLTREENODE_H_
#define TREESSFML__AVLTREENODE_H_

#include <SFML/Graphics.hpp>
#include <vector>

class AVLTreeNode {
 private:
//  sf::RectangleShape sprite;
  sf::CircleShape sprite;
  sf::Text text;
  float start_char_size;
 public:
  int data, height;
  AVLTreeNode *left, *right;
  void SetPosition(sf::Vector2f pos);
  sf::Vector2f GetPosition();
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            AVLTreeNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  AVLTreeNode(int data = 0);
  ~AVLTreeNode();
};

#endif
