//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/26
// <file>			PlayerSecondAttack.h
// <概要>		　　二回目の攻撃
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerFirstAttack.h"
#include"Game/PlayScene/Player/Player.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Framework/StepTimer.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerBody.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerRightHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerTail.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerHead.h"
#include"Framework/StepTimer.h"

PlayerFirstAttack::PlayerFirstAttack(Player* player)
	:
	m_player(player),
	m_deriveTime(1.0f),
	m_elapsedTime(0.0f),
	m_hasRotateFlag(false),
	m_rotateAngle(0.0f)
{
	m_commonResources = CommonResources::GetInstance();
}

PlayerFirstAttack::~PlayerFirstAttack()
{

}

void PlayerFirstAttack::OnEnter()
{
	m_elapsedTime = 0.0f;
	m_hasRotateFlag = false;
	m_rotateAngle = 0.0f;
}

void PlayerFirstAttack::OnExit()
{

}

void PlayerFirstAttack::Initialize()
{

}

void PlayerFirstAttack::Update()
{
	m_elapsedTime += m_commonResources->GetStepTimer()->GetElapsedSeconds();
	MoveChild();
	MovePlayer();
	ChangeState();
}

void PlayerFirstAttack::Render()
{

}

void PlayerFirstAttack::Finalize()
{

}

void PlayerFirstAttack::MoveChild()
{
	MoveHand();
	MoveBody();
	MoveHead();
}

void PlayerFirstAttack::MoveHand()
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

void PlayerFirstAttack::MoveBody()
{

}

void PlayerFirstAttack::MoveHead()
{

}

void PlayerFirstAttack::MovePlayer()
{
	if (m_hasRotateFlag) {
		// 一回転した場合、動きを止める
		return;
	}

	const float rotationSpeed = -0.3f; // 回転速度
	m_rotateAngle += rotationSpeed;

	// プレイヤーの前進する速度
	DirectX::SimpleMath::Vector3 velocity = { 0.0f, 0.0f, 0.0f }; // Z方向に前進する速度

	// プレイヤーの現在のクォータニオンを回転行列に変換
	DirectX::SimpleMath::Matrix rotationMatrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_player->GetQuaternion());

	// 前方向ベクトルを取得
	DirectX::SimpleMath::Vector3 forwardDirection = rotationMatrix.Forward();

	// 速度を前方向に適用
	DirectX::SimpleMath::Vector3 newPosition = m_player->GetPosition() + forwardDirection * velocity;

	// 回転を計算
	DirectX::SimpleMath::Quaternion currentRotation = m_player->GetQuaternion();
	DirectX::SimpleMath::Quaternion rotationIncrement = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(rotationSpeed, 0.0f, 0.0f);
	DirectX::SimpleMath::Quaternion newRotation = currentRotation * rotationIncrement;

	// 新しい位置と回転をプレイヤーに設定
	m_player->SetPosition(newPosition);
	m_player->SetAngle(newRotation);

	// 回転角度が360度を超えたら動きを止める
	if (m_rotateAngle <= -DirectX::XM_2PI) {
		m_hasRotateFlag = true;
	}
}

void PlayerFirstAttack::ChangeState()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();
	auto mouseStateTracker = m_commonResources->GetInputManager()->GetMouseState();

	if (m_hasRotateFlag) 
	{
		if (m_elapsedTime <= m_deriveTime) 
		{
			// m_deriveTime以内にもう一度左クリックされた場合、secondAttackに遷移
			if (mouseStateTracker.leftButton) {
				m_player->ChangeState(m_player->GetSecondAttack());
			}
		}
		 if(m_elapsedTime > m_deriveTime)
		{
			// m_deriveTimeを過ぎた場合、Standing状態に遷移
			m_player->ChangeState(m_player->GetStanding());
		}
		 if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D) ||
			 keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A) ||
			 keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W) ||
			 keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S)) {
			 // キーの開放で、Standingに遷移
			 m_player->ChangeState(m_player->GetStanding());
		 }	
	}

	
}