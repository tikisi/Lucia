#pragma once
#include <Siv3D.hpp> // OpenSiv3D v0.4.2

#define UNUSED_VAR(x) ((void)(&x))

constexpr int BLOCK_SIZE = 72;

// シーンの名前
enum class StageState {
    TestStage
};

// ゲームデータ
struct GameData {
};

// シーン管理クラス
using MyApp = SceneManager<StageState, GameData>;

inline void LoadFont() {
    FontAsset::Register(U"20", 20);
    FontAsset::Register(U"30", 30);
}

class Camera2DTikisi : public Camera2D {
public:
    Camera2DTikisi(const Vec2& center, double scale = 1.0, const Camera2DParameters& setting = Camera2DParameters::Default()) 
        noexcept : Camera2D(center, scale, setting) {} ;

    Vec2 getTargetCenter() const { return this->m_targetCenter; }
};
