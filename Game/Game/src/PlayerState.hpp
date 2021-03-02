#pragma once
#include "Common.hpp"

// プレイヤーの向いている方向
enum class PlayerDir {
	L, R
};

class Player;

class StandState; class WalkState; class RunState; class DuckState;
class Jump1State; class Jump2State; class FallState;

class PlayerState {
protected:
	const String name;

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

	PlayerState(const String& name = U"default") : name(name) {};
	virtual ~PlayerState() = default;
	virtual PlayerState* update(Player& player) = 0;
	virtual void entry(Player& player) {}

	bool operator==(const PlayerState &p) { return this->name == p.name; }

	String getName() const { return this->name; };
};

class OnGrandState : public PlayerState {
public:
	OnGrandState(const String& name = U"OnGrandState") : PlayerState(name) {};
	virtual PlayerState* update(Player& player) override;
};

class StandState : public OnGrandState {
public:
	StandState() : OnGrandState(U"StandState") {};
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class WalkState : public OnGrandState {
public:
	WalkState() : OnGrandState(U"WalkState") {}
	PlayerState* update(Player& player) override;
};

class RunState : public OnGrandState {
public:
	RunState() : OnGrandState(U"RunState") {}
	PlayerState* update(Player& player) override;
};

class DuckState : public OnGrandState {
public:
	DuckState() : OnGrandState(U"DuckState") {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class Jump1State : public PlayerState {
private:
	uint32 counter;
public:
	Jump1State() : PlayerState(U"Jump1State") {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class Jump2State : public PlayerState {
public:
	Jump2State() : PlayerState(U"Jump2State") {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class FallState : public PlayerState {
public:
	FallState() : PlayerState(U"FallState") {}
	PlayerState* update(Player& player) override;
};
