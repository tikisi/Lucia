#include "PlayerState.hpp"
#include "Player.hpp"

StandState PlayerState::standState;
WalkState PlayerState::walkState;
RunState PlayerState::runState;
DuckState PlayerState::duckState;
Jump1State PlayerState::jump1State;
Jump2State PlayerState::jump2State;
FallState PlayerState::fallState;
KnockBackState PlayerState::knockBackState;

const HashTable<PlayerStateType, String> PlayerState::toString = {
    {PlayerStateType::STAND, U"STAND"},
    {PlayerStateType::WALK, U"WALK"},
    {PlayerStateType::RUN, U"RUN"},
    {PlayerStateType::DUCK, U"DUCK"},
    {PlayerStateType::JUMP1, U"JUMP1"},
    {PlayerStateType::JUMP2, U"JUMP2"},
    {PlayerStateType::FALL, U"FALL"},
    {PlayerStateType::ONGRAND, U"ONGRAND"},
    {PlayerStateType::KNOCK_BACK, U"KNOCK_BACK"},
    {PlayerStateType::DEFAULT, U"DEFAULT"},
};

void PlayerState::changeDir() {
    if (KeyRight.pressed() && !KeyLeft.pressed())
        dir = PlayerDir::R;
    if (!KeyRight.pressed() && KeyLeft.pressed())
        dir = PlayerDir::L;
}

PlayerState* PlayerState::update(Player& player) {
    UNUSED_VAR(player);
    if (player.getKnockBackCounter() == 1) {
        return &knockBackState;
    }

    return nullptr;
}

PlayerState* OnGrandState::update(Player& player) {
    PlayerState* state = PlayerState::update(player);

    if (state != nullptr) {
        return state;
    }

    if (KeyZ.down()) {
        return &PlayerState::jump1State;
    }
    if (KeyDown.pressed()) {
        return &PlayerState::duckState;
    }
    if (!player.isGround()) {
        return &PlayerState::fallState;
    }

    return nullptr;
}

PlayerState* StandState::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = OnGrandState::update(player);

    if (state != nullptr) {
        return state;
    }
    else {
        if ((KeyRight.pressed() ^ KeyLeft.pressed())) {
            if (KeyShift.pressed())
                return &PlayerState::runState;
            else
                return &PlayerState::walkState;
        }
    }

    // çsìÆ
    changeDir();

    // Index
    if (++counter >= 60) {
        counter = 0;
    }

    return nullptr;
}

void StandState::entry(Player& player) {
    player.physics.accel = Vec2::Zero();
    counter = 0;
}

uint32 StandState::getIndex() const { return counter / 20; }

PlayerState* WalkState::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = OnGrandState::update(player);

    if (state != nullptr) {
        return state;
    }
    else {
        if (!(KeyRight.pressed() ^ KeyLeft.pressed())) {
            return &PlayerState::standState;
        }
        else if (KeyShift.pressed()) {
            return &PlayerState::runState;
        }
    }

    // çsìÆ
    changeDir();
    player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

    // Index
    if (++counter >= 32) {
        counter = 0;
    }

    return nullptr;
}

void WalkState::entry(Player& player) { counter = 0; }

uint32 WalkState::getIndex() const { return counter / 8; }

PlayerState* RunState::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = OnGrandState::update(player);

    if (state != nullptr) {
        return state;
    }
    else {
        if (!(KeyRight.pressed() ^ KeyLeft.pressed())) {
            return &PlayerState::standState;
        }
        else if (!KeyShift.pressed()) {
            return &PlayerState::walkState;
        }
    }

    // çsìÆ
    changeDir();
    player.physics.accel = Float2(2.0f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

    // Index
    if (++counter >= 32) {
        counter = 0;
    }

    return nullptr;
}

void RunState::entry(Player& player) { counter = 0; }

uint32 RunState::getIndex() const { return counter / 8; }

PlayerState* DuckState::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = OnGrandState::update(player);

    if (state != nullptr) {
        return state;
    }
    else {
        if (!KeyDown.pressed()) {
            return &PlayerState::standState;
        }
    }

    // çsìÆ
    changeDir();

    return state;
}

void DuckState::entry(Player& player) {
    player.physics.accel = Vec2::Zero();
}

PlayerState* Jump1State::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = PlayerState::update(player);
    if (state != nullptr) {
        return state;
    }

    if (player.isGround()) {
        if (KeyLeft.pressed() ^ KeyRight.pressed()) {
            if ((KeyShift.pressed())) {
                return &PlayerState::runState;
            }
            else {
                return &PlayerState::walkState;
            }
        }
        else {
            return &PlayerState::standState;
        }
    }
    if (player.physics.speed.y >= 0) {
        return &PlayerState::fallState;
    }
    if (KeyZ.down()) {
        return &PlayerState::jump2State;
    }

    // çsìÆ
    changeDir();
    player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);
    if (counter++ < 25 && !KeyZ.pressed())
        player.physics.accel.y = 0.5;	// å∏ë¨

    // Index
    counter++;

    return nullptr;
}

void Jump1State::entry(Player& player) {
    counter = 0;
    player.physics.accel.y = -15.0;
}

uint32 Jump1State::getIndex() const {
    return counter / 12;
}

PlayerState* Jump2State::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = PlayerState::update(player);
    if (state != nullptr) {
        return state;
    }

    if (player.isGround()) {
        if (KeyLeft.pressed() ^ KeyRight.pressed()) {
            if ((KeyShift.pressed())) {
                return &PlayerState::runState;
            }
            else {
                return &PlayerState::walkState;
            }
        }
        else {
            return &PlayerState::standState;
        }
    }
    if (player.physics.speed.y >= 0) {
        return &PlayerState::fallState;
    }

    // çsìÆ
    changeDir();
    player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

    return nullptr;
}

void Jump2State::entry(Player& player) {
    player.physics.speed.y = 0.0f;
    player.physics.accel.y = -15.0f;
}

PlayerState* FallState::update(Player& player) {
    // èÛë‘ëJà⁄
    PlayerState* state = PlayerState::update(player);
    if (state != nullptr) {
        return state;
    }

    if (player.isGround()) {
        if (KeyLeft.pressed() ^ KeyRight.pressed()) {
            if ((KeyShift.pressed())) {
                return &PlayerState::runState;
            }
            else {
                return &PlayerState::walkState;
            }
        }
        else {
            return &PlayerState::standState;
        }
    }

    // çsìÆ
    changeDir();
    player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

    return nullptr;
}

void KnockBackState::entry(Player& player) {
    if (player.getKnockBackDir() == DIR::R)
        player.physics.accel = Float2(20.0f, -8.0);
    else
        player.physics.accel = Float2(-20.0f, -8.0);

    counter = 0;
}

PlayerState* KnockBackState::update(Player& player) {
    // ñ≥ìGèÛë‘Ç™èIóπÇµÇΩÇÁ
    if (counter++ > 50) {
        if (player.isGround()) {
            if (KeyLeft.pressed() ^ KeyRight.pressed()) {
                if ((KeyShift.pressed())) {
                    return &PlayerState::runState;
                }
                else {
                    return &PlayerState::walkState;
                }
            }
            else {
                return &PlayerState::standState;
            }
        }
        else {
            return &PlayerState::fallState;
        }
    }

    if (counter < 30) {
        if (player.getKnockBackDir() == DIR::R) {
            player.physics.accel.x = 1.5f;
        }
        else if (player.getKnockBackDir() == DIR::L) {
            player.physics.accel.x = -1.5f;
        }
    }

    return nullptr;
}
