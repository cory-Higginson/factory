
#pragma once
#include "Objects/Chunk.h"
#include "Placement.h"
#include <SFML/Graphics.hpp>
#include <array>

struct conveyor_texture
{
    sf::Texture straight;
    sf::Texture bendr;
    sf::Texture bendl;
    sf::Texture splitter;
};

struct blocks_texture
{
    sf::Texture stone;
};

struct GameData
{
    sf::RenderWindow& window;
    bool buildmode = false;
    sf::Font fonts[3];
    conveyor_texture conveyor_texture;
    blocks_texture blocks_texture;
    int score = 0;
    const float GRID_SIZE = 16.F;
    sf::Vector2u mousePosGrid;
    sf::Vector2i mousePosScreen;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosChunk;
    std::array<Chunk*, 4> rendered_chunks = {nullptr, nullptr, nullptr, nullptr};
};
