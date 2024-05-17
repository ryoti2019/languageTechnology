#include <fstream>
#include "../Application.h"
#include "../Lib/nlohmann/json.hpp"
#include "../Object/Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SaveLoadManager.h"
// �����̂�namespace�̏ȗ�
using json = nlohmann::json;
// �t�@�C����
const std::string SaveLoadManager::FILE_NAME = "GameData.json";
SaveLoadManager::SaveLoadManager(void)
{
}
SaveLoadManager::~SaveLoadManager(void)
{
}
void SaveLoadManager::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	// �Z�[�u�@�\
	if (ins.IsTrgDown(KEY_INPUT_X))
	{
		Save();
	}
	// ���[�h�@�\
	if (ins.IsTrgDown(KEY_INPUT_C))
	{
		Load();
	}

}
void SaveLoadManager::Load(void)
{
	//�` �����ōl���Ď������Ă݂܂��傤 �`

	// �O���t�@�C���̓ǂݍ���
	std::ifstream ifs(Application::PATH_JSON + "GameData.json");
	// json�I�u�W�F�N�g
	json playerData;
	if (ifs)
	{
		// �t�@�C���X�g���[������json�I�u�W�F�N�g�ɕϊ�
		ifs >> playerData;
	}
	else
	{
		// �O���t�@�C���̓ǂݍ��ݎ��s
		return;
	}
	// player�I�u�W�F�N�g���擾
	const auto& playerDatas = playerData["player"];
	// �R���X�g���N�^�o�R�œǂݍ��񂾃Q�[���p�����[�^��n��
	std::vector<float> pos = playerDatas["pos"];
	pos = { pos[0],pos[1],pos[2] };
	std::vector<float> qua = playerDatas["rot"];
	qua = { qua[0],qua[1] ,qua[2] ,qua[3] };

	player_->SetTransform(pos, qua);

}

void SaveLoadManager::Save(void)
{
	// �X�e�[�W�[��Null�`�F�b�N
	if (player_ == nullptr)
	{
		return;
	}
	// �O���t�@�C���̓ǂݍ���(�����ݗp)
	std::ofstream ofs;
	ofs.open(Application::PATH_JSON + "GameData.json");
	// json�I�u�W�F�N�g(�v���C���[���)
	json playerData;
	const auto& transform = player_->GetTransform();
	// ���W
	auto pos = transform.pos;
	playerData["pos"].push_back(pos.x);
	playerData["pos"].push_back(pos.y);
	playerData["pos"].push_back(pos.z);
	// ��]
	auto rot = transform.quaRot;
	playerData["rot"].push_back(rot.x);
	playerData["rot"].push_back(rot.y);
	playerData["rot"].push_back(rot.z);
	playerData["rot"].push_back(rot.w);
	// json�I�u�W�F�N�g(�S��)
	json saveData;
	saveData["player"] = playerData;
	// json�I�u�W�F�N�g��string�ɕϊ�
	auto dmp = saveData.dump();
	// �O���t�@�C���ɏ�����
	ofs.write(dmp.c_str(), dmp.size());
	// �ϊ��Ə����݂��ȉ��̃��_�C���N�g�ŏȗ���
	//ofs << saveData << std::endl;
	// �X�R�[�v���؂��ۂ� �����I�Ƀt�@�C���N���[�Y���ĖႦ�܂����A
	// ���s�V�ǂ��A�����I�Ƀt�@�C���X�g���[�������
	ofs.close();
}

void SaveLoadManager::SetPlayer(std::shared_ptr<Player> player)
{
	player_ = player;
}