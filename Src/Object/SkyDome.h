#pragma once
#include <map>
#include "Common/Transform.h"
#include "ActorBase.h"

class SkyDome : public ActorBase
{

public:

	static constexpr float SCALE = 100.0f;
	static constexpr VECTOR SCALES = { SCALE, SCALE, SCALE };

	// ���
	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};

	// �R���X�g���N�^
	SkyDome(const Transform& syncTransform);

	// �f�X�g���N�^
	~SkyDome(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// ���@�̏��
	const Transform& syncTransform_;

	// ���
	STATE state_;

	// ��ԑJ��
	void ChangeState(STATE state);
	void ChangeStateNone(void);
	void ChangeStateStay(void);
	void ChangeStateFollow(void);

	// �X�V�X�e�b�v
	void UpdateNone(void);
	void UpdateStay(void);
	void UpdateFollow(void);

};