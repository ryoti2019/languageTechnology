#pragma once
#include "ActorBase.h"

class ModelMaterial;
class Renderer;

class Water : public ActorBase
{

public:

	// �R���X�g���N�^
	Water(void);

	// �f�X�g���N�^
	~Water(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<ModelMaterial> modelMaterial_;
	std::shared_ptr<Renderer> renderer_;

	float deltaTime_;

};