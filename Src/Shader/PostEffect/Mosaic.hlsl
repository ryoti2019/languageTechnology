#include "../Common/Pixel/PixelShader2DHeader.hlsli"

cbuffer cbColor : register(b4)
{
    float4 g_color;
    float4 g_size_scale; // 画像サイズX,Y,スケール
}

float4 main(PS_INPUT PSInput):SV_TARGET
{
    // uv座標を変える
    float2 uv = PSInput.uv;
    float scaleX = g_size_scale.x / g_size_scale.z;
    float scaleY = g_size_scale.y / g_size_scale.z;
    uv.x = floor(uv.x * scaleX) / scaleX;
    uv.y = floor(uv.y * scaleY) / scaleY;
    // 変更されたuv座標を元に色を取得する
    float4 srcCol = tex.Sample(texSampler, uv);
    srcCol *= g_color;
    return srcCol;
}