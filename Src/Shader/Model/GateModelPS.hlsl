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
    
    float g_alpha;
    float g_noise;
    float2 dummy;
}

Texture2D noise : register(t1); //テクスチャ
SamplerState noiseMapSampler :register(s1);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    float4 color;
    float4 noiseColor;
    float noiseUv = PSInput.uv;
    float2 uv = PSInput.uv;
    uv.x += g_time * 0.1f;
    uv *= float2(3.0f, 3.0f);

    noiseColor = noise.Sample(noiseMapSampler, uv);
    
    float noise = noiseColor.r + noiseColor.g + noiseColor.b;
    noise = noise - (g_noise * g_noise);
    noiseColor.a += noise;
    
    return noiseColor;
    
    noiseColor.a = g_alpha;
    if (noiseColor.r <= g_noise && noiseColor.g <= g_noise && noiseColor.b <= g_noise)
    {
        noiseColor.a -= 0.01f;
    }
    
}