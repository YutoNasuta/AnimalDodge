#include"pch.h"
#include"BallCollision.h"
#include"Game/Ball/Ball.h"
#include"Game/Stage/GenerateStage.h"
#include"Game/Stage/StageCase.h"

BallCollision::BallCollision()
	:
	m_isHit{},
	m_stageCaseNumber{}
{

}

BallCollision::~BallCollision()
{

}

// 壁との衝突判定をする
void BallCollision::DetectCollisionBallToWall(Ball* ball, GenerateStage* stage)
{
    // ステージケースの数を取得
    int stageCaseMax = stage->GetStageCaseMax();

    // 現在のボールの位置と半径を取得
    DirectX::SimpleMath::Vector3 ballPos = ball->GetPosition();
    float ballRadius = ball->GetBoundingSphere().Radius;

    // ボールの前フレームの位置を計算
    DirectX::SimpleMath::Vector3 previousPos = ballPos - ball->GetVelocity();

    for (int i = 0; i < stageCaseMax; i++)
    {
        auto stageCase = stage->GetStageCase(i);
        DirectX::BoundingBox boundingBox = stageCase->GetBoundingBox();
        DirectX::SimpleMath::Vector3 boxMin = boundingBox.Center - DirectX::SimpleMath::Vector3(boundingBox.Extents);
        DirectX::SimpleMath::Vector3 boxMax = boundingBox.Center + DirectX::SimpleMath::Vector3(boundingBox.Extents);

        // ボールがめり込んでいないかチェック
        if (ballPos.x - ballRadius < boxMax.x && ballPos.x + ballRadius > boxMin.x &&
            ballPos.y - ballRadius < boxMax.y && ballPos.y + ballRadius > boxMin.y &&
            ballPos.z - ballRadius < boxMax.z && ballPos.z + ballRadius > boxMin.z)
        {
            m_isHit = true;
            m_stageCaseNumber = i;

            DirectX::SimpleMath::Vector3 ballVelocity = ball->GetVelocity();

            // x軸方向の衝突判定と反転
            // 左側から右側に進入
            if (previousPos.x + ballRadius <= boxMin.x && ballPos.x + ballRadius > boxMin.x) 
            {
                ballVelocity.x = -ballVelocity.x;
                ballPos.x = boxMin.x - ballRadius;
            }
            // 右側から左側に進入
            else if (previousPos.x - ballRadius >= boxMax.x && ballPos.x - ballRadius < boxMax.x) 
            {
                ballVelocity.x = -ballVelocity.x;
                ballPos.x = boxMax.x + ballRadius;
            }

            // y軸方向の衝突判定と反転
            // 下側から上側に進入
            if (previousPos.y + ballRadius <= boxMin.y && ballPos.y + ballRadius > boxMin.y) 
            {
                ballVelocity.y = -ballVelocity.y;
                ballPos.y = boxMin.y - ballRadius;
            }
            // 上側から下側に進入
            else if (previousPos.y - ballRadius >= boxMax.y && ballPos.y - ballRadius < boxMax.y) 
            {
                ballVelocity.y = -ballVelocity.y;
                ballPos.y = boxMax.y + ballRadius;
            }

            // z軸方向の衝突判定と反転
            // 前側から後側に進入
            if (previousPos.z + ballRadius <= boxMin.z && ballPos.z + ballRadius > boxMin.z) 
            {
                ballVelocity.z = -ballVelocity.z;
                ballPos.z = boxMin.z - ballRadius;
            }
            // 後側から前側に進入
            else if (previousPos.z - ballRadius >= boxMax.z && ballPos.z - ballRadius < boxMax.z) 
            {
                ballVelocity.z = -ballVelocity.z;
                ballPos.z = boxMax.z + ballRadius;
            }

            // 位置と速度を更新
            ball->SetPosition(ballPos);
            ball->SetVelocity(ballVelocity);
            break;
        }
    }
}