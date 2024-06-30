//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/16
// <file>			Resources.cpp
// <�T�v>			�Q�[���Ŏg���摜�⃂�f���B
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlaySceneResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
PlaySceneResources::PlaySceneResources()
{
	m_commonResources = CommonResources::GetInstance();
	CreateModels();
	CreateSrvs();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneResources::~PlaySceneResources()
{

}

/// <summary>
///	���f���̐ݒ�
/// </summary>
void PlaySceneResources::CreateModels()
{
	auto ResourcesManager = m_commonResources->GetResourcesManager();

	// �v���C���[�̃p�[�c����
	ResourcesManager->CreateModel(L"PlayerBody",		 L"Player/PlayerBody.cmo");
	ResourcesManager->CreateModel(L"PlayerLeftHand",	 L"Player/PlayerLeftHand.cmo");
	ResourcesManager->CreateModel(L"PlayerHead",		 L"Player/PlayerHead.cmo");
	ResourcesManager->CreateModel(L"PlayerLeg",			 L"Player/PlayerLeg.cmo");
	ResourcesManager->CreateModel(L"PlayerRightHand",	 L"Player/PlayerRightHand.cmo");
	ResourcesManager->CreateModel(L"PlayerTail",		 L"Player/PlayerTail.cmo");

	// �G�l�~�[�̃p�[�c����
	ResourcesManager->CreateModel(L"CrowHead",		     L"Crow/CrowHead.cmo");
	ResourcesManager->CreateModel(L"CrowLeftWing",		 L"Crow/CrowLeftWing.cmo");
	ResourcesManager->CreateModel(L"CrowRightWing",		 L"Crow/CrowRightWing.cmo");
	ResourcesManager->CreateModel(L"CrowLeg",			 L"Crow/CrowLeg.cmo");

	// �ǂ̐���
	ResourcesManager->CreateModel(L"Wall",				 L"Wall/WallBlock.cmo");

	// ��̐���
	ResourcesManager->CreateModel(L"Sky",				 L"Sky/celestial_sphere.cmo");
}

/// <summary>
/// �摜�̐ݒ�
/// </summary>
void PlaySceneResources::CreateSrvs()
{

}