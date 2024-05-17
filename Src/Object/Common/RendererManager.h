#pragma once
#include <DxLib.h>
#include<vector>
#include<string>
#include<map>
class Vector2;

class RendererManager
{

public:

	// ピクセルシェーダ用のオリジナル定数バッファの使用開始スロット
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;

	// 頂点数
	static constexpr int NUM_VERTEX = 4;

	// 頂点インデックス
	static constexpr int NUM_VERTEX_IDX = 6;

	//ポリゴン数
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
		// シェーダハンドル
		std::string shaderName;

		// シェーダハンドル
		int shaderHandle;

		// 定数バッファの確保サイズ(FLOAT4をいくつ作るか)
		int constBufFloat4Size;

		// FLOAT4の個数
		int Float4Size;

		// スクリーン
		int screen;

		// 定数バッファハンドル
		int constBuf;

		// テクスチャアドレス
		TEXADDRESS texAddress;

		// 定数バッファ
		FLOAT4* constBufs;

		// 画像
		int textures;

		// 定数バッファ
		std::vector<float> constBufsPtr;

	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="shaderFileName"></param>
	/// <param name="constBufFloat4Size"></param>
	RendererManager(void);

	// シェーダの追加
	void Add(std::string shaderFileName, int constBufFloat4Size, int float4Size);

	// 描画矩形の生成
	void MakeSquereVertex(void);

	// 描画
	void Draw(std::string shaderFileName, std::vector<FLOAT4> constBufsPtr);

private:

	// シェーダーのデータ
	std::map <std::string, Material> shaderData_;

	// 頂点
	VERTEX2DSHADER vertexs_[NUM_VERTEX];

	// 頂点インデックス
	WORD indexes_[NUM_VERTEX_IDX];

	float deltaTime_;

	// 定数バッファの更新
	void ConstBufsPtr(std::string shaderFileName, std::vector<float> constBufsPtr);

	//// シェーダハンドル
	//int shader_;

	//// 定数バッファの確保サイズ(FLOAT4をいくつ作るか)
	//int constBufFloat4Size_;

	//// 定数バッファハンドル
	//int constBuf_;

	//// テクスチャアドレス
	//TEXADDRESS texAddress_;

	//// 定数バッファ
	//std::vector<FLOAT4> constBufs_;

	//// 画像
	//std::vector<int> textures_;

};

