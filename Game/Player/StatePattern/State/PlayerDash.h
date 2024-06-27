//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			PlayerDash.h
// <�T�v>		�@�@�v���C���[�_�b�V�����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// �O���錾
class Player;
class CommonResources;

class PlayerDash : public IState
{
public:
	// �R���X�g���N�^
	PlayerDash(Player* player);
	// �f�X�g���N�^
	~PlayerDash();
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
	// ������悤�ɂ���
	void MovePlayer();
	// �ړ����̕␳
	void SlerpRotate(DirectX::SimpleMath::Vector3 direction);

private:
	// �v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �_�b�V������X�s�[�h
	float m_dashSpeed;
	// �_�b�V���������
	DirectX::SimpleMath::Vector3 m_dashDirection;
	// �_�b�V���������ǂ�������
	bool m_isDashing;
	// �_�b�V�����J�n��������
	double m_dashStartTime;
	// �_�b�V���𔲂��鎞��
	double m_dashDuration;
	// ���Ԃ̍���
	double m_differenceTime;
};