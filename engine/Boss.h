#pragma once
#include "Player.h"

class Boss
{
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

    //関数
    void Initialize();//初期化

    void Update();//更新

    void RandSwitch();//色の位置かえAI

    void RandRotate();//回転AI

    void RandColor();//色の切り替えAI
};

