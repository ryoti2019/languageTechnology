#pragma once
#include<memory>
#include "ActorBase.h"

class ModelMaterial;
class Renderer;

class Gate : public ActorBase
{
public:

	// �R���X�g���N�^
	Gate(void);

	// �f�X�g���N�^
	~Gate(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<ModelMaterial> modelMaterial_;
	std::shared_ptr<Renderer> renderer_;

	// ���f��ID
	int resModelId_;
	int playModelId_;

	// �e�N�X�`��
	int texId_;

	float deltaTime_;
	float alphaTime_;
	float time_;

	bool isDissolve_;

};

