#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/InputManager.h"
#include "../Manager/SaveLoadManager.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Common/Capsule.h"
#include "../Object/Common/Collider.h"
#include "../Object/SkyDome.h"
#include "../Object/Stage.h"
#include "../Object/Metal.h"
#include "../Object/Moon.h"
#include "../Object/Water.h"
#include "../Object/Gate.h"
#include "../Object/Player.h"
#include "../Object/Planet.h"
#include "../Object/UnityStage.h"
#include "../Object/Common/RendererManager.h"
#include "../Object/Common/Renderer.h"
#include "../Object/Common/Material.h"
#include "../Application.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
	player_ = nullptr;
	skyDome_ = nullptr;
	stage_ = nullptr;
}

GameScene::~GameScene(void)
{

}

void GameScene::Init(void)
{

	// プレイヤー
	player_ = std::make_unique<Player>();
	player_->Init();

	// ステージ
	stage_ = std::make_unique<Stage>(*player_);
	stage_->Init();

	// ステージの初期設定
	stage_->ChangeStage(Stage::NAME::JSON_STAGE);

	// スカイドーム
	skyDome_ = std::make_unique<SkyDome>(player_->GetTransform());
	skyDome_->Init();

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Load();

	saveLoadManager_ = std::make_unique<SaveLoadManager>();
	saveLoadManager_->SetPlayer(player_);

	unityStage_ = std::make_unique<UnityStage>();
	unityStage_->Load();

	// メタル
	metal_ = std::make_unique<Metal>();
	metal_->Init();

	// 月
	moon_ = std::make_unique<Moon>();
	moon_->Init();

	// 水
	water_ = std::make_unique<Water>();
	water_->Init();

	// ゲート
	gate_ = std::make_unique<Gate>();
	gate_->Init();

	std::weak_ptr<Camera> camera = SceneManager::GetInstance().GetCamera();
	camera.lock().get()->SetFollow(&player_->GetTransform());
	camera.lock().get()->ChangeMode(Camera::MODE::FOLLOW);

	//// モノクロ
	//std::vector<FLOAT4> constBufsPtr1;
	//constBufsPtr1.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// モノクロテクスチャ
	//std::vector<int> textures1;
	//textures1.push_back(SceneManager::GetInstance().GetMainScreen());

	//// モノマテリアル
	//monoMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Monotone.cso"), sizeof(FLOAT4) * 1, constBufsPtr1, textures1);

	//// モノレンダラー
	//monoRenderer_ = std::make_unique<Renderer>(monoMaterial_);

	//// 走査線
	//std::vector<FLOAT4> constBufsPtr2;
	//constBufsPtr2.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// 走査線テクスチャ
	//std::vector<int>textures2;
	//textures2.push_back(SceneManager::GetInstance().GetMainScreen());

	//// 走査線マテリアル
	//scanMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "ScanLine.cso"), sizeof(FLOAT4) * 1, constBufsPtr2, textures2);

	//// 走査線レンダラー
	//scanRenderer_ = std::make_unique<Renderer>(scanMaterial_);

	//// 歪み
	//std::vector<FLOAT4> constBufsPtr3;
	//constBufsPtr3.push_back({ 1.0f, 128.0f, 128.0f, 10.0f });

	//// 歪みテクスチャ
	//std::vector<int> textures3;
	//textures3.push_back(SceneManager::GetInstance().GetMainScreen());
	//textures3.push_back(LoadGraph("Data/Image/Noise128.png"));

	//// 歪みマテリアル
	//distortionMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Distortion.cso"), sizeof(FLOAT4) * 1, constBufsPtr3, textures3);

	//// 歪みレンダラー
	//distortionRenderer_ = std::make_unique<Renderer>(distortionMaterial_);

	//// ノイズ
	//std::vector<FLOAT4> constBufsPtr4;
	//constBufsPtr4.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// ノイズテクスチャ
	//std::vector<int> textures4;
	//textures4.push_back(SceneManager::GetInstance().GetMainScreen());

	//// ノイズ
	//noiseMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Noise.cso"), sizeof(FLOAT4) * 1, constBufsPtr4, textures4);

	//// ノイズレンダラー
	//noiseRenderer_ = std::make_unique<Renderer>(noiseMaterial_);

	//// モザイク
	//std::vector<FLOAT4> constBufsPtr5;
	//constBufsPtr5.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
	//constBufsPtr5.push_back({ 1024.0f, 640.0f, 10.0f, 0.0f });

	//// モザイクテクスチャ
	//std::vector<int> textures5;
	//textures5.push_back(SceneManager::GetInstance().GetMainScreen());

	//// モザイク
	//mosaicMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Mosaic.cso"), sizeof(FLOAT4) * 2, constBufsPtr5, textures5);

	//// モザイクレンダラー
	//mosaicRenderer_ = std::make_unique<Renderer>(mosaicMaterial_);

}

void GameScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	skyDome_->Update();

	stage_->Update();

	player_->Update();

	saveLoadManager_->Update();

	metal_->Update();

	moon_->Update();

	water_->Update();

	gate_->Update();

}

void GameScene::Draw(void)
{

	// 背景
	skyDome_->Draw();
	stage_->Draw();
	unityStage_->Draw();

	player_->Draw();

	// 半透明
	stage_->DrawTranslucent();

	enemyManager_->Draw();

	metal_->Draw();

	moon_->Draw();

	water_->Draw();

	gate_->Draw();

	// ヘルプ
	//DrawFormatString(840, 20, 0x000000, "移動　　：WASD");
	//DrawFormatString(840, 40, 0x000000, "カメラ　：矢印キー");
	//DrawFormatString(840, 60, 0x000000, "ダッシュ：右Shift");
	//DrawFormatString(840, 80, 0x000000, "ジャンプ：＼(バクスラ)");

	// カメラ座標
	auto camera = SceneManager::GetInstance().GetCamera();
	auto cameraPos = camera.lock()->GetPos();
	//DrawFormatString(20, 20, 0xffffff,
		//"カメラ位置(%.2f,%.2f,%.2f)", cameraPos.x, cameraPos.y, cameraPos.z);

	//deltaTime_ += SceneManager::GetInstance().GetDeltaTime();

	// モノシェーダ
	//monoRenderer_->Draw();

	// 走査線シェーダ
	//scanRenderer_->SetConstBufs({ deltaTime_ / 10,0.0f,0.0f,0.0f }, 0);
	//scanRenderer_->Draw();

	// 歪みレンダラー
	//distortionRenderer_->SetConstBufs({ deltaTime_,0.0f,0.0f,0.0f }, 0);
	//distortionRenderer_->Draw();

	// ノイズレンダラー
	//noiseRenderer_->SetConstBufs({ deltaTime_ / 10,0.0f,0.0f,0.0f }, 0);
	//noiseRenderer_->Draw();

	// モザイクレンダラー
	//mosaicRenderer_->Draw();

}
