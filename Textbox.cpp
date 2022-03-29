#include "Textbox.h"
#include "Globals.h"
#include <iostream>

Textbox::Textbox(const sf::Font &font,
                 sf::Vector2f pos,
                 sf::Vector2f size,
                 const sf::String &hint,
                 int max_lines) {
    rect.setSize(size);
    rect.setPosition(pos);
    this->font = font;
    text.setFont(font);
    hint_text.setFont(font);
    hint_text.setString(hint);
    text.setFillColor(kTextColor);
    hint_text.setFillColor(kHintTextColor);
    text.setPosition(rect.getPosition());
    hint_text.setPosition(rect.getPosition());
    this->max_lines = max_lines;
}

void Textbox::SetSelection(bool select) {
    is_selected = select;
}

bool Textbox::Selected() {
    return is_selected;
}

bool Textbox::MouseOver(sf::Vector2f mouse_pos) {
    return (mouse_pos.x >= rect.getPosition().x
        && mouse_pos.x <= rect.getPosition().x + rect.getSize().x &&
        mouse_pos.y >= rect.getPosition().y
        && mouse_pos.y <= rect.getPosition().y + rect.getSize().y);
}

float Textbox::GetWidth() {
    return rect.getGlobalBounds().width;
}

float Textbox::GetHeight() {
    return rect.getGlobalBounds().height;
}

sf::Vector2f Textbox::GetPos() {
    return rect.getPosition();
}

sf::String Textbox::GetString() {
    return text.getString();
}

void Textbox::SetString(const sf::String &str) {
    sf::String old_str = text.getString();
    float old_height = text.getGlobalBounds().height;
    text.setString(str);
    if (text.getGlobalBounds().width >= rect.getSize().x) {
        if (current_lines >= max_lines) {
            text.setString(old_str);
            return;
        }
        ++current_lines;
        sf::String new_str = str;
        new_str.insert(new_str.getSize() - 1, '\n');
        text.setString(new_str);
    } else if (old_height - text.getGlobalBounds().height > 10.0f) {
        --current_lines;
    }
}

void Textbox::Draw(sf::RenderWindow &window) {
    window.draw(rect);
    if (text.getString().isEmpty()) {
        window.draw(hint_text);
    }
    window.draw(text);
}
