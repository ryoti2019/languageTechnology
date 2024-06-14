#pragma once
#include<memory>
#include "ActorBase.h"

class ModelMaterial;
class Renderer;

class Moon : public ActorBase
{
public:

	// �R���X�g���N�^
	Moon(void);

	// �f�X�g���N�^
	~Moon(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<ModelMaterial> modelMaterial_;
	std::shared_ptr<Renderer> renderer_;

};

