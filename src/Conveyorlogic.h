//
// Created by mrmrcory on 12/08/2022.
//

#pragma once
#include "Objects/Block.h"
#include <array>
#include <vector>

class conveyorlogic {
public:
    explicit conveyorlogic();
    void update(float dt);

private:
    std::vector<std::array<conveyor *, 10>> paths{};
};
