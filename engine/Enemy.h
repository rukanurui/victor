#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class Enemy
{
public:

	const int ENEMY_NUM = 10;

	typedef struct Enemy1//ザコ1
	{
		float X=0;//ｘ座標
		float Y=0;//ｙ座標

		float R=0;//半径
		int Flag=0;//フラグ
		int Color_Flag=0;//色のフラグ

		int Timer=0;//フラグを立たせるための時間


		float Angle=0;

		int Patern=0;

		float rnd=0;

		int Die=0;
		
		int Type = 0;
	}ENEMY1;

	ENEMY1 Enemy1[10];

	typedef struct Enemy2//ザコ1
	{
		float X;//ｘ座標
		float Y;//ｙ座標

		float R;//半径
		int Flag;//フラグ
		int Color_Flag;//色のフラグ

		//int id;//配列の要素

		int Timer;//フラグを立たせるための時間

		int SpeedX;
		int SpeedY;

		float Angle;

		int Patern;

		float rnd;

		int Die;
		//struct Enemy1* next;
		//struct Enemy1* before;//前のデータがある場所
	}ENEMY2;

	//ENEMY1* head = NULL; // リストの先頭
	//ENEMY1* tail = NULL; // リストの末尾

	float C_X;//getter Central_X用
	float C_Y;//上のY版


	float P_X;//getter Central_X用
	float P_Y;//上のY版


	void Getter_X(float X) { C_X = X; }
	void Getter_Y(float Y) { C_Y = Y; }

	void Central_X_Get(float X) { P_X = X; }
	void Central_Y_Get(float Y) { P_Y = Y; }


	//関数
//	ENEMY1* createCell(void);//要素の作成
	//void create(float x,float y,float r,int flag,int cr_flag,int id);//最後尾にリストを追加
	//void editCell(float x, float y, float r, int flag, int cr_flag, int id);//中身を編集


	//ここから配列Ver
	void Intialize();//初期化	

	void Update();//更新

	void Generation();//オブジェクトの生成

	void Flagged();//フラグが立つ

	void Move();//敵の動作

	void Rear();//後処理

	//中ボス

	void LittleBoss_Generation();

	void LittleBoss_Flagged();

	void LittleBoss_Move();
};

