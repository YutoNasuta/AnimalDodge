//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			PlayerAttack.h
// <�T�v>		�@�@�v���C���[�U�����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Player/Player.h"

// �O���錾
class Player;

class PlayerAttack : public IState
{

public:
	// �R���X�g���N�^
	PlayerAttack(Player* player);
	// �f�X�g���N�^
	~PlayerAttack();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Render() override;
	// �������Ƃ�
	void OnEnter() override;
	// �o���Ƃ�
	void OnExit() override;
	// ��n��
	void Finalize() override;

	// �q�̓���
	void MoveChild();
	// ��̓���
	void MoveHand();
	// �����ۂ̓���
	void MoveTail();
	// ���̓���
	void MoveBody();
	// ���̓���
	void MoveHead();
	// ������悤�ɂ���
	void MovePlayer();
	// �ړ����̕␳
	void SlerpRotate(DirectX::SimpleMath::Vector3 direction);
private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �U�����J�n��������
	double m_attackStartTime;
	// �U���𔲂��鎞��
	double m_attackDuration;
	// ���Ԃ̍���
	double m_differenceTime;
	// �U�����x
	float m_attackSpeed ;
};