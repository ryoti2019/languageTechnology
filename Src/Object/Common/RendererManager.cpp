#include "../Manager/SceneManager.h"
#include "../Application.h"
#include "../Common/Vector2.h"
#include "RendererManager.h"

RendererManager::RendererManager(void)
{
}

void RendererManager::MakeSquereVertex(void)
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

void RendererManager::ConstBufsPtr(std::string shaderFileName, std::vector<float> constBufsPtr)
{
	// 定数バッファ
	FLOAT4* constBufs = (FLOAT4*)GetBufferShaderConstantBuffer(shaderData_[shaderFileName].constBuf);

	for (int i = 0; i < constBufsPtr.size() / 4; i++)
	{
		// 乗算色
		constBufs->x = constBufsPtr[0 + i];
		constBufs->y = constBufsPtr[1 + i];
		constBufs->z = constBufsPtr[2 + i];
		constBufs->w = constBufsPtr[3 + i];
	}

}

void RendererManager::Add(std::string shaderFileName, int constBufFloat4Size, int float4Size)
{

	Material data;

	data.shaderHandle = LoadPixelShader(shaderFileName.c_str());
	data.screen = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	data.constBuf = CreateShaderConstantBuffer(constBufFloat4Size);
	data.Float4Size = float4Size;
	shaderData_.emplace(shaderFileName, data);

}

void RendererManager::Draw(std::string shaderFileName, std::vector<FLOAT4> constBufsPtr)
{
	// メインスクリーン
	int mainScreen = SceneManager::GetInstance().GetMainScreen();
	SetDrawScreen(shaderData_[shaderFileName].screen);

	// 画面を初期化
	ClearDrawScreen();

	// オリジナルシェーダ設定(ON)
	MV1SetUseOrigShader(true);

	// 頂点インデックス
	MakeSquereVertex();

	// シェーダ設定
	SetUsePixelShader(shaderData_[shaderFileName].shaderHandle);

	// テクスチャの設定
	SetUseTextureToShader(0, mainScreen);

	// 定数バッファの更新
	//ConstBufsPtr(shaderFileName, constBufsPtr);

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(shaderData_[shaderFileName].constBuf);

	// 定数バッファをピクセルシェーダー用定数バッファレジスタに
	SetShaderConstantBuffer(shaderData_[shaderFileName].constBuf, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// 描画
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_VERTEX_IDX);

	// 後始末
	//--------------------------------------------

	// テクスチャ解除
	SetUseTextureToShader(0, -1);

	// ピクセルシェーダ解除
	SetUsePixelShader(-1);

	// オリジナルシェーダ設定(OFF)
	MV1SetUseOrigShader(false);
	//--------------------------------------------

	// メインに戻す
	SetDrawScreen(mainScreen);
	DrawGraph(0, 0, shaderData_[shaderFileName].screen, false);
	//--------------------------------------------

}