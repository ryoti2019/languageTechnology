// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
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
    if(color.a < 0.01f)
    {
        discard;
    }
    
    // �֐��̖߂�l�����X�^���C���ɓn�����
    //return color * g_diff_color;
    
    // ���C�g����(�r���[���)
    //float3 lightDir = g_common.light[0].direction;
    //return float4(lightDir.x, lightDir.y, lightDir.z, 1.0f);
    
    // ���C�g����(���[���h���)
    //return float4(g_light_dir.x, g_light_dir.y, g_light_dir.z, 1.0f);
    
    // �@��(���[���h���)
    //return float4(PSInput.normal.x, PSInput.normal.y, PSInput.normal.z, 1.0f);
    
    // �@��            �FPSInput.normal
    // ���ς��g�p���āA�Fg_light_dir
    // �@�������Ɠ���������������A�Â�
    // �@�������Ɣ��Ε�����������A���邢
    
    // ���������F+1.0
    // ���Ε����F-1.0
    // ���������F 0.0
    float lightDot = dot(PSInput.normal, -g_light_dir);
    float3 rgb = color.rgb * (lightDot * g_diff_color.rgb);
    rgb += g_ambient_color.rgb;
    return float4(rgb, color.a);

}