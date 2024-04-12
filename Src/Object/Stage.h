#pragma once
#include <map>
#include "Common/Transform.h"
class ResourceManager;
class WarpStar;
class Planet;
class Player;

class Stage
{

public:

	// �X�e�[�W�̐؂�ւ��Ԋu
	static constexpr float TIME_STAGE_CHANGE = 1.0f;

	// �X�e�[�W��
	enum class NAME
	{
		MAIN_PLANET,
		FALL_PLANET,
		FLAT_PLANET_BASE,
		FLAT_PLANET_ROT01,
		FLAT_PLANET_ROT02,
		FLAT_PLANET_ROT03,
		FLAT_PLANET_ROT04,
		FLAT_PLANET_FIXED01,
		FLAT_PLANET_FIXED02,
		PLANET10,
		LAST_STAGE,
		SPECIAL_STAGE
	};

	// �R���X�g���N�^
	Stage(std::shared_ptr<Player> player);

	// �f�X�g���N�^
	~Stage(void);

	void Init(void);
	void Update(void);
	void Draw(void);

	// �X�e�[�W�ύX
	void ChangeStage(NAME type);

	// �ΏۃX�e�[�W���擾
	Planet* GetPlanet(NAME type);

private:

	// �V���O���g���Q��
	ResourceManager& resMng_;

	std::weak_ptr<Player> player_;

	// �X�e�[�W�A�N�e�B�u�ɂȂ��Ă���f���̏��
	NAME activeName_;
	Planet* activePlanet_;

	// �f��
	std::map<NAME, Planet*> planets_;

	// ���[�v�X�^�[
	std::vector<WarpStar*> warpStars_;

	// ���Planet
	Planet* nullPlanet = nullptr;

	float step_;

	// �ŏ��̘f��
	void MakeMainStage(void);

	// ���[�v�X�^�[
	void MakeWarpStar(void);

};