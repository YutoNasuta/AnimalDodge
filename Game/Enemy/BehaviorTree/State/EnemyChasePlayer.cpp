//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			EnemyChase.cpp
// <概要>			エネミーの立ち状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"EnemyChasePlayer.h"
#include"Game/Enemy/Enemy.h"
#include"Framework/StepTimer.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include"Game/Enemy/Parts/EnemyLeftHand.h"
#include"Game/Enemy/Parts/EnemyRightHand.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵</param>
EnemyChase::EnemyChase(Enemy* enemy)
{
	m_enemy = enemy;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
}

/// <summary>
/// 実行
/// </summary>
bool EnemyChase::Execute()
{

	// 時間を計る
	m_timeExit += static_cast<float>(m_commonResources->GetStepTimer()->GetElapsedSeconds());
	if (m_timeExit <= EXITTIME)		//タイムより下なら
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
/// エネミーパーツを動かす
/// </summary>
void EnemyChase::MoveParts()
{
	// 手を動かす
	MoveHand();
}

/// <summary>
/// 手の動き
/// </summary>
void EnemyChase::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_enemy->GetBody()->GetRightHand();		// 右手取得
	auto leftHand = m_enemy->GetBody()->GetLeftHand();			// 左手取得

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