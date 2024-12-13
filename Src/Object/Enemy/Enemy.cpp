#include <DxLib.h>
#include "Enemy.h"
Enemy::Enemy(const json& data)
{
	// �O���t�@�C���̓��e�ɉ����āA�Q�[���p�����[�^��ݒ�
	// �A�z�z��map�̂悤�ɒl���擾���邱�Ƃ��ł���
	// �^�������Ă���΁A�����I�Ɍ^�ϊ����������
	// �^�ᔽ������������A��O�G���[����������
	id_ = data["id"];
	type_ = data["type"];
	hp_ = data["hp"];
	power_ = data["power"];
	speed_ = data["speed"];
	// �����X�L���Ή�
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
