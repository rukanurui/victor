#include "Item.h"
#include <vcruntime_string.h>
#include <stdlib.h>

//Player player;

void Item::Intialize()//初期化
{
    memset(Heart_, 0, sizeof(Heart_));

    //構造体初期化代入
    for (int i = 0; i < 10; i++)
    {
        Heart_[i] = { -40,-40,0,0,0,0,0};
    }

    memset(Box_, 0, sizeof(Box_));

    //構造体初期化代入
    for (int i = 0; i < 10; i++)
    {
        Box_[i] = { -40,-40,0,0,0,0,0,0,0};
    }
}

void Item::Update()//更新
{

    HEAL_Up();

    Box_Up();

    BarrierUp();
}

void Item::Leg_SpeedUp()//足速度アップ
{

}

void Item::Arm_SpeedUp()//腕速度アップ
{
   
}

void Item::StrongArm()//敵を一発で倒す
{
 
}

void Item::StudyUp()//取得経験値アップ
{
    
}

void Item::Destroy()//画面内の敵を倒す
{

}

void Item::BarrierUp()
{

    if (BAR1.Flag == 1)
    {
        BAR1.Limit++;

        //規定時間になったら効果をなくす
        if (BAR1.Limit >= 500)
        {
            BAR1.Flag = 0;
            BAR1.Limit = 0;
        }
    }

}



void Item::HEAL_Up()
{
   

    for (int i = 0; i < 10; i++)
    {
       
        if (Heart_[i].Flag == 1)
        {
            
        }
        else
        {
            Heart_[i].Time++;

            if (Heart_[i].Time >= 700 * (i + 1))
            {
                Heart_[i].Time=0;
             
                Heart_[i].Flag = 1;
            }
            else
            {
                Heart_[i].X_Rand = rand() % 2 + 1;
                Heart_[i].Y_Rand = rand() % 2 + 1;

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
        }
    }
}

void Item::Box_Up()
{
    for (int i = 0; i < 10; i++)
    {
        //当たったら作動
        if (Box_[i].HitFlag == 1)
        {
            if (Box_[i].Select == 1)
            {
                //ARM速度
                ARM1.Effect2 = ARM1.Effect;
            }
            else  if (Box_[i].Select == 2)
            {
                //足速度
                LEG1.Effect2 = LEG1.Effect;
            }
            else  if (Box_[i].Select == 3)
            {
                //敵一発
                STU1.Effect2 = STU1.Effect;
            }
            else  if (Box_[i].Select == 4)
            {
                //バリア
                BAR1.Flag = 1;
            }

            Box_[i].HitFlag = 0;
        }
        else
        {
            //出現開始のフラッグ
            if (Box_[i].Flag == 1)
            {
                
            }
            else
            {
                Box_[i].Time++;

                Box_[i].X_Rand = rand() % 2 + 1;
                Box_[i].Y_Rand = rand() % 2 + 1;

                //X軸どっちに出現か
                if (Box_[i].X_Rand == 1)
                {
                    Box_[i].X = rand() % 600 - 300;
                }
                else
                {
                    Box_[i].X = rand() % 600 + 600;
                }

                //Y軸どっちに出現か
                if (Box_[i].Y_Rand == 1)
                {
                    Box_[i].Y = rand() % 300 - 600;
                }
                else
                {
                    Box_[i].Y = rand() % 300 + 600;
                }

                //規定時間になったら出現
                if (Box_[i].Time >= 3500 * (i + 1))
                {
                 
                    Box_[i].Time = 0;

                   

                    //能力ランダム選択α版のみ
                    Box_[i].Select = rand() % 4 + 1;
                    //Box_[i].Select =4;

                    if (Box_[i].Select == 1)
                    {
                        //ARM速度
                        ARM1.Effect += 0.25;
                    }
                    else  if (Box_[i].Select == 2)
                    {
                        //足速度
                        LEG1.Effect += 2;
                    }
                    else  if (Box_[i].Select == 3)
                    {
                        //経験値
                        STU1.Effect += 1;
                    }
                    else  if (Box_[i].Select == 4)
                    {
                        //バリア
                    }
                    Box_[i].Flag = 1;

                }
            }
        }
    }
}
