
#include "Placement.h"

Placement::Placement(sf::Color color, sf::Vector2u pos, sf::Vector2i grid)
{
    sf::Texture tex;
    tex.create(1, 1);
    sprite.setTexture(tex);
    sprite.setScale(16, 16);
    sprite.setColor(color);
    sprite.setPosition(pos.x * 16, pos.y * 16);
}

Placement::Placement(const sf::Texture& texture, sf::Vector2u pos, float rot)
{
    //tec.loadFromFile("Data/debug_sprite_16.png");
    sprite.setTexture(texture);
    sprite.setRotation(rot);
    switch (int(rot))
    {
        case (180):
            pos.y += 1;
        case (90):
            pos.x += 1;
            break;
        case (270):
            pos.y += 1;
            break;
        case (0):
            break;
    }
    sprite.setPosition(pos.x * 16, pos.y * 16);
}
Placement::Placement(const sf::Texture& texture, int alpha)
{
    //tec.loadFromFile("Data/debug_sprite_16.png");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 255, 255, alpha));
}
