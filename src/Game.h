
#pragma once
#include "Builder.h"
#include "Conveyorlogic.h"
#include "Objects/Chunk.h"
#include "Placement.h"
#include "State.h"
#include <list>
class Game : public State {
public:
    Game(GameData &game_data, Builder buildvision);
    bool init() override;
    void update(float dt) override;
    void render() override;
    void mouseClicked(sf::Event event) override;
    void keyPressed(sf::Event event) override;
    void keyReleased(sf::Event event) override;
    void mouseMoved(sf::Event event) override;
    void resize(sf::Event event) override;

private:
    Chunk *current_chunk;
    sf::Font font;
    sf::Text info;
    Builder buildvision;
    sf::View defaultview;
    sf::View cam;
    bool moveup;
    bool movedown;
    conveyorlogic conveyor_logic;
};
