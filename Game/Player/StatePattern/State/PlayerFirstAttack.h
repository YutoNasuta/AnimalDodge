//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/26
// <file>			PlayerFirstAttack.h
// <概要>		　　最初の攻撃
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// 前方宣言
class Player;
class CommonResources;

class PlayerFirstAttack : public IState
{
public:
	// コンストラクタ
	PlayerFirstAttack(Player* player);
	// デストラクタ
	~PlayerFirstAttack();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;
	// 入るとき
	void OnEnter() override;
	// 出るとき
	void OnExit() override;
	// 終了
	void Finalize() override;
	// 子パーツの動き
	void MoveChild();
	// 腕の動き
	void MoveHand();
	// しっぽの動き
	void MoveTail();
	// 胴の動き
	void MoveBody();
	// 頭の動き
	void MoveHead();
	// 体全体の動き
	void MovePlayer();
	// ステート変更
	void ChangeState();

private:
	// プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// 次の攻撃までの派生時間
	float m_deriveTime;
	// 経過時間
	float m_elapsedTime;
	// 回転終了フラグ
	bool m_hasRotateFlag;
	// 回転角度
	float m_rotateAngle;
};