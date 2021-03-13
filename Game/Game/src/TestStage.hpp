#pragma once

#include "Common.hpp"
#include "Object.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

class TestStage : public MyApp::Scene {
private:
    Array<Object*> objects;
    Array<Enemy *> enemies;
    Player player;
    Camera2DTikisi camera;

    // ScrollY
    Point start_pos;

public:
    TestStage(const InitData& init);
    ~TestStage();

    void update() override;
    void draw() const override;

    void cameraUpdate();
    void generateBlock(const Point& pos);
    void loadStage(const String& file);

    void debugPrint();
};
