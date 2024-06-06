#include "../Common/Pixel/PixelShader2DHeader.hlsli"
cbuffer cbP : register(b4)
{
    float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    float4 srcCol = tex.Sample(texSampler, PSInput.uv);

    // �m�C�Y�v�Z(�^��������)
    // Sin�g(�����g)���o���A-1.0�`1.0�̒l��傫������
    // �������̂ݎ��o���B(frac�֐�)
    // frac-sin�̒l���o��B
    float noise = frac(sin(
    dot(PSInput.uv * g_time, float2(12.9898f, 78.233f))) * 43758.5453f) - 0.5f;
    
    // �摜�ɓ����ȏꏊ�ŐF�������Ă�����
    if (srcCol.a == 0.0f && noise > 0.0f)
    {
        // ���S�����Ńm�C�Y�L��́A�m�C�Y�J���[�g�p
        srcCol.rgb = float3(noise, noise, noise);
        // �X�ɕs�����ɂ���
        srcCol.a = 1.0f;
    }
    else
    {
        // �m�C�Y�J���[�����Z����
        srcCol.rgb += float3(noise, noise, noise);
    }
    return srcCol;
}