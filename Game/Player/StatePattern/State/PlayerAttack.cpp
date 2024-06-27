//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			PlayerAttack.h
// <概要>		　　プレイヤー攻撃状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include"pch.h"
#include"PlayerAttack.h"
#include"Game/CommonResources.h"
#include"framework/DeviceResources.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"
#include"Game/Player/PlayerPart/PlayerHead.h"
PlayerAttack::PlayerAttack(Player* player)
	:
	m_player(player),
    m_attackDuration(0.2f)
{
	m_commonResources = CommonResources::GetInstance();
    m_attackSpeed = 2.0f;
}

PlayerAttack::~PlayerAttack()
{

}

void PlayerAttack::OnEnter()
{
    // ダッシュを開始した時間を記録
    m_attackStartTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
    // 初期化
    m_differenceTime = 0;
}

void PlayerAttack::OnExit()
{

}

void PlayerAttack::Initialize()
{

}

void PlayerAttack::Update()
{
  
    double currentTime = m_commonResources->GetStepTimer()->GetTotalSeconds();

    m_differenceTime = m_attackStartTime - currentTime;
    if (currentTime - m_attackStartTime >= m_attackDuration)
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

void PlayerAttack::Render()
{

}

void PlayerAttack::Finalize()
{

}


void PlayerAttack::MoveChild()
{
	MoveHand();
    MoveBody();
    MoveHead();
}

/// <summary>
/// 手の動き
/// </summary>
void PlayerAttack::MoveHand()
{
    auto rightHand = m_player->GetBody()->GetRightHand();
    auto leftHand = m_player->GetBody()->GetLeftHand();

    // 回転の設定
    static float rotationAngle = 0.0f;
    rotationAngle += 0.1f;

    DirectX::SimpleMath::Quaternion TakePointRightQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle + 1), -1.0f * cos(rotationAngle ), 1.0f);

    DirectX::SimpleMath::Quaternion TakePointLeftQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle + 1), 1.0f * cos(rotationAngle), -1.0f);

    DirectX::SimpleMath::Quaternion slerpRotationRight =
        DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), TakePointRightQuaternion, 0.1f);
    DirectX::SimpleMath::Quaternion slerpRotationLeft =
        DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), TakePointLeftQuaternion, 0.1f);

    rightHand->SetAddQuaternion(slerpRotationRight);
    leftHand->SetAddQuaternion(slerpRotationLeft);

}

void PlayerAttack::MoveBody()
{
    auto body = m_player->GetBody();
    // 回転の設定
    static float rotationAngle = 0.0f;
    rotationAngle += 0.1f;

    DirectX::SimpleMath::Quaternion PointBodyQuaternion =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(1.0f * sin(rotationAngle), 0.0f , 0.0f );

    DirectX::SimpleMath::Quaternion slerpRotationBody =
        DirectX::SimpleMath::Quaternion::Slerp(body->GetQuaternion(), PointBodyQuaternion , 0.1f);

    body->SetAddQuaternion(slerpRotationBody);

}

void PlayerAttack::MoveHead()
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

void PlayerAttack::MoveTail()
{

}

void PlayerAttack::MovePlayer()
{
    DirectX::SimpleMath::Vector3 direction = m_player->GetVelocity() * 0.15f;		// 停止処理

    direction.y = 0.0f;			// y軸成分をゼロに

    direction.Normalize();		// 移動量の正規化

    // ジャンプの高さを加味
    float jumpHeight = 1.0f;  // ジャンプの高さを設定（適宜調整）
    float jumpDuration = 0.5f;  // ジャンプの持続時間（適宜調整）

    // 時間経過に基づくジャンプの高さの補間
    double elapsedTime = m_commonResources->GetStepTimer()->GetTotalSeconds() - m_attackStartTime;
    float normalizedTime = static_cast<float>(elapsedTime / jumpDuration);

    if (normalizedTime > 0.5f)
    {
        normalizedTime = 0.5f;  // 持続時間を過ぎたら1に固定
    }

    // ジャンプの高さを計算（放物線運動）
    float heightOffset = jumpHeight * (1 - 4 * (normalizedTime) * (normalizedTime ));

    // ジャンプと移動方向を合成
    DirectX::SimpleMath::Vector3 velocity = direction * m_attackSpeed;
    velocity.y = heightOffset;

    



    m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());		//ポジションの変更
    m_player->SetVelocity(velocity );				//速度の変更

    SlerpRotate(direction);		//プレイヤーの移動と角度から補完をする
}

void PlayerAttack::SlerpRotate(DirectX::SimpleMath::Vector3 direction)
{
    if (direction.LengthSquared() < 1e-2f) { return; }			// 移動量がほとんどないなら計算しない( 1の10-2乗以下 )

    DirectX::SimpleMath::Quaternion targetRotation =
        DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(atan2f(direction.x, direction.z), 0.0f, 0.0f);	// 移動方向ベクトルから目標のクォータニオンを計算

    DirectX::SimpleMath::Quaternion slerpRotation =
        DirectX::SimpleMath::Quaternion::Slerp(m_player->GetQuaternion(), targetRotation, 0.2f);			// 線形補完する

    slerpRotation.Normalize();				//ノーマライズする

    m_player->SetAngle(slerpRotation);			// 現在の角度をプレイヤーのクォータニオンにいれる
}