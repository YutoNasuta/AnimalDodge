//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/07/01
// <file>			BinaryFile.h
// <�T�v>			�o�C�i���t�@�C��������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include<memory>
namespace NakashiLib
{
	class BinaryFile
	{
	protected:

		// �f�[�^
		std::unique_ptr<char[]> m_data;
		// �T�C�Y
		unsigned int m_size;

	public:
		// �t�@�C�������w�肵�ă��[�h
		static BinaryFile LoadFile(const wchar_t* fileName);
		// �R���X�g���N�^
		BinaryFile();
		// ���[�u�R���X�g���N�^
		BinaryFile(BinaryFile&& in);

		// �v���p�e�B
		char* GetData() { return m_data.get(); }
		unsigned int GetSize() { return m_size; }
		
	};
}