//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <»ìÒ>			NakashimaYuto	
// <»ìŠJn“ú>		2024/07/02
// <file>			CrowAttackParameter.h
// <ŠT—v>		@@ƒJƒ‰ƒX‚ÌUŒ‚ƒpƒ‰ƒ[ƒ^
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

class CommonResources;

class CrowAttackParameter
{

public:
	// UŒ‚İ’è
	void SetAttack(bool isAttack) { m_isAttack = isAttack; }
	bool GetAttack() { return m_isAttack; }
	// UŒ‚‚Pİ’è
	void SetAttack1(bool isAttack) { m_isAttack1 = isAttack; }
	bool GetAttack1() { return m_isAttack1; }
	// UŒ‚‚P‚ÅUŒ‚‚·‚é
	void Attack1Execute();

	void SetLastAttack1Time(float value) { m_lastAttack1Time = value; }
	float GetLastAttack1Time() { return m_lastAttack1Time; }
	// UŒ‚1‚ÌƒN[ƒ‹ƒ_ƒEƒ“ŠúŠÔ
	static const float m_attack1Cooldown;
public:
	CrowAttackParameter();
	~CrowAttackParameter();

private:
	CommonResources* m_commonResources;
	// UŒ‚’†‚©‚Ç‚¤‚©
	bool m_isAttack;
	// UŒ‚‚P’†‚©‚Ç‚¤‚©
	bool m_isAttack1;

	// UŒ‚ŠÔŒv‘ª
	float m_attackTime;

	// UŒ‚1‚ÌÅŒã‚ÌUŒ‚ŠÔ
	float m_lastAttack1Time;



};
