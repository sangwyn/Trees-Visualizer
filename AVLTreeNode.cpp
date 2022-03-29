#include "AVLTreeNode.h"
#include "Globals.h"

AVLTreeNode::AVLTreeNode(int data)
{
    this->data = data;
    height = 0;
    left = right = nullptr;
    sprite.setFillColor(kBlackNodeColor);
    font.loadFromFile("Assets/Fonts/JetBrainsMono-Medium.ttf");
    text.setFillColor(kBlackNodeTextColor);
}

void AVLTreeNode::SetPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void AVLTreeNode::Draw(sf::RenderWindow &window) {
    sprite.setRadius(kRadius * global_scale);
    window.draw(sprite);

    text.setString(ToStr(data));
}