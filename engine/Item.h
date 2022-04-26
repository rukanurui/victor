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

		int Select = 0;

		float UI = 0;
	}Leg;
	Leg LEG1;


	typedef struct ARM//腕回転速度アイテム
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Arm;
	Arm ARM1;


	typedef struct STRONG//敵を一発アウト
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Strong;
	Strong STR1;


	typedef struct STUDY//経験値アップ
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Study;
	Study STU1;

	typedef struct BARRIER//経験値アップ
	{
		int Flag = 0;

		int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;

		float UI = 0;

	}Barrier;
	Barrier BAR1;

	
	typedef struct DESTROY//殲滅アイテム
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

	typedef struct ROLLING//回転大きさアップ
	{
		int Flag = 0;

		//int Limit = 0;

		float Effect = 0;

		float Effect2 = 0;

		int Select = 0;//使っている

		float UI = 0;

	}Rolling;
	Rolling ROLL1;

	//関数
	void Intialize();//初期化	

	void Update();//更新



	void Leg_SpeedUp();//移動速度アップ

	void Arm_SpeedUp();//腕回転速度アップ

	void StrongArm();//ザコを一発で倒す

	void StudyUp();//取得経験値アップ

	void DestroyUp();//画面内の敵を倒す

	void BarrierUp();

	void AttackUp();

	void RollUp();



	void HEAL_Up();//回復

	void Box_Up();//箱

	void SelectUp();//能力選択時処理

	int Flag_;
	int Die_;
	int exp_;
	int UI_Flag = 0;

	int Add = 0;

	//選択時変数
	int SelectTime = 0;//１の時はゲーム動作が止まりアビリティ選択中
	int Ability_Select = 0;//
	int NowAbility = 0;//とれた能力
	//int Decision = 0;//決定フラグ　１なら使う2なら捨てる

	int Hit_Now = 0;
	int Decision;

	void Getter_Flag(float Flag) { Flag_ = Flag; }
	void Getter_Die(float Die) { Die_ = Die; }
	void Getter_exp(float exp) { exp_ = exp; }
	void Get_deci(int deci) { Decision= deci; }

};

