//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/01
// <file>			UserInterface.h
// <概要>			ユーザーインターフェースクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

#include"pch.h"
#include"Framework/DeviceResources.h"
#include"Framework/StepTimer.h"


namespace NakashiLib
{
	// UIのアンカーポイント
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER = 1,
		TOP_RIGHT = 2,

		MIDDLE_LEFT = 3,
		MIDDLE_CENTER = 4,
		MIDDLE_RIGHT = 5,

		BOTTOM_LEFT = 6,
		BOTTOM_CENTER = 7,
		BOTTOM_RIGHT = 8
	};

	class UserInterface
	{
	public:
		// データの受け渡し用コンスタントバッファ
		struct ConstBuffer
		{
			DirectX::SimpleMath::Vector4 windowSize;
		};

	private:
		// デバイス取得
		DX::DeviceResources* m_pDR;
		// バッファ取得
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_cBuffer;
		// タイマー取得
		DX::StepTimer	m_timer;
		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		// コモンステート
		std::unique_ptr<DirectX::CommonStates> m_states;
		// テクスチャハンドル
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
		// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
		// ウィンドウのサイズ
		int m_windowWidth, m_windowHeight;
		// テクスチャのサイズ
		int m_textureWidth, m_textureHeight;
		// 大きさ
		DirectX::SimpleMath::Vector2 m_scale;
		// 元の大きさ
		DirectX::SimpleMath::Vector2 m_baseScale;
		// 位置
		DirectX::SimpleMath::Vector2 m_position;

		ANCHOR m_anchor;

		float m_renderRatio;
		float m_renderRatioOffset;

	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		UserInterface();
		~UserInterface();

		void LoadTexture(const wchar_t* path);
		void Create(
			DX::DeviceResources* pDR,
			const wchar_t* path,
			DirectX::SimpleMath::Vector2 position,
			DirectX::SimpleMath::Vector2 scale,
			ANCHOR anchor);

		void Render();

		void SetWindowSize(const int& width, const int& height) { m_windowWidth = width; m_windowHeight = height; }

		void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; }

		DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }

		DirectX::SimpleMath::Vector2 GetBaseScale() { return m_baseScale; }

		void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

		DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

		void SetAnchor(NakashiLib::ANCHOR anchor);

		NakashiLib::ANCHOR GetAnchor() { return m_anchor; }

		void SetRenderRatio(float ratio) { m_renderRatio = ratio; }
		float GetRenderRatio() { return m_renderRatio; }

		void SetRenderRatioOffset(float offset) { m_renderRatioOffset = offset; }
		float GetRenderRatioOffset() { return m_renderRatioOffset; }

	private:
		void CreateShader();
	};
}