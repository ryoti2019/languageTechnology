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

    
    //dstColor.rgb *= 0.2f;,n
    //dstColor.xyz *= 0.2f;
    //float4 gray = (dstColor.r + dstColor.g + dstColor.b) / 3.0f;
    //dstColor.rgb *= 0.2f;
    
    //float3 sepia = dstColor.rgb;
    //sepia.r = dot(dstColor.rgb, float3(0.393f, 0.769f, 0.189f));
    //sepia.g = dot(dstColor.rgb, float3(0.349f, 0.686f, 0.168f));
    //sepia.b = dot(dstColor.rgb, float3(0.272f, 0.534f, 0.131f));
    //dstColor.rgb = lerp(dstColor.rbg, sepia, g_sepia_pow);

    return srcCol;
	
}