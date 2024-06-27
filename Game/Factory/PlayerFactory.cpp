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
/// プレイヤーの生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
/// <param name="blackboard">黒板</param>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayer(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion, BlackBoard* blackboard)
{
	// プレイヤーの宣言
	std::unique_ptr<IComponent> player;
	// プレイヤークラスのインスタンス生成
	player.reset(new Player(parent, initialPosition, initialQuaternion , blackboard));
	// 初期化
	player->Initialize();
	// インスタンスを返す
	return std::move(player);
}

/// <summary>
/// プレイヤーボディの生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerBody(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// プレイヤーボディの宣言
	std::unique_ptr<IComponent> playerBody;
	// ボディクラスのインスタンス生成
	playerBody.reset(new PlayerBody(parent, initialPosition, initialQuaternion));
	// 初期化
	playerBody->Initialize();
	// インスタンスを返す
	return std::move(playerBody);

}

/// <summary>
/// プレイヤーヘッドの生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
std::unique_ptr<IComponent>PlayerFactory::CreatePlayerHead(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// プレイヤーヘッド宣言
	std::unique_ptr<IComponent> playerHead;
	// ボディクラスのインスタンス生成
	playerHead.reset(new PlayerHead(parent, initialPosition, initialQuaternion));
	// 初期化
	playerHead->Initialize();
	// インスタンスを返す
	return std::move(playerHead);
}

/// <summary>
/// プレイヤー左手生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerLeftHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// プレイヤー左手宣言
	std::unique_ptr<IComponent> playerLeftHand;
	// 左手のインスタンスを生成
	playerLeftHand.reset(new PlayerLeftHand(parent, initialPosition, initialQuaternion));
	// 初期化
	playerLeftHand->Initialize();
	// インスタンスを返す
	return std::move(playerLeftHand);
}

/// <summary>
/// プレイヤー右手生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
/// <returns></returns>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerRightHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// プレイヤー右手宣言
	std::unique_ptr<IComponent> playerRightHand;
	// 右手のインスタンスを生成
	playerRightHand.reset(new PlayerRightHand(parent, initialPosition, initialQuaternion));
	// 初期化
	playerRightHand->Initialize();
	// インスタンスを返す
	return std::move(playerRightHand);
}

/// <summary>
/// プレイヤーの足生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
/// <returns></returns>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerLeg(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// プレイヤーの足宣言
	std::unique_ptr<IComponent> playerLeg;
	// 足のインスタンスを生成
	playerLeg.reset(new PlayerLeg(parent, initialPosition, initialQuaternion));
	// 初期化
	playerLeg->Initialize();
	// インスタンスを返す
	return std::move(playerLeg);
}

/// <summary>
/// プレイヤーのしっぽ生成
/// </summary>
/// <param name="parent">親</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialQuaternion">初期回転</param>
/// <returns></returns>
std::unique_ptr<IComponent> PlayerFactory::CreatePlayerTail(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion)
{
	// プレイヤーのしっぽ宣言
	std::unique_ptr<IComponent> playerTail;
	// しっぽのインスタンスを生成
	playerTail.reset(new PlayerTail(parent, initialPosition, initialQuaternion));
	// 初期化
	playerTail->Initialize();
	// インスタンスを返す
	return std::move(playerTail);
}
