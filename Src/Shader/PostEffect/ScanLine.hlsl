#include "../Common/Pixel/PixelShader2DHeader.hlsli"

cbuffer scan : register(b4)
{
    float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	
    // uv����
    float2 uv = PSInput.uv - 0.5f;
    
    ////UV���W�ƃe�N�X�`�����Q�Ƃ��āA �œK�ȐF���擾����

    float4 srcCol = tex.Sample(texSampler, PSInput.uv);
    if (srcCol.a < 0.01f)
    {
        // �`�悵�Ȃ�(�A���t�@�e�X�g)
        discard;
    }
    
    // ������
    srcCol.rgb -= abs(sin((uv.y + g_time) * 60.0f)) * 0.10f;

    return srcCol;
	
}