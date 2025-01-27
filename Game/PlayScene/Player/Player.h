//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			Player.h
// <概要>		　　プレイヤーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Interface/IState.h"
#include"Game/PlayScene/Player/PlayerBase.h"
#include"Game/PlayScene/Player/StatePattern/State/PlayerStanding.h"
#include"StatePattern/State/PlayerJumping.h"
#include"StatePattern/State/PlayerRunning.h"
#include"StatePattern/State/PlayerDash.h"
#include"StatePattern/State/PlayerFirstAttack.h"
#include"StatePattern/State/PlayerSecondAttack.h"
#include"StatePattern/State/PlayerThirdAttack.h"

// 前方宣言
class CommonResources;
class PlayerStanding;
class PlayerJumping;
class PlayerRunning;
class PlayerDash;
class PlayerFirstAttack;
class PlayerSecondAttack;

class PlayerBody;
class BlackBoard;

class Player : public PlayerBase
{
public:
	// インタフェース用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 位置設定
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override{ m_position = position; }		

	// 回転設定
	DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		

	// 質量設定
	float GetMass() const override { return m_mass; }				
	void SetMass(const float& mass) override { m_mass = mass; }		

	// ステート用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 状態取得
	PlayerStanding* GetStanding() { return m_standing.get(); }		// 立ち状態取得
	PlayerJumping* GetJumping() { return m_jumping.get(); }			// ジャンプ状態取得
	PlayerRunning* GetRunning() { return m_runnning.get(); }		// 走る状態取得
	PlayerDash* GetDash() { return m_dash.get(); }					// ダッシュ状態
	PlayerFirstAttack* GetFirstAttack() { return m_firstAttack.get(); }
	PlayerSecondAttack* GetSecondAttack() { return m_secondAttack.get(); }
	PlayerThirdAttack* GetThirdAttack() { return m_thirdAttack.get(); }

	// 状態を遷移する
	void ChangeState(IState* currentState);	

	// 現在のステート情報を取得
	IState* GetNowState() const { return m_currentState; }			

	// プロパティ（取得と設定）++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 速度設定
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }						
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }	

	// 加速度設定
	DirectX::SimpleMath::Vector3 GetAcceleration() const { return m_acceleration; }								
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }	
	
	// 重力設定
	DirectX::SimpleMath::Vector3 GetGravity() const { return m_gravity; }		

	// 摩擦設定
	DirectX::SimpleMath::Vector3 GetFriction() const { return m_friction; }		

	// ワールド行列設定
	DirectX::SimpleMath::Matrix GetWorld() const { return m_worldMatrix; }		
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_worldMatrix = world; }

	// カメラ設定
	DirectX::SimpleMath::Matrix GetCameraView() const { return m_cameraView; }					
	DirectX::SimpleMath::Matrix GetProjection() const { return m_cameraProjection; }			
	DirectX::SimpleMath::Quaternion GetCameraQuaternion() const { return m_cameraQuaternion; }	
	void SetCameraQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_cameraQuaternion = quaternion; }

	// プレイヤーのボディ取得
	PlayerBody* GetBody() const { return m_body; }

	// 地面設定
	DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }
	void SetGround(const DirectX::SimpleMath::Vector3& ground) { m_ground = ground; }
	
	// ノード番号取得
	int GetNodeNumber() const { return m_nodeNumber; }

	// バウンディングボックス設定
	DirectX::BoundingSphere GetBoundingSphere() { return m_playerBoundingSphere; }
	void SetBoundingSphereCenter(DirectX::SimpleMath::Vector3 boundingSphere) { m_playerBoundingSphere.Center = boundingSphere; }

	// HP設定
	float GetHP() { return m_hp; }
	void SetHP(const float& hp) { m_hp = hp; }
public:
	// コンストラクタ
	Player(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion,
		BlackBoard* blackboard);
	// デストラクタ
	~Player();
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// 描画する
	void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection) override;
	// 境界球を作成
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);

private:
	// 共通リソース
	CommonResources* m_commonResources;
	// 地面位置
	DirectX::SimpleMath::Vector3 m_ground;
	// ノード番号
	int m_nodeNumber;
	// ブラックボード取得
	BlackBoard* m_blackBoard;
	
	//　ステート用+++++++++++++++++++++++++++++++++++++++++++++++
	IState* m_currentState;						// 現在の状態
	std::unique_ptr<PlayerStanding> m_standing;	// 立ち状態
	std::unique_ptr<PlayerJumping> m_jumping;	// ジャンプ状態
	std::unique_ptr<PlayerRunning> m_runnning;	// 走り状態
	std::unique_ptr<PlayerDash> m_dash;			// ダッシュ状態
	std::unique_ptr<PlayerFirstAttack> m_firstAttack;
	std::unique_ptr<PlayerSecondAttack> m_secondAttack;
	std::unique_ptr<PlayerThirdAttack> m_thirdAttack;

	//  プレイヤーの情報+++++++++++++++++++++++++++++++++++++++++++
	int m_partID;								 // ID
	DirectX::SimpleMath::Vector3 m_position;	 // 現在の位置
	DirectX::SimpleMath::Vector3 m_velocity;	 // 現在の速度
	DirectX::SimpleMath::Quaternion m_quaternion;// 現在の回転角
	DirectX::SimpleMath::Matrix m_worldMatrix;   // ワールド行列 
	DirectX::SimpleMath::Vector3 m_friction;	 // 摩擦
	float m_mass;								 // 質量
	DirectX::SimpleMath::Vector3 m_acceleration; // 加速度
	DirectX::SimpleMath::Vector3 m_gravity;      // 重力
	float m_hp;						 // ボールのチャージ量

	//  カメラの情報++++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::SimpleMath::Matrix m_cameraView;			 // カメラのビュー行列
	DirectX::SimpleMath::Matrix m_cameraProjection;		 // カメラプロジェクション
	DirectX::SimpleMath::Quaternion m_cameraQuaternion;	 // カメラの回転角

	//  当たり判定用++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::BoundingSphere m_playerBoundingSphere;			// プレイヤー当たり判定球


	PlayerBody* m_body;
};