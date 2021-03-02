#include "PlayerState.hpp"
#include "Player.hpp"

StandState PlayerState::standState;
WalkState PlayerState::walkState;
RunState PlayerState::runState;
DuckState PlayerState::duckState;
Jump1State PlayerState::jump1State;
Jump2State PlayerState::jump2State;
FallState PlayerState::fallState;

void PlayerState::changeDir() {
	if (KeyRight.pressed() && !KeyLeft.pressed())
		dir = PlayerDir::R;
	if (KeyRight.pressed() && !KeyLeft.pressed())
		dir = PlayerDir::L;
}

PlayerState* OnGrandState::update(Player& player) {
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
	// ó‘Ô‘JˆÚ
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

	// s“®
	changeDir();

	return nullptr;
}

void StandState::entry(Player& player) {
	player.physics.accel = Vec2::Zero();
}

PlayerState* WalkState::update(Player& player) {
	// ó‘Ô‘JˆÚ
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

	// s“®
	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	return nullptr;
}

PlayerState* RunState::update(Player& player) {
	// ó‘Ô‘JˆÚ
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

	// s“®
	changeDir();
	player.physics.accel = Float2(2.0f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	return nullptr;
}

PlayerState* DuckState::update(Player& player) {
	// ó‘Ô‘JˆÚ
	PlayerState* state = OnGrandState::update(player);

	if (state != nullptr) {
		return state;
	}
	else {
		if (!KeyDown.pressed()) {
			return &PlayerState::standState;
		}
	}

	// s“®
	changeDir();

	return state;
}

void DuckState::entry(Player& player) {
	player.physics.accel = Vec2::Zero();
}

PlayerState* Jump1State::update(Player& player) {
	// ó‘Ô‘JˆÚ
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

	// s“®
	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);
	if (counter++ < 25 && !KeyZ.pressed())
		player.physics.accel.y = 0.5;	// Œ¸‘¬

	return nullptr;
}

void Jump1State::entry(Player& player) {
	counter = 0;
	player.physics.accel.y = -15.0;
}

PlayerState* Jump2State::update(Player& player) {
	// ó‘Ô‘JˆÚ
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

	// s“®
	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	return nullptr;
}

void Jump2State::entry(Player& player) {
	player.physics.speed.y = 0.0f;
	player.physics.accel.y = -15.0f;
}

PlayerState* FallState::update(Player& player) {
	// ó‘Ô‘JˆÚ
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

	// s“®
	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	return nullptr;
}
