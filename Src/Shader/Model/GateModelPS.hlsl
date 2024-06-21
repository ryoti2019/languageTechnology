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
    float4 g_ambient_color;
    float3 g_light_dir;
    float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    float4 color;
    
    float2 uv = PSInput.uv;
    uv.x += g_time * 0.1f;
    
    // テクスチャーの色を取得
    color = diffuseMapTexture.Sample(diffuseMapSampler, uv);
    if (color.a < 0.01f)
    {
        discard;
    }
    
    float lightDot = dot(PSInput.normal, -g_light_dir);
    float3 rgb = color.rgb * (lightDot * g_diff_color.rgb);
    rgb += g_ambient_color.rgb;
    return float4(rgb, color.a);
}