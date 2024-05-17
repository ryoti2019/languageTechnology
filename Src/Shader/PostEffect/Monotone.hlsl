#include "../Common/Pixel/PixelShader2DHeader.hlsli"

cbuffer mono : register(b4)
{
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	
    // uv����
    float2 uv = PSInput.uv - 0.5f;
    
    //UV���W�ƃe�N�X�`�����Q�Ƃ��āA �œK�ȐF���擾����
    float4 srcCol = tex.Sample(texSampler, PSInput.uv);
    if (srcCol.a < 0.01f)
    {
        // �`�悵�Ȃ�(�A���t�@�e�X�g)
        discard;
    }
	
    float4 dstColor = srcCol;
    
    float4 gray = (dstColor.r + dstColor.g + dstColor.b) / 3.0f;

    return gray;
	
}