#include"pch.h"
#include"CharacterCollision.h"
#include"Game/Enemy/Enemy.h"
#include"Game/Player/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
CharacterCollision::CharacterCollision()
	:
	m_isHit{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
CharacterCollision::~CharacterCollision()
{

}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="enemy">エネミー</param>
void CharacterCollision::CheckHit(Player* player, Enemy* enemy)
{
	// プレイヤーをエネミーのバウンディングボックスを見る
	m_isHit = player->GetBoundingSphere().Intersects(enemy->GetBoundingSphere());

	// 当たっていないならアーリーリターン
	if (!m_isHit) { return ; }

	// 衝突時、押し戻す処理
	// プレイヤーとエネミーの中心を格納
	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
	DirectX::SimpleMath::Vector3 enemyCenter = enemy->GetBoundingSphere().Center;
	// 中心との差分ベクトル
	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter - enemyCenter);

	// 中心との距離
	float diffLength = diffVec.Length();
	// 半径の合計
	float sumRadius = player->GetBoundingSphere().Radius + enemy->GetBoundingSphere().Radius;
	// めり込み距離
	diffLength = sumRadius - diffLength;

	// 正規化
	diffVec.Normalize();
	// 押し戻しベクトル
	diffVec *= diffLength;

	// コライダー座標の更新をする
	// プレイヤーのポジションを押し戻す
	player->SetPosition(player->GetPosition() + diffVec);
	player->SetBoundingSphereCenter(player->GetBoundingSphere().Center + diffVec);
	// エネミーのポジションを押し戻す
	enemy->SetPosition(enemy->GetPosition() - diffVec);
	enemy->SetBoundingSphereCenter(enemy->GetBoundingSphere().Center - diffVec);
	
	return;
}
