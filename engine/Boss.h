#pragma once
#include "Player.h"

class Boss
{

public:
      	float x;
		float y;

		int HP;

		float R;//半径
		int Flag;//フラグ
		int Color_Flag;//色のフラグ

		float Angle;

		int Patern;


        //回転する円の大きさ
        float radius = 200;
        //回転するための値
        float timer = 0;
        //切り替え変数
        int Switch = 0;

        int Switch_Flag = 0;
        int Switch_Count = 0;
        int Switch_Rand = 0;

        //赤球座標
        float RedX = 0;
        float RedY = 0;

        float Red_R = 25;
        float Blue_R = 25;

        //蒼球座標
        float BlueX = 0;
        float BlueY = 0;

        int rotate = 0;

        int rotate_rand = 0;
        int rotate_time = 0;

        float C_X;//getter Central_X用
        float C_Y;//上のY版


        float P_X;//getter Central_X用
        float P_Y;//上のY版

    //関数
    void Initialize();//初期化

    void Update();//更新

    void Move();

    void RandSwitch();//色の位置かえAI

    void RandRotate();//回転AI

    void RandColor();//色の切り替えAI

    void Getter_X(float X) { C_X = X; }
    void Getter_Y(float Y) { C_Y = Y; }

    void Central_X_Get(float X) { P_X = X; }
    void Central_Y_Get(float Y) { P_Y = Y; }
};

