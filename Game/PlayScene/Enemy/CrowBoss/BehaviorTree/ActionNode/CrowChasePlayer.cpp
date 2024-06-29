//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			CrowChase.cpp
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowChasePlayer.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Framework/StepTimer.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowHead.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"
#include"Game/PlayScene/BlackBoard.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="crow">�G</param>
CrowChase::CrowChase(Crow* crow , BlackBoard* blackboard)
{
	m_crow = crow;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
	m_blackBoard = blackboard;
}

/// <summary>
/// ���s
/// </summary>
bool CrowChase::Execute()
{

	// ���Ԃ��v��
	
		MoveParts();
		Chase();
	
		return true;
	

}


/// <summary>
/// �G�l�~�[�p�[�c�𓮂���
/// </summary>
void CrowChase::MoveParts()
{
	// ��𓮂���
	MoveHand();

}

/// <summary>
/// ��̓���
/// </summary>
void CrowChase::MoveHand()
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

	// ���݂̃N�H�[�^�j�I����swingQuaternion��lerp�ŕ��
	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQuaternion(), swingQuaternionRight, 0.1f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQuaternion(), swingQuaternionLeft, 0.1f);

	// �V�����N�H�[�^�j�I�����Z�b�g
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

void CrowChase::Chase()
{
	
	// �v���C���[�̈ʒu���擾
	auto playerPosition = m_blackBoard->GetPlayerPosition();
	auto crowPosition = m_crow->GetPosition();

	// �J���X����v���C���[�ւ̃x�N�g�����v�Z
	DirectX::SimpleMath::Vector3 direction = playerPosition - crowPosition;
	direction.y = 0.0f; // y�����𖳎����Đ����ʂł̕������v�Z

	// �J���X�̌������v���C���[�̕����Ɍ�����
	if (direction.LengthSquared() > 0.0001f) {
		direction.Normalize();
		float targetYaw = atan2(direction.x, direction.z);

		// �N�H�[�^�j�I�����g���ăJ���X�̌�����ݒ�
		DirectX::SimpleMath::Quaternion currentRotation = m_crow->GetQuaternion();
		DirectX::SimpleMath::Quaternion targetRotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(targetYaw, 0.0f, 0.0f);

		// �N�H�[�^�j�I���̕��
		float rotationSpeed = 0.1f;
		DirectX::SimpleMath::Quaternion newRotation = DirectX::SimpleMath::Quaternion::Slerp(currentRotation, targetRotation, rotationSpeed);
		m_crow->SetAngle(newRotation);
	}

	// �v���C���[�̈ʒu�Ɍ��������x���v�Z
	float speed = 0.1f;
	auto velocity = direction * speed;

	// �J���X�̈ʒu�Ƒ��x���X�V
	m_crow->SetPosition(crowPosition + velocity);
	m_crow->SetVelocity(velocity * 0.25f);
	  
}