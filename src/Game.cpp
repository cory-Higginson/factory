
#include "Game.h"

#include "GameData.h"
#include "MapLoader.h"
#include "State.h"
#include <iostream>

Game::Game(GameData& game_data, Builder buildvision) : State(game_data), buildvision(buildvision)
{
    // try to load chunk 0,0
    // if no chunk make one:

    std::array<std::tuple<float, int, sf::Sprite*>, 128 * 128> blocks;
    float y = 0;
    float x = 0;
    for (auto& block: blocks)
    {
        if (y >= (chunkLenG))
        {
            x += 1;
            y = 0;
        }
        std::get<int>(block) = 1;     //id
        std::get<float>(block) = 60.f;//rot
        std::get<sf::Sprite*>(block) = new sf::Sprite{data.blocks_texture.stone,
                                                      sf::IntRect{0, 0, 16, 16}};
        std::get<sf::Sprite*>(block)->setPosition(sf::Vector2f(x * 16, y * 16));
        y += 1;
    };
    std::array<std::array<Block*, chunkLenG>, chunkLenG> block_data;
    for (auto& arrayx: block_data)
    {
        for (auto& j: arrayx)
        {
            j = nullptr;
        }
    }
    MapLoader::loadchunk(0, 0, data);
    //data.rendered_chunks.at(0) = new Chunk{0, 0, false, 0, blocks, block_data};
    //data.rendered_chunks.at(0)->xPos = 0;
    //data.rendered_chunks.at(0)->yPos = 0;
}

bool Game::init()
{
    defaultview.setSize(data.window.getSize().x, data.window.getSize().y);
    defaultview.setCenter(data.window.getSize().x / 2, data.window.getSize().y / 2);
    cam = defaultview;
    sf::Texture tec;
    tec.create(1, 1);
    font.loadFromFile("Data/kongtext.ttf");
    info.setFont(font);
    info.setCharacterSize(10);
    info.setPosition(0, 0);
    return true;
}

void Game::update(float dt)
{
    sf::String a;
    a = data.buildmode ? "Buildmode" : "normal";
    info.setString("info:" + a + "\n"
                                 "screen X: " +
                   std::to_string(data.mousePosScreen.x) + " Y: " + std::to_string(data.mousePosScreen.y) + "\n"
                                                                                                            "window X: " +
                   std::to_string(data.mousePosWindow.x) + " Y: " + std::to_string(data.mousePosWindow.y) + "\n"
                                                                                                            "View X: " +
                   std::to_string(data.mousePosView.x) + " Y: " + std::to_string(data.mousePosView.y) + "\n"
                                                                                                        "chunk X: " +
                   std::to_string(data.mousePosChunk.x) + " Y: " + std::to_string(data.mousePosChunk.y) + "\n"
                                                                                                          "Grid X: " +
                   std::to_string(data.mousePosGrid.x) + " y: " + std::to_string(data.mousePosGrid.y) + "\n");
    if (data.buildmode)
        buildvision.update(dt);
    if (moveup)
        cam.move(0, -500 * dt);
    if (movedown)
        cam.move(0, 500 * dt);
}

void Game::render()
{
    // game scene rendering
    data.window.setView(cam);
    for (auto& rendered_chunk: data.rendered_chunks)
    {
        if (rendered_chunk != nullptr)
        {
            for (auto& block: rendered_chunk->blocks)
            {
                data.window.draw(*std::get<sf::Sprite*>(block));
            }
            for (auto& arrayX: rendered_chunk->block_data)
            {
                for (auto& block: arrayX)
                {
                    if (block != nullptr)
                        data.window.draw(block->sprite);
                }
            }
        }
    }

    if (data.buildmode)
        buildvision.render();


    // UI Rendering
    data.window.setView(defaultview);
    data.window.draw(info);
    data.window.setView(cam);
}

void Game::mouseClicked(sf::Event event)
{
    if (data.buildmode)
        buildvision.mouseInputControls(event);
}


void Game::keyPressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Up)
        moveup = true;
    if (event.key.code == sf::Keyboard::Down)
        movedown = true;
    if (event.key.code == sf::Keyboard::B)
        data.buildmode = !data.buildmode;
    if (event.key.code == sf::Keyboard::Escape)
        closed();
    if (data.buildmode)
        buildvision.keyInputControls(event);
    //if (event.key.code == sf::Keyboard::J)
    //{
    //    std::array<std::tuple<float, int>, 128*128> blocks;
    //    for (auto & block : blocks)
    //    {
    //        std::get<int>(block) = 1;
    //        std::get<float>(block) = 3.f;
    //    };
    //    std::array<std::tuple<int,Block*>*,128*128> block_data{};
    //    for (auto & data : block_data)
    //    {
    //        data = nullptr;
    //    }
    //
    //
    //    Block block;
    //    block.id = "chest";
    //    block.pos = sf::Vector2i(2,5);
    //
    //    std::array<item*, 50> items{};
    //    for (auto & item : items) {
    //        item = nullptr;
    //    }
    //    items.at(43) = new item{400,3,"ruby"};
    //
    //    chest* chest_stuff;
    //    chest_stuff = new chest(block);
    //    chest_stuff->items = items;
    //
    //    block_data.at(2) = new std::tuple<int,Block*>{2,chest_stuff};
    //
    //    Chunk chunk {
    //        1,
    //        2,
    //        false,
    //        43563,
    //        blocks,
    //        block_data
    //    };
    //
    //    auto a = MapLoader::savechunk(chunk);
    //    if (a)
    //        data.window.close();
    //}
}

void Game::keyReleased(sf::Event event)
{
    if (data.buildmode)
        buildvision.keyInputControls(event);
    if (event.key.code == sf::Keyboard::Up)
        moveup = false;
    if (event.key.code == sf::Keyboard::Down)
        movedown = false;
}

void Game::mouseMoved(sf::Event event)
{
    /////////////////////////////////////////
    /// MOUSE CHUNK AND GRID CALCULATIONS ///
    /////////////////////////////////////////
    data.mousePosScreen = sf::Mouse::getPosition();
    data.mousePosWindow = sf::Mouse::getPosition(data.window);
    data.mousePosView = data.window.mapPixelToCoords(data.mousePosWindow);

    /// +X
    if (data.mousePosView.x >= 0.f)
    {
        data.mousePosChunk.x = int(data.mousePosView.x) / 2048;
        if (data.mousePosChunk.x == 0)
        {
            data.mousePosGrid.x = data.mousePosView.x / 16;
        } else
        {
            data.mousePosGrid.x = int(data.mousePosView.x / 16) % (128 * data.mousePosChunk.x);
        }
    }
    /// -X
    else
    {
        data.mousePosChunk.x = -(int(std::abs(data.mousePosView.x)) / 2048) - 1;
        if (data.mousePosChunk.x == -1)
        {
            data.mousePosGrid.x = std::abs(128 + data.mousePosView.x / 16);
        } else
        {
            auto b = std::abs(128 + (std::abs(data.mousePosView.x) / 16));
            data.mousePosGrid.x = 127 - int(b) % (128 * abs(data.mousePosChunk.x));
        }
    }

    /// +Y
    if (data.mousePosView.y >= 0.f)
    {
        data.mousePosChunk.y = int(data.mousePosView.y) / 2048;
        data.mousePosGrid.y = data.mousePosChunk.y == 0 ? data.mousePosView.y / 16 : int(data.mousePosView.y / 16) % (128 * data.mousePosChunk.y);
    }
    /// -Y
    else
    {
        data.mousePosChunk.y = -(int(std::abs(data.mousePosView.y)) / 2048) - 1;
        if (data.mousePosChunk.y == -1)
        {
            data.mousePosGrid.y = std::abs(128 + data.mousePosView.y / 16);
        } else
        {
            auto b = std::abs(128 + (std::abs(data.mousePosView.y) / 16));
            data.mousePosGrid.y = 127 - int(b) % (128 * abs(data.mousePosChunk.y));
        }
    }

    /////////////////////////////////////////
    ///build mode passthrough
    if (data.buildmode)
        buildvision.mouseInputControls(event);
}

void Game::resize(sf::Event event)
{
}

void Game::closed()
{
    for (auto& rendered_chunk: data.rendered_chunks)
    {
        if (rendered_chunk != nullptr)
        {
            MapLoader::savechunk(*rendered_chunk);
        }
    }
    data.window.close();
}
