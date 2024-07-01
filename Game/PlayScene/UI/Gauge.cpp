//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/01
// <file>			Gauge.h
// <概要>		　	ゲージの描画
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Gauge.h"
#include"Game/PlayScene/BlackBoard.h"

/// <summary>
/// コンストラクタ
/// </summary>
Gauge::Gauge()
	:
	m_menuIndex(0),
	m_windowHeight(0),
	m_windowWidth(0),
	m_pDR(nullptr),
	m_baseTexturePath(nullptr),
	m_gauge(nullptr),
	m_frame(nullptr),
	m_ratio()
{

}

/// <summary>
/// コンストラクタ
/// </summary>
Gauge::~Gauge()
{

}

void Gauge::Initialize(DX::DeviceResources* pDR, int width, int height)
{
	m_pDR = pDR;
	m_windowWidth = width;
	m_windowHeight = height;

	m_baseTexturePath = L"Resources/Textures/frame_back.png";

	Add(L"Resources/Textures/frame.png",
		DirectX::SimpleMath::Vector2(width / 4, height / 2),
		DirectX::SimpleMath::Vector2(1.0f, 1.0f),
		NakashiLib::ANCHOR::MIDDLE_LEFT);

}

void Gauge::Update(BlackBoard* blackBoard)
{
	auto m_hp = blackBoard->GetCrowHP();

	m_hp /= 10000;
	m_ratio = m_gauge->GetRenderRatio();

	m_ratio -= m_hp;

	m_gauge->SetRenderRatio(m_ratio);
}

void Gauge::Render()
{
	m_base->Render();
	m_gauge->Render();
	m_frame->Render();
}

void Gauge::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, NakashiLib::ANCHOR anchor)
{
	m_base = std::make_unique<NakashiLib::UserInterface>();
	m_base->Create(m_pDR
		, L"Resources/Textures/frame_base.png"
		, position
		, scale
		, anchor);
	m_base->SetWindowSize(m_windowWidth, m_windowHeight);


	m_gauge = std::make_unique<NakashiLib::UserInterface>();
	m_gauge->Create(m_pDR
		, m_baseTexturePath
		, position
		, scale
		, anchor);
	m_gauge->SetWindowSize(m_windowWidth, m_windowHeight);
	m_gauge->SetRenderRatioOffset(0.3f);

	m_frame = std::make_unique<NakashiLib::UserInterface>();
	m_frame->Create(m_pDR
		, path
		, position
		, scale
		, anchor);
	m_frame->SetWindowSize(m_windowWidth, m_windowHeight);
}

void Gauge::Reset()
{
	m_ratio = 1;
	m_gauge->SetRenderRatio(m_ratio);
}