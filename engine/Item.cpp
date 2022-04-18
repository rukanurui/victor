#include "Item.h"
#include <vcruntime_string.h>
#include <stdlib.h>

//Player player;

void Item::Intialize()//初期化
{
  //  memset(LEG_, 0, sizeof(LEG_));

    //構造体初期化代入
   /// for (int i = 0; i<10; i++)
  //  {
        LEG_ = { 0,0,0,200,200 };
   // }

    LEG_.X = 300;
    LEG_.Y = 500;

    memset(ARM_, 0, sizeof(ARM_));

    //構造体初期化代入
    for (int i = 0; i<10;i++)
    {
        ARM_[i] = { 0,0,0,0,0 };
    }

    memset(STRONG_, 0, sizeof(STRONG_));

    //構造体初期化代入
    for (int i = 0; i<10; i++)
    {
        STRONG_[i] = { 0,0,0,0,0 };
    }

    memset(STUDY_, 0, sizeof(STUDY_));

    //構造体初期化代入
    for (int i = 0; i<10;i++)
    {
        STUDY_[i] = { 0,0,0,0,0 };
    }

    memset(Heart_, 0, sizeof(Heart_));

    //構造体初期化代入
    for (int i = 0; i < 10; i++)
    {
        Heart_[i] = { 0,0,0,0,0,0,0};
    }

    /*
    memset(DESTOROY_, 0, sizeof(DESTOROY_));

    //構造体初期化代入
    for (int i = 0; i++; i < 10)
    {
        DESTOROY_[i] = { 0,0,0,0};
    }
    */
}

void Item::Update()//更新
{
    if (LEG_.Flag == 1)
    {
        Leg_SpeedUp();
    }

    if (ARM_->Flag == 1)
        Arm_SpeedUp();

    if (STRONG_->Flag == 1)
        StrongArm();

    if (STUDY_->Flag == 1)
        StudyUp();

    HEAL_Up();

    //HEAL();
    // player.Controll();
    // if(DESTOROY_->Flag==1)
    // Destroy();
}

void Item::Leg_SpeedUp()//足速度アップ
{
 
        LEG_.Limit++;
        LEG_.Effect = 5;
    


    if (LEG_.Limit >= 600)
    {
        LEG_.Flag = 0;
        LEG_.Limit = 0;
        LEG_.Effect = 0;
    }
}

void Item::Arm_SpeedUp()//腕速度アップ
{
    ARM_->Limit++;
    ARM_->Effect =2;



    if (ARM_->Limit >= 600)
    {
        ARM_->Flag = 0;
        ARM_->Limit = 0;
        ARM_->Effect = 0;
    }
}

void Item::StrongArm()//敵を一発で倒す
{
    STRONG_->Limit++;
    STRONG_->Effect = 1;



    if (STRONG_->Effect==600)
    {
        STRONG_->Flag = 0;
        STRONG_->Limit = 0;
        STRONG_->Effect = 0;
    }
}

void Item::StudyUp()//取得経験値アップ
{
    STUDY_->Limit++;
    STUDY_->Effect = 1;



    if (STUDY_->Effect == 600)
    {
        STUDY_->Flag = 0;
        STUDY_->Limit = 0;
        STUDY_->Effect = 0;
    }
}

void Item::Destroy()//画面内の敵を倒す
{

}



void Item::HEAL_Up()
{
    Heart_[0].Time++;

    for (int i = 0; i < 10; i++)
    {
        if (Heart_[i].Flag == 1)
        {
            
        }
        else
        {
            if (Heart_[0].Time >= 700 * (i + 1))
            {
                Heart_[i].Flag = 1;
                if (Heart_[i].X_Rand == 1)
                {
                    Heart_[i].X = rand() % 600 - 300;
                }
                else
                {
                    Heart_[i].X = rand() % 600 + 300;
                }

                if (Heart_[i].Y_Rand == 1)
                {
                    Heart_[i].Y = rand() % 600 - 300;
                }
                else
                {
                    Heart_[i].Y = rand() % 600 + 300;
                }
            }
            else
            {
                Heart_[i].X_Rand = rand() % 2 + 1;
                Heart_[i].Y_Rand = rand() % 2 + 1;
            }
        }
    }
}
