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
#include"Game/BlackBoard.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G</param>
EnemyChase::EnemyChase(Enemy* enemy , BlackBoard* blackboard)
{
	m_enemy = enemy;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
	m_blackBoard = blackboard;
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
		Chase();
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

void EnemyChase::Chase()
{
	
	// TODO �v���C���[�̈ʒu���擾����悤�ɂ���B���͉��̒l
	DirectX::SimpleMath::Vector2 length = (DirectX::SimpleMath::Vector2(m_blackBoard->GetPlayerPosition().x - m_enemy->GetPosition().x, m_blackBoard->GetPlayerPosition().z - m_enemy->GetPosition().z));

	float r = atan2(length.y, length.x);

	auto velocity = DirectX::SimpleMath::Vector3(0.5f * cos(r), 0.0f, 0.5f * sin(r));

	m_enemy->SetPosition(m_enemy->GetPosition() + m_enemy->GetVelocity());
	m_enemy->SetVelocity(velocity * 0.25f);
	
}