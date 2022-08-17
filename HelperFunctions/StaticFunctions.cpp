
#include "StaticFunctions.h"


bool StaticFunctions::checkSide(int roatation, Placement *side_check) {
    if (side_check != nullptr)
        if (int(side_check->sprite.getRotation()) == roatation)
            return true;
    return false;
}
