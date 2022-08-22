
#include "StaticFunctions.h"
#include "../src/Objects/Block.h"


bool StaticFunctions::checkSide(int rotation, Block* side_check)
{
    if (side_check != nullptr)
        if (int(side_check->sprite.getRotation()) == rotation)
            return true;
    return false;
}
