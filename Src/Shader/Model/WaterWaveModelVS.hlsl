// VS/PS共通
#include "../Common/VertexToPixelHeader.hlsli"
// IN
#include "../Common/Vertex/VertexInputType.hlsli"
#define VERTEX_INPUT DX_MV1_VERTEX_TYPE_NMAP_1FRAME
// OUT
#define VS_OUTPUT VertexToPixelLit
#include "../Common/Vertex/VertexShader3DHeader.hlsli"

// 定数バッファ:スロット4番目
cbuffer cbParam : register(b7)
{
    float g_time;
    float2 g_uv_scale;
    float b;
}

VS_OUTPUT main(VS_INPUT VSInput)
{
    
    VS_OUTPUT ret;
    
    // 頂点座標変換 +++++++++++++++++++++++++++++++++++++( 開始 )
    float4 lLocalPosition;
    float4 lWorldPosition;
    float4 lViewPosition;
    
    // float3 → float4
    lLocalPosition.xyz = VSInput.pos;
    lLocalPosition.w = 1.0f;
    
    // ローカル座標をワールド座標に変換(剛体)
    lWorldPosition.w = 1.0f;
    lWorldPosition.xyz = mul(lLocalPosition, g_base.localWorldMatrix);
    
    // 水の波を作る
    float maxHeight = 5.0f;
    float speed = 0.8f;
    // ワールド座標を移動した場合、再調整が必要になるため、
    // モデルのワールド座標からのワールド頂点座標の相対座標
    // -1.0 ～ + 1.0
    float height = sin(g_time * speed + pow(lLocalPosition.x * 800.0f, 2.0f));
    // 0.0 ～ 1.0
    height = (height + 1.0f) * 0.5f;
    // 0.0 ～ 10.0f
    height *= maxHeight;
    
    lWorldPosition.y += height;
    //lWorldPosition.y += 300.0f;
    
    // ワールド座標をビュー座標に変換
    lViewPosition.w = 1.0f;
    lViewPosition.xyz = mul(lWorldPosition, g_base.viewMatrix);
    ret.vwPos.xyz = lViewPosition.xyz;
    
    // ビュー座標を射影座標に変換
    ret.svPos = mul(lViewPosition, g_base.projectionMatrix);
    
    // 頂点座標変換 +++++++++++++++++++++++++++++++++++++( 終了 )
    // その他、ピクセルシェーダへ引継&初期化 ++++++++++++( 開始 )
    // UV座標
    ret.uv.x = VSInput.uv0.x * g_uv_scale.x;
    ret.uv.y = VSInput.uv0.y * g_uv_scale.y;
    
    // 法線(ローカル座標系)
    ret.normal = VSInput.norm;
    
    // 法線(ワールド座標系)
    ret.normal = normalize(
    mul(VSInput.norm, (float3x3) g_base.localWorldMatrix));
    
    // ディフューズカラー
    ret.diffuse = VSInput.diffuse;
    
    // ライト方向(ローカル)
    ret.lightDir = float3(0.0f, 0.0f, 0.0f);
    
    // ライトから見た座標
    ret.lightAtPos = float3(0.0f, 0.0f, 0.0f);
    
    // その他、ピクセルシェーダへ引継&初期化 ++++++++++++( 終了 )
    
    // 出力パラメータを返す
    return ret;
    
}