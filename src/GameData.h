
#pragma once
#include "Placement.h"
#include <SFML/Graphics.hpp>
#include <array>

struct conveyor_texture {
    sf::Texture straight;
    sf::Texture bendr;
    sf::Texture bendl;
    sf::Texture splitter;
};

struct GameData {
    sf::RenderWindow &window;
    bool buildmode = false;
    sf::Font fonts[3];
    conveyor_texture conveyor;
    int score = 0;
    const float GRID_SIZE = 16.F;
    std::array<std::array<Placement *, 120>, 120> placements;
    sf::Vector2u mousePosGrid;
    sf::Vector2i mousePosScreen;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosChunk;
};
