//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			CrowChase.cpp
// <概要>			エネミーの立ち状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"CrowChasePlayer.h"
#include"Game/Enemy/CrowBoss/Crow.h"
#include"Framework/StepTimer.h"
#include"Game/Enemy/CrowBoss/Parts/CrowHead.h"
#include"Game/Enemy/CrowBoss/Parts/CrowLeftWing.h"
#include"Game/Enemy/CrowBoss/Parts/CrowRightWing.h"
#include"Game/BlackBoard.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="crow">敵</param>
CrowChase::CrowChase(Crow* crow , BlackBoard* blackboard)
{
	m_crow = crow;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
	m_blackBoard = blackboard;
}

/// <summary>
/// 実行
/// </summary>
bool CrowChase::Execute()
{

	// 時間を計る
	m_timeExit += static_cast<float>(m_commonResources->GetStepTimer()->GetElapsedSeconds());
	if (m_timeExit <= EXITTIME)		//タイムより下なら
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
/// エネミーパーツを動かす
/// </summary>
void CrowChase::MoveParts()
{
	// 手を動かす
	MoveHand();

}

/// <summary>
/// 手の動き
/// </summary>
void CrowChase::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_crow->GetHead()->GetRightHand();		// 右手取得
	auto leftHand = m_crow->GetHead()->GetLeftHand();			// 左手取得

	// 振りモーションのパラメーター
	float swingSpeed = 10.0f;
	float swingAmount = 0.8f;

	// 振りモーションを追加
	float swing = static_cast<float>(sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount);

	// プレイヤーの右手の位置を計算
	auto rightQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, swing, 0.0f);
	auto leftQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -swing, 0.0f);

	rightHand->SetAddQuaternion(rightQuaternion);
	leftHand->SetAddQuaternion(leftQuaternion);
}

void CrowChase::Chase()
{
	
	// TODO プレイヤーの位置を取得するようにする。今は仮の値
	DirectX::SimpleMath::Vector2 length = (DirectX::SimpleMath::Vector2(m_blackBoard->GetPlayerPosition().x - m_crow->GetPosition().x, m_blackBoard->GetPlayerPosition().z - m_crow->GetPosition().z));

	float r = atan2(length.y, length.x);

	auto velocity = DirectX::SimpleMath::Vector3(0.5f * cos(r), 0.0f, 0.5f * sin(r));

	m_crow->SetPosition(m_crow->GetPosition() + m_crow->GetVelocity());
	m_crow->SetVelocity(velocity * 0.25f);
	  
}