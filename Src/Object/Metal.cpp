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
#include "Metal.h"

Metal::Metal(void)
{
}

Metal::~Metal(void)
{
}

void Metal::Init(void)
{

	// ��
	transform_.SetModel(
		resMng_.LoadModelDuplicate(ResourceManager::SRC::SHIELD));
	transform_.scl = VScale(AsoUtility::VECTOR_ONE, 1.0f);
	transform_.quaRotLocal =
		Quaternion::Euler(
			AsoUtility::Deg2RadF(0.0f),
			AsoUtility::Deg2RadF(30.0f),
			0.0f
		);

	transform_.pos = { 0.0f,80.0f,200.0f };
	transform_.Update();

	// ���f���`��p
	std::vector<FLOAT4> constBufsPtrVS;
	constBufsPtrVS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	std::vector<FLOAT4> constBufsPtrPS;
	// �g�U��
	constBufsPtrPS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// ����
	constBufsPtrPS.push_back({ 0.2f, 0.2f, 0.2f, 1.0f });

	// ���ˌ�
	constBufsPtrPS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// ���̌����Ă������(���[���h���)(�f�B���N�V���i�����C�g)
	float specularPow = 40.0f;
	auto lDir = GetLightDirection();
	constBufsPtrPS.push_back({ lDir.x,lDir.y,lDir.z, specularPow });

	// ���̈ʒu
	VECTOR cameraPos = SceneManager::GetInstance().GetCamera().lock()->GetPos();
	constBufsPtrPS.push_back({ cameraPos.x,cameraPos.y,cameraPos.z,1.0f });

	std::map<int, int> textures;
	modelMaterial_ = std::make_shared<ModelMaterial>(
		(Application::PATH_SHADER + "MetalModelVS.cso"), sizeof(FLOAT4) * 1, constBufsPtrVS,
		(Application::PATH_SHADER + "MetalModelPS.cso"), sizeof(FLOAT4) * 5, constBufsPtrPS, textures
	);

	renderer_ = std::make_shared<Renderer>(transform_.modelId, modelMaterial_);

}

void Metal::Update(void)
{
}

void Metal::Draw(void)
{
	renderer_->Draw();

	// ���̈ʒu
	VECTOR cameraPos = SceneManager::GetInstance().GetCamera().lock()->GetPos();
	modelMaterial_->SetConstBufsPS({ cameraPos.x,cameraPos.y,cameraPos.z,1.0f }, 4);
}
