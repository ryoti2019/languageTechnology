#include "../Common/Pixel/PixelShader2DHeader.hlsli"
cbuffer cbColor : register(b4)
{
    float g_time;
}

Texture2D noise : register(t1); //�e�N�X�`��

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    
    // uv����
    float2 mainUv = PSInput.uv/* - 0.5f*/;
    float2 noiseUv = PSInput.uv/* - 0.5f*/;
    
    // RGBA���Ƃ��Ă��Đ�����-1����1�̒l�ɂ���
    float4 noiseCol = noise.Sample(texSampler, noiseUv) * 2.0f - 1.0f;
    
    // �m�C�Y�̑傫��
    mainUv.y += noiseCol * 0.2f;
    
    noiseUv.x += sin(g_time * 0.3f);
    noiseUv.y += frac(g_time * 0.5f);
    
    float4 srcCol = tex.Sample(texSampler, mainUv);
    
    return srcCol;
    
}