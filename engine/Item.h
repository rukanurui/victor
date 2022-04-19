#pragma once

//#include "Player.h"
//#include "Enemy.h"

class Item
{
private:

public:
	//変数
	typedef struct LEG//足移動速度アイテム
	{
		int Flag=0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

	}Leg;
	Leg LEG1;


	typedef struct ARM//腕回転速度アイテム
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;
	}Arm;
	Arm ARM1;


	typedef struct STRONG//敵を一発アウト
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;


	}Strong;
	Strong STR1;


	typedef struct STUDY//経験値アップ
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;
	}Study;
	Study STU1;

	typedef struct BARRIER//経験値アップ
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;
	}Barrier;
	Barrier BAR1;

	/*
	typedef struct DESTROY//殲滅アイテム
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
	//関数
	void Intialize();//初期化	

	void Update();//更新



	void Leg_SpeedUp();//移動速度アップ

	void Arm_SpeedUp();//腕回転速度アップ

	void StrongArm();//ザコを一発で倒す

	void StudyUp();//取得経験値アップ

	void Destroy();//画面内の敵を倒す

	void BarrierUp();





	void HEAL_Up();//回復

	void Box_Up();//箱
};

