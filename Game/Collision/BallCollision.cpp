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

// �ǂƂ̏Փ˔��������
void BallCollision::DetectCollisionBallToWall(Ball* ball, GenerateStage* stage)
{
    // �X�e�[�W�P�[�X�̐����擾
    int stageCaseMax = stage->GetStageCaseMax();

    // ���݂̃{�[���̈ʒu�Ɣ��a���擾
    DirectX::SimpleMath::Vector3 ballPos = ball->GetPosition();
    float ballRadius = ball->GetBoundingSphere().Radius;

    // �{�[���̑O�t���[���̈ʒu���v�Z
    DirectX::SimpleMath::Vector3 previousPos = ballPos - ball->GetVelocity();

    for (int i = 0; i < stageCaseMax; i++)
    {
        auto stageCase = stage->GetStageCase(i);
        DirectX::BoundingBox boundingBox = stageCase->GetBoundingBox();
        DirectX::SimpleMath::Vector3 boxMin = boundingBox.Center - DirectX::SimpleMath::Vector3(boundingBox.Extents);
        DirectX::SimpleMath::Vector3 boxMax = boundingBox.Center + DirectX::SimpleMath::Vector3(boundingBox.Extents);

        // �{�[�����߂荞��ł��Ȃ����`�F�b�N
        if (ballPos.x - ballRadius < boxMax.x && ballPos.x + ballRadius > boxMin.x &&
            ballPos.y - ballRadius < boxMax.y && ballPos.y + ballRadius > boxMin.y &&
            ballPos.z - ballRadius < boxMax.z && ballPos.z + ballRadius > boxMin.z)
        {
            m_isHit = true;
            m_stageCaseNumber = i;

            DirectX::SimpleMath::Vector3 ballVelocity = ball->GetVelocity();

            // x�������̏Փ˔���Ɣ��]
            // ��������E���ɐi��
            if (previousPos.x + ballRadius <= boxMin.x && ballPos.x + ballRadius > boxMin.x) 
            {
                ballVelocity.x = -ballVelocity.x;
                ballPos.x = boxMin.x - ballRadius;
            }
            // �E�����獶���ɐi��
            else if (previousPos.x - ballRadius >= boxMax.x && ballPos.x - ballRadius < boxMax.x) 
            {
                ballVelocity.x = -ballVelocity.x;
                ballPos.x = boxMax.x + ballRadius;
            }

            // y�������̏Փ˔���Ɣ��]
            // ��������㑤�ɐi��
            if (previousPos.y + ballRadius <= boxMin.y && ballPos.y + ballRadius > boxMin.y) 
            {
                ballVelocity.y = -ballVelocity.y;
                ballPos.y = boxMin.y - ballRadius;
            }
            // �㑤���牺���ɐi��
            else if (previousPos.y - ballRadius >= boxMax.y && ballPos.y - ballRadius < boxMax.y) 
            {
                ballVelocity.y = -ballVelocity.y;
                ballPos.y = boxMax.y + ballRadius;
            }

            // z�������̏Փ˔���Ɣ��]
            // �O������㑤�ɐi��
            if (previousPos.z + ballRadius <= boxMin.z && ballPos.z + ballRadius > boxMin.z) 
            {
                ballVelocity.z = -ballVelocity.z;
                ballPos.z = boxMin.z - ballRadius;
            }
            // �㑤����O���ɐi��
            else if (previousPos.z - ballRadius >= boxMax.z && ballPos.z - ballRadius < boxMax.z) 
            {
                ballVelocity.z = -ballVelocity.z;
                ballPos.z = boxMax.z + ballRadius;
            }

            // �ʒu�Ƒ��x���X�V
            ball->SetPosition(ballPos);
            ball->SetVelocity(ballVelocity);
            break;
        }
    }
}