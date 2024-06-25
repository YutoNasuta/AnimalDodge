#include"pch.h"
#include"CharacterCollision.h"
#include"Game/Enemy/Enemy.h"
#include"Game/Player/Player.h"

bool CharacterCollision::CheckHit(Player* player, Enemy* enemy)
{
	// �v���C���[���G�l�~�[�̃o�E���f�B���O�{�b�N�X������
	m_isHit = player->GetBoundingSphere().Intersects(enemy->GetBoundingSphere());

	// �q�b�g���Ă��Ȃ����false
	if (!m_isHit) { return false; }

	// �Փˎ��A�����߂�����
	// ���S�Ƃ̍����x�N�g��
	DirectX::SimpleMath::Vector3 diffVec = player->GetBoundingSphere().Center - enemy->GetBoundingCenter();

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
	player->SetPosition(player->GetPosition() + diffVec);
	player->SetBoundingSphereCenter(player->GetBoundingSphere().Center + diffVec);
	
	return true;
}
