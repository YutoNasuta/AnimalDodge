/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Interface/IScene.h"
#include"Game/PlayScene/Camera/TPSCamera.h"

#include"Libraries/Microsoft/DebugDraw.h"
#include"Game/PlayScene/PlaySceneResources.h"

// �O���錾
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
	// �ʒu
	static const DirectX::SimpleMath::Vector3 HOME_PLAYER_POSITION;
	static const DirectX::SimpleMath::Vector3 HOME_CROW_POSITION;
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;


	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	
	// ��]�p(�x)
	int m_angle;


	std::unique_ptr<PlaySceneResources> m_resources;


	// �n�ʈʒu����
	DirectX::SimpleMath::Vector3 m_ground;

	DirectX::SimpleMath::Quaternion m_debugQ;


	// TPS�J����
	std::unique_ptr<TPSCamera> m_tpsCamera;

	std::unique_ptr<Player> m_player;

	std::unique_ptr<Crow> m_crowBoss;

	std::unique_ptr<GenerateStage> m_stage;

	// �����̊�ɂȂ���W
	DirectX::SimpleMath::Vector3 m_rayPosition;
	DirectX::SimpleMath::Vector3 m_ballRayPosition;

	std::unique_ptr<NakashiLib::CreateRay> m_ray[3];

	std::unique_ptr<BlackBoard> m_blackBoard;

	// �����蔻����Ă�
	std::unique_ptr<CharacterCollision> m_characterCollision;

	// UI�Q�[�W
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

	// �ǂݎ���p
	Player* GetPlayer() { return m_player.get(); }
};
