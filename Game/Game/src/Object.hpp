#pragma once
#include "Common.hpp"

class Player;

class Object {
public:
    Float2 pos;
    Float2 size;

    Object(const Float2 & pos, const Float2 &size) : pos(pos), size(size) {}
    virtual ~Object(){};
    virtual void update() = 0;
    virtual void draw() const = 0;
};


class Block : public Object {
public:
    Block(const Float2& pos, const Float2& size = Float2(72, 72)) : Object(pos, size) {}

    virtual void update() override {};
    virtual void draw() const override;
};
