#ifndef TREESSFML__BUTTON_H_
#define TREESSFML__BUTTON_H_

#include <SFML/Graphics.hpp>

class Button {
 private:
  sf::Font font;
  sf::RectangleShape rect;
  sf::Text text_inside;
  bool is_selected = false;
  bool text_selected = false;
  sf::Vector2f pos;
 public:
  Button(sf::Vector2f pos, sf::Font font, sf::String text);
  bool MouseOver(sf::Vector2f mouse_pos);
  void SetSelection(bool select);
  bool Selected();
  void Draw(sf::RenderWindow &window);
  float GetWidth();
  float GetHeight();
  void SetTextSelection(bool select);
  sf::Vector2f GetPos();
  void SetPos(sf::Vector2f pos);
};

#endif
