//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/26
// <file>			PlayerFirstAttack.h
// <�T�v>		�@�@�ŏ��̍U��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// �O���錾
class Player;
class CommonResources;

class PlayerFirstAttack : public IState
{
public:
	// �R���X�g���N�^
	PlayerFirstAttack(Player* player);
	// �f�X�g���N�^
	~PlayerFirstAttack();
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

private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���̍U���܂ł̔h������
	float m_deriveTime;
	// �o�ߎ���
	float m_elapsedTime;
	// ��]�I���t���O
	bool m_hasRotateFlag;
	// ��]�p�x
	float m_rotateAngle;
};