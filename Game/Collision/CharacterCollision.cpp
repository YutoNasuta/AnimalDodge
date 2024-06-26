#include"pch.h"
#include"CharacterCollision.h"
#include"Game/Enemy/Enemy.h"
#include"Game/Player/Player.h"
#include"Game/Stage/GenerateStage.h"
#include"Game/Stage/StageCase.h"

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
void CharacterCollision::DetectCollisionPlayerToEnemy(Player* player, Enemy* enemy)
{
	// �v���C���[���G�l�~�[�̃o�E���f�B���O�{�b�N�X������
	m_isEnemyHit = player->GetBoundingSphere().Intersects(enemy->GetBoundingSphere());

	// �������Ă��Ȃ��Ȃ�A�[���[���^�[��
	if (!m_isEnemyHit) { return; }

	// �Փˎ��A�����߂�����
	// �v���C���[�ƃG�l�~�[�̒��S���i�[
	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
	DirectX::SimpleMath::Vector3 enemyCenter = enemy->GetBoundingSphere().Center;
	// ���S�Ƃ̍����x�N�g��
	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter - enemyCenter);

	// ���S�Ƃ̋���
	float diffLength = diffVec.Length();
	// ���a�̍��v
	float sumRadius = player->GetBoundingSphere().Radius + enemy->GetBoundingSphere().Radius;
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
	enemy->SetPosition(enemy->GetPosition() - diffVec);
	enemy->SetBoundingSphereCenter(enemy->GetBoundingSphere().Center - diffVec);
	
	return;
}
//
///// <summary>
///// �v���C���[�ƕǂ̓����蔻��
///// </summary>
///// <param name="player">�v���C���[</param>
///// <param name="stage">�X�e�[�W</param>
//void CharacterCollision::DetectCollisionPlayerToWall(Player* player, GenerateStage* stage)
//{
//	// �X�e�[�W�P�[�X�̐����擾
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
//	// �Փˎ��A�����߂�����
//	// �v���C���[�ƃG�l�~�[�̒��S���i�[
//	DirectX::SimpleMath::Vector3 playerCenter = player->GetBoundingSphere().Center;
//	DirectX::SimpleMath::Vector3 wallCenter = stage->GetStageCase(m_stageCaseNumber)->GetBoundingBox().Center;
//	// ���S�Ƃ̍����x�N�g��
//	DirectX::SimpleMath::Vector3 diffVec = DirectX::SimpleMath::Vector3(playerCenter - wallCenter);
//
//	// ���S�Ƃ̋���
//	float diffLength = diffVec.Length();
//	// ���a�̍��v
//	float sumRadius = player->GetBoundingSphere().Radius + stage->GetStageCase(m_stageCaseNumber)->GetBoundingBox();
//	// �߂荞�݋���
//	diffLength = sumRadius - diffLength;
//
//	// ���K��
//	diffVec.Normalize();
//	// �����߂��x�N�g��
//	diffVec *= diffLength;
//}