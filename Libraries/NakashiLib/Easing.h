//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2023/09/03
// <file>			Easing.h
// <�T�v>			�C�[�W���O�֐�������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

class Easing {
private:
	float change;		//�ω�0�`1
	float change_amount;//���ۂ̕ω���
	bool turn;			//Turn�֐��p
public:
	Easing();
	~Easing();

	//���l�ύX
	void Start(float speed, float strNum, float endNum);
	//�I���Ăяo��
	bool EndChange();
	//���Z�b�g
	void Reset();

	float GetChange() {
		return change;
	}
	

	//speed 1�t���[���̕ω���,strNum �ω��̏����l,endNum �ω��̍ŏI�l

	float Normal      (float speed, float strNum, float endNum);
	float InSine      (float speed, float strNum, float endNum);
	float OutSine     (float speed, float strNum, float endNum);
	float InOutSine   (float speed, float strNum, float endNum);

	float InQuad      (float speed, float strNum, float endNum);
	float OutQuad     (float speed, float strNum, float endNum);
	float InOutQuad   (float speed, float strNum, float endNum);

	float InQubic     (float speed, float strNum, float endNum);
	float OutQubic    (float speed, float strNum, float endNum);
	float InOutQubic  (float speed, float strNum, float endNum);

	float InQuart     (float speed, float strNum, float endNum);
	float OutQuart    (float speed, float strNum, float endNum);
	float InOutQuart  (float speed, float strNum, float endNum);

	float InQuint     (float speed, float strNum, float endNum);
	float OutQuint    (float speed, float strNum, float endNum);
	float InOutQuint  (float speed, float strNum, float endNum);

	float InExpo      (float speed, float strNum, float endNum);
	float OutExpo     (float speed, float strNum, float endNum);
	float InOutExpo   (float speed, float strNum, float endNum);

	float InCirc      (float speed, float strNum, float endNum);
	float OutCirc     (float speed, float strNum, float endNum);
	float InOutCirc   (float speed, float strNum, float endNum);
	
	float InBack      (float speed, float strNum, float endNum);
	float OutBack     (float speed, float strNum, float endNum);
	float InOutBack   (float speed, float strNum, float endNum);

	float InElastic   (float speed, float strNum, float endNum);
	float OutElastic  (float speed, float strNum, float endNum);
	float InOutElastic(float speed, float strNum, float endNum);

	float InBounce    (float speed, float strNum, float endNum);
	float OutBounce   (float speed, float strNum, float endNum);
	float InOutBounce (float speed, float strNum, float endNum);


	enum class EasingType
	{
		Nomal,

		InSine,OutSine,InOutSine,

		InQuad,OutQuad,InOutQuad,

		InQubic,OutQubic,InOutQubic,

		InQuart,OutQuart,InOutQuart,

		InQuint,OutQuint,InOutQuint,

		InExpo,OutExpo,InOutExpo,

		InCirc,OutCirc,InOutCirc,

		InBack,OutBack,InOutBack,

		InElastic, OutElastic, InOutElastic,

		InBounce, OutBounce, InOutBounce
	};

	//enum����I�����Ď�ނ�ݒ肷��
	//Easing�̎��(Easing::EasingType::�Z�Z),�X�s�[�h,�����l,�ŏI�n
	float Selection(EasingType type, float speed, float strNum, float endNum);

	//�w�肳�ꂽ�͈͂𔽕�����
	//�����l����ŏI�n�ւ̃^�C�v,�ŏI�n���珉���l�ւ̃^�C�v,�X�s�[�h,�����l,�ŏI�n
	float Turn(EasingType type1, EasingType type2, float speed, float strNum, float endNum);

	//�w�肵���͈͂��J��Ԃ�������
	//Easing�̎��(Easing::EasingType::�Z�Z),�X�s�[�h,�����l,�ŏI�n
	float Rope(EasingType type, float speed, float strNum, float endNum);
};