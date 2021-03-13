#pragma once
#include "Common.hpp"
#include "Physics.hpp"

class Object;

class Enemy {
public:
    Physics physics;

    Enemy(const Physics& physics) : physics(physics) {}
    virtual void update() = 0;
    virtual void draw() const = 0;
    virtual void collisionToObj(Object& obj);
};

class NormalZombie : public Enemy {
public:
    NormalZombie(const Physics& physics) : Enemy(physics) {}
    NormalZombie(const Float2& pos, const Float2& size = Float2(BLOCK_SIZE, BLOCK_SIZE * 2)) : Enemy(Physics(pos, size)) {}

    void update() override;
    void draw() const override;
};
