// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

// �萔�o�b�t�@:�X���b�g4�Ԗ�
cbuffer cbParam : register(b4)
{
    float4 g_diff_color;    // �g�U��
    float4 g_ambient_color; // ����
    float3 g_light_dir;     // ���̕���
    float g_specular_pow;   // 
    float3 g_camera_pos;    // �J�������W
    float dummy;
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
    
    float4 diffuse = PSInput.diffuse;
    
    // �����x�N�g��
    float3 eye = PSInput.worldPos - g_camera_pos;

    // ���K���x�N�g��
    eye = normalize(eye);
    
    float3 norm = PSInput.normal;
    
    // �����x�N�g���Ɩ@���̓���
    float cDot = dot(norm, eye);

    // ��Βl���Ƃ�
    cDot = abs(cDot);
    
    // ���]
    cDot = 1.0f - cDot;
    
    float rimDot = pow(cDot, 2.0f); // ��������߂�
    float4 rimColor = float4(0.0f, 1.0f, 0.0f, 1.0f);
    diffuse = rimColor * rimDot;
    
    return diffuse + color;

}