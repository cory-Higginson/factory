#include <SFML/Graphics.hpp>
#pragma once


class Placement {
public:
    Placement(sf::Color color, sf::Vector2u pos, sf::Vector2i grid);
    Placement(const sf::Texture& texture, sf::Vector2u vector_2 = sf::Vector2u(0, 0), float rot = 0);
    Placement(const sf::Texture& texture, int alpha);
    sf::Sprite sprite;

private:
    sf::Texture tec;
};
