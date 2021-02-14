#include "Player.hpp"

void Player::update() {
    // ˆÚ“®
    physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

    if (jumpCounter == 0 && KeyZ.down()) { jumpCounter = 1; }
    if (jumpCounter != 0) {
        if (jumpCounter == 1) {
            physics.accel.y = -15.0f;  // ‰‘¬
        }
        else if (jumpCounter < 25 && !KeyZ.pressed()) {
            physics.accel.y = 0.5;     // Œ¸‘¬
        }
        else if (KeyZ.down()) {
            physics.accel.y = -15.0f;
        }
        jumpCounter++;
    }

    physics.update();
}

void Player::draw() const {
    RectF(physics.pos, physics.size)
        .drawFrame(2.0, Palette::Red);
}

void Player::collision(const Object& obj) {
    if (physics.collision(obj) == Physics::Edge::cd) {
        jumpCounter = 0;
    }
}
