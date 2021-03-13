#include "Enemy.hpp"

void Enemy::collisionToObj(Object& obj) {
    physics.collision(obj);
}

void NormalZombie::update() {
    physics.accel.x = -1.5f;
    physics.update();
}

void NormalZombie::draw() const {
    RectF(physics.pos, physics.size).drawFrame(1.0, Palette::Red);
}