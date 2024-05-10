#pragma once
#include <vector>
#include <string>
#include "../../Lib/nlohmann/json.hpp"
// �����̂�namespace�̏ȗ�
using json = nlohmann::json;
class Enemy
{
public:

	// ���
	enum class TYPE
	{
		NONE,
		GOBLIN,
		BAT,
		OGRE,
	};
	// �X�L��
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

	// �l�擾
	std::string GetId(void) const;
	TYPE GetType(void) const;
	int GetHp(void) const;
	int GetPower(void) const;
	float GetSpeed(void) const;
	const std::vector<SKILL>& GetSkills(void) const;

private:

	// ID
	std::string id_;
	// ���
	TYPE type_;
	// HP
	int hp_;
	// �U����
	int power_;
	// �X�s�[�h
	float speed_;
	// �X�L��
	std::vector<SKILL> skills_;
};