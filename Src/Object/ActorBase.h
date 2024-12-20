#pragma once
#include <memory>
#include "Common/Transform.h"
class ResourceManager;
class SceneManager;
class TestRenderer;

class ActorBase : public std::enable_shared_from_this<ActorBase>
{

public:

	// コンストラクタ
	ActorBase(void);

	// デストラクタ
	virtual ~ActorBase(void);

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	const Transform& GetTransform(void) const;

protected:

	// テストクラス
	std::unique_ptr<TestRenderer> testRenderer_;

	// シングルトン参照
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// モデル制御の基本情報
	Transform transform_;

};
