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
#include "Gate.h"

Gate::Gate(void)
{
}

Gate::~Gate(void)
{
}

void Gate::Init(void)
{

	// ゲートミスト
	transform_.SetModel(
		resMng_.LoadModelDuplicate(ResourceManager::SRC::GATE_MIST));
	transform_.scl = VScale(AsoUtility::VECTOR_ONE, 1.0f);
	transform_.quaRotLocal =
		Quaternion::Euler(
			AsoUtility::Deg2RadF(0.0f),
			AsoUtility::Deg2RadF(0.0f),
			0.0f
		);

	// ゲートの枠
	//modelId_ = MV1DuplicateModel();

	transform_.pos = { 0.0f,100.0f,500.0f };
	transform_.Update();

	// モデル描画用
	std::vector<FLOAT4> constBufsPtrVS;
	//constBufsPtrVS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	std::vector<FLOAT4> constBufsPtrPS;
	// 拡散光
	constBufsPtrPS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });

	// 環境光
	constBufsPtrPS.push_back({ 0.2f, 0.2f, 0.2f, 1.0f });

	// 光の向いている方向(ワールド空間)(ディレクショナルライト)
	auto lDir = GetLightDirection();
	deltaTime_ = SceneManager::GetInstance().GetDeltaTime();
	constBufsPtrPS.push_back({ lDir.x,lDir.y,lDir.z, deltaTime_ });

	std::map<int, int> textures;
	modelMaterial_ = std::make_shared<ModelMaterial>(
		(Application::PATH_SHADER + "GateModelVS.cso"), sizeof(FLOAT4) * 1, constBufsPtrVS,
		(Application::PATH_SHADER + "GateModelPS.cso"), sizeof(FLOAT4) * 3, constBufsPtrPS, textures
	);

	renderer_ = std::make_shared<Renderer>(transform_.modelId, modelMaterial_);

}

void Gate::Update(void)
{
}

void Gate::Draw(void)
{

	deltaTime_ += SceneManager::GetInstance().GetDeltaTime();
	modelMaterial_->SetConstBufsPS({ 0.0f,0.0f,0.0f,deltaTime_ }, 2);
	renderer_->Draw();

}
