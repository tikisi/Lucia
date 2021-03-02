#include "TestStage.hpp"

TestStage::TestStage(const InitData& init)
    : IScene(init), player(Scene::CenterF() - Float2(0, 10)),
    camera(Scene::Center(), 1.0, Camera2DParameters::NoControl()) {
    /*for (int i = 0; i < 20; i++) {
        objects.push_back(new Block(Float2(72 * i, Scene::CenterF().y + 2.0 * 72.0)));
    }*/
    loadStage(U"stage/test.txt");
}

TestStage::~TestStage() {
    for (auto it = objects.begin(); it != objects.end();) {
        delete* it;
        it = objects.erase(it);
    }
}

void TestStage::update() {
    // Update
    objects.each([](const auto& it) {it->update(); });
    player.update();

    // Collision
    objects.each([&](const auto& it) {player.collision(*it); });

    cameraUpdate();
    // 変換後の座標での処理 
    {
        const auto t = camera.createTransformer();
        if (MouseL.down()) {
            generateBlock(Cursor::Pos());
        }
    }

    debugPrint();
}

void TestStage::draw() const {
    {
        // 変数t1の生存期間は描画座標が変換される
        const auto t = camera.createTransformer();

        objects.each([](const auto& it) {it->draw(); });
        player.draw();
    }

    Rect(0, Scene::Height() - 100, Scene::Width(), 100)
        .draw(Color(0, 0, 0, 220));
    FontAsset(U"30")(U"UI").drawAt(Scene::Center().x, Scene::Height() - 70, Palette::White);
}

void TestStage::cameraUpdate() {
    camera.update();

    Float2 p_pos = player.getPos();
    Point c_pos = camera.getCenter().asPoint();
    int dy = start_pos.y - (int)p_pos.y;
    int n_y = p_pos.y + (dy < 0 ? 384 - (abs(dy) % 384) : dy % 384);

    Print << U"p_pos: {}"_fmt(p_pos.y);
    Print << U"n_y: {}"_fmt(n_y);

    // 上がって地面に着地　または　下がったときにYをスクロール
    if ((n_y <= c_pos.y && player.isGround()) || n_y >= c_pos.y)
        camera.setTargetCenter(Vec2(p_pos.x, n_y));
    else
        camera.setTargetCenter(Vec2(p_pos.x, camera.getTargetCenter().y));
}

void TestStage::generateBlock(const Point& pos) {
    objects.push_back(new Block(pos));
}

void TestStage::loadStage(const String& file) {
    TextReader reader(file);

    if (!reader) {
        throw Error(U"Failed to open" + file);
    }

    String line;
    for (size_t i = 0; reader.readLine(line); i++) {
        for (size_t j = 0; j < line.size(); j++) {
            switch (line[j]) {
            case '1':
                objects.push_back(new Block(Float2(j * BLOCK_SIZE, i * BLOCK_SIZE)));
                break;
            case 'p':
                player.physics.pos = Float2(j * BLOCK_SIZE, i * BLOCK_SIZE);
                start_pos = player.physics.pos.asPoint();
                break;
            default:
                break;
            }
        }
    }
}

void TestStage::debugPrint() {
    Print << U"s - p: {}"_fmt(start_pos.y - player.physics.pos.y);
}
