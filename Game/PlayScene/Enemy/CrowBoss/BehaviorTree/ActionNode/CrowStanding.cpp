//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			CrowStanding.h
// <概要>			エネミーの立ち状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowStanding.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Framework/StepTimer.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowHead.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/PlayScene/Enemy/CrowBoss/Parts/CrowRightWing.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵</param>
CrowStanding::CrowStanding(Crow* crow)
{
	m_crow = crow;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
}

/// <summary>
/// 実行
/// </summary>
bool CrowStanding::Execute()
{
	
	
		MoveParts();	

		return true;
	
	
}


/// <summary>
/// エネミーパーツを動かす
/// </summary>
void CrowStanding::MoveParts()
{
	// 手を動かす
	MoveHand();
}

/// <summary>
/// 手の動き
/// </summary>
void CrowStanding::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_crow->GetHead()->GetRightWing();
	auto leftHand = m_crow->GetHead()->GetLeftWing();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;

	// 右手の振りモーションのパラメーター
	float swingSpeed = 4.0f;
	float swingAmount = DirectX::XM_PI / 3; // 60度の振り幅

	// 振りモーションを追加
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;

	// 振りモーションをクォータニオンで表現
	DirectX::SimpleMath::Quaternion swingQuaternionRight = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(swing, 0.0f, swing);
	DirectX::SimpleMath::Quaternion swingQuaternionLeft = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(-swing, 0.0, -swing);

	// 現在のクォータニオンとswingQuaternionをSLERPで補間
	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQuaternion(), swingQuaternionRight, 0.1f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQuaternion(), swingQuaternionLeft, 0.1f);

	// 新しいクォータニオンをセット
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}