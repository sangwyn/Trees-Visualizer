#ifndef TREESSFML__GLOBALS_H_
#define TREESSFML__GLOBALS_H_

#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>

const sf::Color kBackgroundColor = sf::Color(57, 57, 57);
const sf::Color kUIColor = sf::Color::White;
const sf::Color kUnselectedColor = sf::Color(100, 100, 100);
const sf::Color kErrorColor = sf::Color::Red;

const sf::Color kHintTextColor = sf::Color(150, 150, 150);
const sf::Color kTextColor = sf::Color::Black;
const sf::Color kSelectedColor = sf::Color::Cyan;

const sf::Color kDefaultNodeColor = sf::Color::White;
const sf::Color kDefaultNodeTextColor = sf::Color::Black;
const sf::Color kBlackNodeColor = sf::Color::Black;
const sf::Color kBlackNodeTextColor = sf::Color::White;
const sf::Color kRedNodeColor = sf::Color::Red;
const sf::Color kRedNodeTextColor = sf::Color::White;

const float kRadius = 30.0f;
const float kVertDistance = 110.0f;
const float kHorDistance = 20.0f;

const float kDeltaPos = 70.0f;
extern sf::Vector2f root_pos;
const float kRootAngle = 90.0f;

const float kDeltaScale = 0.002f;
extern float global_scale;
extern int *selected_key;
extern bool couldnt_insert;

template <typename T>

std::string ToStr (const T & t) {
    std::ostringstream os;
    os << t;
    return os.str ();
}

int StrToInt(std::string str);

float DegToRad(float deg);

#endif
