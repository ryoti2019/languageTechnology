// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

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
    //return color;
    
    //color.rgba = float4(1.0, 1.0, 1.0, 1.0);
    return float4(1.0, 1.0, 1.0, 1.0);

}