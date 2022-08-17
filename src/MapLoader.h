#include "../tinyxml/tinyxml2.h"
#include "Objects/Chunk.h"
#pragma once


class MapLoader {
public:
    Chunk loadchunk(int xchunk, int ychunk);
    static bool savechunk(Chunk chunk_to_save);
};
