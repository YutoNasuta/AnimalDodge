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

/// <summary>
/// プレイヤーと壁の当たり判定
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="stage">ステージ</param>
void CharacterCollision::DetectCollisionPlayerToWall(Player* player, GenerateStage* stage)
{
    const float MIN_PUSHBACK_DISTANCE = 0.01f; // 最小押し戻し距離を定義

    for (int i = 0; i < 4; i++)
    {
        const auto& wall = stage->GetStageCase(i);
        if (player->GetBoundingSphere().Intersects(wall->GetBoundingBox()))
        {
            // プレイヤーの中心と壁の中心を取得
            DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
            DirectX::SimpleMath::Vector3 wallCenter = wall->GetBoundingBox().Center;
            DirectX::SimpleMath::Vector3 wallExtents = wall->GetBoundingBox().Extents;

            // 壁の各面との距離を計算
            float distances[6] = {
                (wallCenter.x - wallExtents.x) - playerCenter.x, // left
                playerCenter.x - (wallCenter.x + wallExtents.x), // right
                (wallCenter.y - wallExtents.y) - playerCenter.y, // bottom
                playerCenter.y - (wallCenter.y + wallExtents.y), // top
                (wallCenter.z - wallExtents.z) - playerCenter.z, // back
                playerCenter.z - (wallCenter.z + wallExtents.z)  // front
            };

            // 最も衝突の深い面を見つける
            float penetrationDepth = player->GetBoundingSphere().Radius;
            int minIndex = -1;
            float minDistance = penetrationDepth;

            for (int j = 0; j < 6; j++)
            {
                if (std::abs(distances[j]) < minDistance)
                {
                    minDistance = std::abs(distances[j]);
                    minIndex = j;
                }
            }

            // 押し戻しベクトルを計算
            DirectX::SimpleMath::Vector3 pushBackVector;

            switch (minIndex)
            {
            case 0: // left
                pushBackVector = DirectX::SimpleMath::Vector3(-minDistance, 0.0f, 0.0f);
                break;
            case 1: // right
                pushBackVector = DirectX::SimpleMath::Vector3(minDistance, 0.0f, 0.0f);
                break;
            case 2: // bottom
                pushBackVector = DirectX::SimpleMath::Vector3(0.0f, -minDistance, 0.0f);
                break;
            case 3: // top
                pushBackVector = DirectX::SimpleMath::Vector3(0.0f, minDistance, 0.0f);
                break;
            case 4: // back
                pushBackVector = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -minDistance);
                break;
            case 5: // front
                pushBackVector = DirectX::SimpleMath::Vector3(0.0f, 0.0f, minDistance);
                break;
            default:
                break;
            }

            // 押し戻しベクトルが最小距離未満ならアーリーリターン
            if (pushBackVector.Length() < MIN_PUSHBACK_DISTANCE) { return; }

            // プレイヤーのポジションを押し戻す
            player->SetPosition(player->GetPosition() + pushBackVector);
            player->SetBoundingSphereCenter(player->GetBoundingSphere().Center + pushBackVector);

            m_isWallHit = true;
            return;
        }
    }

    m_isWallHit = false;
}