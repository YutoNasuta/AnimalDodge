//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/23
// <file>			BlackBoard.h
// <�T�v>		�@�@�V�[���ň����A�f�[�^�̏W�܂�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
class BlackBoard
{
public:
	// �d�͎擾
	 DirectX::SimpleMath::Vector3 GetGravity() { return m_gravity; }
	 // �����x�擾
	 DirectX::SimpleMath::Vector3 GetAcceleration() { return m_acceleration; }
	 // �v���C���[�ʒu�ݒ�
	 DirectX::SimpleMath::Vector3 GetPlayerPosition() { return m_playerPosition; }
	 void SetPlayerPosition(DirectX::SimpleMath::Vector3 position) { m_playerPosition = position; }

	 // �G�ʒu�ݒ�
	 DirectX::SimpleMath::Vector3 GetEnemyPosition() { return m_enemyPosition; }
	 void SetEnemyPosition(DirectX::SimpleMath::Vector3 position) { m_enemyPosition = position; }

	 // �J���XHP�擾
	float GetCrowHP() { return m_crowHP; }
	void SetCrowHP(float hp) { m_crowHP = hp; }

	 float GetGameTime() { return m_gameTime; }

public:
	BlackBoard();
	~BlackBoard();

private:
	// �d��
	DirectX::SimpleMath::Vector3 m_gravity;
	// �����x
	DirectX::SimpleMath::Vector3 m_acceleration;


	// �v���C���[�̃|�W�V����
	DirectX::SimpleMath::Vector3 m_playerPosition;
	// �G�̃|�W�V����
	DirectX::SimpleMath::Vector3 m_enemyPosition;
	// �J���X��HP
	float m_crowHP;

	// �Q�[��������
	float m_gameTime;
};