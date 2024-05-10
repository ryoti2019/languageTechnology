#include <memory>
#include <fstream>
#include <DxLib.h>
#include "../../Lib/nlohmann/json.hpp"
#include "../../Application.h"
#include "Enemy.h"
#include "EnemyManager.h"
// �����̂�namespace�̏ȗ�
using json = nlohmann::json;
void EnemyManager::Load(void)
{
	// �O���t�@�C���̓ǂݍ���
	std::ifstream ifs(Application::PATH_JSON + "Enemy.json");
	// json�I�u�W�F�N�g
	json enemyData;
		if (ifs)
		{
			// �t�@�C���X�g���[������json�I�u�W�F�N�g�ɕϊ�
			ifs >> enemyData;
		}
		else
		{
			// �O���t�@�C���̓ǂݍ��ݎ��s
			return;
		}
	// enemy�I�u�W�F�N�g���擾
	const auto& enemyDatas = enemyData["enemy"];
	// enemy�I�u�W�F�N�g�͕�������͂��Ȃ̂ŁA�J��Ԃ�����
	for (const json& enemyData : enemyDatas)
	{
		// enemy�I�u�W�F�N�g�̐����A�C���X�^���X����
		// �R���X�g���N�^�o�R�œǂݍ��񂾃Q�[���p�����[�^��n��
		auto enemy = std::make_shared<Enemy>(enemyData);
		enemys_.emplace_back(std::move(enemy));
	}
}

void EnemyManager::Draw(void)
{
	int n = 0;
	for (auto& e : enemys_)
	{
		std::string id = e->GetId();
		int type = (int)e->GetType();
		int hp = e->GetHp();

		std::string skill = "";
		for (auto& s : e->GetSkills())
		{
			skill += std::to_string((int)s);
		}

		++n;

		DrawFormatString(0, 0 + 15 * n, 0x000000, "id:%s, type:%d, hp:%d, skills:%s", id.c_str(), type, hp, skill.c_str());
	}

}