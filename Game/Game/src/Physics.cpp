#include "Physics.hpp"

void Physics::update() {
    this->accel += this->g;
    this->speed += this->accel - (this->speed * this->e);
    this->pos += this->speed.asPoint();
    this->t_speed = speed;

    // ������
    std::fill(collisionEdges, collisionEdges + 4, false);
}

Physics::Edge Physics::collision(const Object& obj) {
    // �萔
    static constexpr float fix_y = 0.1f;    // ���߂��܂܂ɂ����

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
        // �Փ˂�����
        Edge edge = Edge::none;

        // 8��������
        // �k��
        if (t_speed.x > 0.01f && t_speed.y < -0.01f) {
            if ((b - d).cross(centerB - d) < 0) {
                speed.x = 0.0f;
                pos.x = a.x - size.x;
                edge = Edge::bc;
            }
            else {
                speed.y = 0.0f;
                pos.y = d.y;
                edge = Edge::ab;
            }
        }
        else if (t_speed.x < -0.01f && t_speed.y > 0.01f) {
            // �쐼
            if ((b - d).cross(centerB - d) < 0) {
                speed.y = 0.0f;
                pos.y = a.y - size.y + fix_y;
                edge = Edge::cd;
            }
            else {
                speed.x = 0.0f;
                pos.x = b.x;
                edge = Edge::da;
            }
        }
        else if (t_speed.x < -0.01f && t_speed.y < -0.01f) {
            // �k��
            if ((a - c).cross(centerB - c) < 0) {
                speed.y = 0;
                pos.y = c.y;
                edge = Edge::ab;
            }
            else {
                speed.x = 0;
                pos.x = b.x;
                edge = Edge::da;
            }
        }
        else if (t_speed.x > 0.01f && t_speed.y > 0.01f) {
            // �쓌
            if ((a - c).cross(centerB - c) < 0) {
                speed.x = 0;
                pos.x = a.x - size.x;
                edge = Edge::bc;
            }
            else {
                speed.y = 0.0f;
                pos.y = a.y - size.y + fix_y;
                edge = Edge::cd;
            }
        }
        else if (t_speed.x > 0.01f && abs(t_speed.y) <= 0.01f) {
            // ��
            speed.x = 0.0f;
            pos.x = obj.pos.x - size.x;
            edge = Edge::bc;
        }
        else if (t_speed.x < -0.01f && abs(t_speed.y) <= 0.01f) {
            // ��
            speed.x = 0.0f;
            pos.x = obj.pos.x + obj.size.x;
            edge = Edge::da;
        }
        else if (abs(t_speed.x) <= 0.01f && t_speed.y > 0.01f) {
            // ��
            speed.y = 0.0f;
            pos.y = obj.pos.y - size.y + fix_y;
            edge = Edge::cd;
        }
        else if (abs(t_speed.x) <= 0.01f && t_speed.y < -0.01f) {
            // ��
            speed.y = 0.0f;
            pos.y = obj.pos.y + obj.size.y;
            edge = Edge::ab;
        }

        if (edge != Edge::none)
            collisionEdges[(int)edge] = true;
        return edge;
    }

    return Edge::none;
}
