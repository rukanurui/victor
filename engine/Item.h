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
		int Flag=0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

	}Leg;
	Leg LEG1;


	typedef struct ARM//�r��]���x�A�C�e��
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;
	}Arm;
	Arm ARM1;


	typedef struct STRONG//�G���ꔭ�A�E�g
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;


	}Strong;
	Strong STR1;


	typedef struct STUDY//�o���l�A�b�v
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;
	}Study;
	Study STU1;

	typedef struct BARRIER//�o���l�A�b�v
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;
	}Barrier;
	Barrier BAR1;

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

	typedef struct HEART//HEAL
	{
		int Flag;

		float X;

		float Y;

		float R;

		int X_Rand;

		int Y_Rand;

		int Time;
	}Heart;
	Heart Heart_[10];

	typedef struct BOX//BOX
	{
		int Flag;

		float X;

		float Y;

		float R;

		int X_Rand;

		int Y_Rand;

		int Time;

		int Select;

		int HitFlag;
	}Box;
	Box Box_[10];
	//�֐�
	void Intialize();//������	

	void Update();//�X�V



	void Leg_SpeedUp();//�ړ����x�A�b�v

	void Arm_SpeedUp();//�r��]���x�A�b�v

	void StrongArm();//�U�R���ꔭ�œ|��

	void StudyUp();//�擾�o���l�A�b�v

	void Destroy();//��ʓ��̓G��|��

	void BarrierUp();





	void HEAL_Up();//��

	void Box_Up();//��
};

