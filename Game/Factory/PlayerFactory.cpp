#include"pch.h"
#include"Game/Factory/PlayerFactory.h"
#include"Game/Player/Player.h"
#include"Game/Player/PlayerPart/PlayerBody.h"
#include"Game/Player/PlayerPart/PlayerHead.h"
#include"Game/Player/PlayerPart/PlayerLeftHand.h"
#include"Game/Player/PlayerPart/PlayerLeg.h"
#include"Game/Player/PlayerPart/PlayerRightHand.h"
#include"Game/Player/PlayerPart/PlayerTail.h"

/// <summary>
/// �v���C���[�̐���
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
/// <param name="blackboard">����</param>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayer(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion, BlackBoard* blackboard)
{
	// �v���C���[�̐錾
	std::unique_ptr<IComponent> player;
	// �v���C���[�N���X�̃C���X�^���X����
	player.reset(new Player(parent, initialPosition, initialQuaternion , blackboard));
	// ������
	player->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(player);
}

/// <summary>
/// �v���C���[�{�f�B�̐���
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerBody(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// �v���C���[�{�f�B�̐錾
	std::unique_ptr<IComponent> playerBody;
	// �{�f�B�N���X�̃C���X�^���X����
	playerBody.reset(new PlayerBody(parent, initialPosition, initialQuaternion));
	// ������
	playerBody->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(playerBody);

}

/// <summary>
/// �v���C���[�w�b�h�̐���
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
std::unique_ptr<IComponent>PlayerFactory::CreatePlayerHead(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// �v���C���[�w�b�h�錾
	std::unique_ptr<IComponent> playerHead;
	// �{�f�B�N���X�̃C���X�^���X����
	playerHead.reset(new PlayerHead(parent, initialPosition, initialQuaternion));
	// ������
	playerHead->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(playerHead);
}

/// <summary>
/// �v���C���[���萶��
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerLeftHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// �v���C���[����錾
	std::unique_ptr<IComponent> playerLeftHand;
	// ����̃C���X�^���X�𐶐�
	playerLeftHand.reset(new PlayerLeftHand(parent, initialPosition, initialQuaternion));
	// ������
	playerLeftHand->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(playerLeftHand);
}

/// <summary>
/// �v���C���[�E�萶��
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
/// <returns></returns>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerRightHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// �v���C���[�E��錾
	std::unique_ptr<IComponent> playerRightHand;
	// �E��̃C���X�^���X�𐶐�
	playerRightHand.reset(new PlayerRightHand(parent, initialPosition, initialQuaternion));
	// ������
	playerRightHand->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(playerRightHand);
}

/// <summary>
/// �v���C���[�̑�����
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
/// <returns></returns>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerLeg(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// �v���C���[�̑��錾
	std::unique_ptr<IComponent> playerLeg;
	// ���̃C���X�^���X�𐶐�
	playerLeg.reset(new PlayerLeg(parent, initialPosition, initialQuaternion));
	// ������
	playerLeg->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(playerLeg);
}

/// <summary>
/// �v���C���[�̂����ې���
/// </summary>
/// <param name="parent">�e</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialQuaternion">������]</param>
/// <returns></returns>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerTail(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// �v���C���[�̂����ې錾
	std::unique_ptr<IComponent> playerTail;
	// �����ۂ̃C���X�^���X�𐶐�
	playerTail.reset(new PlayerTail(parent, initialPosition, initialQuaternion));
	// ������
	playerTail->Initialize();
	// �C���X�^���X��Ԃ�
	return std::move(playerTail);
}
