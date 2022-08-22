#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <tuple>


const int chunkLenG = 128;// chunk size
const int chunkLenP = chunkLenG * 16;
const int total_blocks = chunkLenG * chunkLenG;//  total blocks in one chunk


struct Chunk
/**
 * chunk structure
 */
{
public:
    int xPos;                                                            ///< [in,out] @details xpos X chunk location
    int yPos;                                                            ///< [in,out] @details xpos X chunk location
    bool populated;                                                      ///< [in,out] @details populated has the chunk been generated
    double last_update;                                                  ///< [in,out] @details last_update when was the last update
    std::array<std::tuple<float, int, sf::Sprite*>, total_blocks> blocks;///< [in,out] @details blocks array containing all the blocks @param float: rot @param int: id
    std::array<std::array<Block*, chunkLenG>, chunkLenG> block_data;     ///< [in,out] @details array cointaining all special blocks @example chests,conveyors,factorys ect
};
