#include "../Common/Pixel/PixelShader2DHeader.hlsli"

cbuffer mono : register(b4)
{
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	
    // uv調整
    float2 uv = PSInput.uv - 0.5f;
    
    //UV座標とテクスチャを参照して、 最適な色を取得する
    float4 srcCol = tex.Sample(texSampler, PSInput.uv);
    if (srcCol.a < 0.01f)
    {
        // 描画しない(アルファテスト)
        discard;
    }
	
    float4 dstColor = srcCol;
    
    float4 gray = (dstColor.r + dstColor.g + dstColor.b) / 3.0f;

    return gray;
	
}