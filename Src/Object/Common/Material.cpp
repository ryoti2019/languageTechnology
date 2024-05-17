#include "Material.h"

Material::Material(std::string shaderFileName, int constBufFloat4Size, std::vector<FLOAT4> constBufs)
{
	shader_ = LoadPixelShader(shaderFileName.c_str());
	constBuf_ = CreateShaderConstantBuffer(constBufFloat4Size);
	constBufs_ = constBufs;
}
