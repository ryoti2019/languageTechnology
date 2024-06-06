#pragma once
#include<DxLib.h>
#include<vector>
#include<string>
#include<map>

class Material
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
	Material(std::string shaderFileName, int constBufFloat4Size, std::vector<FLOAT4> constBufs, std::map<int, int> textures);

	// �V�F�[�_�n���h��
	int shader_;

	// �萔�o�b�t�@�̊m�ۃT�C�Y(FLOAT4��������邩)
	int constBufFloat4Size_;

	// �萔�o�b�t�@�n���h��
	int constBuf_;

	// �e�N�X�`���A�h���X
	TEXADDRESS texAddress_;

	// �萔�o�b�t�@
	std::vector<FLOAT4> constBufs_;

	// �摜
	std::map<int, int> textures_;

private:
};

