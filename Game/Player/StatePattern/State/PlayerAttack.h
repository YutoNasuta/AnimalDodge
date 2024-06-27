//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			PlayerAttack.h
// <概要>		　　プレイヤー攻撃状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"
#include"Game/Player/Player.h"

// 前方宣言
class Player;

class PlayerAttack : public IState
{

public:
	// コンストラクタ
	PlayerAttack(Player* player);
	// デストラクタ
	~PlayerAttack();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;
	// 入ったとき
	void OnEnter() override;
	// 出たとき
	void OnExit() override;
	// 後始末
	void Finalize() override;

	// 子の動き
	void MoveChild();
	// 手の動き
	void MoveHand();
	// しっぽの動き
	void MoveTail();
	// 胴の動き
	void MoveBody();
	// 頭の動き
	void MoveHead();
	// 動けるようにする
	void MovePlayer();
	// 移動時の補正
	void SlerpRotate(DirectX::SimpleMath::Vector3 direction);
private:
	// プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// 攻撃を開始した時間
	double m_attackStartTime;
	// 攻撃を抜ける時間
	double m_attackDuration;
	// 時間の差分
	double m_differenceTime;
	// 攻撃速度
	float m_attackSpeed ;
};