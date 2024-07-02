//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/02
// <file>			CrowAttackParameter.h
// <概要>		　　カラスの攻撃パラメータ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"CrowAttackParameter.h"
#include"Game/CommonResources.h"
#include"Framework/StepTimer.h"

const float CrowAttackParameter::m_attack1Cooldown = 5.0f; // 例として5秒

/// <summary>
/// コンストラクタ
/// </summary>
CrowAttackParameter::CrowAttackParameter()
	:
	m_attackTime{}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
CrowAttackParameter::~CrowAttackParameter()
{

}

/// <summary>
/// アタック１を起動
/// </summary>
void CrowAttackParameter::Attack1Execute()
{
	auto Timer = m_commonResources->GetStepTimer();
	float currentTime = Timer->GetTotalSeconds();

	// クールダウン期間中は攻撃しない
	if (currentTime < m_lastAttack1Time + m_attack1Cooldown)
	{
		return;
	}

	// 攻撃1を開始
	SetAttack1(true);
	m_lastAttack1Time = currentTime;
}