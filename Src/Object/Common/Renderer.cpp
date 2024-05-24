#include "../Manager/SceneManager.h"
#include "../Application.h"
#include "../Common/Material.h"
#include "Renderer.h"

Renderer::Renderer(std::shared_ptr<Material> material)
{
	material_ = material;
	screen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
}

void Renderer::MakeSquereVertex(Vector2 pos, Vector2 size)
{
}

void Renderer::MakeSquereVertex(void)
{

	// 頂点インデックス
	for (auto& v : vertexs_)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// 左上
	vertexs_[0].pos = { 0.0f, 0.0f, 0.0f };
	vertexs_[0].u = 0.0f;
	vertexs_[0].v = 0.0f;
	// 右上
	vertexs_[1].pos = { Application::SCREEN_SIZE_X, 0.0f, 0.0f };
	vertexs_[1].u = 1.0f;
	vertexs_[1].v = 0.0f;
	// 左下
	vertexs_[2].pos = { 0.0f, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[2].u = 0.0f;
	vertexs_[2].v = 1.0f;
	// 右下
	vertexs_[3].pos = { Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[3].u = 1.0f;
	vertexs_[3].v = 1.0f;

	//0,1,2 1,3,2
	indexes_[0] = 0;
	indexes_[1] = 1;
	indexes_[2] = 2;
	indexes_[3] = 1;
	indexes_[4] = 3;
	indexes_[5] = 2;

}

void Renderer::SetConstBufs(FLOAT4 constBufs, int idx)
{
	material_->constBufs_[idx] = constBufs;
}

void Renderer::Draw(void)
{

	// メインスクリーン
	int mainScreen = SceneManager::GetInstance().GetMainScreen();

	SetDrawScreen(screen_);

	// 画面を初期化
	ClearDrawScreen();

	// オリジナルシェーダ設定(ON)
	MV1SetUseOrigShader(true);

	// 頂点インデックス
	MakeSquereVertex();

	// シェーダ設定
	SetUsePixelShader(material_->shader_);

	// テクスチャの設定
	for (int i = 1; i < material_->textures_.size(); i++)
	{
		SetUseTextureToShader(i, material_->textures_[i]);
	}

	// 定数バッファ
	FLOAT4* constBufs = (FLOAT4*)GetBufferShaderConstantBuffer(material_->constBuf_);

	// 乗算色
	for (const auto& bufs: material_->constBufs_)
	{
		constBufs->x = bufs.x;
		constBufs->y = bufs.y;
		constBufs->z = bufs.z;
		constBufs->w = bufs.w;
		constBufs++;
	}

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(material_->constBuf_);

	// 定数バッファをピクセルシェーダー用定数バッファレジスタに
	SetShaderConstantBuffer(material_->constBuf_, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// 描画
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_VERTEX_IDX);

	// 後始末
	//--------------------------------------------

	// テクスチャ解除
	for (int i = 0; i < material_->textures_.size(); i++)
	{
		SetUseTextureToShader(i, material_->textures_[i]);
	}

	// ピクセルシェーダ解除
	SetUsePixelShader(-1);

	// オリジナルシェーダ設定(OFF)
	MV1SetUseOrigShader(false);
	//--------------------------------------------

	// メインに戻す
	SetDrawScreen(mainScreen);
	DrawGraph(0, 0, screen_, false);
	//--------------------------------------------

}

void Renderer::Draw(int x, int y)
{
}
