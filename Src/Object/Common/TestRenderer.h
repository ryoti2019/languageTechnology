#pragma once
#include<memory>
class ActorBase;

class TestRenderer
{
public:

	// �R���X�g���N�^
	TestRenderer(std::shared_ptr<ActorBase> actor);

	// �f�X�g���N�^
	~TestRenderer(void);

private:
	std::shared_ptr<ActorBase> actor_;


};

