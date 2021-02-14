#pragma once
#include "Common.hpp"
#include "Physics.hpp"

class Player {
private:
    uint32 jumpCounter;

public:
    Physics physics;

    void init() { jumpCounter = 0; }
    Player(const Physics& physics) : physics(physics) { this->init(); }
    Player(const Float2& pos, const Float2& size = Float2((float)BLOCK_SIZE, BLOCK_SIZE * 2)):
        physics(pos, size) {
        this->init();
    }

    void update();
    void draw() const;

    void collision(const Object& obj);
    Float2 getPos() const { return physics.pos; }
    Float2 getSize() const { return physics.size; }
    Float2 getCenter() const { return physics.getCenter(); }
    bool isGround() const { return jumpCounter == 0; }
};
