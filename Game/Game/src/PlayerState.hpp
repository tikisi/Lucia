#pragma once
#include "Common.hpp"

// プレイヤーの向いている方向
enum class PlayerDir {
	L, R
};

enum class PlayerStateType : uint32 {
	STAND,
	WALK,
	RUN,
	DUCK,
	JUMP1,
	JUMP2,
	FALL,
	ONGRAND,
	DEFAULT
};

class Player;
class StandState; class WalkState; class RunState; class DuckState;
class Jump1State; class Jump2State; class FallState; class OnGrandState;

class PlayerState {
protected:
	const PlayerStateType type;
	void changeDir();

public:
	// 方向
	inline static PlayerDir dir = PlayerDir::R;

	// enum to string
	static const HashTable<PlayerStateType, String> toString;

	// 各状態
	static StandState standState;
	static WalkState walkState;
	static RunState runState;
	static DuckState duckState;
	static Jump1State jump1State;
	static Jump2State jump2State;
	static FallState fallState;

	PlayerState(const PlayerStateType type = PlayerStateType::DEFAULT) : type(type) {};
	virtual ~PlayerState() = default;
	bool operator==(const PlayerState& p) { return this->type == p.type; }

	// override
	virtual PlayerState* update(Player& player) = 0;
	virtual void entry(Player& player) { UNUSED_VAR(player); }
	virtual uint32 getIndex() const { return 0; };

	// utility
	PlayerStateType getType() const { return this->type; }
	String getName() const { return toString.at(this->type); }
};

class OnGrandState : public PlayerState {
public:
	OnGrandState(const PlayerStateType type = PlayerStateType::ONGRAND) : PlayerState(type) {};
	virtual PlayerState* update(Player& player) override;
};

class StandState : public OnGrandState {
private:
	uint32 counter;

public:
	StandState() : OnGrandState(PlayerStateType::STAND) {};
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
	uint32 getIndex() const override;
};

class WalkState : public OnGrandState {
private:
	uint32 counter;

public:
	WalkState() : OnGrandState(PlayerStateType::WALK) {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
	uint32 getIndex() const override;
};

class RunState : public OnGrandState {
private:
	uint32 counter;

public:
	RunState() : OnGrandState(PlayerStateType::RUN) {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
	uint32 getIndex() const override;
};

class DuckState : public OnGrandState {
public:
	DuckState() : OnGrandState(PlayerStateType::DUCK) {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class Jump1State : public PlayerState {
private:
	uint32 counter;
public:
	Jump1State() : PlayerState(PlayerStateType::JUMP1) {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
	uint32 getIndex() const override;
};

class Jump2State : public PlayerState {
public:
	Jump2State() : PlayerState(PlayerStateType::JUMP2) {}
	PlayerState* update(Player& player) override;
	void entry(Player& player) override;
};

class FallState : public PlayerState {
public:
	FallState() : PlayerState(PlayerStateType::FALL) {}
	PlayerState* update(Player& player) override;
};
