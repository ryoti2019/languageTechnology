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

	// ���^��
	metal_ = std::make_unique<Metal>();
	metal_->Init();

	// ��
	moon_ = std::make_unique<Moon>();
	moon_->Init();

	// ��
	water_ = std::make_unique<Water>();
	water_->Init();

	// �Q�[�g
	gate_ = std::make_unique<Gate>();
	gate_->Init();

	std::weak_ptr<Camera> camera = SceneManager::GetInstance().GetCamera();
	camera.lock().get()->SetFollow(&player_->GetTransform());
	camera.lock().get()->ChangeMode(Camera::MODE::FOLLOW);

	//// ���m�N��
	//std::vector<FLOAT4> constBufsPtr1;
	//constBufsPtr1.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// ���m�N���e�N�X�`��
	//std::vector<int> textures1;
	//textures1.push_back(SceneManager::GetInstance().GetMainScreen());

	//// ���m�}�e���A��
	//monoMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Monotone.cso"), sizeof(FLOAT4) * 1, constBufsPtr1, textures1);

	//// ���m�����_���[
	//monoRenderer_ = std::make_unique<Renderer>(monoMaterial_);

	//// ������
	//std::vector<FLOAT4> constBufsPtr2;
	//constBufsPtr2.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// �������e�N�X�`��
	//std::vector<int>textures2;
	//textures2.push_back(SceneManager::GetInstance().GetMainScreen());

	//// �������}�e���A��
	//scanMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "ScanLine.cso"), sizeof(FLOAT4) * 1, constBufsPtr2, textures2);

	//// �����������_���[
	//scanRenderer_ = std::make_unique<Renderer>(scanMaterial_);

	//// �c��
	//std::vector<FLOAT4> constBufsPtr3;
	//constBufsPtr3.push_back({ 1.0f, 128.0f, 128.0f, 10.0f });

	//// �c�݃e�N�X�`��
	//std::vector<int> textures3;
	//textures3.push_back(SceneManager::GetInstance().GetMainScreen());
	//textures3.push_back(LoadGraph("Data/Image/Noise128.png"));

	//// �c�݃}�e���A��
	//distortionMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Distortion.cso"), sizeof(FLOAT4) * 1, constBufsPtr3, textures3);

	//// �c�݃����_���[
	//distortionRenderer_ = std::make_unique<Renderer>(distortionMaterial_);

	//// �m�C�Y
	//std::vector<FLOAT4> constBufsPtr4;
	//constBufsPtr4.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// �m�C�Y�e�N�X�`��
	//std::vector<int> textures4;
	//textures4.push_back(SceneManager::GetInstance().GetMainScreen());

	//// �m�C�Y
	//noiseMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Noise.cso"), sizeof(FLOAT4) * 1, constBufsPtr4, textures4);

	//// �m�C�Y�����_���[
	//noiseRenderer_ = std::make_unique<Renderer>(noiseMaterial_);

	//// ���U�C�N
	//std::vector<FLOAT4> constBufsPtr5;
	//constBufsPtr5.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
	//constBufsPtr5.push_back({ 1024.0f, 640.0f, 10.0f, 0.0f });

	//// ���U�C�N�e�N�X�`��
	//std::vector<int> textures5;
	//textures5.push_back(SceneManager::GetInstance().GetMainScreen());

	//// ���U�C�N
	//mosaicMaterial_ = std::make_unique<Material>((Application::PATH_SHADER + "Mosaic.cso"), sizeof(FLOAT4) * 2, constBufsPtr5, textures5);

	//// ���U�C�N�����_���[
	//mosaicRenderer_ = std::make_unique<Renderer>(mosaicMaterial_);

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

	metal_->Update();

	moon_->Update();

	water_->Update();

	gate_->Update();

}

void GameScene::Draw(void)
{

	// �w�i
	skyDome_->Draw();
	stage_->Draw();
	unityStage_->Draw();

	player_->Draw();

	// ������
	stage_->DrawTranslucent();

	enemyManager_->Draw();

	metal_->Draw();

	moon_->Draw();

	water_->Draw();

	gate_->Draw();

	// �w���v
	//DrawFormatString(840, 20, 0x000000, "�ړ��@�@�FWASD");
	//DrawFormatString(840, 40, 0x000000, "�J�����@�F���L�[");
	//DrawFormatString(840, 60, 0x000000, "�_�b�V���F�EShift");
	//DrawFormatString(840, 80, 0x000000, "�W�����v�F�_(�o�N�X��)");

	// �J�������W
	auto camera = SceneManager::GetInstance().GetCamera();
	auto cameraPos = camera.lock()->GetPos();
	//DrawFormatString(20, 20, 0xffffff,
		//"�J�����ʒu(%.2f,%.2f,%.2f)", cameraPos.x, cameraPos.y, cameraPos.z);

	//deltaTime_ += SceneManager::GetInstance().GetDeltaTime();

	// ���m�V�F�[�_
	//monoRenderer_->Draw();

	// �������V�F�[�_
	//scanRenderer_->SetConstBufs({ deltaTime_ / 10,0.0f,0.0f,0.0f }, 0);
	//scanRenderer_->Draw();

	// �c�݃����_���[
	//distortionRenderer_->SetConstBufs({ deltaTime_,0.0f,0.0f,0.0f }, 0);
	//distortionRenderer_->Draw();

	// �m�C�Y�����_���[
	//noiseRenderer_->SetConstBufs({ deltaTime_ / 10,0.0f,0.0f,0.0f }, 0);
	//noiseRenderer_->Draw();

	// ���U�C�N�����_���[
	//mosaicRenderer_->Draw();

}
