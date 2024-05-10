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

	// �v���C���[
	player_ = std::make_unique<Player>();
	player_->Init();

	// �X�e�[�W
	stage_ = std::make_unique<Stage>(*player_);
	stage_->Init();

	// �X�e�[�W�̏����ݒ�
	stage_->ChangeStage(Stage::NAME::MAIN_PLANET);

	// �X�J�C�h�[��
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

	// �|�X�g�G�t�F�N�g�p�X�N���[��
	postEffectScreenMono_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	// �s�N�Z���V�F�[�_�̃��[�h
	monoShader_ = LoadPixelShader((Application::PATH_SHADER + "Monotone.cso").c_str());

	// �s�N�Z���V�F�[�_�p�̒萔�o�b�t�@���쐬
	monoShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * 3);

	// ��ʑS�̂𕢂�2�̃|���S��

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
	
	player_->Draw();

	enemyManager_->Draw();

	// �w���v
	DrawFormatString(840, 20, 0x000000, "�ړ��@�@�FWASD");
	DrawFormatString(840, 40, 0x000000, "�J�����@�F���L�[");
	DrawFormatString(840, 60, 0x000000, "�_�b�V���F�EShift");
	DrawFormatString(840, 80, 0x000000, "�W�����v�F�_(�o�N�X��)");

	// ���C���X�N���[��
	int mainScreen = SceneManager::GetInstance().GetMainScreen();
	SetDrawScreen(postEffectScreenMono_);

	// ��ʂ�������
	ClearDrawScreen();

	// �I���W�i���V�F�[�_�ݒ�(ON)
	MV1SetUseOrigShader(true);

	// ���_�C���f�b�N�X
	for (auto& v : vertexs_)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// ����
	vertexs_[0].pos = { 0.0f, 0.0f, 0.0f };
	vertexs_[0].u = 0.0f;
	vertexs_[0].v = 0.0f;
	// �E��
	vertexs_[1].pos = { Application::SCREEN_SIZE_X, 0.0f, 0.0f };
	vertexs_[1].u = 1.0f;
	vertexs_[1].v = 0.0f;
	// ����
	vertexs_[2].pos = { 0.0f, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[2].u = 0.0f;
	vertexs_[2].v = 1.0f;
	// �E��
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

	// �V�F�[�_�ݒ�
	SetUsePixelShader(monoShader_);

	// �e�N�X�`���̐ݒ�
	SetUseTextureToShader(0, mainScreen);

	// �萔�o�b�t�@
	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(monoShaderConstBuf_);

	// ��Z�F
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

	// �萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(monoShaderConstBuf_);

	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�p�萔�o�b�t�@���W�X�^��
	SetShaderConstantBuffer(monoShaderConstBuf_, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// �`��
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_VERTEX_IDX);

	// ��n��
	//--------------------------------------------

	// �e�N�X�`������
	SetUseTextureToShader(0, -1);

	// �s�N�Z���V�F�[�_����
	SetUsePixelShader(-1);

	// �I���W�i���V�F�[�_�ݒ�(OFF)
	MV1SetUseOrigShader(false);
	//--------------------------------------------

	// ���C���ɖ߂�
	SetDrawScreen(mainScreen);
	DrawGraph(0, 0, postEffectScreenMono_, false);
	//--------------------------------------------

}
