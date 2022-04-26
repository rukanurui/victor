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

		int Select = 0;

		float UI = 0;
	}Leg;
	Leg LEG1;


	typedef struct ARM//�r��]���x�A�C�e��
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Arm;
	Arm ARM1;


	typedef struct STRONG//�G���ꔭ�A�E�g
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Strong;
	Strong STR1;


	typedef struct STUDY//�o���l�A�b�v
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Study;
	Study STU1;

	typedef struct BARRIER//�o���l�A�b�v
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Barrier;
	Barrier BAR1;

	
	typedef struct DESTROY//�r�ŃA�C�e��
	{
		int Flag=0;

		int Limit=0;

		int Time = 0;

		int Select = 0;

		float UI = 0;
	}Destroy;
	Destroy DESTROY_;
	

	typedef struct HEART//HEAL
	{
		int Flag;

		float X;

		float Y;

		float R;

		int X_Rand;

		int Y_Rand;

		int Time;

		//int Select = 0;

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

	typedef struct ATTACK
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int x = 0;

		int y = 0;

		int lv = 1;

		int Select = 0;

		float UI = 0;
	}Attack;
	Attack ATT1;

	typedef struct ROLLING//��]�傫���A�b�v
	{
		int Flag = 0;

		//int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;//�g���Ă���

		float UI = 0;

	}Rolling;
	Rolling ROLL1;

	//�֐�
	void Intialize();//������	

	void Update();//�X�V



	void Leg_SpeedUp();//�ړ����x�A�b�v

	void Arm_SpeedUp();//�r��]���x�A�b�v

	void StrongArm();//�U�R���ꔭ�œ|��

	void StudyUp();//�擾�o���l�A�b�v

	void DestroyUp();//��ʓ��̓G��|��

	void BarrierUp();

	void AttackUp();

	void RollUp();



	void HEAL_Up();//��

	void Box_Up();//��

	void SelectUp();//�\�͑I��������

	int Flag_;
	int Die_;
	int exp_;
	int UI_Flag = 0;

	int Add = 0;

	//�I�����ϐ�
	int SelectTime = 0;//�P�̎��̓Q�[�����삪�~�܂�A�r���e�B�I��
	int Ability_Select = 0;//
	int NowAbility = 0;//�Ƃꂽ�\��
	//int Decision = 0;//����t���O�@�P�Ȃ�g��2�Ȃ�̂Ă�

	int Hit_Now = 0;
	int Decision;

	void Getter_Flag(float Flag) { Flag_ = Flag; }
	void Getter_Die(float Die) { Die_ = Die; }
	void Getter_exp(float exp) { exp_ = exp; }
	void Get_deci(int deci) { Decision= deci; }

};

