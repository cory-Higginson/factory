
#include "MapLoader.h"
#include <iostream>
#include <tuple>

Chunk MapLoader::loadchunk(int xchunk, int ychunk) {
    return Chunk();
}
bool MapLoader::savechunk(Chunk chunk_to_save) {

    tinyxml2::XMLDocument chunk;                        // creates xml document
    tinyxml2::XMLNode *pRoot = chunk.NewElement("Root");// makes a root node
    chunk.InsertFirstChild(pRoot);                      // attach to xml document

    // chunk position
    tinyxml2::XMLElement *pElement = chunk.NewElement("position");
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
    for (auto &block: chunk_to_save.blocks) {
        // save each block(element) with a rotation(attr) and id(attr) as a child of blocks list
        tinyxml2::XMLElement *pBlockElement = chunk.NewElement("block");
        pBlockElement->SetAttribute("rotation", std::get<float>(block));
        pBlockElement->SetAttribute("id", std::get<int>(block));
        pElement->InsertEndChild(pBlockElement);
    };
    pElement->SetAttribute("size", chunk_to_save.blocks.size());
    pRoot->InsertEndChild(pElement);

    // save block data
    pElement = chunk.NewElement("BlockDataList");
    for (auto &block: chunk_to_save.block_data) {
        // save each block(element) with a rotation(attr) and id(attr) as a child of blocks list
        tinyxml2::XMLElement *pBlockDataElement = chunk.NewElement("BlockData");
        if (block != nullptr) {
            auto rblock = std::get<int>(*block);
            auto dblock = std::get<Block *>(*block);
            pBlockDataElement->SetAttribute("id", dblock->id.c_str());
            pBlockDataElement->SetAttribute("rot", rblock);
            pBlockDataElement->SetAttribute("X", dblock->pos.x);
            pBlockDataElement->SetAttribute("Y", dblock->pos.y);

            if (dblock->id == "chest") {
                chest *cblock;
                cblock = dynamic_cast<chest *>(dblock);
                for (auto &item: cblock->items) {
                    // save each item(element) with a id(attr) and slot(attr) and count(attr) as child of block data
                    tinyxml2::XMLElement *pitemElement = chunk.NewElement("item");
                    if (item != nullptr) {
                        pitemElement->SetAttribute("id", item->id.c_str());
                        pitemElement->SetAttribute("slot", item->slot);
                        pitemElement->SetAttribute("count", item->count);
                        pBlockDataElement->InsertEndChild(pitemElement);
                    }
                };
            }
            pElement->InsertEndChild(pBlockDataElement);
        }
    };
    pElement->SetAttribute("size", chunk_to_save.blocks.size());
    pRoot->InsertEndChild(pElement);

    // build filename via chunk XY eg chunk 3_5;
    auto filename = "chunk " + std::to_string(chunk_to_save.xPos) + "_" + std::to_string(chunk_to_save.yPos) + ".xml";
    tinyxml2::XMLError eResult = chunk.SaveFile(filename.c_str());
    if (eResult != 0) {
        std::cout << eResult << std::endl;
        return false;
    }
    return true;
}
