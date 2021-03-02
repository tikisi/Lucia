#include "Player.hpp"

void Player::update() {
/*	// èÛë‘ëJà⁄Å{à⁄ìÆ
	PlayerState *n_state = state->update(*this);
	while (n_state != nullptr) {
		state = n_state;
		n_state = state->update(*this);
	}
*/
	PlayerState* n_state = state->update(*this);
	if (n_state != nullptr) {
		state = n_state;
		state->entry(*this);
	}

	_isGround = false;
	physics.update();

	Print <<  U"State: " + state->getName();
}

void Player::draw() const {
	auto rect = RectF(physics.pos, physics.size);
	TextureAsset(U"Test").resized(rect.size).drawAt(rect.center());
	//rect.drawFrame(2.0, Palette::White);

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
