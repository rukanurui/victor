#include "Boss.h"

void Boss::Initialize()
{
	HP = 10;
	x = 640;
	y = 360;

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

}

void Boss::RandSwitch()
{
}

void Boss::RandRotate()
{
}

void Boss::RandColor()
{
}
