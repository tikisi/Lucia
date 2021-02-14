#pragma once
#include "Common.hpp"
#include "Physics.hpp"

class Player {
private:
    uint32 jumpCounter;
    bool isGround;

public:
    Physics physics;

    void init() {
        jumpCounter = 0;
        isGround = false;
    }
    Player(const Physics& physics) : physics(physics) { this->init(); }
    Player(const Float2& pos, const Float2& size = Float2(72, 144)) :
        physics(pos, size) {
        this->init();
    }

    void update();
    void draw() const;

    void collision(const Object& obj);
};
