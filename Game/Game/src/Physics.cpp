#include "Physics.hpp"

void Physics::update() {
    this->accel += this->g;
    this->speed += this->accel - (this->speed * this->e);
    this->pos += this->speed.asPoint();
    this->t_speed = speed;

    // 初期化
    this->accel = Vec2::Zero();
    std::fill(collisionEdges, collisionEdges + 4, false);
}

Physics::Edge Physics::collision(const Object& obj) {
    // 定数
    static constexpr float fix_y = 0.1f;    // 埋めたままにする量
    static constexpr float sv = 0.40f;      // 方向の判断基準値

    // 中心座標
    Float2 centerA = Float2(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f));
    Float2 centerB = centerA - speed;

    // ブロックの各頂点
    Float2 a = obj.pos;
    Float2 b(a.x + obj.size.x, a.y);
    Float2 c = a + obj.size;
    Float2 d(a.x, a.y + obj.size.y);


    float dx = abs(centerA.x - (obj.pos.x + obj.size.x / 2.0f));
    float dy = abs(centerA.y - (obj.pos.y + obj.size.y / 2.0f));

    if ((obj.size.x + size.x) / 2.0f > dx &&
        (obj.size.y + size.y) / 2.0f > dy) {
        // 衝突した辺
        Edge edge = Edge::none;

        // 8方向から
        // 北東
        if (t_speed.x > sv && t_speed.y < -sv) {
            if ((b - d).cross(centerA - d) < 0) {
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
        else if (t_speed.x < -sv && t_speed.y > sv) {
            // 南西
            if ((b - d).cross(centerA - d) < 0) {
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
        else if (t_speed.x < -sv && t_speed.y < -sv) {
            // 北西
            if ((a - c).cross(centerA - c) < 0) {
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
        else if (t_speed.x > sv && t_speed.y > sv) {
            // 南東
            if ((a - c).cross(centerA - c) < 0) {
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
        else if (t_speed.x > sv && abs(t_speed.y) <= sv) {
            // →
            speed.x = 0.0f;
            pos.x = obj.pos.x - size.x;
            edge = Edge::bc;
        }
        else if (t_speed.x < -sv && abs(t_speed.y) <= sv) {
            // ←
            speed.x = 0.0f;
            pos.x = obj.pos.x + obj.size.x;
            edge = Edge::da;
        }
        else if (abs(t_speed.x) <= sv && t_speed.y > sv) {
            // ↓
            speed.y = 0.0f;
            pos.y = obj.pos.y - size.y + fix_y;
            edge = Edge::cd;
        }
        else if (abs(t_speed.x) <= sv && t_speed.y < -sv) {
            // ↑
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

bool Physics::collision(const Physics& phy) {
    // 中心座標
    Float2 center1 = Float2(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f));
    Float2 center2 = Float2(phy.pos.x + (phy.size.x / 2.0f), phy.pos.y + (phy.size.y / 2.0f));

    float dx = abs(center1.x - center2.x);
    float dy = abs(center1.y - center2.y);

    if ((phy.size.x + size.x) / 2.0f > dx &&
        (phy.size.y + size.y) / 2.0f > dy) {
        return true;
    }
    else {
        return false;
    }
}
