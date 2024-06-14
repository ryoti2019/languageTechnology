// VS/PS共通
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

// 定数バッファ:スロット4番目
cbuffer cbParam : register(b4)
{
    float4 g_diff_color;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    return g_diff_color;
}