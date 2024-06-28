//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/26
// <file>			PlayerFirstAttack.h
// <概要>		　　三回目の攻撃
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// 前方宣言
class Player;
class CommonResources;

class PlayerThirdAttack : public IState
{
public:
	// コンストラクタ
	PlayerThirdAttack(Player* player);
	// デストラクタ
	~PlayerThirdAttack();
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
	// 動きの補完
	void SlerpRotate(DirectX::SimpleMath::Vector3 direction);

private:
	// プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// 後ろへ動くスピード
	float m_backWardSpeed;
	// 攻撃時間
	float m_attackDuration;
	// 攻撃スタート
	float m_attackStartTime;

};

