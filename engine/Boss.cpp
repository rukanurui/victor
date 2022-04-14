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
	//Ø‚è‘Ö‚¦•Ï”
	Switch = 0;

    rotate = 1;
}

void Boss::Update()
{

    //F‚ÌØ‚è‘Ö‚¦
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

    //“®‚«
    

    //‰ñ“]
    if (rotate == 1)
    {
        timer += 0.5;
    }
    else if (rotate == 2)
    {
        timer -= 0.5;
    }


    //ƒtƒ‰ƒOØ‚è‘Ö‚¦‚É‚æ‚éˆÊ’u”½“]
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
