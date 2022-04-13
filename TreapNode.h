#ifndef TREESSFML__TREAPNODE_H_
#define TREESSFML__TREAPNODE_H_

#include <SFML/Graphics.hpp>

class TreapNode {
 private:
  sf::CircleShape sprite;
  sf::Text text;
  sf::Font font;
 public:
  int height = 1;
  int key, priority;
  TreapNode *left, *right;
  void SetPosition(sf::Vector2f pos);
  sf::Vector2f GetPosition();
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            TreapNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  TreapNode(int key);
};

#endif
