#pragma once
#include<memory>
#include "SceneBase.h"
class Stage;
class SkyDome;
class Metal;
class Moon;
class Water;
class Player;
class EnemyManager;
class SaveLoadManager;
class UnityStage;
class RendererManager;
class Renderer;
class Material;

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

	// ステージ
	std::shared_ptr<Stage> stage_;

	// スカイドーム
	std::unique_ptr<SkyDome> skyDome_;

	// 金属
	std::shared_ptr<Metal> metal_;

	// 月
	std::shared_ptr<Moon> moon_;

	// 水
	std::shared_ptr<Water> water_;

	// プレイヤー
	std::shared_ptr<Player> player_;

	// 敵
	std::unique_ptr<EnemyManager> enemyManager_;

	// セーブとロードの管理
	std::unique_ptr<SaveLoadManager> saveLoadManager_;

	// Unityから読み込んだステージ
	std::unique_ptr<UnityStage> unityStage_;

	// レンダラーマネージャー
	std::unique_ptr<RendererManager> rendererManager_;

	// モノマテリアル
	std::shared_ptr<Material> monoMaterial_;

	// モノレンダラー
	std::unique_ptr<Renderer> monoRenderer_;

	// 走査線マテリアル
	std::shared_ptr<Material> scanMaterial_;

	// 走査線レンダラー
	std::unique_ptr<Renderer> scanRenderer_;

	// 歪みマテリアル
	std::shared_ptr<Material> distortionMaterial_;

	// 歪みレンダラー
	std::unique_ptr<Renderer> distortionRenderer_;

	// ノイズマテリアル
	std::shared_ptr<Material> noiseMaterial_;

	// ノイズレンダラー
	std::unique_ptr<Renderer> noiseRenderer_;

	// モザイクマテリアル
	std::shared_ptr<Material> mosaicMaterial_;

	// モザイクレンダラー
	std::unique_ptr<Renderer> mosaicRenderer_;

	// デルタタイム
	float deltaTime_;


};
