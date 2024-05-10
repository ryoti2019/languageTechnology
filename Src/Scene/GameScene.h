#pragma once
#include "SceneBase.h"
class Stage;
class SkyDome;
class Player;
class EnemyManager;
class SaveLoadManager;

class GameScene : public SceneBase
{

public:
	
	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// �s�N�Z���V�F�[�_�p�̃I���W�i���萔�o�b�t�@�̎g�p�J�n�X���b�g
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;

	// ���_��
	static constexpr int NUM_VERTEX = 4;

	// ���_�C���f�b�N�X
	static constexpr int NUM_VERTEX_IDX = 6;

	//�|���S����
	static constexpr int NUM_POLYGON = 2;

	// �X�e�[�W
	std::unique_ptr<Stage> stage_;

	// �X�J�C�h�[��
	std::unique_ptr<SkyDome> skyDome_;

	// �v���C���[
	std::shared_ptr<Player> player_;

	// �G
	std::unique_ptr<EnemyManager> enemyManager_;

	// �Z�[�u�ƃ��[�h�̊Ǘ�
	std::unique_ptr<SaveLoadManager> saveLoadManager_;

	// �|�X�g�G�t�F�N�g�p�X�N���[��(���m�N��)
	int postEffectScreenMono_;

	// �V�F�[�_�n���h��
	int monoShader_;

	// �萔�o�b�t�@�n���h��
	int monoShaderConstBuf_;

	// �Z�s�A�J���[
	int sepiaColorConstBuf_;

	float deltaTime_;

	// ���_
	VERTEX2DSHADER vertexs_[NUM_VERTEX];

	// ���_�C���f�b�N�X
	WORD indexes_[NUM_VERTEX_IDX];

};
