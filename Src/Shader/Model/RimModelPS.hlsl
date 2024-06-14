// VS/PS共通
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

// 定数バッファ:スロット4番目
cbuffer cbParam : register(b4)
{
    float4 g_diff_color;    // 拡散光
    float4 g_ambient_color; // 環境光
    float3 g_light_dir;     // 光の方向
    float g_specular_pow;   // 
    float3 g_camera_pos;    // カメラ座標
    float dummy;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    
    float4 color;
    
    // テクスチャーの色を取得
    color = diffuseMapTexture.Sample(diffuseMapSampler, PSInput.uv);
    if (color.a < 0.01f)
    {
        discard;
    }
    
    float4 diffuse = PSInput.diffuse;
    
    // 視線ベクトル
    float3 eye = PSInput.worldPos - g_camera_pos;

    // 正規化ベクトル
    eye = normalize(eye);
    
    float3 norm = PSInput.normal;
    
    // 視線ベクトルと法線の内積
    float cDot = dot(norm, eye);

    // 絶対値をとる
    cDot = abs(cDot);
    
    // 反転
    cDot = 1.0f - cDot;
    
    float rimDot = pow(cDot, 2.0f); // 強弱を強める
    float4 rimColor = float4(0.0f, 1.0f, 0.0f, 1.0f);
    diffuse = rimColor * rimDot;
    
    return diffuse + color;

}