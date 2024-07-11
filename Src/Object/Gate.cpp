#include <DxLib.h>
#include "../Manager/InputManager.h"
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

	transform_.pos = { 0.0f,100.0f,500.0f };
	transform_.Update();

	// ゲートの枠
	resModelId_ = MV1LoadModel("Data/Model/Gate/Gate.mv1");
	playModelId_ = MV1DuplicateModel(resModelId_);

	MV1SetPosition(playModelId_, { 0.0f,-30.0f,500.0f });

	// テクスチャ
	texId_ = resMng_.Load(ResourceManager::SRC::TEX_GATE).handleId_;

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
	alphaTime_ = 1.0f;
	time_ = 0.0f;
	constBufsPtrPS.push_back({ alphaTime_,time_,0.0f,0.0f });

	std::map<int, int> textures;
	textures.emplace(1, texId_);
	modelMaterial_ = std::make_shared<ModelMaterial>(
		(Application::PATH_SHADER + "GateModelVS.cso"), sizeof(FLOAT4) * 1, constBufsPtrVS,
		(Application::PATH_SHADER + "GateModelPS.cso"), sizeof(FLOAT4) * 4, constBufsPtrPS, textures
	);

	renderer_ = std::make_shared<Renderer>(transform_.modelId, modelMaterial_);

	isDissolve_ = false;

}

void Gate::Update(void)
{

	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_V))
	{
		isDissolve_ = true;
	}

}

void Gate::Draw(void)
{

	// ゲートの枠の描画
	MV1DrawModel(playModelId_);

	// ゲートミストの描画
	deltaTime_ += SceneManager::GetInstance().GetDeltaTime();
	if (isDissolve_)
	{
		alphaTime_ -= 0.01f;
		time_ += 0.01;
	}
	modelMaterial_->SetConstBufsPS({ 0.0f,0.0f,0.0f,deltaTime_ }, 2);
	modelMaterial_->SetConstBufsPS({ alphaTime_,time_,0.0f,0.0f }, 3);
	modelMaterial_->SetTextureAddress(ModelMaterial::TEXADDRESS::MIRROR);
	renderer_->Draw();
}
