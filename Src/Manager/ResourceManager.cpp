#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	// 推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	Resource* res;

	// タイトル画像
	res = new RES(RES_T::IMG, PATH_IMG + "Title.png");
	resourcesMap_.emplace(SRC::TITLE, res);

	// PushSpace
	res = new RES(RES_T::IMG, PATH_IMG + "PushSpace.png");
	resourcesMap_.emplace(SRC::PUSH_SPACE, res);

	// 吹き出し
	res = new RES(RES_T::IMG, PATH_IMG + "SpeechBalloon.png");
	resourcesMap_.emplace(SRC::SPEECH_BALLOON, res);
	
	// プレイヤー
	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Player.mv1");
	resourcesMap_.emplace(SRC::PLAYER, res);

	// プレイヤー影
	res = new RES(RES_T::IMG, PATH_IMG + "Shadow.png");
	resourcesMap_.emplace(SRC::PLAYER_SHADOW, res);

	// スカイドーム
	res = new RES(RES_T::MODEL, PATH_MDL + "SkyDome/SkyDome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, res);

	// 最初の惑星
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/MainPlanet.mv1");
	resourcesMap_.emplace(SRC::MAIN_PLANET, res);

	// 落とし穴の惑星
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/FallPlanet.mv1");
	resourcesMap_.emplace(SRC::FALL_PLANET, res);

	// 平坦な惑星01
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/FlatPlanet01.mv1");
	resourcesMap_.emplace(SRC::FLAT_PLANET_01, res);

	// 平坦な惑星02
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/FlatPlanet02.mv1");
	resourcesMap_.emplace(SRC::FLAT_PLANET_02, res);

	// 最後の惑星
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/LastPlanet.mv1");
	resourcesMap_.emplace(SRC::LAST_PLANET, res);

	// 特別な惑星
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/RoadPlanet.mv1");
	resourcesMap_.emplace(SRC::SPECIAL_PLANET, res);

	// 地面
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/Ground.mv1");
	resourcesMap_.emplace(SRC::GROUND, res);

	// 家１
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/House1.mv1");
	resourcesMap_.emplace(SRC::HOUSE1, res);

	// 家２
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/House2.mv1");
	resourcesMap_.emplace(SRC::HOUSE2, res);

	// 家３
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/House3.mv1");
	resourcesMap_.emplace(SRC::HOUSE3, res);

	// 木1
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/TreeThick.mv1");
	resourcesMap_.emplace(SRC::TREE_THICK, res);

	// 木2
	res = new RES(RES_T::MODEL, PATH_MDL + "Planet/TreeThin.mv1");
	resourcesMap_.emplace(SRC::TREE_THIN, res);

	// 足煙
	res = new RES(RES_T::EFFEKSEER, PATH_EFF + "Smoke/Smoke.efkefc");
	resourcesMap_.emplace(SRC::FOOT_SMOKE, res);

	// ワープスターモデル
	res = new RES(RES_T::MODEL, PATH_MDL + "Star/star.mv1");
	resourcesMap_.emplace(SRC::WARP_STAR, res);

	// ワープスター用回転エフェクト
	res = new RES(RES_T::EFFEKSEER, PATH_EFF + "StarDust/StarDust.efkefc");
	resourcesMap_.emplace(SRC::WARP_STAR_ROT_EFF, res);

	// ワープの軌跡線
	res = new RES(RES_T::EFFEKSEER, PATH_EFF + "Warp/WarpOrbit.efkefc");
	resourcesMap_.emplace(SRC::WARP_ORBIT, res);

	// ブラックホール
	res = new RES(RES_T::EFFEKSEER, PATH_EFF + "BlackHole/BlackHole.efkefc");
	resourcesMap_.emplace(SRC::BLACK_HOLE, res);

	// ゴール
	res = new RES(RES_T::MODEL, PATH_MDL + "GoalStar/GoalStar.mv1");
	resourcesMap_.emplace(SRC::GOAL_STAR, res);

	// Clear
	res = new RES(RES_T::IMG, PATH_IMG + "Congratulations.png");
	resourcesMap_.emplace(SRC::CLEAR, res);

	// タンク
	res = new RES(RES_T::MODEL, PATH_MDL + "Tank/Body.mv1");
	resourcesMap_.emplace(SRC::TANK_BODY, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Tank/Wheel.mv1");
	resourcesMap_.emplace(SRC::TANK_WHEEL, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Tank/Barrel.mv1");
	resourcesMap_.emplace(SRC::TANK_BARREL, res);

	// 月
	res = new RES(RES_T::MODEL, PATH_MDL + "Moon/Moon.mv1");
	resourcesMap_.emplace(SRC::MOON, std::move(res));

	// 盾
	res = new RES(RES_T::MODEL, PATH_MDL + "Metal/Shield.mv1");
	resourcesMap_.emplace(SRC::SHIELD, std::move(res));

	// 斧
	res = new RES(RES_T::MODEL, PATH_MDL + "Metal/Axe.mv1");
	resourcesMap_.emplace(SRC::AXE, std::move(res));

	// 水
	res = new RES(RES_T::MODEL, PATH_MDL + "Water/WaterWaveCube.mv1");
	resourcesMap_.emplace(SRC::WATER, std::move(res));

	// ライト
	res = new RES(RES_T::EFFEKSEER, PATH_EFF + "Light/Light.efkefc");
	resourcesMap_.emplace(SRC::EFF_LIGHT, res);

	// トゥーン用マップテクスチャ
	res = new RES(RES_T::IMG, PATH_MDL + "Player/ToonMap.png");
	resourcesMap_.emplace(SRC::TEX_TOON, res);

	// ゲート
	res = new RES(RES_T::MODEL, PATH_MDL + "Gate/Gate.mv1");
	resourcesMap_.emplace(SRC::GATE, res);

	// ゲートミスト
	res = new RES(RES_T::MODEL, PATH_MDL + "Gate/GateMist.mv1");
	resourcesMap_.emplace(SRC::GATE_MIST, res);

	// ノイズテクスチャ
	res = new RES(RES_T::IMG, PATH_MDL + "Gate/Noise2.png");
	resourcesMap_.emplace(SRC::TEX_GATE, res);

}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
