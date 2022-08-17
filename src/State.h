
#pragma once
#include "GameData.h"
#include "Placement.h"
#include "list"
#include <SFML/Graphics.hpp>

//struct GameData
//{
//};

class State {
public:
    explicit State(GameData &game_data) : data(game_data){};
    virtual bool init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void mouseClicked(sf::Event event) = 0;
    virtual void keyPressed(sf::Event event) = 0;
    virtual void keyReleased(sf::Event event) = 0;
    virtual void mouseMoved(sf::Event event) = 0;
    virtual void resize(sf::Event event) = 0;

protected:
    GameData &data;
};