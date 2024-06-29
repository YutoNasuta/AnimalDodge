//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			CrowHead.cpp
// <�T�v>			�v���C���[�̓��̃p�[�c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowHead.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftLeg.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightLeg.h"
#include"Libraries/NakashiLib/InputManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
CrowHead::CrowHead(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: CrowBase(parent , position ,quaternion),
	m_commonResources{},
	m_partID{CrowBase::PartID::BODY},
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_rightWing{},
	m_leftWing{},
	m_rightLeg{},
	m_leftLeg{},
	m_addQuaternion{},
	m_nodeNumber{1}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CrowHead::~CrowHead()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void CrowHead::Initialize()
{

	ModelInitialize();
	ChildInitialize();

	// ���N���X��Initialize�Ăяo��
	CrowBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// �q���̏�����
/// </summary>
void CrowHead::ChildInitialize()
{
	// �H���q�I�u�W�F�N�g��
	auto rightWing =
		std::make_unique<CrowRightWing>(
			this,
			DirectX::SimpleMath::Vector3(-5.0f, 5.0f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_rightWing = rightWing.get();
	SetChild(std::move(rightWing));

	auto leftWing =
		std::make_unique<CrowLeftWing>(
			this,
			DirectX::SimpleMath::Vector3(5.0f, 5.0f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_leftWing = leftWing.get();
	SetChild(std::move(leftWing));

	// �����q�I�u�W�F�N�g��
	auto rightLeg = std::make_unique<CrowRightLeg>(
		this,
		DirectX::SimpleMath::Vector3(-2.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_rightLeg = rightLeg.get();
	SetChild(std::move(rightLeg));

	auto leftLeg = std::make_unique<CrowLeftLeg>(
		this,
		DirectX::SimpleMath::Vector3(2.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_leftLeg = leftLeg.get();
	SetChild(std::move(leftLeg));
}

/// <summary>
/// ���f���̏�����
/// </summary>
void CrowHead::ModelInitialize()
{
	//m_commonResources->GetResourcesManager()->CreateModel(L"CrowHead", L"CrowHead.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyLeftHand", L"EnemyLeftHand.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"CrowHead", L"CrowHead.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyLeg", L"EnemyLeg.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyRightHand", L"EnemyRightHand.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyTail", L"EnemyTail.cmo");
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"CrowHead");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">����</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
void CrowHead::Update(
	const DirectX::SimpleMath::Vector3& position , 
	const DirectX::SimpleMath::Quaternion& quaternion)
{

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = m_quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// ���݂̉�]�p���X�V����

	CrowBase::Update(
		m_position,
		m_quaternion);

	m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position)
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetInitialQuaternion());
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void CrowHead::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	CrowBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// �㏈��
/// </summary>
void CrowHead::Finalize()
{
}

