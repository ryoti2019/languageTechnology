// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"
// IN
#include "../Common/Vertex/VertexInputType.hlsli"
#define VERTEX_INPUT DX_MV1_VERTEX_TYPE_NMAP_1FRAME
// OUT
#define VS_OUTPUT VertexToPixelLit
#include "../Common/Vertex/VertexShader3DHeader.hlsli"

VS_OUTPUT main(VS_INPUT VSInput)
{
    VS_OUTPUT ret;
    
    // ���_���W�ϊ� +++++++++++++++++++++++++++++++++++++( �J�n )
    float4 lLocalPosition;
    float4 lWorldPosition;
    float4 lViewPosition;
    
    // float3 �� float4
    lLocalPosition.xyz = VSInput.pos;
    lLocalPosition.w = 1.0f;
    
    // ���[�J�����W�����[���h���W�ɕϊ�(����)
    lWorldPosition.w = 1.0f;
    lWorldPosition.xyz = mul(lLocalPosition, g_base.localWorldMatrix);
    
    // ���[���h���W���r���[���W�ɕϊ�
    lViewPosition.w = 1.0f;
    lViewPosition.xyz = mul(lWorldPosition, g_base.viewMatrix);
    ret.vwPos.xyz = lViewPosition.xyz;
    
    // �r���[���W���ˉe���W�ɕϊ�
    ret.svPos = mul(lViewPosition, g_base.projectionMatrix);
    // ���_���W�ϊ� +++++++++++++++++++++++++++++++++++++( �I�� )
    
    // �o�̓p�����[�^��Ԃ�
    return ret;
}