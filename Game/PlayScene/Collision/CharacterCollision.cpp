#include"pch.h"
#include"CharacterCollision.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Game/PlayScene/Player/Player.h"
#include"Game/PlayScene/Stage/GenerateStage.h"
#include"Game/PlayScene/Stage/StageCase.h"

/// <summary>
/// コンストラクタ
/// </summary>
CharacterCollision::CharacterCollision()
	:
	m_isEnemyHit{},
	m_isWallHit{},
	m_stageCaseNumber{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
CharacterCollision::~CharacterCollision()
{

}

/// <summary>
/// プレイヤーとエネミーの当たり判定
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="enemy">エネミー</param>
void CharacterCollision::DetectCollisionPlayerToEnemy(Player* player, Crow* crowBoss)
{
	// プレイヤーをエネミーのバウンディングボックスを見る
	m_isEnemyHit = player->GetBoundingSphere().Intersects(crowBoss->GetBoundingSphere());

	// 当たっていないならアーリーリターン
	if (!m_isEnemyHit) { return; }

	// 衝突時、押し戻す処理
	// プレイヤーとエネミーの中心を格納
	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
	DirectX::SimpleMath::Vector3 enemyCenter = crowBoss->GetBoundingSphere().Center;
	// 中心との差分ベクトル
	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter - enemyCenter);

	// 中心との距離
	float diffLength = diffVec.Length();
	// 半径の合計
	float sumRadius = player->GetBoundingSphere().Radius + crowBoss->GetBoundingSphere().Radius;
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
	crowBoss->SetPosition(crowBoss->GetPosition() - diffVec);
	crowBoss->SetBoundingSphereCenter(crowBoss->GetBoundingSphere().Center - diffVec);
	
	return;
}
//
///// <summary>
///// プレイヤーと壁の当たり判定
///// </summary>
///// <param name="player">プレイヤー</param>
///// <param name="stage">ステージ</param>
//void CharacterCollision::DetectCollisionPlayerToWall(Player* player, GenerateStage* stage)
//{
//	// ステージケースの数を取得
//	int stageCaseMax = stage->GetStageCaseMax();
//
//	for (int i = 0; i < stageCaseMax; i++)
//	{
//		m_isWallHit = player->GetBoundingSphere().Intersects(stage->GetStageCase(i)->GetBoundingBox());
//		if (m_isWallHit) { m_stageCaseNumber = i; break; }
//	}
//
//	if (!m_isWallHit) { return; }
//
//	// 衝突時、押し戻す処理
//	// プレイヤーとエネミーの中心を格納
//	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
//	DirectX::SimpleMath::Vector3 wallCenter = stage->GetStageCase(m_stageCaseNumber)->GetBoundingBox().Center;
//	// 中心との差分ベクトル
//	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter - wallCenter);
//
//	// 中心との距離
//	float diffLength = diffVec.Length();
//	// 半径の合計
//	float sumRadius = player->GetBoundingSphere().Radius + stage->GetStageCase(m_stageCaseNumber)->GetBoundingBox();
//	// めり込み距離
//	diffLength = sumRadius - diffLength;
//
//	// 正規化
//	diffVec.Normalize();
//	// 押し戻しベクトル
//	diffVec *= diffLength;
//}