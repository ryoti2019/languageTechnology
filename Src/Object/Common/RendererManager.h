#pragma once
#include <DxLib.h>
#include<vector>
#include<string>
#include<map>
class Vector2;

class RendererManager
{

public:

	// �s�N�Z���V�F�[�_�p�̃I���W�i���萔�o�b�t�@�̎g�p�J�n�X���b�g
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;

	// ���_��
	static constexpr int NUM_VERTEX = 4;

	// ���_�C���f�b�N�X
	static constexpr int NUM_VERTEX_IDX = 6;

	//�|���S����
	static constexpr int NUM_POLYGON = 2;

	enum class TEXADDRESS
	{
		NONE,
		WRAP,
		MIRROR,
		CLAMP,
		BORDER,
		MAX,
	};

	struct Material
	{
		// �V�F�[�_�n���h��
		std::string shaderName;

		// �V�F�[�_�n���h��
		int shaderHandle;

		// �萔�o�b�t�@�̊m�ۃT�C�Y(FLOAT4��������邩)
		int constBufFloat4Size;

		// FLOAT4�̌�
		int Float4Size;

		// �X�N���[��
		int screen;

		// �萔�o�b�t�@�n���h��
		int constBuf;

		// �e�N�X�`���A�h���X
		TEXADDRESS texAddress;

		// �萔�o�b�t�@
		FLOAT4* constBufs;

		// �摜
		int textures;

		// �萔�o�b�t�@
		std::vector<float> constBufsPtr;

	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="shaderFileName"></param>
	/// <param name="constBufFloat4Size"></param>
	RendererManager(void);

	// �V�F�[�_�̒ǉ�
	void Add(std::string shaderFileName, int constBufFloat4Size, int float4Size);

	// �`���`�̐���
	void MakeSquereVertex(void);

	// �`��
	void Draw(std::string shaderFileName, std::vector<FLOAT4> constBufsPtr);

private:

	// �V�F�[�_�[�̃f�[�^
	std::map <std::string, Material> shaderData_;

	// ���_
	VERTEX2DSHADER vertexs_[NUM_VERTEX];

	// ���_�C���f�b�N�X
	WORD indexes_[NUM_VERTEX_IDX];

	float deltaTime_;

	// �萔�o�b�t�@�̍X�V
	void ConstBufsPtr(std::string shaderFileName, std::vector<float> constBufsPtr);

	//// �V�F�[�_�n���h��
	//int shader_;

	//// �萔�o�b�t�@�̊m�ۃT�C�Y(FLOAT4��������邩)
	//int constBufFloat4Size_;

	//// �萔�o�b�t�@�n���h��
	//int constBuf_;

	//// �e�N�X�`���A�h���X
	//TEXADDRESS texAddress_;

	//// �萔�o�b�t�@
	//std::vector<FLOAT4> constBufs_;

	//// �摜
	//std::vector<int> textures_;

};

