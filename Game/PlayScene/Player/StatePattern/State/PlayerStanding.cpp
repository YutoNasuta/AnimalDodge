//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerStanding.cpp
// <概要>		　　プレイヤーの動いていないステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerStanding.h"
#include"Game/PlayScene/Player/Player.h"
#include"framework/DeviceResources.h"
#include"Game/CommonResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerBody.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerRightHand.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerTail.h"
#include"Game/PlayScene/Player/PlayerPart/PlayerHead.h"
#include"Framework/StepTimer.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="resource">共通リソース</param>
PlayerStanding::PlayerStanding(
	Player* player
)
:
	m_player(player)
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerStanding::~PlayerStanding()
{
}

/// <summary>
/// このステートに入った時
/// </summary>
void PlayerStanding::OnEnter()
{
	m_player->SetAngle(m_player->GetQuaternion());	//クォータニオンを合わせる
}

/// <summary>
/// このステートを抜けたとき
/// </summary>
void PlayerStanding::OnExit()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerStanding::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerStanding::Update()
{
	auto keyboardStateTracker = m_commonResources->GetInputManager()->GetKeyboardState();

	m_player->SetVelocity(m_player->GetVelocity() * m_player->GetFriction());				// 速度に摩擦をつける
	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());	// 位置の更新

	MoveChild();
	ChangeStateKey(keyboardStateTracker);																		//ステート変更
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerStanding::Render()
{
}

/// <summary>
/// ステート変更処理
/// </summary>
/// <param name="keyboardStateTracker">キーボード</param>
void PlayerStanding::ChangeStateKey(
	const DirectX::Keyboard::State& keyboardStateTracker
)
{
	
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::D) || keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::A) ||
		keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::W) || keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Keys::S))			// WASDのどれかを押したとき
	{
		m_player->ChangeState(m_player->GetRunning());			// プレイヤの状態を「ランニング」状態に遷移する
	}
	const auto& mouseState = m_commonResources->GetInputManager()->GetMouseState();		// マウスの状態取得
	
	if (mouseState.leftButton == 1)				// 左ボタンが押された　かつ　ボールを持っている
	{
		m_player->ChangeState(m_player->GetFirstAttack());			// 投げ状態に変更
	}
	if (keyboardStateTracker.IsKeyDown(DirectX::Keyboard::Space))	 //スペースキーを押したとき
	{
		m_player->ChangeState(m_player->GetJumping());			// ジャンプ状態に遷移する
	}
}

/// <summary>
/// 後処理
/// </summary>
void PlayerStanding::Finalize()
{
}

void PlayerStanding::MoveChild()
{
	MoveHand();
	MoveTail();
	MoveBody();
	MoveHead();
}

/// <summary>
/// 手の動き
/// </summary>
void PlayerStanding::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_player->GetBody()->GetRightHand();
	auto leftHand = m_player->GetBody()->GetLeftHand();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;
	// 右手の振りモーションのパラメーター
	float swingSpeed = 1.0f;
	float swingAmount = 0.1f;

	// 振りモーションを追加
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;


	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);// 線形補完する

	rightHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	leftHand->SetAddQuaternion(slerpRotationLeft);
}

/// <summary>
/// しっぽの動き
/// </summary>
void PlayerStanding::MoveTail()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto tail = m_player->GetBody()->GetTail();
	// 振りモーションのパラメーター
	float swingSpeed = 1.0f;
	float swingAmount = 0.6f;

	// 振りモーションを追加
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;
	auto swingQuaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, swing);


	tail->SetAddQuaternion(swingQuaternion);
}

void PlayerStanding::MoveBody()
{
	auto body = m_player->GetBody();
	DirectX::SimpleMath::Quaternion InitialPoint = body->GetInitialQuaternion();

	DirectX::SimpleMath::Quaternion SlerpRotationBody =
		DirectX::SimpleMath::Quaternion::Slerp(body->GetAddQUaternion(), InitialPoint, 0.2f);

	body->SetAddQuaternion(SlerpRotationBody);

}

void PlayerStanding::MoveHead()
{
	auto head = m_player->GetBody()->GetHead();
	DirectX::SimpleMath::Quaternion InitialPoint = head->GetInitialQuaternion();

	DirectX::SimpleMath::Quaternion SlerpRotationHead =
		DirectX::SimpleMath::Quaternion::Slerp(head->GetAddQuaternion(), InitialPoint, 0.2f);

	head->SetAddQuaternion(SlerpRotationHead);
}