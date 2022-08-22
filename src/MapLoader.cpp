
#include "MapLoader.h"
#include <iostream>
#include <tuple>

bool MapLoader::loadchunk(int xchunk, int ychunk, GameData& data)
{
    if (data.rendered_chunks.at(0) != nullptr)
    {
        delete data.rendered_chunks.at(0);
        data.rendered_chunks.at(0) = nullptr;
    }
    tinyxml2::XMLDocument chunk;
    ;
    auto filename = "chunk " + std::to_string(xchunk) + "_" + std::to_string(ychunk) + ".xml";
    if (chunk.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
        return createchunk(xchunk, ychunk, data.rendered_chunks.at(0));
    }
    tinyxml2::XMLNode* Root = chunk.FirstChildElement("Root");
    tinyxml2::XMLElement* element = Root->FirstChildElement("position");
    auto chunk_X = element->IntAttribute("X");
    auto chunk_Y = element->IntAttribute("Y");
    auto populated = Root->FirstChildElement("populated")->BoolText(true);
    auto last_update = Root->FirstChildElement("last_update")->DoubleText();

    // Block List
    element = Root->FirstChildElement("BlockList")->FirstChildElement();
    std::array<std::tuple<float, int, sf::Sprite*>, total_blocks> blocks;
    int x = 0;
    int y = 0;
    int cnt = 0;
    for (auto& block: blocks)
    {

        if (y >= (chunkLenG))
        {
            x += 1;
            y = 0;
        }
        std::get<int>(block) = element->IntAttribute("id");          //id
        std::get<float>(block) = element->FloatAttribute("rotation");//rot
        std::get<sf::Sprite*>(block) = new sf::Sprite{};
        switch (std::get<int>(block))
        {
            case 2:
                break;
            case 1:
            default:
                std::get<sf::Sprite*>(block)->setTexture(data.blocks_texture.stone);
                break;
        }
        int posy = y;
        int posx = x;
        switch (int(std::get<float>(block)))
        {
            case (180):
                posy += 1;
            case (90):
                posx += 1;
                break;
            case (270):
                posy += 1;
                break;
            case (0):
                break;
        }
        std::get<sf::Sprite*>(block)->setPosition(sf::Vector2f((float(posx) * 16) + (chunk_X * chunkLenP),
                                                               (float(posy) * 16) + (chunk_Y * chunkLenP)));
        y += 1;
        element->NextSiblingElement();
    }

    // load block data
    element = Root->FirstChildElement("BlockDataList");
    std::array<std::array<Block*, chunkLenG>, chunkLenG> block_data{};
    if (!element->NoChildren())
    {
        element = Root->FirstChildElement("BlockDataList")->FirstChildElement();
        for (int i = 0; i < Root->FirstChildElement("BlockDataList")->IntAttribute("size"); ++i)
        {
            element = Root->FirstChildElement("BlockDataList")->FirstChildElement();
            x = element->IntAttribute("X");
            y = element->IntAttribute("Y");
            if (element->Attribute("id") == std::string{"conveyorS"} or
                element->Attribute("id") == std::string{"conveyorR"} or
                element->Attribute("id") == std::string{"conveyorL"})
            {
                block_data[x][y] = new conveyor{Block{}};
                block_data[x][y]->id = element->Attribute("id");
                block_data[x][y]->rotation = element->IntAttribute("rot");
                block_data[x][y]->pos = sf::Vector2i{x, y};
                if (element->Attribute("id") == std::string{"conveyorS"})
                {
                    block_data[x][y]->sprite.setTexture(data.conveyor_texture.straight);
                } else if (element->Attribute("id") == std::string{"conveyorR"})
                {
                    block_data[x][y]->sprite.setTexture(data.conveyor_texture.bendr);
                } else
                {
                    block_data[x][y]->sprite.setTexture(data.conveyor_texture.bendl);
                }


                block_data[x][y]->sprite.setRotation(block_data[x][y]->rotation);
                int posx = block_data[x][y]->pos.x;
                int posy = block_data[x][y]->pos.y;
                switch (block_data[x][y]->rotation)
                {
                    case (180):
                        posy += 1;
                    case (90):
                        posx += 1;
                        break;
                    case (270):
                        posy += 1;
                        break;
                    case (0):
                        break;
                }
                block_data[x][y]->sprite.setPosition(sf::Vector2f((float(posx) * 16) + (chunk_X * chunkLenP),
                                                                  (float(posy) * 16) + (chunk_Y * chunkLenP)));
                Root->FirstChildElement("BlockDataList")->DeleteChild(element);
            }
        }
    } else
    {
        for (auto& i: block_data)
        {
            for (auto& j: i)
            {
                j = nullptr;
            }
        }
    }
    data.rendered_chunks.at(0) = new Chunk{chunk_X, chunk_Y, populated, last_update, blocks, block_data};
    chunk.Clear();
    return true;
}
bool MapLoader::savechunk(Chunk chunk_to_save)
{

    tinyxml2::XMLDocument chunk;                        // creates xml document
    tinyxml2::XMLNode* pRoot = chunk.NewElement("Root");// makes a root node
    chunk.InsertFirstChild(pRoot);                      // attach to xml document

    // chunk position
    tinyxml2::XMLElement* pElement = chunk.NewElement("position");
    pElement->SetAttribute("X", chunk_to_save.xPos);
    pElement->SetAttribute("Y", chunk_to_save.yPos);
    pRoot->InsertEndChild(pElement);

    // chunk populated?
    pElement = chunk.NewElement("populated");
    pElement->SetText(chunk_to_save.populated);
    pRoot->InsertEndChild(pElement);

    // chunk last update
    pElement = chunk.NewElement("last_update");
    pElement->SetText(chunk_to_save.last_update);
    pRoot->InsertEndChild(pElement);

    //chunk save blocks in blocklist
    pElement = chunk.NewElement("BlockList");
    for (auto& block: chunk_to_save.blocks)
    {
        // save each block(element) with a rotation(attr) and id(attr) as a child of blocks list
        tinyxml2::XMLElement* pBlockElement = chunk.NewElement("block");
        pBlockElement->SetAttribute("rotation", std::get<float>(block));
        pBlockElement->SetAttribute("id", std::get<int>(block));
        pElement->InsertEndChild(pBlockElement);
    };
    pElement->SetAttribute("size", chunk_to_save.blocks.size());
    pRoot->InsertEndChild(pElement);

    // save block data
    pElement = chunk.NewElement("BlockDataList");
    int total = 0;
    for (auto& array: chunk_to_save.block_data)
    {
        for (auto& block: array)
        {// save each block(element) with a rotation(attr) and id(attr) as a child of blocks list
            tinyxml2::XMLElement* pBlockDataElement = chunk.NewElement("BlockData");
            if (block != nullptr)
            {
                total += 1;
                pBlockDataElement->SetAttribute("id", block->id.c_str());
                pBlockDataElement->SetAttribute("rot", block->rotation);
                pBlockDataElement->SetAttribute("X", block->pos.x);
                pBlockDataElement->SetAttribute("Y", block->pos.y);

                if (block->id == "chest")
                {
                    chest* cblock;
                    cblock = dynamic_cast<chest*>(block);
                    for (auto& item: cblock->items)
                    {
                        // save each item(element) with a id(attr) and slot(attr) and count(attr) as child of block data
                        tinyxml2::XMLElement* pitemElement = chunk.NewElement("item");
                        if (item != nullptr)
                        {
                            pitemElement->SetAttribute("id", item->id.c_str());
                            pitemElement->SetAttribute("slot", item->slot);
                            pitemElement->SetAttribute("count", item->count);
                            pBlockDataElement->InsertEndChild(pitemElement);
                        }
                    };
                }
                if (block->id == "conveyorS" or block->id == "conveyorR" or block->id == "conveyorL")
                {
                    conveyor* cblock;
                    cblock = dynamic_cast<conveyor*>(block);
                    if (cblock->item != nullptr)
                    {
                        // save each item(element) with a id(attr) and slot(attr) and count(attr) as child of block data
                        tinyxml2::XMLElement* pitemElement = chunk.NewElement("item");
                        pitemElement->SetAttribute("id", cblock->item->id.c_str());
                        pBlockDataElement->InsertEndChild(pitemElement);
                    }
                }
                pElement->InsertEndChild(pBlockDataElement);
            }
        }
    };
    pElement->SetAttribute("size", total);
    pRoot->InsertEndChild(pElement);

    // build filename via chunk XY eg chunk 3_5;
    auto filename = "chunk " + std::to_string(chunk_to_save.xPos) + "_" + std::to_string(chunk_to_save.yPos) + ".xml";
    tinyxml2::XMLError eResult = chunk.SaveFile(filename.c_str());
    if (eResult != 0)
    {
        std::cout << eResult << std::endl;
        return false;
    }
    return true;
}


bool MapLoader::createchunk(int xchunk, int ychunk, Chunk* chunkptr)
{
    return false;
}
