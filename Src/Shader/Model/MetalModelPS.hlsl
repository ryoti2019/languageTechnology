// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

// �萔�o�b�t�@:�X���b�g4�Ԗ�
cbuffer cbParam : register(b4)
{
    float4 g_diff_color;        // �g�U��
    float4 g_ambient_color;     // ����
    float4 g_specular_color;    // ���ˌ�
    float3 g_light_dir;         // ���̕���
    float g_specular_pow;       // 
    float3 g_camera_pos;        // �J�������W
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
    
    // �@��
    float3 norm = PSInput.normal;
    
    // �g�U���̋���
    float difDot = dot(norm, -g_light_dir);
    
    // �t�ڐ�(���_����̃J��������)
    float3 toEye = normalize(g_camera_pos - PSInput.worldPos);
    
    // ���˃x�N�g��
    float3 reflectDir = normalize(g_light_dir + (norm * 2.0f));
    
    // ���ˌ��̋���(���Α������̒l�ɂȂ�̂Ő�Βl������)
    float refDot = abs(dot(reflectDir, toEye));
    
    // ���ˌ����i��
    float refDotEx = pow(refDot, g_specular_pow);
    
    // �g�U��
    float3 diffuse = color.rgb * (difDot * g_diff_color).rgb;
    
    // �F�̍���
    float3 rgb = diffuse + (refDotEx * g_specular_color).rgb + g_ambient_color.rgb;
    
    return float4(rgb, color.a);

}