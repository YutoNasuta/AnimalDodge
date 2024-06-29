//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			PlayerDash.cpp
// <概要>		　　プレイヤーダッシュ状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerDash.h"
#include"Game/PlayScene/Player/Player.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include "Framework/StepTimer.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerBody.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerRightHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerTail.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerHead.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
PlayerDash::PlayerDash(Player* player)
	:
	m_player(player),
	m_dashDuration(0.2f)
{
	m_commonResources = CommonResources::GetInstance();
	m_dashSpeed = 1.5f;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerDash::~PlayerDash()
{

}

/// <summary>
/// このステートに入るとき
/// </summary>
void PlayerDash::OnEnter()
{
	// ダッシュを開始した時間を記録
	m_dashStartTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
	// 初期化
	m_differenceTime = 0;
}

/// <summary>
/// このステートを出るとき
/// </summary>
void PlayerDash::OnExit()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerDash::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
void PlayerDash::Update()
{
	double currentTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
	
	m_differenceTime = m_dashStartTime - currentTime;

	if (currentTime - m_dashStartTime >= m_dashDuration)
	{
		// プレイヤーをスタンディング状態に変更
		m_player->ChangeState(m_player->GetStanding()); 
	}
	else
	{
		MoveChild();
		MovePlayer();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerDash::Render()
{

}

/// <summary>
/// 後処理
/// </summary>
void PlayerDash::Finalize()
{

}

/// <summary>
/// ダッシュする動き
/// </summary>
void PlayerDash::MoveChild()
{
	MoveHand();
	MoveBody();
	MoveHead();
}

void PlayerDash::MoveHand()
{
	auto rightHand = m_player->GetBody()->GetRightHand();
	auto leftHand = m_player->GetBody()->GetLeftHand();

	// 回転の設定
	static float rotationAngle = 0.0f;
	rotationAngle += 0.1f;

	DirectX::SimpleMath::Quaternion TakePointRightQuaternion =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle + 1), -1.0f * cos(rotationAngle), 1.0f);

	DirectX::SimpleMath::Quaternion TakePointLeftQuaternion =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle + 1), 1.0f * cos(rotationAngle), -1.0f);

	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.1f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.1f);

	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

void PlayerDash::MoveBody()
{
	auto body = m_player->GetBody();
	// 回転の設定
	static float rotationAngle = 0.0f;
	rotationAngle += 0.1f;

	DirectX::SimpleMath::Quaternion PointBodyQuaternion =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 0.0f, 0.0f);

	DirectX::SimpleMath::Quaternion slerpRotationBody =
		DirectX::SimpleMath::Quaternion::Slerp(body->GetQuaternion(), PointBodyQuaternion, 0.1f);

	body->SetAddQuaternion(slerpRotationBody);
}

void PlayerDash::MoveHead()
{
	auto head = m_player->GetBody()->GetHead();
	// 回転の設定
	static float rotationAngle = 0.0f;
	rotationAngle += 0.1f;

	DirectX::SimpleMath::Quaternion PointBodyQuaternion =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.3f * sin(rotationAngle), 0.0f, 0.0f);

	DirectX::SimpleMath::Quaternion slerpRotationBody =
		DirectX::SimpleMath::Quaternion::Slerp(head->GetAddQuaternion(), PointBodyQuaternion, 0.1f);

	head->SetAddQuaternion(slerpRotationBody);
}

void PlayerDash::MoveTail()
{

}

void PlayerDash::MovePlayer()
{
	DirectX::SimpleMath::Vector3 direction = m_player->GetVelocity() * 0.15f;

	direction.y = 0.0f;			// y軸成分をゼロに

	direction.Normalize();		// 移動量の正規化

	// ジャンプの高さを加味
	float jumpHeight = 1.0f;	// ジャンプの高さを設定（適宜調整）
	float jumpDuration = 0.5f;  // ジャンプの持続時間（適宜調整）

	// 時間経過に基づくジャンプの高さの補間
	double elapsedTime = m_commonResources->GetStepTimer()->GetTotalSeconds() - m_dashStartTime;
	float normalizedTime = static_cast<float>(elapsedTime / jumpDuration);

	if (normalizedTime > 0.5f)
	{
		normalizedTime = 0.5f;  // 持続時間を過ぎたら1に固定
	}

	// ジャンプの高さを計算（放物線運動）
	float heightOffset = jumpHeight * (1 - 4 * (normalizedTime) * (normalizedTime));

	// ジャンプと移動方向を合成
	DirectX::SimpleMath::Vector3 velocity = direction * m_dashSpeed;
	velocity.y = heightOffset;

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		//ポジションの変更
	m_player->SetVelocity(velocity);				//速度の変更

	SlerpRotate(direction);		//プレイヤーの移動と角度から補完をする
}

void PlayerDash::SlerpRotate(DirectX::SimpleMath::Vector3 direction)
{
	if (direction.LengthSquared() < 1e-2f) { return; }			// 移動量がほとんどないなら計算しない( 1の10-2乗以下 )

	DirectX::SimpleMath::Quaternion targetRotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// 移動方向ベクトルから目標のクォータニオンを計算

	DirectX::SimpleMath::Quaternion slerpRotation =
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// 線形補完する

	slerpRotation.Normalize();				//ノーマライズする

	m_player->SetAngle(slerpRotation);			// 現在の角度をプレイヤーのクォータニオンにいれる
}