#include"pch.h"
#include"CharacterCollision.h"
#include"Game/PlayScene/Enemy/CrowBoss/Crow.h"
#include"Game/PlayScene/Player/Player.h"
#include"Game/PlayScene/Stage/GenerateStage.h"
#include"Game/PlayScene/Stage/StageCase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterCollision::CharacterCollision()
	:
	m_isEnemyHit{},
	m_isWallHit{},
	m_stageCaseNumber{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterCollision::~CharacterCollision()
{

}

/// <summary>
/// �v���C���[�ƃG�l�~�[�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="enemy">�G�l�~�[</param>
void CharacterCollision::DetectCollisionPlayerToEnemy(Player* player, Crow* crowBoss)
{
	// �v���C���[���G�l�~�[�̃o�E���f�B���O�{�b�N�X������
	m_isEnemyHit = player->GetBoundingSphere().Intersects(crowBoss->GetBoundingSphere());

	// �������Ă��Ȃ��Ȃ�A�[���[���^�[��
	if (!m_isEnemyHit) { return; }

	// �Փˎ��A�����߂�����
	// �v���C���[�ƃG�l�~�[�̒��S���i�[
	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
	DirectX::SimpleMath::Vector3 enemyCenter = crowBoss->GetBoundingSphere().Center;
	// ���S�Ƃ̍����x�N�g��
	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter - enemyCenter);

	// ���S�Ƃ̋���
	float diffLength = diffVec.Length();
	// ���a�̍��v
	float sumRadius = player->GetBoundingSphere().Radius + crowBoss->GetBoundingSphere().Radius;
	// �߂荞�݋���
	diffLength = sumRadius - diffLength;

	// ���K��
	diffVec.Normalize();
	// �����߂��x�N�g��
	diffVec *= diffLength;

	// �R���C�_�[���W�̍X�V������
	// �v���C���[�̃|�W�V�����������߂�
	player->SetPosition(player->GetPosition() + diffVec);
	player->SetBoundingSphereCenter(player->GetBoundingSphere().Center + diffVec);
	// �G�l�~�[�̃|�W�V�����������߂�
	crowBoss->SetPosition(crowBoss->GetPosition() - diffVec);
	crowBoss->SetBoundingSphereCenter(crowBoss->GetBoundingSphere().Center - diffVec);
	
	return;
}

/// <summary>
/// �v���C���[�ƕǂ̓����蔻��
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="stage">�X�e�[�W</param>
void CharacterCollision::DetectCollisionPlayerToWall(Player* player, GenerateStage* stage)
{
    const float MIN_PUSHBACK_DISTANCE = 0.01f; // �ŏ������߂��������`

    for (int i = 0; i < 4; i++)
    {
        const auto& wall = stage->GetStageCase(i);
        if (player->GetBoundingSphere().Intersects(wall->GetBoundingBox()))
        {
            // �v���C���[�̒��S�ƕǂ̒��S���擾
            DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
            DirectX::SimpleMath::Vector3 wallCenter = wall->GetBoundingBox().Center;
            DirectX::SimpleMath::Vector3 wallExtents = wall->GetBoundingBox().Extents;

            // �ǂ̊e�ʂƂ̋������v�Z
            float distances[6] = {
                (wallCenter.x - wallExtents.x) - playerCenter.x, // left
                playerCenter.x - (wallCenter.x + wallExtents.x), // right
                (wallCenter.y - wallExtents.y) - playerCenter.y, // bottom
                playerCenter.y - (wallCenter.y + wallExtents.y), // top
                (wallCenter.z - wallExtents.z) - playerCenter.z, // back
                playerCenter.z - (wallCenter.z + wallExtents.z)  // front
            };

            // �ł��Փ˂̐[���ʂ�������
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

            // �����߂��x�N�g�����v�Z
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

            // �����߂��x�N�g�����ŏ����������Ȃ�A�[���[���^�[��
            if (pushBackVector.Length() < MIN_PUSHBACK_DISTANCE) { return; }

            // �v���C���[�̃|�W�V�����������߂�
            player->SetPosition(player->GetPosition() + pushBackVector);
            player->SetBoundingSphereCenter(player->GetBoundingSphere().Center + pushBackVector);

            m_isWallHit = true;
            return;
        }
    }

    m_isWallHit = false;
}