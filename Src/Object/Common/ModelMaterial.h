#pragma once
#include<DxLib.h>
#include<vector>
#include<string>
#include<map>
class ModelMaterial
{
public:

	enum class TEXADDRESS
	{
		NONE,
		WRAP,
		MIRROR,
		CLAMP,
		BORDER,
		MAX,
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="shaderFileName"></param>
	/// <param name="constBufFloat4Size"></param>
	ModelMaterial(std::string shaderFileNameVS, int constBufFloat4SizeVS, std::vector<FLOAT4> constBufsVS,
				  std::string shaderFileNamePS, int constBufFloat4SizePS, std::vector<FLOAT4> constBufsPS, std::map<int, int> textures);

	//�V�F�[�_�n���h���̎擾
	int GetShaderVS(void);
	int GetShaderPS(void);

	// �萔�o�b�t�@�T�C�Y�̎擾
	int GetConstBufSizeVS(void);
	int GetConstBufSizePS(void);

	// �萔�o�b�t�@�n���h���̎擾
	int GetconstBufVS(void);
	int GetconstBufPS(void);

	// �萔�o�b�t�@�n���h���̂̐ݒ�
	void SetConstBufsVS(FLOAT4 constBufs, int idx);
	void SetConstBufsPS(FLOAT4 constBufs, int idx);

	// �萔�o�b�t�@�̎擾
	std::vector<FLOAT4> GetConstBufsVS(void);
	std::vector<FLOAT4> GetConstBufsPS(void);

	// �摜�̎擾
	std::map<int, int> GetTextures(void);

	// �A�h���X�̎擾
	TEXADDRESS GetTextureAddress(void);

private:

	// �V�F�[�_�n���h��
	int shaderVS_;
	int shaderPS_;

	// �萔�o�b�t�@�̊m�ۃT�C�Y(FLOAT4��������邩)
	int constBufFloat4SizeVS_;
	int constBufFloat4SizePS_;

	// �萔�o�b�t�@�n���h��
	int constBufVS_;
	int constBufPS_;
	
	// �e�N�X�`���A�h���X
	TEXADDRESS texAddress_;

	// �萔�o�b�t�@
	std::vector<FLOAT4> constBufsVS_;
	std::vector<FLOAT4> constBufsPS_;

	// �摜(�X���b�g�A�n���h��ID)
	std::map<int,int> textures_;

};

