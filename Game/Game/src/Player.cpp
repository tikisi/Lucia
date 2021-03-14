#include "Player.hpp"
#include "Enemy.hpp"


void Player::init() {
    state = &PlayerState::standState;
    knockBackCounter = 0;
    _isGround = false;
    hp = 20;

    // 	Texture分割
    const Texture texture(U"UnityChan.png");
    const Size size(64, 64);
    const Array<uint32> num{ 5, 4, 4, 7 };

    textures.resize(num.size());

    for (uint32 i = 0; i < num.size(); i++) {
        for (uint32 j = 0; j < num[i]; j++) {
            textures[i].push_back(texture(Size(j * size.x, i * size.y), size));
        }
    }
}

void Player::update() {
    PlayerState* n_state = state->update(*this);
    if (n_state != nullptr) {
        state = n_state;
        state->entry(*this);
        state->update(*this);
    }

    physics.update();

    // フラグを下げる
    _isGround = false;

    // ノックバック
    if (knockBackCounter != 0) {
        if (knockBackCounter++ == 120) {
            knockBackCounter = 0;
        }
    }

    if (KeyS.down()) {
        this->knockBackCounter = 1;
        this->knockBackDir = DIR::L;
    }
    Print << U"State: " << state->getName();
    Print << U"Speed: " << physics.speed;
    Print << U"Accel: " << physics.accel;
    Print << U"HP:    " << hp;
}

void Player::draw() const {
    auto rect = RectF(physics.pos, physics.size);

    if (knockBackCounter == 0 || (knockBackCounter / 10) % 2 == 1) {
        if (state->dir == PlayerDir::R)
            selectTexture().drawAt(rect.center());
        else
            selectTexture().mirrored().drawAt(rect.center());
    }

    rect.drawFrame(2.0, Palette::White);

    // 衝突した辺
    if (physics.collisionEdges[0])
        rect.top().draw(3.0, Palette::Red);
    if (physics.collisionEdges[1])
        rect.right().draw(3.0, Palette::Red);
    if (physics.collisionEdges[2])
        rect.bottom().draw(3.0, Palette::Red);
    if (physics.collisionEdges[3])
        rect.left().draw(3.0, Palette::Red);
}

void Player::collision(const Object& obj) {
    if (physics.collision(obj) == Physics::Edge::cd) {
        _isGround = true;
    }
}

void Player::collision(const Enemy& enemy) {
    // 無敵状態でないとき
    if (knockBackCounter == 0) {
        if (physics.collision(enemy.physics)) {
            hp -= enemy.getDamage();

            // ノックバック処理
            knockBackCounter = 1;
            // 敵が止まっているとき
            if (Abs(enemy.physics.speed.x) <= 0.1f) {
                if (physics.speed.x < 0.0f) knockBackDir = DIR::R;
                else knockBackDir = DIR::L;
            }
            // 敵が動いているとき
            else {
                if (enemy.physics.speed.x <= 0.1f) knockBackDir = DIR::L;
                else knockBackDir = DIR::R;
            }
        }
    }
}

const TextureRegion& Player::selectTexture() const {
    using type = PlayerStateType;
    switch (state->getType()) {
    case type::STAND:
    case type::DUCK:
    case type::KNOCK_BACK:
        return textures[0][state->getIndex()];
    case type::WALK:
        return textures[1][state->getIndex()];
    case type::RUN:
        return textures[2][state->getIndex()];
    case type::JUMP1:
    case type::JUMP2:
    case type::FALL:
        return textures[3][state->getIndex()];
    default:
        return textures[0][0];
    }
}
