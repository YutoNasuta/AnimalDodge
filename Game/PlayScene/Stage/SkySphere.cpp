//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/30
// <file>			SkySphere.h
// <�T�v>		�@�@�X�e�[�W�̋�����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"SkySphere.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include "Framework/DeviceResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkySphere::SkySphere()
{
	m_commonResources = CommonResources::GetInstance();
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"Sky");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkySphere::~SkySphere()
{

}

void SkySphere::SkyRender(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection)
{

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g�̐ݒ�
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// �ʃ��C�g�̖�����
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// ���f����������������
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		});

	// ���[���h�s��̍X�V
	DirectX::SimpleMath::Matrix world 
		= DirectX::SimpleMath::Matrix::Identity
		* DirectX::SimpleMath::Matrix::CreateScale(5);

	// ���f���̕`��
	m_model->Draw(context, *states, world, view, projection);

}
