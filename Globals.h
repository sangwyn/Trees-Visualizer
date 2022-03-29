#ifndef TREESSFML__GLOBALS_H_
#define TREESSFML__GLOBALS_H_

#include <SFML/Graphics.hpp>
#include <sstream>

const sf::Color kBackgroundColor = sf::Color(57, 57, 57);
const sf::Color kUIColor = sf::Color::White;
const sf::Color kUnselectedColor = sf::Color(100, 100, 100);
const sf::Color kErrorColor = sf::Color::Red;

const sf::Color kHintTextColor = sf::Color(150, 150, 150);
const sf::Color kTextColor = sf::Color::Black;

const sf::Color kBlackNodeColor = sf::Color::White;
const sf::Color kBlackNodeTextColor = sf::Color::Black;
const sf::Color kRedNodeColor = sf::Color::Red;
const sf::Color kRedNodeTextColor = sf::Color::White;

const float kRadius = 10.0f;
const float kVertDistance = 20.0f;
const float kHorDistance = 20.0f;

extern float global_scale;

template <typename T>

std::string ToStr (const T & t) {
    std::ostringstream os;
    os << t;
    return os.str ();
}

#endif
