#include "Button.h"
#include "Globals.h"

Button::Button(sf::Vector2f pos,
               sf::Font font,
               sf::String text) {
    this->font = font;

    rect.setPosition(pos);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(2);

    text_inside.setFont(this->font);
    text_inside.setPosition(pos.x + 5.0f, pos.y);
    text_inside.setFillColor(kUIColor);
    text_inside.setString(text);
    rect.setSize({text_inside.getGlobalBounds().width + 15.0f,
                  text_inside.getGlobalBounds().height + 15.0f});
}

void Button::SetSelection(bool select) {
    is_selected = select;
}

bool Button::Selected() {
    return is_selected;
}

bool Button::MouseOver(sf::Vector2f mouse_pos) {
    return (mouse_pos.x >= rect.getPosition().x
        && mouse_pos.x <= rect.getPosition().x + rect.getSize().x &&
        mouse_pos.y >= rect.getPosition().y
        && mouse_pos.y <= rect.getPosition().y + rect.getSize().y);
}

void Button::Draw(sf::RenderWindow &window) {
    if (is_selected)
        rect.setOutlineColor(kUIColor);
    else
        rect.setOutlineColor(kUnselectedColor);
    window.draw(rect);
    window.draw(text_inside);
}

float Button::GetWidth() {
    return rect.getGlobalBounds().width;
}

float Button::GetHeight() {
    return rect.getGlobalBounds().height;
}

sf::Vector2f Button::GetPos() {
    return rect.getPosition();
}
