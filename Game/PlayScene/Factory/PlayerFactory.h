#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Interface/IPlayerFactory.h"

class PlayerFactory : public IPlayerFactory
{
public:

	// プレイヤー生成
	std::unique_ptr<IComponent> CreatePlayer(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion, BlackBoard* blackboard);
	// 頭生成
	std::unique_ptr<IComponent> CreatePlayerHead(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// 胴生成
	std::unique_ptr<IComponent> CreatePlayerBody(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// 右腕生成
	std::unique_ptr<IComponent> CreatePlayerRightHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// 左腕生成
	std::unique_ptr<IComponent> CreatePlayerLeftHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// 足生成
	std::unique_ptr<IComponent> CreatePlayerLeg(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion );
	// しっぽ生成
	std::unique_ptr<IComponent> CreatePlayerTail(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);

};