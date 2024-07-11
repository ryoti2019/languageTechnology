#pragma once
#include<memory>
#include "ActorBase.h"

class ModelMaterial;
class Renderer;

class Gate : public ActorBase
{
public:

	// コンストラクタ
	Gate(void);

	// デストラクタ
	~Gate(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<ModelMaterial> modelMaterial_;
	std::shared_ptr<Renderer> renderer_;

	// モデルID
	int resModelId_;
	int playModelId_;

	// テクスチャ
	int texId_;

	float deltaTime_;
	float alphaTime_;
	float time_;

	bool isDissolve_;

};

