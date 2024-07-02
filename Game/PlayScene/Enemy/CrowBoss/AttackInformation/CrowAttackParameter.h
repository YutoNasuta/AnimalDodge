//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/02
// <file>			CrowAttackParameter.h
// <概要>		　　カラスの攻撃パラメータ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

class CommonResources;

class CrowAttackParameter
{

public:
	// 攻撃設定
	void SetAttack(bool isAttack) { m_isAttack = isAttack; }
	bool GetAttack() { return m_isAttack; }
	// 攻撃１設定
	void SetAttack1(bool isAttack) { m_isAttack1 = isAttack; }
	bool GetAttack1() { return m_isAttack1; }
	// 攻撃１で攻撃する
	void Attack1Execute();

	void SetLastAttack1Time(float value) { m_lastAttack1Time = value; }
	float GetLastAttack1Time() { return m_lastAttack1Time; }
	// 攻撃1のクールダウン期間
	static const float m_attack1Cooldown;
public:
	CrowAttackParameter();
	~CrowAttackParameter();

private:
	CommonResources* m_commonResources;
	// 攻撃中かどうか
	bool m_isAttack;
	// 攻撃１中かどうか
	bool m_isAttack1;

	// 攻撃時間計測
	float m_attackTime;

	// 攻撃1の最後の攻撃時間
	float m_lastAttack1Time;



};
