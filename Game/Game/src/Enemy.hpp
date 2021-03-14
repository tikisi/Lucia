#pragma once
#include "Common.hpp"
#include "Physics.hpp"

class Object;

class Enemy {
private:
    uint32 damage;

public:
    Physics physics;

    Enemy(const Physics& physics, const uint32& damage) : physics(physics), damage(damage) {}
    virtual void update() = 0;
    virtual void draw() const = 0;
    virtual void collision(Object& obj);

    virtual uint32 getDamage() const { return damage; }
};

class NormalZombie : public Enemy {
public:
    NormalZombie(const Physics& physics) : Enemy(physics, 8) {}
    NormalZombie(const Float2& pos, const Float2& size = Float2(BLOCK_SIZE, BLOCK_SIZE)) : Enemy(Physics(pos, size), 8) {}

    void update() override;
    void draw() const override;
};
