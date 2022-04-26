#include "Enemy.h"
#include <cstdlib>   
#include <time.h>

//ここから配列Ver
void Enemy::Update()
{
    Generation();//フラグが立ったら生成する

    Move();//ゲーム内の動作


}

void Enemy::Generation()//生成
{

    Flagged();//条件が整ったらフラグが立つ

    //生成する
    //敵の出現する座標と色の設定
        for (int i = 0; i<ENEMY_NUM;i++)
        {
            if (Enemy1[i].Flag == 0)
            {
                if (Enemy1[i].XY_rand == 1)
                {
                    if (Enemy1[i].X_rand == 1)
                    {
                        Enemy1[i].X = rand() % 100 - 830;
                    }
                    else
                    {
                        Enemy1[i].X = rand() % 100 + 2000;
                    }

                    Enemy1[i].Y = rand() % 700;
                }
                else
                {
                    if (Enemy1[i].Y_rand == 1)
                    {
                        Enemy1[i].Y = rand() % 200 - 930;
                    }
                    else
                    {
                        Enemy1[i].Y = rand() % 600 +900;
                    }

                    Enemy1[i].X = rand() % 1200;
                }
               
                Enemy1[i].R = 30;
                Enemy1[i].Patern = rand() % Appearance + 1;
                //Enemy1[i].Patern = 3;

                Enemy1[i].Type = rand() % TypeKinds + 1;//1:普通2：2撃3:
      //Enemy1[i].Type =1;

      //体力振り分け
                if (Enemy1[i].Type == 1)
                {
                    Enemy1[i].HP = 1;
                }
                else if(Enemy1[i].Type==2)
                {
                    Enemy1[i].HP = 2;
                }
                else if(Enemy1[i].Type==3)
                {
                    Enemy1[i].HP = 3;
                }
                else
                {
                    Enemy1[i].HP = 4;
                }
            }
        }
}

void Enemy::Intialize()//初期化
{
    //ランダム
    srand((unsigned)time(NULL));

    memset(Enemy1, 0, sizeof(Enemy1));

    //構造体初期化代入
    for (int i = 0; i<ENEMY_NUM; i++)
    {
        Enemy1[i] = { 0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0};

       // Enemy1[i].Timer = rand() % 0 - 500;
       // Enemy1[i].Flag = 1;
        Enemy1[i].XY_rand = rand() % 2 + 1;

        Enemy1[i].X_rand = rand() % 2 + 1;
        Enemy1[i].Y_rand = rand() % 2 + 1;
    }


 

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (Enemy1[i].X_rand == 1)
        {
        //    Enemy1[i].X = rand() % 100 - 830;
        }
        else
        {
         //   Enemy1[i].X = rand() % 100 + 2000;;
        }

        Appearance = 2;
        TypeKinds = 1;
        
       // Enemy1[i].Y = rand() % 700;
        Enemy1[i].R = 30;
        Enemy1[i].Patern = rand() % Appearance + 1;
        //Enemy1[i].Patern = 3;//デバック用
        Enemy1[i].Color_Flag = rand() % 2 + 1;
        Enemy1[i].Type = rand() % TypeKinds + 1;//1:普通2：2撃3:
        //Enemy1[i].Type =1;
        Enemy_Ge = 150;
       
        //体力振り分け
        if (Enemy1[i].Type == 1)
        {
            Enemy1[i].HP = 2;
        }
        else
        {
            Enemy1[i].HP = 1;
        }
    }
}

void Enemy::Flagged()//フラグ処理
{

  
    for (int i = 0; i<ENEMY_NUM;i++)
    {
        if (Enemy1[i].Flag == 0)
        {
            Enemy1[i].Timer++;
           // Enemy1[i].Timer++;
            //規定条件になったらフラグが立つ
            if (Enemy1[i].Timer >=(Enemy_Ge*i)-(i*0.5+TimeLost))
            {
                if (Enemy1[i].Die==0)
                {
                    //マップ内なら外に飛ばしてから出現
                    if (Enemy1[i].X - C_X > 0 || Enemy1[i].X-C_X < 1280)
                    {
                        //Enemy1[i].X = -400;
                    }

                    Enemy1[i].Flag = 1;
                    Enemy1[i].Timer = 0;

                    //パターン３の場合のみ毎フレーム自機の座標を見ない
                    if (Enemy1[i].Patern == 3)
                    {
                        Enemy1[i].Angle = atan2(P_Y - (Enemy1[i].Y - C_Y), P_X - (Enemy1[i].X - C_X));
                    }
                }
                //Enemy1[i].Timer = 0;
            }
        }
    }
}

void Enemy::Move()//敵の動作
{
    //キャラの座標毎フレーム確認
    //player.Controll();

    //自キャラに寄ってく
    //自と敵の方向を確認する
    for (int i = 0; i<ENEMY_NUM; i++)
   {
       // Enemy1[i].Angle = atan2(P_Y - (Enemy1[i].Y-C_Y), P_X - (Enemy1[i].X-C_X));
        //パターン３以外毎フレーム自機の座標を見る
        if (Enemy1[i].Patern != 3)
        {
            Enemy1[i].Angle = atan2(P_Y - (Enemy1[i].Y - C_Y), P_X - (Enemy1[i].X - C_X));
        }

        if (Enemy1[i].Flag == 1&&Enemy1[i].knock_back==0)
        {
            if (Enemy1[i].Patern == 1)
            {
                if (Stop_ == 0)
                {
                    //フラグが立っているときに自機に向かっていく
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 1.3;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 1.3;
                }
                Enemy1[i].R = 30;
            }
            else if (Enemy1[i].Patern == 2)
            {
                if (Stop_ == 0)
                {
                    //フラグが立っているときに自機に向かっていく
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 0.7;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 0.7;
                }
                Enemy1[i].R = 30;
            }
            else if (Enemy1[i].Patern == 3)
            {
                if (Stop_ == 0)
                {
                    //フラグが立っているときに最初に記憶した自機の位置に向かっていく（追尾しない）
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 2.0;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 2.0;
                }
                Enemy1[i].R = 20;
            }
            else if (Enemy1[i].Patern == 4)
            {
                if (Stop_ == 0)
                {
                    //フラグが立っているときに自機に向かっていく(でかい)
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 1.3;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 1.3;
                }
                Enemy1[i].R = 60;
            }
            else if (Enemy1[i].Patern == 5)
            {
                if (Stop_ == 0)
                {
                    //フラグが立っているときに自機に向かっていく
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 1.6;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 1.6;
                }
                Enemy1[i].R = 40;
            }
            else if (Enemy1[i].Patern == 6)
            {
                if (Stop_ == 0)
                {
                    //フラグが立っているときに自機に向かっていく
                    //Enemy1[i].X += cos(Enemy1[i].Angle) * 0.9;
                    //Enemy1[i].Y += sin(Enemy1[i].Angle) * 0.9;
                }
                Enemy1[i].R = 30;
            }
        }
        else if (Enemy1[i].knock_back == 1)
        {
            Enemy1[i].Knock_Time++;

            Enemy1[i].X -= cos(Enemy1[i].Angle) * 18;
            Enemy1[i].Y -= sin(Enemy1[i].Angle) * 18;

            if (Enemy1[i].Knock_Time >= 5)
            {
                Enemy1[i].knock_back = 0;
            }
        }
    }
}

void Enemy::Rear()//敵の後処理
{

}

void Enemy::LittleBoss_Generation()//生成処理
{

}

void Enemy::LittleBoss_Flagged()//フラグが立つまでの処理
{

}

void Enemy::LittleBoss_Move()//挙動
{

}
