//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			EnemyChase.cpp
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"EnemyChasePlayer.h"
#include"Game/Enemy/Enemy.h"
#include"Framework/StepTimer.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include"Game/Enemy/Parts/EnemyLeftHand.h"
#include"Game/Enemy/Parts/EnemyRightHand.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G</param>
EnemyChase::EnemyChase(Enemy* enemy)
{
	m_enemy = enemy;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
}

/// <summary>
/// ���s
/// </summary>
bool EnemyChase::Execute()
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
void EnemyChase::MoveParts()
{
	// ��𓮂���
	MoveHand();
}

/// <summary>
/// ��̓���
/// </summary>
void EnemyChase::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_enemy->GetBody()->GetRightHand();		// �E��擾
	auto leftHand = m_enemy->GetBody()->GetLeftHand();			// ����擾

	// �U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 10.0f;
	float swingAmount = 0.8f;

	// �U�胂�[�V������ǉ�
	float swing = static_cast<float>(sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount);

	// �v���C���[�̉E��̈ʒu���v�Z
	auto rightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, swing, 0.0f);
	auto leftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -swing, 0.0f);

	rightHand->SetAddQuaternion(rightQuaternion);
	leftHand->SetAddQuaternion(leftQuaternion);
}