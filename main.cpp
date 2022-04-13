#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"
#include "Textbox.h"
#include "TreeManager.h"

int main() {
    srand(time(NULL));

    sf::RenderWindow
        window(sf::VideoMode(1600, 900),
               "Tree Garden", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("Assets/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::View view(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2),
                  sf::Vector2f(window.getSize().x, window.getSize().y));
//    window.setView(view);

    sf::Font font;
    font.loadFromFile("Assets/Fonts/JetBrainsMono-Medium.ttf");
    std::vector<Button *> buttons;
    buttons.push_back(new Button({10, 850},
                                 font,
                                 "AVL Tree"));
    buttons.push_back(new Button({buttons[0]->GetPos().x
                                      + buttons[0]->GetWidth() + 10.0f, 850},
                                 font,
                                 "RB Tree"));
    buttons.push_back(new Button({buttons[1]->GetPos().x
                                      + buttons[1]->GetWidth() + 10.0f, 850},
                                 font,
                                 "Treap"));
    buttons.push_back(new Button({buttons[2]->GetPos().x
                                      + buttons[2]->GetWidth() + 10.0f, 850},
                                 font,
                                 "Splay tree"));
    buttons.push_back(new Button({1000, 218},
                                 font,
                                 "Add new nodes"));
    buttons.push_back(new Button({1000, 10},
                                 font,
                                 "Add random keys"));
    buttons.push_back(new Button({1000, 485.0f},
                                 font,
                                 "Delete nodes"));
    buttons[0]->SetTextSelection(true);
    std::vector<Textbox *> tboxes;
    tboxes.push_back(new Textbox(font, {1050, 62}, {500, 40}, "Node count"));
    tboxes.push_back(new Textbox(font,
                                 {1050, 270},
                                 {500, 200},
                                 "Node keys (1 2 3...)",
                                 5));
    tboxes.push_back(new Textbox(font,
                                 {1050, 530},
                                 {500, 200},
                                 "Node keys (1 2 3...)",
                                 5));
    tboxes.push_back(new Textbox(font,
                                 {1050, 112},
                                 {500, 40},
                                 "Min (-1000 by default)"));
    tboxes.push_back(new Textbox(font,
                                 {1050, 162},
                                 {500, 40},
                                 "Max (1000 by default)"));

    sf::Text error_text;
    error_text.setFont(font);
    error_text.setFillColor(kErrorColor);
    error_text.setPosition({1050, 750});
//    error_text.setString("BRUH ERROR OCCURED");


    TreeManager garden;
//    for (int i = 1; i <= 10; ++i) {
//        garden.InsertNode(i);
//    }

    sf::Vector2f velocity = {0.0f, 0.0f};
    bool typing_text = false;
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
                            if ((i == 0 || i == 1 || i == 2 || i == 3 || i == 4)
                                && !std::isdigit(event.text.unicode)
                                && event.text.unicode != ' '
                                && event.text.unicode != '-'
                                || (i == 0 || i == 3 || i == 4)
                                    && event.text.unicode == ' '
                                || i == 0 && event.text.unicode == '-')
                                break;
                            tboxes[i]->SetString(
                                tboxes[i]->GetString() + event.text.unicode);
                            break;
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    for (int i = 0; i < tboxes.size(); ++i) {
                        if (tboxes[i]->Selected()) {
                            tboxes[i]->SetString(tboxes[i]->GetString().substring(
                                0,
                                tboxes[i]->GetString().getSize() - 1));
                            break;
                        }
                    }
                }
                if (!typing_text) {
                    if (event.key.code == sf::Keyboard::Dash) {
//                        view.setCenter((sf::Vector2f)sf::Mouse::getPosition(window));
//                        view.setCenter(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()));
                        view.zoom(1.1f);
//                        view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
                        global_scale *= 1.1f;
                    }
                    if (event.key.code == sf::Keyboard::Equal) {
//                        view.setCenter((sf::Vector2f)sf::Mouse::getPosition(window));
//                        view.setCenter(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()));
                        view.zoom(0.9f);
//                        view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
                        global_scale *= 0.9f;
                    }
                    velocity.x = velocity.y = 0;
                    if (event.key.code == sf::Keyboard::Left) {
                        velocity.x = kDeltaPos;
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        velocity.x = -kDeltaPos;
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        velocity.y = kDeltaPos;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        velocity.y = -kDeltaPos;
                    }
                    view.move(-velocity * global_scale);
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Dash
                    || event.key.code == sf::Keyboard::Equal) {
                }
                if (event.key.code == sf::Keyboard::Left
                    || event.key.code == sf::Keyboard::Right) {
                    velocity.x = 0;
                }
                if (event.key.code == sf::Keyboard::Up
                    || event.key.code == sf::Keyboard::Down) {
                    velocity.y = 0;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (selected_key) {
                    garden.RemoveNode(*selected_key);
                    delete selected_key;
                    selected_key = nullptr;
                }
                for (int i = 0; i < buttons.size(); ++i) {
                    if (buttons[i]->Selected()) {
                        error_text.setString("");
                        if (i == 0) {
                            garden.SetTreeType("avl");
                            buttons[0]->SetTextSelection(true);
                            buttons[1]->SetTextSelection(false);
                            buttons[2]->SetTextSelection(false);
                            buttons[3]->SetTextSelection(false);
                        } else if (i == 1) {
                            garden.SetTreeType("rb");
                            buttons[0]->SetTextSelection(false);
                            buttons[1]->SetTextSelection(true);
                            buttons[2]->SetTextSelection(false);
                            buttons[3]->SetTextSelection(false);
                        } else if (i == 2) {
                            garden.SetTreeType("treap");
                            buttons[0]->SetTextSelection(false);
                            buttons[1]->SetTextSelection(false);
                            buttons[2]->SetTextSelection(true);
                            buttons[3]->SetTextSelection(false);
                        } else if (i == 3) {
                            garden.SetTreeType("splay");
                            buttons[0]->SetTextSelection(false);
                            buttons[1]->SetTextSelection(false);
                            buttons[2]->SetTextSelection(false);
                            buttons[3]->SetTextSelection(true);
                        } else if (i == 4) {
                            try {
//                                sf::String
//                                    node_count_str = tboxes[0]->GetString();
                                sf::String keys_str = tboxes[1]->GetString();
//                                int node_count = StrToInt(node_count_str);
                                if (keys_str.isEmpty())
                                    throw keys_str;
//                                try {
                                try {
                                    std::vector<int> keys;
                                    sf::String num_str;
                                    int sign = 1;
                                    for (auto c: keys_str) {
                                        if (std::isdigit(c)) {
                                            num_str += c;
                                        } else if (c == '-') {
                                            if (!num_str.isEmpty()
                                                || sign == -1)
                                                throw c;
                                            sign = -1;
                                        } else if (!num_str.isEmpty()) {
                                            keys.push_back(
                                                sign * StrToInt(num_str));
                                            num_str = "";
                                            sign = 1;
                                        }
                                    }
                                    if (!num_str.isEmpty()) {
                                        keys.push_back(
                                            sign * StrToInt(num_str));
                                    }
//                                        if (keys.size() != node_count)
//                                            throw node_count;
                                    for (auto k: keys) {
                                        try {
                                            couldnt_insert = false;
                                            garden.InsertNode(k);
                                            if (couldnt_insert)
                                                throw k;
                                        }
                                        catch (int key) {
                                            error_text.setString(
                                                "Node with this key \nalready exists: "
                                                    + ToStr(key));
                                        }
                                    }
                                    tboxes[1]->SetString("");
                                }
                                catch (sf::Uint32 c) {
                                    sf::String error_str =
                                        "Unexpected symbol in number: ";
                                    error_str += c;
                                    error_text.setString(error_str);
                                }
//                                }
//                                catch (int c) {
//                                    error_text.setString(
//                                        "Node count and input keys \ncount don't match.");
//                                }
                            }
                            catch (sf::String s) {
                                error_text.setString("No keys to input.");
                            }
                        } else if (i == 5) {
                            try {
                                try {
                                    sf::String
                                        node_count_str = tboxes[0]->GetString();
                                    sf::String
                                        keys_str = tboxes[1]->GetString();
                                    int node_count = StrToInt(node_count_str);
                                    if (node_count_str.isEmpty())
                                        throw node_count_str;

                                    int rand_min =
                                        (tboxes[3]->GetString().isEmpty()
                                         ? -1000
                                         : StrToInt(
                                                tboxes[3]->GetString()));
                                    int rand_max =
                                        (tboxes[4]->GetString().isEmpty() ? 1000
                                                                          : StrToInt(
                                                tboxes[4]->GetString()));
                                    if (rand_max - rand_min < node_count)
                                        throw rand_min;

                                    int i = 0;
                                    int it_count = 0;
                                    for (; i < node_count; ++i) {
                                        try {
                                            couldnt_insert = false;
                                            garden.InsertNode(
                                                std::rand() % (rand_max - rand_min) + rand_min);
                                            if (couldnt_insert)
                                                throw i;
                                            it_count = 0;
                                        }
                                        catch (int key) {
                                            ++it_count;
                                            --i;
                                            if (it_count > 2000) {
                                                error_text.setString("All keys in random range \nalready exist.");
                                                break;
                                            }
                                        }
                                    }
                                }
                                catch (int a) {
                                    error_text.setString("Invalid random borders.");
                                }
                            }
                            catch (sf::String s) {
                                error_text.setString("Node count required.");
                            }
                        } else if (i == 6) {
                            try {
                                try {
                                    sf::String
                                        keys_str = tboxes[2]->GetString();
                                    if (keys_str.isEmpty())
                                        throw keys_str;
                                    std::vector<int> keys;
                                    sf::String num_str;
                                    int sign = 1;
                                    for (auto c: keys_str) {
                                        if (std::isdigit(c)) {
                                            num_str += c;
                                        } else if (c == '-') {
                                            if (!num_str.isEmpty()
                                                || sign == -1)
                                                throw c;
                                            sign = -1;
                                        } else if (!num_str.isEmpty()) {
                                            keys.push_back(
                                                sign * StrToInt(num_str));
                                            num_str = "";
                                            sign = 1;
                                        }
                                    }
                                    if (!num_str.isEmpty()) {
                                        keys.push_back(
                                            sign * StrToInt(num_str));
                                    }
                                    for (auto k: keys) {
                                        try {
                                            garden.RemoveNode(k);
                                        } catch (int key) {
                                            error_text.setString(
                                                "No node with such \nkey exists: "
                                                    + ToStr(key));
                                        }
                                    }
                                    tboxes[2]->SetString("");
                                }
                                catch (sf::Uint32 c) {
                                    sf::String error_str =
                                        "Unexpected symbol in number: ";
                                    error_str += c;
                                    error_text.setString(error_str);
                                }
                            }
                            catch (sf::String s) {
                                error_text.setString("No keys to delete.");
                            }
                        }
                        break;
                    }
                }
                typing_text = false;
                for (int i = 0; i < tboxes.size(); ++i) {
                    if (tboxes[i]->MouseOver((sf::Vector2f) sf::Mouse::getPosition(
                        window))) {
                        tboxes[i]->SetSelection(true);
                        typing_text = true;
                        velocity = {0.0f, 0.0f};
                    } else {
                        tboxes[i]->SetSelection(false);
                    }
                }
            }
        }
//        root_pos += velocity;
//        view.move(velocity);

//        if (global_scale + scale_changing > 0)
//            global_scale += scale_changing;

//        if (scale_changing > 0)
//            view.zoom(1.1f);
//        else
//            view.zoom(0.1f);

        for (auto b: buttons) {
            b->SetSelection(b->MouseOver((sf::Vector2f) sf::Mouse::getPosition(
                window)));
        }

        window.clear(kBackgroundColor);
        window.setView(view);
        garden.DrawTree(window,
                        font,
                        (sf::Vector2f) window.mapPixelToCoords(sf::Mouse::getPosition(
                            window), window.getView()));
        window.setView(window.getDefaultView());

        for (auto b: buttons) {
            b->Draw(window);
        }
        for (auto b: tboxes) {
            b->Draw(window);
        }
        window.draw(error_text);

        window.display();
    }
    return 0;
}
