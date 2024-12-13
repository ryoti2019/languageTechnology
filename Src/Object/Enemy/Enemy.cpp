#include <DxLib.h>
#include "Enemy.h"
Enemy::Enemy(const json& data)
{
	// 外部ファイルの内容に応じて、ゲームパラメータを設定
	// 連想配列mapのように値を取得することができる
	// 型が合っていれば、自動的に型変換処理される
	// 型違反が発生したら、例外エラーが発生する
	id_ = data["id"];
	type_ = data["type"];
	hp_ = data["hp"];
	power_ = data["power"];
	speed_ = data["speed"];
	// 複数スキル対応
	const auto& skills = data["skills"];
	for (const auto& skill : skills)
	{
		skills_.emplace_back(skill);
	}
}

Enemy::~Enemy(void)
{
}

void Enemy::Draw(void)
{
	for (int i = 0; i < 5; i++)
	{
		//DrawFormatString(0, 0 + i * 20, 0xffffff, "id:%s  type:%d", id_, (int)type_ );/* "hp:%d", hp_, "power:%d", power_, "speed:%f", speed_);*/
	}
}

std::string Enemy::GetId(void) const
{
	return id_;
}

Enemy::TYPE Enemy::GetType(void) const
{
	return type_;
}

int Enemy::GetHp(void) const
{
	return hp_;
}

int Enemy::GetPower(void) const
{
	return power_;
}

float Enemy::GetSpeed(void) const
{
	return speed_;
}

const std::vector<Enemy::SKILL>& Enemy::GetSkills(void) const
{
	return skills_;
}
