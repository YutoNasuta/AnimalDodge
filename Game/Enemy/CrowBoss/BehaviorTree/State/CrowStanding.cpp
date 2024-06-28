//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			CrowStanding.h
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowStanding.h"
#include"Game/Enemy/CrowBoss/Crow.h"
#include"Framework/StepTimer.h"
#include"Game/Enemy/CrowBoss/Parts/CrowHead.h"
#include"Game/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/Enemy/CrowBoss/Parts/CrowRightWing.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G</param>
CrowStanding::CrowStanding(Crow* crow)
{
	m_crow = crow;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
}

/// <summary>
/// ���s
/// </summary>
bool CrowStanding::Execute()
{
	
	// ���Ԃ��v��
	m_timeExit += static_cast<float>(m_commonResources->GetStepTimer()->GetElapsedSeconds());
	if (m_timeExit <= EXITTIME)		//�^�C����艺�Ȃ�
	{
		MoveParts();
		return false;
	}
	else
	{
		return true;
	}
	
}


/// <summary>
/// �G�l�~�[�p�[�c�𓮂���
/// </summary>
void CrowStanding::MoveParts()
{
	// ��𓮂���
	MoveHand();
}

/// <summary>
/// ��̓���
/// </summary>
void CrowStanding::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_crow->GetHead()->GetRightHand();
	auto leftHand = m_crow->GetHead()->GetLeftHand();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;
	// �E��̐U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 1.0f;
	float swingAmount = 0.1f;

	// �U�胂�[�V������ǉ�
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;


	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);// ���`�⊮����

	rightHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	leftHand->SetAddQuaternion(slerpRotationLeft);
}