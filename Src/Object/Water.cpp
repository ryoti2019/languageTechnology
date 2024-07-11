#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "Common/Transform.h"
#include "../Utility/AsoUtility.h"
#include "../Application.h"
#include "../Object/Common/Renderer.h"
#include "../Object/Common/Material.h"
#include "../Object/Common/ModelMaterial.h"
#include "../Object/Common/Renderer.h"
#include "Water.h"

Water::Water(void)
{
}

Water::~Water(void)
{
}

void Water::Init(void)
{

	// ��
	transform_.SetModel(
		resMng_.LoadModelDuplicate(ResourceManager::SRC::WATER));
	transform_.scl = VScale(AsoUtility::VECTOR_ONE, 5.0f);
	transform_.pos = { -800.0f,-450.0f,100.0f };
	transform_.Update();

	// ���_�V�F�[�_�p�̒萔�o�b�t�@
	std::vector<FLOAT4> constBufsPtrVS;
	auto gTime = SceneManager::GetInstance().GetDeltaTime();
	constBufsPtrVS.push_back({ gTime, 4.0f, 4.0f, 0.0f });

	std::vector<FLOAT4> constBufsPtrPS;
	// �g�U��
	constBufsPtrPS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// ����
	constBufsPtrPS.push_back({ 0.2f, 0.2f, 0.2f, 1.0f });

	// ���̌����Ă������(���[���h���)(�f�B���N�V���i�����C�g)
	auto lDir = GetLightDirection();
	constBufsPtrPS.push_back({ lDir.x,lDir.y,lDir.z, gTime });

	std::map<int, int> textures;

	// ���f���`��p
	modelMaterial_ = std::make_shared<ModelMaterial>(
		(Application::PATH_SHADER + "WaterWaveModelVS.cso"), sizeof(FLOAT4) * 1, constBufsPtrVS,
		(Application::PATH_SHADER + "WaterWaveModelPS.cso"), sizeof(FLOAT4) * 3, constBufsPtrPS, textures
	);

	renderer_ = std::make_shared<Renderer>(transform_.modelId, modelMaterial_);

	deltaTime_ = 0.0f;

}

void Water::Update(void)
{
}

void Water::Draw(void)
{

	auto lDir = GetLightDirection();
	deltaTime_ += SceneManager::GetInstance().GetDeltaTime();
	modelMaterial_->SetConstBufsVS({ deltaTime_, 4.0f, 4.0f, 0.0f },0);
	modelMaterial_->SetConstBufsPS({ lDir.x,lDir.y,lDir.z, deltaTime_ }, 2);

	renderer_->Draw();
}
