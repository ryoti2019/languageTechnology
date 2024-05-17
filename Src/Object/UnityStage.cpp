#include <fstream>
#include "../Application.h"
#include "../Lib/nlohmann/json.hpp"
#include "../Object/Common/Transform.h"
#include "../Manager/ResourceManager.h"
#include "../Utility/AsoUtility.h"
#include "UnityStage.h"
// 長いのでnamespaceの省略
using json = nlohmann::json;

UnityStage::UnityStage(void)
{
}

UnityStage::~UnityStage(void)
{
}

void UnityStage::Update(void)
{
}

void UnityStage::Draw(void)
{
	for (auto& transform : transform_)
	{
		MV1DrawModel(transform->modelId);
	}
}

void UnityStage::Load(void)
{

	// 外部ファイルの読み込み
	std::ifstream ifs(Application::PATH_JSON + "ExportData.json");
	// jsonオブジェクト
	json stageData;
	if (ifs)
	{
		// ファイルストリームからjsonオブジェクトに変換
		ifs >> stageData;
	}
	else
	{
		// 外部ファイルの読み込み失敗
		return;
	}

	std::string keys[] = {
		"ground",
		"houses1",
		"houses2",
		"houses3",
		"treeThicks",
		"treeThins"
	};

	int i = 0;

	// ステージオブジェクトを取得

	for (auto& key : keys)
	{
		const auto& data = stageData[key];
		for (auto& stage : data)
		{
			std::unique_ptr<Transform> temp = std::make_unique<Transform>();
			ResourceManager::SRC src;
			switch (i)
			{
			case 0:
				src = ResourceManager::SRC::GROUND;
				break;
			case 1:
				src = ResourceManager::SRC::HOUSE1;
				break;
			case 2:
				src = ResourceManager::SRC::HOUSE2;
				break;
			case 3:
				src = ResourceManager::SRC::HOUSE3;
				break;
			case 4:
				src = ResourceManager::SRC::TREE_THICK;
				break;
			case 5:
				src = ResourceManager::SRC::TREE_THIN;
				break;
			}
			temp->SetModel(ResourceManager::GetInstance().LoadModelDuplicate(src));
			// playerオブジェクトを取得
			auto scl = stage["scl"];
			temp->scl = { (float)scl["x"] / 100,(float)scl["y"] / 100,(float)scl["z"] / 100 };
			auto pos = stage["pos"];
			temp->pos = { (float)pos["x"],(float)pos["y"],(float)pos["z"] };
			auto rot = stage["rot"];
			temp->rot = { (float)rot["x"],(float)rot["y"],(float)rot["z"] };
			temp->quaRot = Quaternion::Euler(temp->rot);
			temp->quaRot = temp->quaRot.Mult(
				Quaternion::AngleAxis(
					AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y));
			
			transform_.emplace_back(std::move(temp));
		}
		i++;
	}
	

	for (auto& transform : transform_)
	{
		transform->Update();
	}

}