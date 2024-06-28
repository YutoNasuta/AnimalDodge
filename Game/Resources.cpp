//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/16
// <file>			Resources.cpp
// <概要>			ゲームで使う画像やモデル達
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Resources.h"
#include"CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
/// <summary>
/// コンストラクタ
/// </summary>
NakashiLib::Resources::Resources()
{
	m_commonResources = CommonResources::GetInstance();
	CreateModels();
	CreateSrvs();
}

/// <summary>
/// デストラクタ
/// </summary>
NakashiLib::Resources::~Resources()
{

}

/// <summary>
///	モデルの設定
/// </summary>
void NakashiLib::Resources::CreateModels()
{
	auto ResourcesManager = m_commonResources->GetResourcesManager();

	// プレイヤーのパーツ生成
	ResourcesManager->CreateModel(L"PlayerBody",		 L"Player/PlayerBody.cmo");
	ResourcesManager->CreateModel(L"PlayerLeftHand",	 L"Player/PlayerLeftHand.cmo");
	ResourcesManager->CreateModel(L"PlayerHead",		 L"Player/PlayerHead.cmo");
	ResourcesManager->CreateModel(L"PlayerLeg",			 L"Player/PlayerLeg.cmo");
	ResourcesManager->CreateModel(L"PlayerRightHand",	 L"Player/PlayerRightHand.cmo");
	ResourcesManager->CreateModel(L"PlayerTail",		 L"Player/PlayerTail.cmo");

	// エネミーのパーツ生成
	ResourcesManager->CreateModel(L"CrowHead",		     L"Crow/CrowHead.cmo");
	ResourcesManager->CreateModel(L"CrowLeftWing",		 L"Crow/CrowLeftWing.cmo");
	ResourcesManager->CreateModel(L"CrowRightWing",		 L"Crow/CrowRightWing.cmo");
	ResourcesManager->CreateModel(L"CrowLeg",			 L"Crow/CrowLeg.cmo");
}

/// <summary>
/// 画像の設定
/// </summary>
void NakashiLib::Resources::CreateSrvs()
{

}