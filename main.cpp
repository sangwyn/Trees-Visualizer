#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"
#include "Textbox.h"

int main() {
    sf::RenderWindow
        window(sf::VideoMode(1600, 900),
               "Tree Garden", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("Assets/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Font font;
    font.loadFromFile("Assets/Fonts/JetBrainsMono-Medium.ttf");
    std::vector<Button *> buttons;
    buttons.push_back(new Button({10, 850},
                                 font,
                                 "AVL Tree"));
    buttons.push_back(new Button({buttons[0]->GetPos().x + buttons[0]->GetWidth() + 10.0f, 850},
                                 font,
                                 "RB Tree"));
    buttons.push_back(new Button({buttons[1]->GetPos().x + buttons[1]->GetWidth() + 10.0f, 850},
                                 font,
                                 "Treap"));
    buttons.push_back(new Button({buttons[2]->GetPos().x + buttons[2]->GetWidth() + 10.0f, 850},
                                 font,
                                 "Splay tree"));
    buttons.push_back(new Button({1300, 10},
                                 font,
                                 "Add new node"));
    buttons.push_back(new Button({1300, buttons[4]->GetPos().y + buttons[4]->GetHeight() + 10.0f},
                                 font,
                                 "Delete node"));
    std::vector<Textbox *> tboxes;
    tboxes.push_back(new Textbox(font, {100, 100}, {300, 40}, "Debug text"));
    tboxes.push_back(new Textbox(font, {100, 200}, {400, 80}, "Debug text 2", 2));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode != 8
                    && event.text.unicode != 13 && event.text.unicode != 9) {
                    for (int i = 0; i < tboxes.size(); ++i) {
                        if (tboxes[i]->Selected()) {
                            tboxes[i]->SetString(tboxes[i]->GetString() + event.text.unicode);
                            break;
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    for (int i = 0; i < tboxes.size(); ++i) {
                        if (tboxes[i]->Selected()) {
                            tboxes[i]->SetString(tboxes[i]->GetString().substring(0, tboxes[i]->GetString().getSize() - 1));
                            break;
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                for (int i = 0; i < buttons.size(); ++i) {
                    if (buttons[i]->Selected()) {
                        if (i == 0) {

                        }
                        break;
                    }
                }
                for (int i = 0; i < tboxes.size(); ++i) {
                    if (tboxes[i]->MouseOver((sf::Vector2f)sf::Mouse::getPosition(
                        window))) {
                        tboxes[i]->SetSelection(true);
                    } else {
                        tboxes[i]->SetSelection(false);
                    }
                }
            }
        }

        window.clear(kBackgroundColor);

        for (auto b: buttons) {
            b->SetSelection(b->MouseOver((sf::Vector2f) sf::Mouse::getPosition(
                window)));
            b->Draw(window);
        }
        for (auto b: tboxes) {
            b->Draw(window);
        }

        window.display();
    }
    return 0;
}
