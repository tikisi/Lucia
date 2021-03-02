#include "PlayerState.hpp"
#include "Common.hpp"

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
	if (KeyDown.down()) {
		return &PlayerState::duckState;
	}
	if (!player.isGround()) {
		return &PlayerState::fallState;
	}

	return nullptr;
}

PlayerState* StandState::update(Player& player) {
	PlayerState* state = OnGrandState::update(player);

	changeDir();

	if (state == nullptr) {
		if ((KeyRight | KeyLeft).down()) {
			if (KeyShift.pressed())
				state = &PlayerState::runState;
			else
				state = &PlayerState::walkState;
		}
	}

	return state;
}

PlayerState* WalkState::update(Player& player) {
	PlayerState* state = OnGrandState::update(player);

	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	if (state == nullptr) {
		if (!(KeyRight.pressed() ^ KeyLeft.pressed())) {
			state = &PlayerState::standState;
		}
		else if (KeyShift.pressed()) {
			state = &PlayerState::runState;
		}
	}

	return state;
}

PlayerState* RunState::update(Player& player) {
	PlayerState* state = OnGrandState::update(player);

	changeDir();
	player.physics.accel = Float2(2.0f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	if (state == nullptr) {
		if (!(KeyRight.pressed() ^ KeyLeft.pressed())) {
			state = &PlayerState::standState;
		}
		else if (!KeyShift.pressed()) {
			state = &PlayerState::walkState;
		}
	}

	return state;
}

PlayerState* DuckState::update(Player& player) {
	PlayerState* state = OnGrandState::update(player);

	changeDir();

	if (state == nullptr) {
		if (!KeyDown.pressed()) {
			state = &PlayerState::standState;
		}
	}

	return state;
}

PlayerState* Jump1State::update(Player& player) {

	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);
	// Œ¸‘¬
	if (counter++ < 25 && !KeyZ.pressed())
		player.physics.accel.y = 0.5;

	if (player.isGround()) {
		return &PlayerState::standState;
	}
	if (player.physics.speed.y >= 0) {
		return &PlayerState::fallState;
	}
	if (KeyZ.down()) {
		return &PlayerState::jump2State;
	}

	return nullptr;
}

void Jump1State::entry(Player& player) {
	counter = 0;
	player.physics.accel.y = -15.0;
}

PlayerState* Jump2State::update(Player& player) {
	changeDir();
	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	if (player.isGround()) {
		return &PlayerState::standState;
	}
	if (player.physics.speed.y >= 0) {
		return &PlayerState::fallState;
	}

	return nullptr;
}

void Jump2State::entry(Player& player) {
	player.physics.speed.y = 0.0f;
	player.physics.accel.y = -15.0f;
}

PlayerState* FallState::update(Player& player) {
	changeDir();

	player.physics.accel = Float2(1.5f * (KeyRight.pressed() - KeyLeft.pressed()), 0);

	if (player.isGround()) {
		return &PlayerState::fallState;
	}

	return nullptr;
}
