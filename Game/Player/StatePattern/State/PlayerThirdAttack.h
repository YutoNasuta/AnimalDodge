//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/26
// <file>			PlayerFirstAttack.h
// <�T�v>		�@�@�O��ڂ̍U��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// �O���錾
class Player;
class CommonResources;

class PlayerThirdAttack : public IState
{
public:
	// �R���X�g���N�^
	PlayerThirdAttack(Player* player);
	// �f�X�g���N�^
	~PlayerThirdAttack();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Render() override;
	// ����Ƃ�
	void OnEnter() override;
	// �o��Ƃ�
	void OnExit() override;
	// �I��
	void Finalize() override;
	// �q�p�[�c�̓���
	void MoveChild();
	// �r�̓���
	void MoveHand();
	// �����ۂ̓���
	void MoveTail();
	// ���̓���
	void MoveBody();
	// ���̓���
	void MoveHead();
	// �̑S�̂̓���
	void MovePlayer();
	// �X�e�[�g�ύX
	void ChangeState();
	// �����̕⊮
	void SlerpRotate(DirectX::SimpleMath::Vector3 direction);

private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���֓����X�s�[�h
	float m_backWardSpeed;
	// �U������
	float m_attackDuration;
	// �U���X�^�[�g
	float m_attackStartTime;

};

