#include <memory>
#include <fstream>
#include <DxLib.h>
#include "../../Lib/nlohmann/json.hpp"
#include "../../Application.h"
#include "Enemy.h"
#include "EnemyManager.h"
// 長いのでnamespaceの省略
using json = nlohmann::json;
void EnemyManager::Load(void)
{
	// 外部ファイルの読み込み
	std::ifstream ifs(Application::PATH_JSON + "Enemy.json");
	// jsonオブジェクト
	json enemyData;
		if (ifs)
		{
			// ファイルストリームからjsonオブジェクトに変換
			ifs >> enemyData;
		}
		else
		{
			// 外部ファイルの読み込み失敗
			return;
		}
	// enemyオブジェクトを取得
	const auto& enemyDatas = enemyData["enemy"];
	// enemyオブジェクトは複数あるはずなので、繰り返し処理
	for (const json& enemyData : enemyDatas)
	{
		// enemyオブジェクトの数分、インスタンス生成
		// コンストラクタ経由で読み込んだゲームパラメータを渡す
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