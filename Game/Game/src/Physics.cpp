#include "Physics.hpp"

void Physics::update() {
    this->accel += this->g;
    this->speed += this->accel - (this->speed * this->e);
    this->pos += this->speed.asPoint();
    this->t_speed = speed;
}

Physics::Edge Physics::collision(const Object& obj) {
    // ���S���W
    Float2 centerA = Float2(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f));
    Float2 centerB = centerA - speed;

    // �u���b�N�̊e���_
    Float2 a = obj.pos;
    Float2 b(a.x + obj.size.x, a.y);
    Float2 c = a + obj.size;
    Float2 d(a.x, a.y + obj.size.y);

    float dx = abs(centerA.x - (obj.pos.x + obj.size.x / 2.0f));
    float dy = abs(centerA.y - (obj.pos.y + obj.size.y / 2.0f));

    if ((obj.size.x + size.x) / 2.0f > dx &&
        (obj.size.y + size.y) / 2.0f > dy) {
        // 8��������
        // �k��
        if (t_speed.x > 0.01f && t_speed.y < -0.01f) {
            if ((b - d).cross(centerB - d) < 0) {
                speed.x = 0.0f;
                pos.x = a.x - size.x;
                return Edge::bc;
            }
            else {
                speed.y = 0.0f;
                pos.y = d.y;
                return Edge::ab;
            }
        }
        else if (t_speed.x < -0.01f && t_speed.y > 0.01f) {
            // �쐼
            if ((b - d).cross(centerB - d) < 0) {
                speed.y = 0.0f;
                pos.y = a.y - size.y;
                return Edge::cd;
            }
            else {
                speed.x = 0.0f;
                pos.x = b.x;
                return Edge::da;
            }
        }
        else if (t_speed.x < -0.01f && t_speed.y < -0.01f) {
            // �k��
            if ((a - c).cross(centerB - c) < 0) {
                speed.y = 0;
                pos.y = c.y;
                return Edge::ab;
            }
            else {
                speed.x = 0;
                pos.x = b.x;
                return Edge::da;
            }
        }
        else if (t_speed.x > 0.01f && t_speed.y > 0.01f) {
            //�쓌
            if ((a - c).cross(centerB - c) < 0) {
                speed.x = 0;
                pos.x = a.x - size.x;
                return Edge::bc;
            }
            else {
                speed.y = 0.0f;
                pos.y = a.y - size.y;
                return Edge::cd;
            }
        }
        else if (t_speed.x > 0.01f && abs(t_speed.y) <= 0.01f) {
            // ��
            speed.x = 0.0f;
            pos.x = obj.pos.x - size.x;
            return Edge::bc;
        }
        else if (t_speed.x < -0.01f && abs(t_speed.y) <= 0.01f) {
            // ��
            speed.x = 0.0f;
            pos.x = obj.pos.x + obj.size.x;
            return Edge::da;
        }
        else if (abs(t_speed.x) <= 0.01f && t_speed.y > 0.01f) {
            // ��
            speed.y = 0.0f;
            pos.y = obj.pos.y - size.y;
            return Edge::cd;
        }
        else if (abs(t_speed.x) <= 0.01f && t_speed.y < -0.01f) {
            // ��
            speed.y = 0.0f;
            pos.y = obj.pos.y + obj.size.y;
            return Edge::ab;
        }
    }

    return Edge::none;
}
