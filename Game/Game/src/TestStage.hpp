#pragma once

#include "Common.hpp"
#include "Object.hpp"
#include "Player.hpp"

class TestStage : public MyApp::Scene {
private:
    Array<Object*> objects;
    Player player;
    Camera2D camera;

    // ScrollY
    Point start_pos;

public:
    TestStage(const InitData& init);
    ~TestStage();

    void update() override;
    void draw() const override;

    void generateBlock(const Point& pos);
    void loadMap(const String& file);
};
