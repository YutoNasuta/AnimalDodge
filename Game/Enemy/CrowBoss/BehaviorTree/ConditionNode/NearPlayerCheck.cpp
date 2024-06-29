//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/29
// <file>			NearPlayerCheck.h
// <概要>			近くにプレイヤーがいるかどうか判定
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"NearPlayerCheck.h"
#include"Game/Enemy/CrowBoss/Crow.h"
#include"Game/BlackBoard.h"
#include<cmath>
/// <summary>
///  コンストラクタ
/// </summary>
/// <param name="Crow">自分</param>
/// <param name="blackboard">ブラックボード</param>
NearPlayerCheck::NearPlayerCheck(Crow* Crow, BlackBoard* blackboard)
	:
	ConditionNode([this]() { return this->CheckNearPlayer(); })
{
	m_crow = Crow;
	m_blackBoard = blackboard;
}

/// <summary>
/// デストラクタ
/// </summary>
NearPlayerCheck::~NearPlayerCheck()
{

}

/// <summary>
/// 近くにプレイヤーがいるかどうか
/// </summary>
bool NearPlayerCheck::CheckNearPlayer()
{
    // カラスとプレイヤーの位置を取得
    auto crowPosition = m_crow->GetPosition();
    auto playerPosition = m_blackBoard->GetPlayerPosition();

    // 距離の計算
    float distance = std::sqrt(
        std::pow(crowPosition.x - playerPosition.x, 2) +
        std::pow(crowPosition.y - playerPosition.y, 2) +
        std::pow(crowPosition.z - playerPosition.z, 2)
    );

    // 閾値（近いと判定する距離）を設定
    constexpr float threshold = 100.0f; // この値は適宜調整してください

    // 距離が閾値より小さいかどうかをチェック
    return distance < threshold;
}