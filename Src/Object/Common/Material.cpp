#include "Material.h"

Material::Material(std::string shaderFileName, int constBufFloat4Size, std::vector<FLOAT4> constBufs, std::map<int,int> textures)
{
	shader_ = LoadPixelShader(shaderFileName.c_str());
	constBuf_ = CreateShaderConstantBuffer(constBufFloat4Size);
	constBufs_ = constBufs;
	textures_ = textures;
	texAddress_ = TEXADDRESS::CLAMP;
}