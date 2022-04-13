#ifndef TREESSFML__TEXTBOX_H_
#define TREESSFML__TEXTBOX_H_

#include <SFML/Graphics.hpp>

class Textbox {
 private:
  sf::RectangleShape rect;
  sf::Font font;
  sf::Text text;
  sf::Text hint_text;
  bool is_selected = false;
  int max_lines;
  int current_lines = 1;
  sf::Vector2f pos;
  sf::Vector2f size;
  float text_size = 30;
 public:
  Textbox(const sf::Font &font,
          sf::Vector2f pos,
          sf::Vector2f size,
          const sf::String &hint,
          int max_lines = 1);

  bool MouseOver(sf::Vector2f mouse_pos);
  void SetSelection(bool select);
  bool Selected();

  float GetWidth();
  float GetHeight();
  sf::Vector2f GetPos();
  sf::String GetString();
  void SetString(const sf::String &str);
  void PopBack();

  void Draw(sf::RenderWindow &window);
};

#endif
