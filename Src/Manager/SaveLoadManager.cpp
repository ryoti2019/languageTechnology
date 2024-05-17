#include <fstream>
#include "../Application.h"
#include "../Lib/nlohmann/json.hpp"
#include "../Object/Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SaveLoadManager.h"
// 長いのでnamespaceの省略
using json = nlohmann::json;
// ファイル名
const std::string SaveLoadManager::FILE_NAME = "GameData.json";
SaveLoadManager::SaveLoadManager(void)
{
}
SaveLoadManager::~SaveLoadManager(void)
{
}
void SaveLoadManager::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	// セーブ機能
	if (ins.IsTrgDown(KEY_INPUT_X))
	{
		Save();
	}
	// ロード機能
	if (ins.IsTrgDown(KEY_INPUT_C))
	{
		Load();
	}

}
void SaveLoadManager::Load(void)
{
	//～ 自分で考えて実装してみましょう ～

	// 外部ファイルの読み込み
	std::ifstream ifs(Application::PATH_JSON + "GameData.json");
	// jsonオブジェクト
	json playerData;
	if (ifs)
	{
		// ファイルストリームからjsonオブジェクトに変換
		ifs >> playerData;
	}
	else
	{
		// 外部ファイルの読み込み失敗
		return;
	}
	// playerオブジェクトを取得
	const auto& playerDatas = playerData["player"];
	// コンストラクタ経由で読み込んだゲームパラメータを渡す
	std::vector<float> pos = playerDatas["pos"];
	pos = { pos[0],pos[1],pos[2] };
	std::vector<float> qua = playerDatas["rot"];
	qua = { qua[0],qua[1] ,qua[2] ,qua[3] };

	player_->SetTransform(pos, qua);

}

void SaveLoadManager::Save(void)
{
	// ステージーのNullチェック
	if (player_ == nullptr)
	{
		return;
	}
	// 外部ファイルの読み込み(書込み用)
	std::ofstream ofs;
	ofs.open(Application::PATH_JSON + "GameData.json");
	// jsonオブジェクト(プレイヤー情報)
	json playerData;
	const auto& transform = player_->GetTransform();
	// 座標
	auto pos = transform.pos;
	playerData["pos"].push_back(pos.x);
	playerData["pos"].push_back(pos.y);
	playerData["pos"].push_back(pos.z);
	// 回転
	auto rot = transform.quaRot;
	playerData["rot"].push_back(rot.x);
	playerData["rot"].push_back(rot.y);
	playerData["rot"].push_back(rot.z);
	playerData["rot"].push_back(rot.w);
	// jsonオブジェクト(全体)
	json saveData;
	saveData["player"] = playerData;
	// jsonオブジェクトをstringに変換
	auto dmp = saveData.dump();
	// 外部ファイルに書込み
	ofs.write(dmp.c_str(), dmp.size());
	// 変換と書込みを以下のリダイレクトで省略可
	//ofs << saveData << std::endl;
	// スコープが切れる際に 自動的にファイルクローズして貰えますが、
	// お行儀良く、明示的にファイルストリームを閉じる
	ofs.close();
}

void SaveLoadManager::SetPlayer(std::shared_ptr<Player> player)
{
	player_ = player;
}