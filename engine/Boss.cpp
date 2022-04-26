#include "Boss.h"

void Boss::Initialize()
{
	HP = 10;
	x = -300;
	y = -300;

	R = 50;
	Flag = 0;
	Color_Flag = 0;

	Angle = 0;

	Patern = 1;


	timer = 0;
	//切り替え変数
	Switch = 0;

    rotate = 1;
}

void Boss::Update()
{

    //色の切り替え
    if (Color_Flag==1 && Switch == 0)
    {
        Switch = 1;
        Color_Flag = 0;
    }
    else if (Color_Flag== 1 && Switch == 1)
    {
        Switch = 0;
        Color_Flag = 0;
    }

    //動き
    

    //回転
    if (rotate == 1)
    {
        timer += 0.5;
    }
    else if (rotate == 2)
    {
        timer -= 0.5;
    }


    //フラグ切り替えによる位置反転
    if (Switch == 0)
    {

        RedX = sin(timer * 0.07) * radius + x;
        RedY = cos(timer * 0.07) * radius + y;

        BlueX = -sin(timer * 0.07) * radius + x;
        BlueY = -cos(timer * 0.07) * radius + y;
    }
    else
    {
        RedX = -sin(timer * 0.07) * radius + x;
        RedY = -cos(timer * 0.07) * radius + y;

        BlueX = sin(timer * 0.07) * radius + x;
        BlueY = cos(timer * 0.07) * radius + y;
    }

    RandSwitch();
    RandRotate();
    Move();
}

void Boss::Move()
{
    Angle = atan2(P_Y - (y - C_Y), P_X - (x- C_X));
    //フラグが立っているときに自機に向かっていく
    x += cos(Angle) * 1.3;
    y += sin(Angle) * 1.3;
}

void Boss::RandSwitch()
{
    if (Switch_Flag == 0)
    {
        Switch = 0;
    }
    else
    {
        Switch = 1;
    }

    Switch_Count++;

    if (Switch_Count >= 240)
    {
        Switch_Rand = rand() % 2 + 1;
        Switch_Count = 0;
    }

    if (Switch_Rand == 1)
    {
        Switch_Flag = 1;
    }
    else
    {
        Switch_Flag = 0;
    }
}

void Boss::RandRotate()
{
    rotate_time++;

    if (rotate_time >= 360)
    {
        rotate_rand = rand() % 2 + 1;
        rotate_time = 0;
    }

    if (rotate_rand == 1)
    {
        rotate = 1;
    }
    else
    {
        rotate = 2;
    }
}

void Boss::RandColor()
{
}
