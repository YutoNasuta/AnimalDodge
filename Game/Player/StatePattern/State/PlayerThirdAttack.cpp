//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/26
// <file>			PlayerThirdAttack.h
// <概要>		　　三回目の攻撃
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerThirdAttack.h"
#include"Game/Player/Player.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include "Framework/StepTimer.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"
#include"Game/Player/PlayerPart/PlayerHead.h"
#include"Framework/StepTimer.h"

PlayerThirdAttack::PlayerThirdAttack(Player* player)
	:
	m_player(player),
	m_attackDuration(0.2f)
	
{
	m_commonResources = CommonResources::GetInstance();
	m_backWardSpeed = 1.5f;
}

PlayerThirdAttack::~PlayerThirdAttack()
{

}

void PlayerThirdAttack::OnEnter()
{
	m_attackStartTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
}

void PlayerThirdAttack::OnExit()
{

}

void PlayerThirdAttack::Initialize()
{

}

void PlayerThirdAttack::Update()
{
	double currentTime = m_commonResources->GetStepTimer()->GetTotalSeconds();

	if (currentTime - m_attackStartTime >= m_attackDuration)
	{
		m_player->ChangeState(m_player->GetStanding());
	}
	else
	{
		MoveChild();
		MovePlayer();
	}
}

void PlayerThirdAttack::Render()
{

}

void PlayerThirdAttack::Finalize()
{

}

void PlayerThirdAttack::MoveChild()
{
	MoveHand();
	MoveBody();
	MoveHead();
}

void PlayerThirdAttack::MoveHand()
{
	//auto rightHand = m_player->GetBody()->GetRightHand();
	//auto leftHand = m_player->GetBody()->GetLeftHand();

	//static float rotationAngle = 0.0f;
	//rotationAngle += 0.1f;

	//DirectX::SimpleMath::Quaternion TakePointRightQuaternion =
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 0.0f , 0.0f);

	//DirectX::SimpleMath::Quaternion TakePointLeftQuaternion =
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 1.0f * sin(rotationAngle),0.0f );

	//DirectX::SimpleMath::Quaternion slerpRotationRight =
	//	DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.1f);
	//DirectX::SimpleMath::Quaternion slerpRotationLeft =
	//	DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.1f);

	//rightHand->SetAddQuaternion(slerpRotationRight);
	//leftHand->SetAddQuaternion(slerpRotationLeft);
}

void PlayerThirdAttack::MoveBody()
{

}

void PlayerThirdAttack::MoveHead()
{

}

void PlayerThirdAttack::MovePlayer()
{
	//// プレイヤーの速度ベクトルを取得し、方向を反転させる
	//DirectX::SimpleMath::Vector3 direction = -m_player->GetVelocity();

	//direction.y = 0.0f;            // y軸成分をゼロに
	//direction.Normalize();        // 移動量の正規化

	//// ジャンプの高さを加味
	//float jumpHeight = 2.0f;    // ジャンプの高さを設定（適宜調整）
	//float jumpDuration = 1.0f;  // ジャンプの持続時間（適宜調整）

	//// 時間経過に基づくジャンプの高さの補間
	//double elapsedTime = m_commonResources->GetStepTimer()->GetTotalSeconds() - m_attackStartTime;
	//float normalizedTime = static_cast<float>(elapsedTime / jumpDuration);

	//if (normalizedTime > 1.0f)
	//{
	//	normalizedTime = 1.0f;  // 持続時間を過ぎたら1に固定
	//}

	//// ジャンプの高さを計算（放物線運動）
	//float heightOffset = jumpHeight * (1 - 4 * (normalizedTime - 0.5f) * (normalizedTime - 0.5f));

	//// ジャンプと移動方向を合成
	//DirectX::SimpleMath::Vector3 velocity = direction * m_backWardSpeed;
	//velocity.y = heightOffset;

	//m_player->SetVelocity(velocity);  // 速度の変更
	//m_player->SetPosition(m_player->GetPosition() + velocity * m_commonResources->GetStepTimer()->GetElapsedSeconds());  // ポジションの変更

	//SlerpRotate(direction);  // プレイヤーの移動と角度から補完をする
}

void PlayerThirdAttack::ChangeState()
{
	//auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	//auto mouseStateTracker = m_commonResources->GetInputManager()->GetMouseState();
	//	
	//		// deriveTimeを過ぎた場合、Standing状態に遷移
	//	m_player->ChangeState(m_player->GetStanding());
	//	
	//	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D) ||
	//		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A) ||
	//		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W) ||
	//		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S)) {
	//		// キーの開放で、Standingに遷移
	//		m_player->ChangeState(m_player->GetStanding());
	//	}
}


void PlayerThirdAttack::SlerpRotate(DirectX::SimpleMath::Vector3 direction)
{
	if (direction.LengthSquared() < 1e-2f) { return; }	// 移動量がほとんどないなら計算しない

	DirectX::SimpleMath::Quaternion targetRotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// 移動方向ベクトルから目標のクォータニオンを計算

	DirectX::SimpleMath::Quaternion slerpRotation =
		DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);	// 線形補完する

	slerpRotation.Normalize();	// ノーマライズする

	m_player->SetAngle(slerpRotation);	// 現在の角度をプレイヤーのクォータニオンにいれる
}
