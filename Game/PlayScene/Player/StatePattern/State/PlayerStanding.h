//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			PlayerStanding.h
// <概要>		　　プレイヤーの動いていないステート
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// 前方宣言
class Player;
class CommonResources;

class PlayerStanding : public IState
{
public:
	// コンストラクタ
	PlayerStanding(Player* player);
	// デストラクタ
	~PlayerStanding();
	// 初期化
	void Initialize() override;
	// 立ち状態
	void Update() override;
	// 立ちの描画
	void Render() override;
	// 入った時
	void OnEnter() override;
	// 出たとき
	void OnExit() override;
	// 後始末
	void Finalize() override;
	// キーでState変更
	void ChangeStateKey(const DirectX::Keyboard::State& keyboardStateTracker);
	// 子の動き
	void MoveChild();
	// 腕の動き
	void MoveHand();
	// しっぽの動き
	void MoveTail();
	// 頭の動き
	void MoveHead();
	// 胴体の動き
	void MoveBody();

private:
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
};
