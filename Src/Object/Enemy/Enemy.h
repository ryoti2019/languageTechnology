#pragma once
#include <vector>
#include <string>
#include "../../Lib/nlohmann/json.hpp"
// 長いのでnamespaceの省略
using json = nlohmann::json;
class Enemy
{
public:

	// 種別
	enum class TYPE
	{
		NONE,
		GOBLIN,
		BAT,
		OGRE,
	};
	// スキル
	enum class SKILL
	{
		NONE,
		DASH,
		ESCAPE,
		TACKLE,
		CHARGE_ATTACK
	};
	Enemy(const json& data);
	~Enemy(void);

	void Draw(void);

	// 値取得
	std::string GetId(void) const;
	TYPE GetType(void) const;
	int GetHp(void) const;
	int GetPower(void) const;
	float GetSpeed(void) const;
	const std::vector<SKILL>& GetSkills(void) const;

private:

	// ID
	std::string id_;
	// 種別
	TYPE type_;
	// HP
	int hp_;
	// 攻撃力
	int power_;
	// スピード
	float speed_;
	// スキル
	std::vector<SKILL> skills_;
};