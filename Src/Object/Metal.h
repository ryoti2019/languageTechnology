#pragma once
#include<memory>
#include "ActorBase.h"

class ModelMaterial;
class Renderer;

class Metal : public ActorBase
{
public:
	// コンストラクタ
	Metal(void);

	// デストラクタ
	~Metal(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<ModelMaterial> modelMaterial_;
	std::shared_ptr<Renderer> renderer_;

};

