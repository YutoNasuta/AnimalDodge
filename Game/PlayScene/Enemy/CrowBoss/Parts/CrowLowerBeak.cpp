//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/30
// <file>			CrowLowerBeak.h
// <�T�v>		�@�@�G�l�~�[�̏�{
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowLowerBeak.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
CrowLowerBeak::CrowLowerBeak(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: CrowBase(parent, position, quaternion),
	m_commonResources{},
	m_partID{ CrowBase::PartID::BEAK_LOWER },
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_nodeNumber{ 1 }
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CrowLowerBeak::~CrowLowerBeak()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="resources"></param>
void CrowLowerBeak::Initialize()
{
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"CrowLowerBeak");	//���f���擾

	CrowBase::Initialize(m_nodeNumber, m_model);	// ���N���X��Initialize�Ăяo��
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">����</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
void CrowLowerBeak::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion)
{

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// ���݂̉�]�p���X�V����

	CrowBase::Update(			//�x�[�X���X�V
		m_position,
		m_quaternion);

	m_worldMatrix 				//�s��̕ύX
		= DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, -0.5f, 0.0f))
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position);


}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void CrowLowerBeak::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	CrowBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// �㏈��
/// </summary>
void CrowLowerBeak::Finalize()
{

}