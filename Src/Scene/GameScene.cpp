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

	DeleteGraph(postEffectScreenMono_);
	DeleteGraph(postEffectScreenScan_);

	DeleteShader(monoShader_);
	DeleteShader(scanShader_);

	DeleteShaderConstantBuffer(monoShaderConstBuf_);
	DeleteShaderConstantBuffer(scanShaderConstBuf_);

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

	std::weak_ptr<Camera> camera = SceneManager::GetInstance().GetCamera();
	camera.lock().get()->SetFollow(&player_->GetTransform());
	camera.lock().get()->ChangeMode(Camera::MODE::FOLLOW);
	//SceneManager::GetInstance().GetCamera().lock().get().SetFollow(&player_->GetTransform());
	//SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FOLLOW);

	//// ポストエフェクト用スクリーン(モノトーン)
	//postEffectScreenMono_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//// ピクセルシェーダのロード
	//monoShader_ = LoadPixelShader((Application::PATH_SHADER + "Monotone.cso").c_str());

	//// ピクセルシェーダ用の定数バッファを作成
	//monoShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * 3);

	std::vector<FLOAT4> constBufsPtr1;
	constBufsPtr1.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// グレースケール
	monoMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Monotone.cso"),sizeof(FLOAT4) * 1, constBufsPtr1);
	
	// モノレンダラー
	monoRenderer_ = std::make_unique<Renderer>(monoMaterial_);

	std::vector<FLOAT4> constBufsPtr2;
	constBufsPtr2.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// 走査線
	scanMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "ScanLine.cso"), sizeof(FLOAT4) * 1, constBufsPtr2);

	// 走査線レンダラー
	scanRenderer_ = std::make_unique<Renderer>(scanMaterial_);

	//rendererManager_ = std::make_unique<RendererManager>();

	//rendererManager_->Add((Application::PATH_SHADER + "Monotone.cso"), sizeof(FLOAT4) * 1, 1);
	//rendererManager_->Add((Application::PATH_SHADER + "ScanLine.cso"), sizeof(FLOAT4) * 1, 1);

	// ポストエフェクト用スクリーン(走査線)
	//postEffectScreenScan_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	// ピクセルシェーダのロード
	//scanShader_ = LoadPixelShader((Application::PATH_SHADER + "ScanLine.cso").c_str());

	// ピクセルシェーダ用の定数バッファを作成
	//scanShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * 1);

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

}

void GameScene::Draw(void)
{

	// 背景
	skyDome_->Draw();
	stage_->Draw();
	unityStage_->Draw();
	
	player_->Draw();

	enemyManager_->Draw();

	// ヘルプ
	DrawFormatString(840, 20, 0x000000, "移動　　：WASD");
	DrawFormatString(840, 40, 0x000000, "カメラ　：矢印キー");
	DrawFormatString(840, 60, 0x000000, "ダッシュ：右Shift");
	DrawFormatString(840, 80, 0x000000, "ジャンプ：＼(バクスラ)");

	// モノシェーダ
  	monoRenderer_->Draw();

	// 走査線シェーダ
	deltaTime_ -= SceneManager::GetInstance().GetDeltaTime();
	scanRenderer_->SetConstBufs({ deltaTime_ / 10,0.0f,0.0f,0.0f }, 0);
	scanRenderer_->Draw();

}
