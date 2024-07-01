//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/07/01
// <file>			BinaryFile.h
// <概要>			バイナリファイルを扱う
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include<memory>
namespace NakashiLib
{
	class BinaryFile
	{
	protected:

		// データ
		std::unique_ptr<char[]> m_data;
		// サイズ
		unsigned int m_size;

	public:
		// ファイル名を指定してロード
		static BinaryFile LoadFile(const wchar_t* fileName);
		// コンストラクタ
		BinaryFile();
		// ムーブコンストラクタ
		BinaryFile(BinaryFile&& in);

		// プロパティ
		char* GetData() { return m_data.get(); }
		unsigned int GetSize() { return m_size; }
		
	};
}