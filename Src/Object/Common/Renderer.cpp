#include "../Manager/SceneManager.h"
#include "../Application.h"
#include "../Common/Material.h"
#include "../Common/ModelMaterial.h"
#include "Renderer.h"

Renderer::Renderer(int modelId, std::shared_ptr<ModelMaterial> modelMaterial)
{
	modelId_ = modelId;
	modelMaterial_ = modelMaterial;
}
Renderer::~Renderer()
{
	DeleteShader(modelMaterial_->GetShaderVS());
	DeleteShaderConstantBuffer(modelMaterial_->GetconstBufVS());
	DeleteShader(modelMaterial_->GetShaderPS());
	DeleteShaderConstantBuffer(modelMaterial_->GetconstBufPS());
}

void Renderer::MakeSquereVertex(void)
{

	// ���_�C���f�b�N�X
	for (auto& v : vertexs_)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// ����
	vertexs_[0].pos = { 0.0f, 0.0f, 0.0f };
	vertexs_[0].u = 0.0f;
	vertexs_[0].v = 0.0f;
	// �E��
	vertexs_[1].pos = { Application::SCREEN_SIZE_X, 0.0f, 0.0f };
	vertexs_[1].u = 1.0f;
	vertexs_[1].v = 0.0f;
	// ����
	vertexs_[2].pos = { 0.0f, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[2].u = 0.0f;
	vertexs_[2].v = 1.0f;
	// �E��
	vertexs_[3].pos = { Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0.0f };
	vertexs_[3].u = 1.0f;
	vertexs_[3].v = 1.0f;

	//0,1,2 1,3,2
	indexes_[0] = 0;
	indexes_[1] = 1;
	indexes_[2] = 2;
	indexes_[3] = 1;
	indexes_[4] = 3;
	indexes_[5] = 2;

}

void Renderer::Draw(void)
{

	//// ���C���X�N���[��
	//int mainScreen = SceneManager::GetInstance().GetMainScreen();

	//SetDrawScreen(screen_);

	//// ��ʂ�������
	//ClearDrawScreen();

	// �I���W�i���V�F�[�_�ݒ�(ON)
	MV1SetUseOrigShader(true);

	// ���_�C���f�b�N�X
	//MakeSquereVertex();

	// ���_�V�F�[�_�̐ݒ�
	SetReserveVS();

	// �s�N�Z���V�F�[�_�̐ݒ�
	SetReservePS();

	// �e�N�X�`���A�h���X�^�C�v�̎擾
	auto texA = modelMaterial_->GetTextureAddress();
	int texAType = static_cast<int>(texA);

	// �e�N�X�`���A�h���X�^�C�v��ύX
	SetTextureAddressModeUV(texAType, texAType);

	// �`��
	MV1DrawModel(modelId_);

	// ��n��
	//--------------------------------------------

	// �e�N�X�`���A�h���X�^�C�v�����ɖ߂�
	SetTextureAddressModeUV(DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);

	// �e�N�X�`������
	const auto& textures = modelMaterial_->GetTextures();
	for (const auto& tex : textures)
	{
		SetUseTextureToShader(tex.first,-1);
	}

	// ���_�V�F�[�_����
	SetUseVertexShader(-1);

	// �s�N�Z���V�F�[�_����
	SetUsePixelShader(-1);

	// �I���W�i���V�F�[�_�ݒ�(OFF)
	MV1SetUseOrigShader(false);
	//--------------------------------------------

	//// ���C���ɖ߂�
	//SetDrawScreen(mainScreen);
	//DrawGraph(0, 0, screen_, false);
	//--------------------------------------------

}

void Renderer::SetReservePS(void)
{
	// �V�F�[�_�ݒ�
	SetUsePixelShader(modelMaterial_->GetShaderPS());

	size_t size;

	// �e�N�X�`���̐ݒ�
	const auto& textures = modelMaterial_->GetTextures();
	size = textures.size();
	if (size == 0)
	{
		// �O��g�p���̃e�N�X�`���������p���Ȃ��悤��
		SetUseTextureToShader(0, -1);
	}
	else
	{
		for (auto tex : textures)
		{
			SetUseTextureToShader(tex.first, tex.second);
		}
	}

	// �萔�o�b�t�@
	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(modelMaterial_->GetconstBufPS());
	const auto& constBufs = modelMaterial_->GetConstBufsPS();

	size = modelMaterial_->GetConstBufsPS().size();


	// ��Z�F
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			constBufsPtr++;
		}
		constBufsPtr->x = constBufs[i].x;
		constBufsPtr->y = constBufs[i].y;
		constBufsPtr->z = constBufs[i].z;
		constBufsPtr->w = constBufs[i].w;
	}

	// �萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(modelMaterial_->GetconstBufPS());

	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�p�萔�o�b�t�@���W�X�^��
	SetShaderConstantBuffer(modelMaterial_->GetconstBufPS(), DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// �`��
	//DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_VERTEX_IDX);

}

void Renderer::SetReserveVS(void)
{
	// ���_�V�F�[�_�ݒ�
	SetUseVertexShader(modelMaterial_->GetShaderVS());

	// �萔�o�b�t�@
	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(modelMaterial_->GetconstBufVS());
	const auto& constBufs = modelMaterial_->GetConstBufsVS();

	size_t size = modelMaterial_->GetConstBufsVS().size();

	// ��Z�F
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			constBufsPtr++;
		}
		constBufsPtr->x = constBufs[i].x;
		constBufsPtr->y = constBufs[i].y;
		constBufsPtr->z = constBufs[i].z;
		constBufsPtr->w = constBufs[i].w;
	}

	// �萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(modelMaterial_->GetconstBufVS());

	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�p�萔�o�b�t�@���W�X�^��
	SetShaderConstantBuffer(modelMaterial_->GetconstBufVS(), DX_SHADERTYPE_VERTEX, CONSTANT_BUF_SLOT_BEGIN_VS);
}
