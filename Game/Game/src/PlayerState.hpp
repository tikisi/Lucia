#pragma once
#include "Player.hpp"

// プレイヤーの向いている方向
enum class PlayerDir {
	L, R
};

class StandState; class WalkState; class RunState; class DuckState;
class Jump1State; class Jump2State; class FallState;

class PlayerState {
protected:
	void changeDir();
public:
	// 各状態
	static StandState standState;
	static WalkState walkState;
	static RunState runState;
	static DuckState duckState;
	static Jump1State jump1State;
	static Jump2State jump2State;
	static FallState fallState;

	// 方向
	inline static PlayerDir dir = PlayerDir::R;

	PlayerState() = default;
	virtual ~PlayerState() = default;

	virtual PlayerState* update(Player& player) = 0;
	virtual void entry(Player& player) {}
};

class OnGrandState : public PlayerState {
public:
	OnGrandState() = default;
	virtual PlayerState* update(Player& player) override;
};

class StandState : public OnGrandState {
public:
	StandState() = default;
	PlayerState* update(Player& player) override;
};

class WalkState : public OnGrandState {
public:
	WalkState() = default;
	PlayerState* update(Player& player) override;
};

class RunState : public OnGrandState {
public:
	RunState() = default;
	PlayerState* update(Player& player) override;
};

class DuckState : public OnGrandState {
public:
	DuckState() = default;
	PlayerState* update(Player& player) override;
};

class Jump1State : public PlayerState {
private:
	uint32 counter;
public:
	Jump1State() = default;
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class Jump2State : public PlayerState {
public:
	Jump2State() = default;
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class FallState : public PlayerState {
public:
	FallState() = default;
	PlayerState* update(Player& player) override;
};
