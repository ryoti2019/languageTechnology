#include <fstream>
#include "../Application.h"
#include "../Lib/nlohmann/json.hpp"
#include "../Object/Common/Transform.h"
#include "../Manager/ResourceManager.h"
#include "../Utility/AsoUtility.h"
#include "UnityStage.h"
// �����̂�namespace�̏ȗ�
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

	// �O���t�@�C���̓ǂݍ���
	std::ifstream ifs(Application::PATH_JSON + "ExportData.json");
	// json�I�u�W�F�N�g
	json stageData;
	if (ifs)
	{
		// �t�@�C���X�g���[������json�I�u�W�F�N�g�ɕϊ�
		ifs >> stageData;
	}
	else
	{
		// �O���t�@�C���̓ǂݍ��ݎ��s
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

	// �X�e�[�W�I�u�W�F�N�g���擾

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
			// player�I�u�W�F�N�g���擾
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