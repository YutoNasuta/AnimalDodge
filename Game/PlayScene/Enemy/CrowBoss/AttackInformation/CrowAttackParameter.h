//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/02
// <file>			CrowAttackParameter.h
// <�T�v>		�@�@�J���X�̍U���p�����[�^
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

class CommonResources;

class CrowAttackParameter
{

public:
	// �U���ݒ�
	void SetAttack(bool isAttack) { m_isAttack = isAttack; }
	bool GetAttack() { return m_isAttack; }
	// �U���P�ݒ�
	void SetAttack1(bool isAttack) { m_isAttack1 = isAttack; }
	bool GetAttack1() { return m_isAttack1; }
	// �U���P�ōU������
	void Attack1Execute();

	void SetLastAttack1Time(float value) { m_lastAttack1Time = value; }
	float GetLastAttack1Time() { return m_lastAttack1Time; }
	// �U��1�̃N�[���_�E������
	static const float m_attack1Cooldown;
public:
	CrowAttackParameter();
	~CrowAttackParameter();

private:
	CommonResources* m_commonResources;
	// �U�������ǂ���
	bool m_isAttack;
	// �U���P�����ǂ���
	bool m_isAttack1;

	// �U�����Ԍv��
	float m_attackTime;

	// �U��1�̍Ō�̍U������
	float m_lastAttack1Time;



};
