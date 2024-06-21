#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Application.h"
#include "Common/Transform.h"
#include "Common/Renderer.h"
#include "../Object/Common/ModelMaterial.h"
#include "WarpStar.h"
#include "Planet.h"

Planet::Planet(const Stage::NAME& name, const TYPE& type, const Transform& transform)
{

	name_ = name;
	type_ = type;
	transform_ = transform;

	gravityPow_ = 0.0f;
	gravityRadius_ = 0.0f;
	deadLength_ = 0.0f;

}

Planet::~Planet(void)
{
}

void Planet::Init(void)
{
	gravityPow_ = DEFAULT_GRAVITY_POW;
	gravityRadius_ = DEFAULT_GRAVITY_RADIUS;
	deadLength_ = DEFAULT_DEAD_LENGTH;

	// モデル描画用
	std::vector<FLOAT4> constBufsPtrVS;
	// カメラ座標
	auto camera = SceneManager::GetInstance().GetCamera();
	auto cameraPos = camera.lock()->GetPos();
	constBufsPtrVS.push_back({ cameraPos.x,cameraPos.y,cameraPos.z,0.0f });
	// フォグ開始・終了距離
	float start = 0.0f;
	float end = 0.0f;
	GetFogStartEnd(&start, &end);
	constBufsPtrVS.push_back({ start,end,0.0f,0.0f });

	// ポイントライト座標
	auto& pointLightPos = SceneManager::GetInstance().GetPointLight();
	constBufsPtrVS.push_back({ pointLightPos.x,pointLightPos.y, pointLightPos.z, 0.0f });

	std::vector<FLOAT4> constBufsPtrPS;
	constBufsPtrPS.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
	// 光の向いている方向(ワールド空間)(ディレクショナルライト)
	auto lDir = GetLightDirection();
	constBufsPtrPS.push_back({ lDir.x,lDir.y,lDir.z,0.0f });
	constBufsPtrPS.push_back({ 0.2f,0.2f,0.2f,1.0f });
	std::map<int, int> textures;
	modelMaterial_ = std::make_shared<ModelMaterial>(
		(Application::PATH_SHADER + "StdModelVS.cso"), sizeof(FLOAT4) * (2 + 1), constBufsPtrVS,
		(Application::PATH_SHADER + "StdModelPS.cso"), sizeof(FLOAT4) * 3, constBufsPtrPS, textures
	);

	renderer_ = std::make_shared<Renderer>(transform_.modelId, modelMaterial_);

}

void Planet::Update(void)
{
}

void Planet::Draw(void)
{
	// カメラ座標
	auto camera = SceneManager::GetInstance().GetCamera();
	auto cameraPos = camera.lock()->GetPos();
	modelMaterial_->SetConstBufsVS({ cameraPos.x,cameraPos.y,cameraPos.z,0.0f }, 0);
	renderer_->Draw();
}

void Planet::SetPosition(const VECTOR& pos)
{
    transform_.pos = pos;
    transform_.Update();
}

void Planet::SetRotation(const Quaternion& rot)
{
	transform_.quaRot = rot;
	transform_.Update();
}

float Planet::GetGravityPow(void) const
{
	return gravityPow_;
}

void Planet::SetGravityPow(float pow)
{
	gravityPow_ = pow;
}

float Planet::GetGravityRadius(void) const
{
	return gravityRadius_;
}

void Planet::SetGravityRadius(float radius)
{
	gravityRadius_ = radius;
}

const Planet::TYPE& Planet::GetType(void) const
{
	return type_;
}

bool Planet::InRangeGravity(const VECTOR& pos) const
{
	return false;
}

bool Planet::InRangeDead(const VECTOR& pos) const
{
	return false;
}

void Planet::SetDeadLength(float len)
{
	deadLength_ = len;
}

const Stage::NAME& Planet::GetName(void) const
{
	return name_;
}
