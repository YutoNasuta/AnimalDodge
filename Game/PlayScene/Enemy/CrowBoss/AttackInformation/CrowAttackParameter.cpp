//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/02
// <file>			CrowAttackParameter.h
// <�T�v>		�@�@�J���X�̍U���p�����[�^
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"CrowAttackParameter.h"
#include"Game/CommonResources.h"
#include"Framework/StepTimer.h"

const float CrowAttackParameter::m_attack1Cooldown = 5.0f; // ��Ƃ���5�b

/// <summary>
/// �R���X�g���N�^
/// </summary>
CrowAttackParameter::CrowAttackParameter()
	:
	m_attackTime{}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CrowAttackParameter::~CrowAttackParameter()
{

}

/// <summary>
/// �A�^�b�N�P���N��
/// </summary>
void CrowAttackParameter::Attack1Execute()
{
	auto Timer = m_commonResources->GetStepTimer();
	float currentTime = Timer->GetTotalSeconds();

	// �N�[���_�E�����Ԓ��͍U�����Ȃ�
	if (currentTime < m_lastAttack1Time + m_attack1Cooldown)
	{
		return;
	}

	// �U��1���J�n
	SetAttack1(true);
	m_lastAttack1Time = currentTime;
}