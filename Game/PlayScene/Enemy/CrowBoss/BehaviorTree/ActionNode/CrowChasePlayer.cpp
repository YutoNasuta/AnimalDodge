//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			CrowChase.cpp
// <概要>			エネミーの立ち状態
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
	
		MoveParts();
		Chase();
	
		return true;
	

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

	// 現在のクォータニオンとswingQuaternionをlerpで補間
	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQuaternion(), swingQuaternionRight, 0.1f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQuaternion(), swingQuaternionLeft, 0.1f);

	// 新しいクォータニオンをセット
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

void CrowChase::Chase()
{
	
	// プレイヤーの位置を取得
	auto playerPosition = m_blackBoard->GetPlayerPosition();
	auto crowPosition = m_crow->GetPosition();

	// カラスからプレイヤーへのベクトルを計算
	DirectX::SimpleMath::Vector3 direction = playerPosition - crowPosition;
	direction.y = 0.0f; // y成分を無視して水平面での方向を計算

	// カラスの向きをプレイヤーの方向に向ける
	if (direction.LengthSquared() > 0.0001f) {
		direction.Normalize();
		float targetYaw = atan2(direction.x, direction.z);

		// クォータニオンを使ってカラスの向きを設定
		DirectX::SimpleMath::Quaternion currentRotation = m_crow->GetQuaternion();
		DirectX::SimpleMath::Quaternion targetRotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(targetYaw, 0.0f, 0.0f);

		// クォータニオンの補間
		float rotationSpeed = 0.1f;
		DirectX::SimpleMath::Quaternion newRotation = DirectX::SimpleMath::Quaternion::Slerp(currentRotation, targetRotation, rotationSpeed);
		m_crow->SetAngle(newRotation);
	}

	// プレイヤーの位置に向かう速度を計算
	float speed = 0.1f;
	auto velocity = direction * speed;

	// カラスの位置と速度を更新
	m_crow->SetPosition(crowPosition + velocity);
	m_crow->SetVelocity(velocity * 0.25f);
	  
}