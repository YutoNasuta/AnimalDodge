//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			PlayerDash.h
// <概要>		　　プレイヤーダッシュ状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// 前方宣言
class Player;
class CommonResources;

class PlayerDash : public IState
{
public:
	// コンストラクタ
	PlayerDash(Player* player);
	// デストラクタ
	~PlayerDash();
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
	// 動けるようにする
	void MovePlayer();
	// 移動時の補正
	void SlerpRotate(DirectX::SimpleMath::Vector3 direction);

private:
	// プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// ダッシュするスピード
	float m_dashSpeed;
	// ダッシュする方向
	DirectX::SimpleMath::Vector3 m_dashDirection;
	// ダッシュしたかどうか判定
	bool m_isDashing;
	// ダッシュを開始した時間
	double m_dashStartTime;
	// ダッシュを抜ける時間
	double m_dashDuration;
	// 時間の差分
	double m_differenceTime;
};