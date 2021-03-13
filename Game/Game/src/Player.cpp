#include "Player.hpp"


void Player::init() {
	state = &PlayerState::standState;
	knockBackFlag = false;
	_isGround = false;

	// 	Textureï™äÑ
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

	// ÉtÉâÉOÇâ∫Ç∞ÇÈ
	_isGround = false;


	if (KeyS.down()) {
		this->knockBackFlag = true;
		this->knockBackDir = DIR::L;
	}
	Print << U"State: " << state->getName();
	Print << U"Speed: " << physics.speed;
	Print << U"Accel: " << physics.accel;
}

void Player::draw() const {
	auto rect = RectF(physics.pos, physics.size);
	if (state->dir == PlayerDir::R)
		textures[Min(static_cast<int>(state->getType()), 3)][state->getIndex()].drawAt(rect.center());
	else
		textures[Min(static_cast<int>(state->getType()), 3)][state->getIndex()].mirrored().drawAt(rect.center());

	rect.drawFrame(2.0, Palette::White);

	// è’ìÀÇµÇΩï”
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
