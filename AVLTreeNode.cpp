#include "AVLTreeNode.h"
#include "Globals.h"
#include <cmath>
#include <iostream>
#include <algorithm>

AVLTreeNode::AVLTreeNode(int data) {
    this->data = data;
    height = 1;
    left = right = nullptr;
    sprite.setFillColor(kDefaultNodeColor);
    text.setFillColor(kDefaultNodeTextColor);

//    sprite.setSize({kRadius * 2, kRadius * 2});
//    sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
    sprite.setRadius(kRadius);
    sprite.setOrigin({kRadius, kRadius});

    sprite.setOutlineColor(kUnselectedColor);
    sprite.setOutlineThickness(2);

    text.setString(ToStr(data));
    text.setOrigin(text.getGlobalBounds().width / 2,
                   text.getGlobalBounds().height + 1);
    text.setPosition(sprite.getPosition());
    while (!sprite.getGlobalBounds().contains({text.getGlobalBounds().left,
                                               text.getGlobalBounds().top}) ||
        !sprite.getGlobalBounds().contains({text.getGlobalBounds().left
                                                + text.getGlobalBounds().width,
                                            text.getGlobalBounds().top
                                                + text.getGlobalBounds().height})) {
        text.setCharacterSize(text.getCharacterSize() - 1);
        text.setOrigin(text.getGlobalBounds().width / 2,
                       text.getGlobalBounds().height + 1);
        text.setPosition(sprite.getPosition());
    }
}

void AVLTreeNode::SetPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

sf::Vector2f AVLTreeNode::GetPosition() {
    return sprite.getPosition();
}

void AVLTreeNode::Draw(sf::RenderWindow &window,
                       sf::Font &font,
                       sf::Vector2f mouse_pos,
                       AVLTreeNode *parent,
                       int depth,
                       int max_depth,
                       std::vector<sf::Text> &all_text,
                       std::vector<sf::CircleShape> &all_sprites) {
//    sprite.setRadius(kRadius * max_depth * 0.4f);
    sprite.setOrigin({sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2});
    text.setString(ToStr(data));
    text.setFont(font);
    if (sprite.getGlobalBounds().contains(mouse_pos) && !selected_key) {
        sprite.setOutlineColor(kSelectedColor);
        selected_key = new int;
        *selected_key = data;
    } else {
        sprite.setOutlineColor(kUnselectedColor);
    }

    sprite.setPosition(root_pos);
    if (parent) {
        sf::Vector2f base_pos = parent->GetPosition();
        float delta_x = pow(2, max_depth - depth) * kRadius;
//        delta_x *= max_depth * 0.4f;
        float delta_y = kVertDistance * max_depth * kVertIncrease;
        if (this == parent->right) {
            sprite.setPosition(
                base_pos.x + delta_x,
                base_pos.y + delta_y);
        } else {
            sprite.setPosition(
                base_pos.x - delta_x,
                base_pos.y + delta_y);
        }
        sf::VertexArray rib(sf::Lines);
        rib.append(base_pos);
        rib.append(sprite.getPosition());
        rib[0].color = rib[1].color = kUIColor;
        window.draw(rib);
    }
    text.setOrigin(text.getGlobalBounds().width / 2,
                   text.getGlobalBounds().height + 1);
    text.setPosition(sprite.getPosition());
    while (!sprite.getGlobalBounds().contains({text.getGlobalBounds().left,
                                               text.getGlobalBounds().top}) ||
        !sprite.getGlobalBounds().contains({text.getGlobalBounds().left
                                                + text.getGlobalBounds().width,
                                            text.getGlobalBounds().top
                                                + text.getGlobalBounds().height})) {
        text.setCharacterSize(text.getCharacterSize() - 1);
        text.setOrigin(text.getGlobalBounds().width / 2,
                       text.getGlobalBounds().height + 1);
        text.setPosition(sprite.getPosition());
    }
//    while (sprite.getGlobalBounds().contains({text.getGlobalBounds().left,
//                                               text.getGlobalBounds().top}) &&
//        sprite.getGlobalBounds().contains({text.getGlobalBounds().left
//                                                + text.getGlobalBounds().width,
//                                            text.getGlobalBounds().top
//                                                + text.getGlobalBounds().height})) {
//        text.setCharacterSize(text.getCharacterSize() + 1);
//        text.setOrigin(text.getGlobalBounds().width / 2,
//                       text.getGlobalBounds().height + 1);
//        text.setPosition(sprite.getPosition());
//    }
//    text.setCharacterSize(text.getCharacterSize() - 1);

    all_sprites.push_back(sprite);
    all_text.push_back(text);
}

AVLTreeNode::~AVLTreeNode() {
    data = height = 0;
    left = right = nullptr;
//    delete this;
}