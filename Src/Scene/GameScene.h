#pragma once
#include "SceneBase.h"
class Stage;
class SkyDome;
class Player;
class EnemyManager;
class SaveLoadManager;

class GameScene : public SceneBase
{

public:
	
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// ピクセルシェーダ用のオリジナル定数バッファの使用開始スロット
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;

	// 頂点数
	static constexpr int NUM_VERTEX = 4;

	// 頂点インデックス
	static constexpr int NUM_VERTEX_IDX = 6;

	//ポリゴン数
	static constexpr int NUM_POLYGON = 2;

	// ステージ
	std::unique_ptr<Stage> stage_;

	// スカイドーム
	std::unique_ptr<SkyDome> skyDome_;

	// プレイヤー
	std::shared_ptr<Player> player_;

	// 敵
	std::unique_ptr<EnemyManager> enemyManager_;

	// セーブとロードの管理
	std::unique_ptr<SaveLoadManager> saveLoadManager_;

	// ポストエフェクト用スクリーン(モノクロ)
	int postEffectScreenMono_;

	// シェーダハンドル
	int monoShader_;

	// 定数バッファハンドル
	int monoShaderConstBuf_;

	// セピアカラー
	int sepiaColorConstBuf_;

	float deltaTime_;

	// 頂点
	VERTEX2DSHADER vertexs_[NUM_VERTEX];

	// 頂点インデックス
	WORD indexes_[NUM_VERTEX_IDX];

};
