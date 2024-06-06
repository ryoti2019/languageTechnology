#include "../Common/Pixel/PixelShader2DHeader.hlsli"
cbuffer cbP : register(b4)
{
    float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    float4 srcCol = tex.Sample(texSampler, PSInput.uv);

    // ノイズ計算(疑似乱数式)
    // Sin波(正弦波)を出す、-1.0～1.0の値を大きくする
    // 小数部のみ取り出す。(frac関数)
    // frac-sinの値が出る。
    float noise = frac(sin(
    dot(PSInput.uv * g_time, float2(12.9898f, 78.233f))) * 43758.5453f) - 0.5f;
    
    // 画像に透明な場所で色が入っていたら
    if (srcCol.a == 0.0f && noise > 0.0f)
    {
        // 完全透明でノイズ有りは、ノイズカラー使用
        srcCol.rgb = float3(noise, noise, noise);
        // 更に不透明にする
        srcCol.a = 1.0f;
    }
    else
    {
        // ノイズカラーを加算する
        srcCol.rgb += float3(noise, noise, noise);
    }
    return srcCol;
}