#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "Common/Transform.h"
#include "../Application.h"
#include "../Object/Common/Renderer.h"
#include "../Object/Common/Material.h"
#include "../Object/Common/ModelMaterial.h"
#include "../Object/Common/Renderer.h"
#include "Player.h"
#include "WarpStar.h"

WarpStar::WarpStar(Player& player, const Transform& transform): player_(player)
{
	transform_ = transform;
	state_ = STATE::NONE;
}

WarpStar::~WarpStar(void)
{
}

void WarpStar::Init(void)
{

	// モデルの基本情報
	transform_.SetModel(
		resMng_.LoadModelDuplicate(
			ResourceManager::SRC::WARP_STAR)
	);
	transform_.Update();

	// モデル描画用
	std::vector<FLOAT4> constBufsPtr1;
	//constBufsPtr1.push_back({ 0.0f, 0.0f, 0.0f, 0.0f });
	std::map<int, int> textures;
	modelMaterial_ = std::make_shared<ModelMaterial>(
		(Application::PATH_SHADER + "StdModelVS.cso"), sizeof(FLOAT4) * 1, constBufsPtr1,
		(Application::PATH_SHADER + "StdModelPS.cso"), sizeof(FLOAT4) * 1, constBufsPtr1, textures
	);

	renderer_ = std::make_shared<Renderer>(transform_.modelId, modelMaterial_);

	ChangeState(STATE::IDLE);

}

void WarpStar::Update(void)
{

	// 更新ステップ
	switch (state_)
	{
	case WarpStar::STATE::NONE:
		UpdateNone();
		break;
	case WarpStar::STATE::IDLE:
		UpdateIdle();
		break;
	case WarpStar::STATE::RESERVE:
		UpdateReserve();
		break;
	case WarpStar::STATE::MOVE:
		UpdateMove();
		break;
	}

}

void WarpStar::Draw(void)
{
	//MV1DrawModel(transform_.modelId);
	renderer_->Draw();
}

void WarpStar::ChangeState(STATE state)
{

	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	switch (state_)
	{
	case WarpStar::STATE::NONE:
		ChangeStateNone();
		break;
	case WarpStar::STATE::IDLE:
		ChangeStateIdle();
		break;
	case WarpStar::STATE::RESERVE:
		ChangeStateReserve();
		break;
	case WarpStar::STATE::MOVE:
		ChangeStateMove();
		break;
	}

}

void WarpStar::ChangeStateNone(void)
{
}

void WarpStar::ChangeStateIdle(void)
{
}

void WarpStar::ChangeStateReserve(void)
{
}

void WarpStar::ChangeStateMove(void)
{
}

void WarpStar::UpdateNone(void)
{
}

void WarpStar::UpdateIdle(void)
{
}

void WarpStar::UpdateReserve(void)
{
}

void WarpStar::UpdateMove(void)
{
}
