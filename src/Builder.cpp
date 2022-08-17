
#include "Builder.h"
#include "../HelperFunctions/StaticFunctions.h"
#include "GameData.h"
#include <iostream>


Builder::Builder(GameData &game_data) : data(game_data) {
    build_preview = nullptr;
    build_preview = new Placement(data.conveyor.straight, 128);
    del_view.setSize(sf::Vector2f(16, 16));
    del_view.setFillColor(sf::Color(255, 0, 0, 128));
}

void Builder::mouseInputControls(sf::Event event) {
    if (event.type == sf::Event::EventType::MouseButtonPressed) {
        switch (event.mouseButton.button) {
            case (sf::Mouse::Button::Left):
                mouse_left_held = true;
                break;
            case (sf::Mouse::Button::Right):
                del_view.setPosition(data.mousePosGrid.x * 16, data.mousePosGrid.y * 16);
                mouse_right_held = true;
                break;
        }
    }
    if (event.type == sf::Event::EventType::MouseButtonReleased) {
        switch (event.mouseButton.button) {
            case (sf::Mouse::Button::Left):
                mouse_left_held = false;
                break;
            case (sf::Mouse::Button::Right):
                mouse_right_held = false;
                break;
        }
    }
}
void Builder::removement() {
    if (data.placements[data.mousePosGrid.x][data.mousePosGrid.y] != nullptr) {
        delete data.placements[data.mousePosGrid.x][data.mousePosGrid.y];
        data.placements[data.mousePosGrid.x][data.mousePosGrid.y] = nullptr;
    }
}
void Builder::placement() {
    if (data.placements[data.mousePosGrid.x][data.mousePosGrid.y] == nullptr or data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation() != build_preview->sprite.getRotation()) {
        bool behind = false;
        bool right = false;
        bool left = false;
        int build_rot = int(build_preview->sprite.getRotation());
        //sf::Vector2u forward;
        sf::Vector2u grid = data.mousePosGrid;

        switch (build_rot) {
            case 0:
                if (!grid.x < 0 or !grid.y + 1 < 0)
                    behind = StaticFunctions::checkSide(build_rot, data.placements[grid.x][grid.y + 1]);
                if (!behind) {
                    if (!grid.x - 1 < 0 or !grid.y < 0)
                        left = StaticFunctions::checkSide(90, data.placements[grid.x - 1][grid.y]);
                    if (!grid.x + 1 < 0 or !grid.y < 0)
                        right = StaticFunctions::checkSide(270, data.placements[grid.x + 1][grid.y]);
                }
                //forward = sf::Vector2u(grid.x,grid.y + 1);
                break;
            case 90:
                behind = StaticFunctions::checkSide(build_rot, data.placements[grid.x - 1][grid.y]);
                if (!behind) {
                    left = StaticFunctions::checkSide(180, data.placements[grid.x][grid.y - 1]);
                    right = StaticFunctions::checkSide(0, data.placements[grid.x][grid.y + 1]);
                }
                //forward = sf::Vector2u(grid.x + 1,grid.y);
                break;
            case 180:
                behind = StaticFunctions::checkSide(build_rot, data.placements[grid.x][grid.y - 1]);
                if (!behind) {
                    left = StaticFunctions::checkSide(270, data.placements[grid.x + 1][grid.y]);
                    right = StaticFunctions::checkSide(90, data.placements[grid.x - 1][grid.y]);
                }
                //forward = sf::Vector2u(grid.x,grid.y - 1);
                break;
            case 270:
                behind = StaticFunctions::checkSide(build_rot, data.placements[grid.x + 1][grid.y]);
                if (!behind) {
                    left = StaticFunctions::checkSide(0, data.placements[grid.x][grid.y + 1]);
                    right = StaticFunctions::checkSide(180, data.placements[grid.x][grid.y - 1]);
                }
                //forward = sf::Vector2u(grid.x - 1,grid.y);
                break;
        }
        if (left == right)
            data.placements[grid.x][grid.y] = new Placement(data.conveyor.straight, grid, build_rot);
        else if (left)
            data.placements[grid.x][grid.y] = new Placement(data.conveyor.bendl, grid, build_rot);
        else
            data.placements[grid.x][grid.y] = new Placement(data.conveyor.bendr, grid, build_rot);
        {
                //if (data.placements[forward.x][forward.y] != nullptr)
                //    if (build_preview->sprite.getRotation() != data.placements[forward.x][forward.y]->sprite.getRotation()
                //        and build_preview->sprite.getRotation() != data.placements[forward.x][forward.y]->sprite.getRotation() + 180
                //        and build_preview->sprite.getRotation() != data.placements[forward.x][forward.y]->sprite.getRotation() - 180)
                //        auto rot = data.placements[forward.x][forward.y]->sprite.getRotation();
                //        delete data.placements[forward.x][forward.y];}
        } {//    data.placements[data.mousePosGrid.x][data.mousePosGrid.y] = new Placement(data.conveyor_texture.straight, data.mousePosGrid, build_preview->sprite.getRotation());
            //} else {
            //    if (data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation() != build_preview->sprite.getRotation())
            //        if (data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation() == build_preview->sprite.getRotation() - 90 or data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation() == build_preview->sprite.getRotation() - 360)
            //            data.placements[data.mousePosGrid.x][data.mousePosGrid.y] = new Placement(data.conveyor_texture.bendr, data.mousePosGrid, data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation());
            //        else if (data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation() == build_preview->sprite.getRotation() - 270)
            //            data.placements[data.mousePosGrid.x][data.mousePosGrid.y] = new Placement(data.conveyor_texture.bendl, data.mousePosGrid, data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation());
            //        else if (data.placements[data.mousePosGrid.x][data.mousePosGrid.y]->sprite.getRotation() == build_preview->sprite.getRotation() - 180)
            //            data.placements[data.mousePosGrid.x][data.mousePosGrid.y] = new Placement(data.conveyor_texture.straight, data.mousePosGrid, build_preview->sprite.getRotation());
            //}}
        }
    }
}
void Builder::keyInputControls(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R)
            build_preview->sprite.setRotation(build_preview->sprite.getRotation() + 90);
    }
}
void Builder::render() {

    if (mouse_right_held)
        data.window.draw(del_view);
    else
        data.window.draw(build_preview->sprite);
}
void Builder::update(float dt) {
    previewUpdate();
    if (mouse_left_held) {
        placement();
    }
    if (mouse_right_held) {
        auto x = (data.mousePosGrid.x * 16) - del_view.getPosition().x;
        auto y = (data.mousePosGrid.y * 16) - del_view.getPosition().y;
        if (x >= 0)
            x += 16;
        if (y >= 0)
            y += 16;
        del_view.setSize(sf::Vector2f(x, y));
        removement();
    }
}


void Builder::previewUpdate() {
    auto pos = data.mousePosGrid;
    switch (int(build_preview->sprite.getRotation())) {
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
    build_preview->sprite.setPosition(pos.x * 16, pos.y * 16);
}
