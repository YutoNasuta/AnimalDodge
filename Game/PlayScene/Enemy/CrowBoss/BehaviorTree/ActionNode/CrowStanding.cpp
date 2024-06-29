//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			CrowStanding.h
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowStanding.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Framework/StepTimer.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowHead.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"
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
	
	
		MoveParts();	

		return true;
	
	
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
	auto rightHand = m_crow->GetHead()->GetRightWing();
	auto leftHand = m_crow->GetHead()->GetLeftWing();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;

	// �E��̐U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 4.0f;
	float swingAmount = DirectX::XM_PI / 3; // 60�x�̐U�蕝

	// �U�胂�[�V������ǉ�
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;

	// �U�胂�[�V�������N�H�[�^�j�I���ŕ\��
	DirectX::SimpleMath::Quaternion swingQuaternionRight = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(swing, 0.0f, swing);
	DirectX::SimpleMath::Quaternion swingQuaternionLeft = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(-swing, 0.0, -swing);

	// ���݂̃N�H�[�^�j�I����swingQuaternion��SLERP�ŕ��
	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQuaternion(), swingQuaternionRight, 0.1f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQuaternion(), swingQuaternionLeft, 0.1f);

	// �V�����N�H�[�^�j�I�����Z�b�g
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}