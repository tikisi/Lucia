#include "Object.hpp"
#include "Player.hpp"

void Block::draw() const {
    RectF(pos, size)
        .drawFrame(2.0, 1.0, Palette::Green);
}
