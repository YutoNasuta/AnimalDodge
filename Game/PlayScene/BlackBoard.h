//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/23
// <file>			BlackBoard.h
// <概要>		　　シーンで扱う、データの集まり
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
class BlackBoard
{
public:
	// 重力取得
	 DirectX::SimpleMath::Vector3 GetGravity() { return m_gravity; }
	 // 加速度取得
	 DirectX::SimpleMath::Vector3 GetAcceleration() { return m_acceleration; }
	 // プレイヤー位置設定
	 DirectX::SimpleMath::Vector3 GetPlayerPosition() { return m_playerPosition; }
	 void SetPlayerPosition(DirectX::SimpleMath::Vector3 position) { m_playerPosition = position; }

	 // 敵位置設定
	 DirectX::SimpleMath::Vector3 GetEnemyPosition() { return m_enemyPosition; }
	 void SetEnemyPosition(DirectX::SimpleMath::Vector3 position) { m_enemyPosition = position; }

	 // カラスHP取得
	float GetCrowHP() { return m_crowHP; }
	void SetCrowHP(float hp) { m_crowHP = hp; }

	 float GetGameTime() { return m_gameTime; }

public:
	BlackBoard();
	~BlackBoard();

private:
	// 重力
	DirectX::SimpleMath::Vector3 m_gravity;
	// 加速度
	DirectX::SimpleMath::Vector3 m_acceleration;


	// プレイヤーのポジション
	DirectX::SimpleMath::Vector3 m_playerPosition;
	// 敵のポジション
	DirectX::SimpleMath::Vector3 m_enemyPosition;
	// カラスのHP
	float m_crowHP;

	// ゲーム内時間
	float m_gameTime;
};