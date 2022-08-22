
#include "Builder.h"
#include "../HelperFunctions/StaticFunctions.h"
#include "GameData.h"
#include <iostream>


Builder::Builder(GameData& game_data) : data(game_data)
{
    build_preview = new Placement(data.conveyor_texture.straight, 128);
    del_view.setSize(sf::Vector2f(16, 16));
    del_view.setFillColor(sf::Color(255, 0, 0, 128));
}

void Builder::mouseInputControls(sf::Event event)
{
    if (event.type == sf::Event::EventType::MouseButtonPressed)
    {
        switch (event.mouseButton.button)
        {
            case (sf::Mouse::Button::Left):
                mouse_left_held = true;
                break;

            case (sf::Mouse::Button::Right):
                del_view.setPosition(data.mousePosGrid.x * 16, data.mousePosGrid.y * 16);
                mouse_right_held = true;
                break;
        }
    }


    if (event.type == sf::Event::EventType::MouseButtonReleased)
    {
        switch (event.mouseButton.button)
        {
            case (sf::Mouse::Button::Left):
                mouse_left_held = false;
                break;
            case (sf::Mouse::Button::Right):
                mouse_right_held = false;
                break;
        }
    }
}
void Builder::removement()
{
    if (data.rendered_chunks.at(0)->block_data[data.mousePosGrid.x][data.mousePosGrid.y] != nullptr) {}
    {
        delete data.rendered_chunks.at(0)->block_data[data.mousePosGrid.x][data.mousePosGrid.y];
        data.rendered_chunks.at(0)->block_data[data.mousePosGrid.x][data.mousePosGrid.y] = nullptr;
    }
}
void Builder::placement()
{
    if (data.rendered_chunks.at(0)->block_data[data.mousePosGrid.x][data.mousePosGrid.y] == nullptr or data.rendered_chunks.at(0)->block_data[data.mousePosGrid.x][data.mousePosGrid.y]->rotation != build_preview->sprite.getRotation())
    {
        bool behind = false;
        bool right = false;
        bool left = false;
        int build_rot = int(build_preview->sprite.getRotation());
        //sf::Vector2u forward;
        sf::Vector2u grid{data.mousePosGrid};
        auto& block_data = data.rendered_chunks.at(0)->block_data;

        switch (build_rot)
        {
            case 0:
                if (!grid.x < 0 or !grid.y + 1 < 0)
                    behind = StaticFunctions::checkSide(build_rot, block_data[grid.x][grid.y + 1]);
                if (!behind)
                {
                    if (!grid.x - 1 < 0 or grid.y >= 0)
                        left = StaticFunctions::checkSide(90, block_data[grid.x - 1][grid.y]);
                    if (!grid.x + 1 < 0 or grid.y >= 0)
                        right = StaticFunctions::checkSide(270, block_data[grid.x + 1][grid.y]);
                }
                //forward = sf::Vector2u(grid.x,grid.y + 1);
                break;
            case 90:
                behind = StaticFunctions::checkSide(build_rot, block_data[grid.x - 1][grid.y]);
                if (!behind)
                {
                    left = StaticFunctions::checkSide(180, block_data[grid.x][grid.y - 1]);
                    right = StaticFunctions::checkSide(0, block_data[grid.x][grid.y + 1]);
                }
                //forward = sf::Vector2u(grid.x + 1,grid.y);
                break;
            case 180:
                behind = StaticFunctions::checkSide(build_rot, block_data[grid.x][grid.y - 1]);
                if (!behind)
                {
                    left = StaticFunctions::checkSide(270, block_data[grid.x + 1][grid.y]);
                    right = StaticFunctions::checkSide(90, block_data[grid.x - 1][grid.y]);
                }
                //forward = sf::Vector2u(grid.x,grid.y - 1);
                break;
            case 270:
                behind = StaticFunctions::checkSide(build_rot, block_data[grid.x + 1][grid.y]);
                if (!behind)
                {
                    left = StaticFunctions::checkSide(0, block_data[grid.x][grid.y + 1]);
                    right = StaticFunctions::checkSide(180, block_data[grid.x][grid.y - 1]);
                }
                //forward = sf::Vector2u(grid.x - 1,grid.y);
                break;
        }
        block_data[grid.x][grid.y] = new conveyor(Block{});

        if (left == right)
        {
            block_data[grid.x][grid.y]->id = "conveyorS";
            block_data[grid.x][grid.y]->sprite.setTexture(data.conveyor_texture.straight);
        } else if (left)
        {
            block_data[grid.x][grid.y]->id = "conveyorL";
            block_data[grid.x][grid.y]->sprite.setTexture(data.conveyor_texture.bendl);
        } else
        {
            block_data[grid.x][grid.y]->id = "conveyorR";
            block_data[grid.x][grid.y]->sprite.setTexture(data.conveyor_texture.bendr);
        }

        block_data[grid.x][grid.y]->sprite.setRotation(build_rot);
        block_data[grid.x][grid.y]->rotation = build_rot;
        sf::Vector2u pos{grid};
        switch (int(build_rot))
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
        sf::Vector2f sprite_pos{(float(pos.x) * 16) + (data.mousePosChunk.x * chunkLenP),
                                (float(pos.y) * 16) + (data.mousePosChunk.y * chunkLenP)};
        block_data[grid.x][grid.y]->sprite.setPosition(sprite_pos);
        block_data[grid.x][grid.y]->pos.x = grid.x;
        block_data[grid.x][grid.y]->pos.y = grid.y;
    }
}
void Builder::keyInputControls(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
            build_preview->sprite.setRotation(build_preview->sprite.getRotation() + 90);
    }
}
void Builder::render()
{

    if (mouse_right_held)
        data.window.draw(del_view);
    else
        data.window.draw(build_preview->sprite);
}
void Builder::update(float dt)
{
    previewUpdate();
    if (mouse_left_held)
    {
        placement();
    }
    if (mouse_right_held)
    {
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


void Builder::previewUpdate()
{
    auto pos = data.mousePosGrid;
    switch (int(build_preview->sprite.getRotation()))
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
    sf::Vector2f sprite_pos{(float(pos.x) * 16) + (data.mousePosChunk.x * chunkLenP),
                            (float(pos.y) * 16) + (data.mousePosChunk.y * chunkLenP)};
    build_preview->sprite.setPosition(sprite_pos);
}
