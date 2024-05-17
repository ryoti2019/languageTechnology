#pragma once
#include<DxLib.h>
#include<memory>
#include "../Common/Vector2.h"
class Material;

class Renderer
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

	// コンストラクタ
	Renderer(std::shared_ptr<Material> material);

	// 描画矩形の生成
	void MakeSquereVertex(Vector2 pos, Vector2 size);

	void MakeSquereVertex(void);

	void SetConstBufs(FLOAT4 constBufs, int idx);

	// 描画
	void Draw(void);

	void Draw(int x, int y);

private:

	// 座標
	Vector2 pos_;

	// 描画サイズ
	Vector2 size_;

	// 頂点
	VERTEX2DSHADER vertexs_[NUM_VERTEX];

	// 頂点インデックス
	WORD indexes_[NUM_VERTEX_IDX];

	// ピクセルマテリアル
	std::shared_ptr<Material> material_; //※マテリアルの実体生成前設定を強制する目的で参照

	int screen_;

};

