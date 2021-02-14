
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

// シーンの名前
enum class StageState
{
    TestStage
};

// ゲームデータ
struct GameData
{
};

// シーン管理クラス
using MyApp = SceneManager<StageState, GameData>;

inline void LoadFont() {
    FontAsset::Register(U"20", 20);
    FontAsset::Register(U"30", 30);
}
