#pragma once
#include <Siv3D.hpp>

#include "Object.hpp"

class Physics {
 public:
  // �Փ˂����ӂ�\��
  enum class Edge { ab, bc, cd, da, none};
  Float2 size;
  Float2 pos;
  Float2 speed;
  Float2 accel;
  const Float2 e;  // Vec2(���C�W���A��C��R)
  const Float2 g;  // �d��
  
  Float2 t_speed;   // �����蔻��p�X�s�[�h�x�N�g��

  Physics(Float2 pos, Float2 size, Float2 speed = Float2(0, 0),
          Float2 accel = Float2(0, 0), Float2 e = Float2(0.2f, 0.02f),
          Float2 g = Float2(0, 0.5f))
      : pos(pos), size(size), speed(speed), accel(accel), e(e), g(g) {}

  void update();

  Physics::Edge collision(const Object &obj);
};
