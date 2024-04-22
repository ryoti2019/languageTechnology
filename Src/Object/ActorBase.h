#pragma once
#include <memory>
#include "Common/Transform.h"
class ResourceManager;
class SceneManager;
class TestRenderer;

class ActorBase : public std::enable_shared_from_this<ActorBase>
{

public:

	// �R���X�g���N�^
	ActorBase(void);

	// �f�X�g���N�^
	virtual ~ActorBase(void);

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	const Transform& GetTransform(void) const;

protected:

	// �e�X�g�N���X
	std::unique_ptr<TestRenderer> testRenderer_;

	// �V���O���g���Q��
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// ���f������̊�{���
	Transform transform_;

};
