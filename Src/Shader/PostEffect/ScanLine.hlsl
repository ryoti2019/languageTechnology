#include "../Common/Pixel/PixelShader2DHeader.hlsli"

cbuffer scan : register(b4)
{
    float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	
    // uv調整
    float2 uv = PSInput.uv - 0.5f;
    
    ////UV座標とテクスチャを参照して、 最適な色を取得する

    float4 srcCol = tex.Sample(texSampler, PSInput.uv);
    if (srcCol.a < 0.01f)
    {
        // 描画しない(アルファテスト)
        discard;
    }
    
    // 走査線
    srcCol.rgb -= abs(sin((uv.y + g_time) * 60.0f)) * 0.10f;

    return srcCol;
	
}