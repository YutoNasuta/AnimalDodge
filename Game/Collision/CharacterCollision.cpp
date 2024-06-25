#include"pch.h"
#include"CharacterCollision.h"
#include"Game/Enemy/Enemy.h"
#include"Game/Player/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterCollision::CharacterCollision()
	:
	m_isHit{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterCollision::~CharacterCollision()
{

}

/// <summary>
/// �����蔻��
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="enemy">�G�l�~�[</param>
void CharacterCollision::CheckHit(Player* player, Enemy* enemy)
{
	// �v���C���[���G�l�~�[�̃o�E���f�B���O�{�b�N�X������
	m_isHit = player->GetBoundingSphere().Intersects(enemy->GetBoundingSphere());

	// �������Ă��Ȃ��Ȃ�A�[���[���^�[��
	if (!m_isHit) { return ; }

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
