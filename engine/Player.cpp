#include "Player.h"


void Player::Controll()
{

    GamePad* GP = nullptr;
    GP = new GamePad();

   // Item* item = nullptr;
  //  item = new Item();

    //パッドの更新
    GP->Update();

    
    //操作 色の切り替え
    if (GP->iPad_A == 1 && Switch == 0 && Old_iPad_A == 0)
    {
        Switch = 1;
    }
    else if (GP->iPad_A == 1 && Switch == 1 && Old_iPad_A == 0)
    {
        Switch = 0;
    }

    //  GP.vibration.wLeftMotorSpeed = 65535;

     // XInputSetState(0, &GP.vibration);

      //トリガー処理のための記憶
    Old_iPad_left = GP->iPad_left, Old_iPad_right = GP->iPad_right, iOld_Pad_up = GP->iPad_up, Old_iPad_down = GP->iPad_down;
    Old_iPad_leftshoulder = GP->iPad_leftshoulder, Old_iPad_rightshoulder = GP->iPad_rightshoulder;
    Old_iPad_A = GP->iPad_A, Old_iPad_B = GP->iPad_B, Old_iPad_X = GP->iPad_X, Old_iPad_Y = GP->iPad_Y;

   // if(Map_X)

    if (GP->state.Gamepad.sThumbLX != 0 || GP->state.Gamepad.sThumbLY != 0)//ゲームパッドアナログスティック入力時処理
    {

        if (WrongFlag == 0)
        {
            //横の制限
            if (Map_X > -742 && Map_X < 680 && Central_x <= 645 && Central_x >= 635)
            {
                Map_X += static_cast<FLOAT>(GP->state.Gamepad.sThumbLX / 32767.0 * (2.0f + Effect_));
            }
            else
            {
                if (Map_X <= -742)Map_X += 1;
                else if (Map_X >= 680)Map_X -= 1;


                if (Central_x > 25 && Central_x < 1255)Central_x += static_cast<FLOAT>(GP->state.Gamepad.sThumbLX / 32767.0 * (2.0f + Effect_));
                else if (Central_x <= 25) Central_x += 1;
                else if (Central_x >= 1255)Central_x -= 1;

            }

            //縦の制限
            //Map_Y -= static_cast<FLOAT>(GP->state.Gamepad.sThumbLY / 32767.0 * (2.0f + Effect_));

            if (Central_y > 25 && Central_y < 695)Central_y -= static_cast<FLOAT>(GP->state.Gamepad.sThumbLY / 32767.0 * (2.0f + Effect_));
            else if (Central_y <= 25)Central_y += 1;
            else if (Central_y >= 695)Central_y -= 1;
        }
    }

    //回転
    if (WrongFlag == 0)
    {
        if (GP->iPad_leftshoulder == 1)
        {
            timer += 0.5 + Effect_2;
        }

        if (GP->iPad_rightshoulder == 1)
        {
            timer -= 0.5 + Effect_2;
        }
    }


    //フラグ切り替えによる位置反転
    if (Switch == 0)
    {

        Player_RedX = sin(timer * 0.07) * Player_radius + Central_x;
        Player_RedY = cos(timer * 0.07) * Player_radius + Central_y;

        Player_BlueX = -sin(timer * 0.07) * Player_radius + Central_x;
        Player_BlueY = -cos(timer * 0.07) * Player_radius + Central_y;
    }
    else
    {
        Player_RedX = -sin(timer * 0.07) * Player_radius + Central_x;
        Player_RedY = -cos(timer * 0.07) * Player_radius + Central_y;

        Player_BlueX = sin(timer * 0.07) * Player_radius + Central_x;
        Player_BlueY = cos(timer * 0.07) * Player_radius + Central_y;
    }


    Wrong();

    invincible();
}

void Player::Initialize()
{
   
}

void Player::Shake()
{
   
    if (WrongFlag == 0)
    {
        WrongFlag = 1;
  }
    else
    {
        WrongTimer =0;
    }

   
}

void Player::Wrong()
{
    GamePad* GP = nullptr;
    GP = new GamePad();

    //パッドの更新
    GP->Update();

    //フラグが立ったら規定時間まで震える
    if (WrongFlag == 1)
    {
        WrongTimer++;

        GP->vibration.wLeftMotorSpeed = 65535;

        XInputSetState(0, &GP->vibration);

        if (WrongTimer >= 60)
        {
            WrongFlag = 0;
            WrongTimer = 0;
        }
    }
}

void Player::invincible()
{
    if (invincibleFlag == 1)
    {
        invincibleTime += 1;

        if (invincibleTime >= 100)
        {
            invincibleFlag = 0;
            invincibleTime = 0;
        }
    }
}
