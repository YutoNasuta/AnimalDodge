//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			CrowHead.h
// <概要>			プレイヤーの胴体パーツ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Game/PlayScene/Enemy/CrowBoss/CrowBase.h"
#include"Framework/DeviceResources.h"

// 前方宣言
class CommonResources;
class CrowRightWing;
class CrowLeftWing;
class CrowLeftLeg;
class CrowRightLeg;
class CrowUpperBeak;
class CrowLowerBeak;

class CrowHead : public CrowBase
{
public:

	// 現在の位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// 現在の位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetQuaternion() const  override { return m_quaternion; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion) override { m_quaternion = quaternion; }
	// 質量を取得
	float GetMass() const override { return m_mass; }
	// 質量を設定
	void SetMass(const float& mass) override { m_mass = mass; }


	DirectX::Model* GetModel() override { return m_model; }

	// 速度取得
	DirectX::SimpleMath::Vector3 GetVelocity()const {return m_velocity;};
	// 速度設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }

	void SetAddQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_addQuaternion = quaternion; }
	DirectX::SimpleMath::Quaternion GetAddQuaternion() const { return m_addQuaternion; }


	// 子取得用
	CrowRightWing* GetRightWing() const { return m_rightWing; }
	CrowLeftWing* GetLeftWing() const { return m_leftWing; }
	CrowLeftLeg* GetLeftLeg() const { return m_leftLeg; }
	CrowRightLeg* GetRightLeg() const { return m_rightLeg; }
	CrowUpperBeak* GetUpperBeak() const { return m_upperBeak; }

public:
	// コンストラクタ
	CrowHead(IComponent* parent, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// デストラクタ
	 ~CrowHead() ;
	// 初期化する
	void Initialize() override;
	// 子パーツ初期化用
	void ChildInitialize();
	void ModelInitialize();
	// 更新する
	void Update(
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// 描画する
	void Render(const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection) override;
	// 後処理を行う
	void Finalize();
	
private:
	// 共通
	CommonResources* m_commonResources;
	// 部品ID
	int m_partID;
	// モデル
	DirectX::Model* m_model;	
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_position;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_quaternion;
	// 質量
	float m_mass;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 追加のクォータニオン
	DirectX::SimpleMath::Quaternion m_addQuaternion;
	// ノード番号
	int m_nodeNumber;


	// bodyの子取得用
	CrowRightWing* m_rightWing;
	CrowLeftWing* m_leftWing;
	CrowLeftLeg* m_leftLeg;
	CrowRightLeg* m_rightLeg;
	CrowUpperBeak* m_upperBeak;
	CrowLowerBeak* m_lowerBeak;
	
};