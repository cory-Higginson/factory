
#include "../tinyxml/tinyxml2.h"
#include "GameData.h"
#include "Objects/Chunk.h"
#pragma once


class MapLoader {
public:
    static bool loadchunk(int xchunk, int ychunk, GameData& data);
    static bool savechunk(Chunk chunk_to_save);
    static bool createchunk(int xchunk, int ychunk, Chunk* chunkptr);
};
