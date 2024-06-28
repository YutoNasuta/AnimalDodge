//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			Crow.h
// <概要>			エネミーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Game/Enemy/CrowBoss/CrowBase.h"

class CommonResources;

class CrowHead;

class BehaviorTreeBuilder;

class BlackBoard;

class BehaviorTreeExecute;


class Crow : public CrowBase 
{
public:
    // インタフェース用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						// 現在の位置を取得する
    void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }		// 現在の位置を設定する

    DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						//  現在の回転角を取得する
    void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		// 現在の回転角を設定する

    float GetMass() const override { return m_mass; }				// 質量を設定
    void SetMass(const float& mass) override { m_mass = mass; }		// 質量を設定



    CrowHead* GetHead() const { return m_head; }

public: //プロパティ

    DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
    void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }

    DirectX::BoundingSphere GetBoundingSphere() { return m_crowBoundingSphere; }
    void SetBoundingSphereCenter(DirectX::SimpleMath::Vector3 boundingSphere) { m_crowBoundingSphere.Center = boundingSphere; }
public:
    Crow(
        IComponent* parent,
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion,
        BlackBoard* blackboard);
    ~Crow();

    void Initialize() override;
    void Update(
   
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Quaternion& quaternion) override;

    // 描画する
    void Render(
        const DirectX::SimpleMath::Matrix& view,
        const DirectX::SimpleMath::Matrix& projection) override;

    const float GetNumber() const { return Number; }
    void SetDebug(float value) { Debug = value; }
    const float GetDebug() const { return Debug; }

    // 境界球を作成
    DirectX::BoundingSphere CreateBoundingSphere(const float& radius);

private:
    // 共通リソース
    CommonResources* m_commonResources;

    // ブラックボード
    BlackBoard* m_blackBoard;

    float Number;
    float Debug;

    //  プレイヤーの情報+++++++++++++++++++++++++++++++++++++++++++
    int m_partID;								 //ID
    DirectX::SimpleMath::Vector3 m_position;	 //  現在の位置
    DirectX::SimpleMath::Vector3 m_velocity;	 //  現在の速度
    DirectX::SimpleMath::Quaternion m_quaternion;//  現在の回転角
    DirectX::SimpleMath::Matrix m_worldMatrix;   //  ワールド行列 
    DirectX::SimpleMath::Vector3 m_friction;	 //　摩擦
    float m_mass;								 //  質量
    DirectX::SimpleMath::Vector3 m_acceleration; //  加速度
    DirectX::SimpleMath::Vector3 m_gravity;      //　重力
    bool m_ballTaking;							 // ボールを持っている状態か持っていない状態か
    float m_forceCharge;						 // ボールのチャージ量

    // ビヘイビアツリーノード実行用
    std::unique_ptr<BehaviorTreeBuilder> m_behaviorTreeBuilder;
    std::unique_ptr<BehaviorTreeExecute> m_behaviorExecutor;

    CrowHead* m_head;

    DirectX::BoundingSphere m_crowBoundingSphere;			// プレイヤー当たり判定球
    DirectX::SimpleMath::Vector3 m_CrowCenter;			// プレイヤーの中心
};