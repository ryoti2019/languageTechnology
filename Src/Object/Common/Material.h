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
	/// コンストラクタ
	/// </summary>
	/// <param name="shaderFileName"></param>
	/// <param name="constBufFloat4Size"></param>
	Material(std::string shaderFileName, int constBufFloat4Size, std::vector<FLOAT4> constBufs, std::map<int, int> textures);

	// シェーダハンドル
	int shader_;

	// 定数バッファの確保サイズ(FLOAT4をいくつ作るか)
	int constBufFloat4Size_;

	// 定数バッファハンドル
	int constBuf_;

	// テクスチャアドレス
	TEXADDRESS texAddress_;

	// 定数バッファ
	std::vector<FLOAT4> constBufs_;

	// 画像
	std::map<int, int> textures_;

private:
};

