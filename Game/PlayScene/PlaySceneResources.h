//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/16
// <file>			Resources.h
// <�T�v>			�Q�[���Ŏg���摜�⃂�f���B
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

// �O���錾
class CommonResources;

	class PlaySceneResources
	{
	private:
		CommonResources* m_commonResources;

	public:
		PlaySceneResources();
		~PlaySceneResources();

		void CreateModels();
		void CreateSrvs();
	};
