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

	// �v���C���[
	player_ = std::make_unique<Player>();
	player_->Init();

	// �X�e�[�W
	stage_ = std::make_unique<Stage>(*player_);
	stage_->Init();

	// �X�e�[�W�̏����ݒ�
	stage_->ChangeStage(Stage::NAME::JSON_STAGE);

	// �X�J�C�h�[��
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

	//// �|�X�g�G�t�F�N�g�p�X�N���[��(���m�g�[��)
	//postEffectScreenMono_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//// �s�N�Z���V�F�[�_�̃��[�h
	//monoShader_ = LoadPixelShader((Application::PATH_SHADER + "Monotone.cso").c_str());

	//// �s�N�Z���V�F�[�_�p�̒萔�o�b�t�@���쐬
	//monoShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * 3);

	std::vector<FLOAT4> constBufsPtr1;
	constBufsPtr1.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// �O���[�X�P�[��
	monoMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Monotone.cso"),sizeof(FLOAT4) * 1, constBufsPtr1);
	
	// ���m�����_���[
	monoRenderer_ = std::make_unique<Renderer>(monoMaterial_);

	std::vector<FLOAT4> constBufsPtr2;
	constBufsPtr2.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// ������
	scanMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "ScanLine.cso"), sizeof(FLOAT4) * 1, constBufsPtr2);

	// �����������_���[
	scanRenderer_ = std::make_unique<Renderer>(scanMaterial_);

	//rendererManager_ = std::make_unique<RendererManager>();

	//rendererManager_->Add((Application::PATH_SHADER + "Monotone.cso"), sizeof(FLOAT4) * 1, 1);
	//rendererManager_->Add((Application::PATH_SHADER + "ScanLine.cso"), sizeof(FLOAT4) * 1, 1);

	// �|�X�g�G�t�F�N�g�p�X�N���[��(������)
	//postEffectScreenScan_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	// �s�N�Z���V�F�[�_�̃��[�h
	//scanShader_ = LoadPixelShader((Application::PATH_SHADER + "ScanLine.cso").c_str());

	// �s�N�Z���V�F�[�_�p�̒萔�o�b�t�@���쐬
	//scanShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * 1);

}

void GameScene::Update(void)
{

	// �V�[���J��
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

	// �w�i
	skyDome_->Draw();
	stage_->Draw();
	unityStage_->Draw();
	
	player_->Draw();

	enemyManager_->Draw();

	// �w���v
	DrawFormatString(840, 20, 0x000000, "�ړ��@�@�FWASD");
	DrawFormatString(840, 40, 0x000000, "�J�����@�F���L�[");
	DrawFormatString(840, 60, 0x000000, "�_�b�V���F�EShift");
	DrawFormatString(840, 80, 0x000000, "�W�����v�F�_(�o�N�X��)");

	// ���m�V�F�[�_
  	monoRenderer_->Draw();

	// �������V�F�[�_
	deltaTime_ -= SceneManager::GetInstance().GetDeltaTime();
	scanRenderer_->SetConstBufs({ deltaTime_ / 10,0.0f,0.0f,0.0f }, 0);
	scanRenderer_->Draw();

}
