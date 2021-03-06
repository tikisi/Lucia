#pragma once
#include "Common.hpp"
#include "Physics.hpp"
#include "PlayerState.hpp"

class Enemy;

class Player {
private:
    PlayerState* state;
    bool _isGround;

    // KnockBack
    uint32 knockBackCounter;
    DIR knockBackDir;

    // HP
    int hp;

public:
    Physics physics;

    Array<Array<TextureRegion>> textures;

    void init();
    Player(const Physics& physics) : physics(physics) { this->init(); }
    Player(const Float2& pos, const Float2& size = Float2((float)BLOCK_SIZE, BLOCK_SIZE * 2)) :
        physics(pos, size) {
        this->init();
    }

    void update();
    void draw() const;

    // �����蔻��
    void collision(const Object& obj);
    void collision(const Enemy& enemy);

    const TextureRegion& selectTexture() const;
    Float2 getPos() const { return physics.pos; }
    Float2 getSize() const { return physics.size; }
    Float2 getCenter() const { return physics.getCenter(); }
    bool isGround() const { return _isGround; }

    // KnockBack
    uint32 getKnockBackCounter() const { return knockBackCounter; }
    DIR getKnockBackDir() const { return knockBackDir; }
};
