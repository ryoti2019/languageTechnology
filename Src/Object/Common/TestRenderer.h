#pragma once
#include<memory>
class ActorBase;

class TestRenderer
{
public:

	// コンストラクタ
	TestRenderer(std::shared_ptr<ActorBase> actor);

	// デストラクタ
	~TestRenderer(void);

private:
	std::shared_ptr<ActorBase> actor_;


};

