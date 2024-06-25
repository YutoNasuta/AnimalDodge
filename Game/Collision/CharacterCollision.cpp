#include"pch.h"
#include"CharacterCollision.h"
#include"Game/Enemy/Enemy.h"
#include"Game/Player/Player.h"

bool CharacterCollision::CheckHit(Player* player, Enemy* enemy)
{
	// プレイヤーをエネミーのバウンディングボックスを見る
	m_isHit = player->GetBoundingSphere().Intersects(enemy->GetBoundingSphere());

	// ヒットしていなければfalse
	if (!m_isHit) { return false; }

	// 衝突時、押し戻す処理
	// 中心との差分ベクトル
	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
	DirectX::SimpleMath::Vector3 enemyCenter = enemy->GetBoundingSphere().Center;
	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter.x - enemyCenter.x,playerCenter.y - enemyCenter.y,playerCenter.z - enemyCenter.z);

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
	player->SetPosition(player->GetPosition() + diffVec);
	player->SetBoundingSphereCenter(player->GetBoundingSphere().Center + diffVec);
	enemy->SetPosition(enemy->GetPosition() - diffVec);
	enemy->SetBoundingSphereCenter(enemy->GetBoundingSphere().Center - diffVec);
	
	return true;
}
