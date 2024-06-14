// VS/PS����
#include "../Common/VertexToPixelHeader.hlsli"
// IN
#include "../Common/Vertex/VertexInputType.hlsli"
#define VERTEX_INPUT DX_MV1_VERTEX_TYPE_NMAP_1FRAME
// OUT
#define VS_OUTPUT VertexToPixelLit
#include "../Common/Vertex/VertexShader3DHeader.hlsli"

// �萔�o�b�t�@:�X���b�g4�Ԗ�
cbuffer cbParam : register(b7)
{
    float g_time;
    float2 g_uv_scale;
    float b;
}

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
    
    // ���̔g�����
    float maxHeight = 5.0f;
    float speed = 0.8f;
    // ���[���h���W���ړ������ꍇ�A�Ē������K�v�ɂȂ邽�߁A
    // ���f���̃��[���h���W����̃��[���h���_���W�̑��΍��W
    // -1.0 �` + 1.0
    float height = sin(g_time * speed + pow(lLocalPosition.x * 800.0f, 2.0f));
    // 0.0 �` 1.0
    height = (height + 1.0f) * 0.5f;
    // 0.0 �` 10.0f
    height *= maxHeight;
    
    lWorldPosition.y += height;
    //lWorldPosition.y += 300.0f;
    
    // ���[���h���W���r���[���W�ɕϊ�
    lViewPosition.w = 1.0f;
    lViewPosition.xyz = mul(lWorldPosition, g_base.viewMatrix);
    ret.vwPos.xyz = lViewPosition.xyz;
    
    // �r���[���W���ˉe���W�ɕϊ�
    ret.svPos = mul(lViewPosition, g_base.projectionMatrix);
    
    // ���_���W�ϊ� +++++++++++++++++++++++++++++++++++++( �I�� )
    // ���̑��A�s�N�Z���V�F�[�_�ֈ��p&������ ++++++++++++( �J�n )
    // UV���W
    ret.uv.x = VSInput.uv0.x * g_uv_scale.x;
    ret.uv.y = VSInput.uv0.y * g_uv_scale.y;
    
    // �@��(���[�J�����W�n)
    ret.normal = VSInput.norm;
    
    // �@��(���[���h���W�n)
    ret.normal = normalize(
    mul(VSInput.norm, (float3x3) g_base.localWorldMatrix));
    
    // �f�B�t���[�Y�J���[
    ret.diffuse = VSInput.diffuse;
    
    // ���C�g����(���[�J��)
    ret.lightDir = float3(0.0f, 0.0f, 0.0f);
    
    // ���C�g���猩�����W
    ret.lightAtPos = float3(0.0f, 0.0f, 0.0f);
    
    // ���̑��A�s�N�Z���V�F�[�_�ֈ��p&������ ++++++++++++( �I�� )
    
    // �o�̓p�����[�^��Ԃ�
    return ret;
    
}