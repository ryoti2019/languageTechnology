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

	DeleteShader(monoShader_);

	DeleteShaderConstantBuffer(monoShaderConstBuf_);

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
	stage_->ChangeStage(Stage::NAME::MAIN_PLANET);

	// スカイドーム
	skyDome_ = std::make_unique<SkyDome>(player_->GetTransform());
	skyDome_->Init();

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Load();

	saveLoadManager_ = std::make_unique<SaveLoadManager>();
	saveLoadManager_->SetPlayer(player_);

	std::weak_ptr<Camera> camera = SceneManager::GetInstance().GetCamera();
	camera.lock().get()->SetFollow(&player_->GetTransform());
	camera.lock().get()->ChangeMode(Camera::MODE::FOLLOW);
	//SceneManager::GetInstance().GetCamera().lock().get().SetFollow(&player_->GetTransform());
	//SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FOLLOW);

	// ポストエフェクト用スクリーン
	postEffectScreenMono_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	// ピクセルシェーダのロード
	monoShader_ = LoadPixelShader((Application::PATH_SHADER + "Monotone.cso").c_str());

	// ピクセルシェーダ用の定数バッファを作成
	monoShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * 3);

	// 画面全体を覆う2つのポリゴン

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
	
	player_->Draw();

	enemyManager_->Draw();

	// ヘルプ
	DrawFormatString(840, 20, 0x000000, "移動　　：WASD");
	DrawFormatString(840, 40, 0x000000, "カメラ　：矢印キー");
	DrawFormatString(840, 60, 0x000000, "ダッシュ：右Shift");
	DrawFormatString(840, 80, 0x000000, "ジャンプ：＼(バクスラ)");

	// メインスクリーン
	int mainScreen = SceneManager::GetInstance().GetMainScreen();
	SetDrawScreen(postEffectScreenMono_);

	// 画面を初期化
	ClearDrawScreen();

	// オリジナルシェーダ設定(ON)
	MV1SetUseOrigShader(true);

	// 頂点インデックス
	for (auto& v : vertexs_)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// 左上
	vertexs_[0].pos = { 0.0f, 0.0f, 0.0f };
	vertexs_[0].u = 0.0f;
	vertexs_[0].v = 0.0f;
	// 右上
	vertexs_[1].pos = { Application::SCREEN_SIZE_X, 0.0f, 0.0f };
	vertexs_[1].u = 1.0f;
	vertexs_[1].v = 0.0f;
	// 左下
	vertexs_[2].pos = { 0.0f, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[2].u = 0.0f;
	vertexs_[2].v = 1.0f;
	// 右下
	vertexs_[3].pos = { Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[3].u = 1.0f;
	vertexs_[3].v = 1.0f;

	//0,1,2 1,3,2
	indexes_[0] = 0;
	indexes_[1] = 1;
	indexes_[2] = 2;
	indexes_[3] = 1;
	indexes_[4] = 3;
	indexes_[5] = 2;

	// シェーダ設定
	SetUsePixelShader(monoShader_);

	// テクスチャの設定
	SetUseTextureToShader(0, mainScreen);

	// 定数バッファ
	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(monoShaderConstBuf_);

	// 乗算色
	constBufsPtr->x = 1.0f;
	constBufsPtr->y = 1.0f;
	constBufsPtr->z = 1.0f;
	constBufsPtr->w = 1.0f;

	constBufsPtr++;

	constBufsPtr->x = 5.0f;
	constBufsPtr->y = 5.0f;
	constBufsPtr->z = 5.0f;

	deltaTime_ -= SceneManager::GetInstance().GetDeltaTime();
	constBufsPtr->w = deltaTime_ / 4;

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(monoShaderConstBuf_);

	// 定数バッファをピクセルシェーダー用定数バッファレジスタに
	SetShaderConstantBuffer(monoShaderConstBuf_, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// 描画
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_VERTEX_IDX);

	// 後始末
	//--------------------------------------------

	// テクスチャ解除
	SetUseTextureToShader(0, -1);

	// ピクセルシェーダ解除
	SetUsePixelShader(-1);

	// オリジナルシェーダ設定(OFF)
	MV1SetUseOrigShader(false);
	//--------------------------------------------

	// メインに戻す
	SetDrawScreen(mainScreen);
	DrawGraph(0, 0, postEffectScreenMono_, false);
	//--------------------------------------------

}
