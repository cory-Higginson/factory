#include "Conveyorlogic.h"


conveyorlogic::conveyorlogic() {
}

void conveyorlogic::update(float dt) {
    for (auto &path: paths) {
        for (auto &conveyor: path) {
            if (conveyor->hasItems()) {}
        }
    }
}
