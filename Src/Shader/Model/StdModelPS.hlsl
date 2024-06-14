// VS/PS共通
#include "../Common/VertexToPixelHeader.hlsli"

// IN
#define PS_INPUT VertexToPixelLit

// PS
#include "../Common/Pixel/PixelShader3DHeader.hlsli"

// 定数バッファ:スロット4番目
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
    
    // テクスチャーの色を取得
    color = diffuseMapTexture.Sample(diffuseMapSampler, PSInput.uv);
    if(color.a < 0.01f)
    {
        discard;
    }
    
    // 関数の戻り値がラスタライ座に渡される
    //return color * g_diff_color;
    
    // ライト方向(ビュー空間)
    //float3 lightDir = g_common.light[0].direction;
    //return float4(lightDir.x, lightDir.y, lightDir.z, 1.0f);
    
    // ライト方向(ワールド空間)
    //return float4(g_light_dir.x, g_light_dir.y, g_light_dir.z, 1.0f);
    
    // 法線(ワールド空間)
    //return float4(PSInput.normal.x, PSInput.normal.y, PSInput.normal.z, 1.0f);
    
    // 法線            ：PSInput.normal
    // 内積を使用して、：g_light_dir
    // 法線が光と同じ方向だったら、暗い
    // 法線が光と反対方向だったら、明るい
    
    // 同じ方向：+1.0
    // 反対方向：-1.0
    // 垂直方向： 0.0
    float lightDot = dot(PSInput.normal, -g_light_dir);
    float3 rgb = color.rgb * (lightDot * g_diff_color.rgb);
    rgb += g_ambient_color.rgb;
    return float4(rgb, color.a);

}