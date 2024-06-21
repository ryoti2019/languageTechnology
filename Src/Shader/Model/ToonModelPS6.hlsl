// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLitFog

// PS
#define TOON 1
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

// �萔�o�b�t�@:�X���b�g4�Ԗ�
cbuffer cbParam : register(b4)
{
    float4 g_diff_color;
    float3 g_light_dir;
    float dummy;
    float4 g_ambient_color;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    
    float4 color;
    
    // �e�N�X�`���[�̐F���擾
    color = diffuseMapTexture.Sample(diffuseMapSampler, PSInput.uv);
    if (color.a < 0.01f)
    {
        discard;
    }
    
    // �t�H�O
    color.rgb *= PSInput.fogFactor;

    // �n�[�t�����o�[�g�g�U�Ɩ��ɂ��f�B���N�V���i�����C�e�B���O�v�Z�ɉ����A
	// �|�C���g���C�g��������
    float p = dot(PSInput.normal * -1.0f, g_light_dir.xyz);
    p *= 0.4f;
    p = clamp(-1.0f, 1.4f, p + (PSInput.lightPower * 0.8f));
    p = p * 0.5f + 0.5f;
    p = p * p;
 
    float4 toon = toonDiffuseGradTexture.Sample(
        toonDiffuseGradSampler, float2(p, 0.0f));
 
    float3 destColor = color.rgb * toon.rgb + g_ambient_color.rgb;
    return float4(destColor, color.a);
    
}