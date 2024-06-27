#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Interface/IPlayerFactory.h"

class PlayerFactory : public IPlayerFactory
{
public:

	// �v���C���[����
	std::unique_ptr<IComponent> CreatePlayer(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion, BlackBoard* blackboard);
	// ������
	std::unique_ptr<IComponent> CreatePlayerHead(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// ������
	std::unique_ptr<IComponent> CreatePlayerBody(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// �E�r����
	std::unique_ptr<IComponent> CreatePlayerRightHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// ���r����
	std::unique_ptr<IComponent> CreatePlayerLeftHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);
	// ������
	std::unique_ptr<IComponent> CreatePlayerLeg(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion );
	// �����ې���
	std::unique_ptr<IComponent> CreatePlayerTail(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion);

};