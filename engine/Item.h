#pragma once

//#include "Player.h"
//#include "Enemy.h"

class Item
{
private:

public:
	//�ϐ�
	typedef struct LEG//���ړ����x�A�C�e��
	{
		int Flag;

		int Limit;

		float Effect;

		float X;

		float Y;
	}Leg;
	Leg LEG_[10];


	typedef struct ARM//�r��]���x�A�C�e��
	{
		int Flag;

		int Limit;

		float Effect;

		float X;

		float Y;
	}Arm;
	Arm ARM_[10];


	typedef struct STRONG//�G���ꔭ�A�E�g
	{
		int Flag;

		int Limit;

		float Effect;

		float X;

		float Y;
	}Strong;
	Strong STRONG_[10];


	typedef struct STUDY//�o���l�A�b�v
	{
		int Flag;

		int Limit;

		float Effect;

		float X;

		float Y;
	}Study;
	Study STUDY_[10];

	/*
	typedef struct DESTROY//�r�ŃA�C�e��
	{
		int Flag;

		int Limit;

		float X;

		float Y;
	}Destroy;
	Destroy DESTOROY_[10];
	*/
	//�֐�
	void Intialize();//������	

	void Update();//�X�V



	void Leg_SpeedUp();//�ړ����x�A�b�v

	void Arm_SpeedUp();//�r��]���x�A�b�v

	void StrongArm();//�U�R���ꔭ�œ|��

	void StudyUp();//�擾�o���l�A�b�v

	void Destroy();//��ʓ��̓G��|��
};

