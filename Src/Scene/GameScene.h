#pragma once
#include<memory>
#include "SceneBase.h"
class Stage;
class SkyDome;
class Metal;
class Moon;
class Water;
class Player;
class EnemyManager;
class SaveLoadManager;
class UnityStage;
class RendererManager;
class Renderer;
class Material;

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

	// �X�e�[�W
	std::shared_ptr<Stage> stage_;

	// �X�J�C�h�[��
	std::unique_ptr<SkyDome> skyDome_;

	// ����
	std::shared_ptr<Metal> metal_;

	// ��
	std::shared_ptr<Moon> moon_;

	// ��
	std::shared_ptr<Water> water_;

	// �v���C���[
	std::shared_ptr<Player> player_;

	// �G
	std::unique_ptr<EnemyManager> enemyManager_;

	// �Z�[�u�ƃ��[�h�̊Ǘ�
	std::unique_ptr<SaveLoadManager> saveLoadManager_;

	// Unity����ǂݍ��񂾃X�e�[�W
	std::unique_ptr<UnityStage> unityStage_;

	// �����_���[�}�l�[�W���[
	std::unique_ptr<RendererManager> rendererManager_;

	// ���m�}�e���A��
	std::shared_ptr<Material> monoMaterial_;

	// ���m�����_���[
	std::unique_ptr<Renderer> monoRenderer_;

	// �������}�e���A��
	std::shared_ptr<Material> scanMaterial_;

	// �����������_���[
	std::unique_ptr<Renderer> scanRenderer_;

	// �c�݃}�e���A��
	std::shared_ptr<Material> distortionMaterial_;

	// �c�݃����_���[
	std::unique_ptr<Renderer> distortionRenderer_;

	// �m�C�Y�}�e���A��
	std::shared_ptr<Material> noiseMaterial_;

	// �m�C�Y�����_���[
	std::unique_ptr<Renderer> noiseRenderer_;

	// ���U�C�N�}�e���A��
	std::shared_ptr<Material> mosaicMaterial_;

	// ���U�C�N�����_���[
	std::unique_ptr<Renderer> mosaicRenderer_;

	// �f���^�^�C��
	float deltaTime_;


};
