//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <êªçÏé“>			NakashimaYuto	
// <êªçÏäJénì˙>		2024/07/01
// <file>			Gauge.h
// <äTóv>		Å@	ÉQÅ[ÉWÇÃï`âÊ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

#include"pch.h"
#include"Framework/DeviceResources.h"
#include"Libraries/NakashiLib/UserInterface.h"

class BlackBoard;
class Gauge
{
private:
	unsigned int m_menuIndex;
	DX::DeviceResources* m_pDR;

	std::unique_ptr<NakashiLib::UserInterface> m_gauge;
	std::unique_ptr<NakashiLib::UserInterface> m_frame;
	std::unique_ptr<NakashiLib::UserInterface> m_base;

	const wchar_t* m_baseTexturePath;

	std::unique_ptr<NakashiLib::UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	DirectX::Keyboard::KeyboardStateTracker m_tracker;

	float m_ratio;

public:

	Gauge();
	~Gauge();

	void Initialize(DX::DeviceResources* pDR, int width, int height);
	void Update(BlackBoard* blackBoard);
	void Render();

	void Add(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		NakashiLib::ANCHOR anchor);

	void Reset();
};