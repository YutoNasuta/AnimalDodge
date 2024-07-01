/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Interface/IScene.h"
#include"Game/PlayScene/Camera/TPSCamera.h"

#include"Libraries/Microsoft/DebugDraw.h"
#include"Game/PlayScene/PlaySceneResources.h"

// 前方宣言
class CommonResources;
class TPSCamera;
class Crow;

class Player;

class GenerateStage;
class BlackBoard;
class CharacterCollision;
class PlaySceneResources;
class Gauge;

namespace mylib
{
	class GridFloor;
}

namespace NakashiLib
{
	
	class CollisionMesh;
	class CreateRay;
}

class PlayScene final :
    public IScene
{

public:
	// 位置
	static const DirectX::SimpleMath::Vector3 HOME_PLAYER_POSITION;
	static const DirectX::SimpleMath::Vector3 HOME_CROW_POSITION;
private:
	// 共通リソース
	CommonResources* m_commonResources;


	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// シーンチェンジフラグ
	bool m_isChangeScene;
	
	// 回転角(度)
	int m_angle;


	std::unique_ptr<PlaySceneResources> m_resources;


	// 地面位置判定
	DirectX::SimpleMath::Vector3 m_ground;

	DirectX::SimpleMath::Quaternion m_debugQ;


	// TPSカメラ
	std::unique_ptr<TPSCamera> m_tpsCamera;

	std::unique_ptr<Player> m_player;

	std::unique_ptr<Crow> m_crowBoss;

	std::unique_ptr<GenerateStage> m_stage;

	// 線分の基準になる座標
	DirectX::SimpleMath::Vector3 m_rayPosition;
	DirectX::SimpleMath::Vector3 m_ballRayPosition;

	std::unique_ptr<NakashiLib::CreateRay> m_ray[3];

	std::unique_ptr<BlackBoard> m_blackBoard;

	// 当たり判定を呼ぶ
	std::unique_ptr<CharacterCollision> m_characterCollision;

	// UIゲージ
	std::unique_ptr<Gauge> m_gauge;

public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
	
public:
	DirectX::SimpleMath::Matrix GetProjection() const { return m_projection; }

	DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }

	// 読み取り専用
	Player* GetPlayer() { return m_player.get(); }
};
