#include "GameData.h"
#include "Placement.h"
#include <SFML/Graphics.hpp>
#pragma once

class Builder {
public:
    explicit Builder(GameData &game_data);
    void mouseInputControls(sf::Event event);
    void keyInputControls(sf::Event event);
    void render();
    void update(float dt);

private:
    Placement *build_preview = nullptr;// = placement(data.conveyor_texture.straight,sf::Vector2u(0,0),0);
    sf::RectangleShape del_view;
    GameData &data;
    void previewUpdate();
    bool mouse_left_held = false;
    bool mouse_right_held = false;
    void placement();
    void removement();
};
