#include "TestStage.hpp"

TestStage::TestStage(const InitData& init)
    : IScene(init), player(Scene::CenterF() - Float2(0, 10)),
    camera(Scene::Center(), 1.0, Camera2DParameters::NoControl()) {
    /*for (int i = 0; i < 20; i++) {
        objects.push_back(new Block(Float2(72 * i, Scene::CenterF().y + 2.0 * 72.0)));
    }*/
    loadMap(U"stage/test.txt");
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

    // camera
    camera.update();
    camera.setTargetCenter(Vec2(player.physics.pos.x + player.physics.size.x / 2,
        player.physics.pos.y + ((start_pos.y - (int)player.physics.pos.y) % 360)));
    {
        const auto t = camera.createTransformer();
        if (MouseL.down()) {
            generateBlock(Cursor::Pos());
        }
    }
    ClearPrint();
    Print << (start_pos.y - player.physics.pos.y);
}

void TestStage::draw() const {
    {
        // •Ï”t1‚Ì¶‘¶ŠúŠÔ‚Í•`‰æÀ•W‚ª•ÏŠ·‚³‚ê‚é
        const auto t = camera.createTransformer();

        objects.each([](const auto& it) {it->draw(); });
        player.draw();
    }

    Rect(0, Scene::Height() - 100, Scene::Width(), 100)
        .draw(Color(0, 0, 0, 220));
    FontAsset(U"30")(U"UI").drawAt(Scene::Center().x, Scene::Height() - 70, Palette::White);
}

void TestStage::generateBlock(const Point& pos) {
    objects.push_back(new Block(pos));
}

void TestStage::loadMap(const String& file) {
    TextReader reader(file);

    if (!reader) {
        throw Error(U"Failed to open" + file);
    }

    String line;
    for (size_t i = 0; reader.readLine(line); i++) {
        for (size_t j = 0; j < line.size(); j++) {
            switch (line[j])
            {
            case '1':
                objects.push_back(new Block(Float2(j * 72, i * 72)));
                break;
            case 'p':
                player.physics.pos = Float2(j * 72, i * 72);
                start_pos = player.physics.pos.asPoint();
                break;
            default:
                break;
            }
        }
    }
}
