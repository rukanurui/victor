#include "Player.h"


void Player::Controll()
{

    GamePad* GP = nullptr;
    GP = new GamePad();

   // Item* item = nullptr;
  //  item = new Item();

    //�p�b�h�̍X�V
    GP->Update();

    
    //���� �F�̐؂�ւ�
    if (GP->iPad_A == 1 && Switch == 0 && Old_iPad_A == 0&&scene_==1&&WrongFlag==0)
    {
        Switch = 1;
    }
    else if (GP->iPad_A == 1 && Switch == 1 && Old_iPad_A == 0&&scene_==1&&WrongFlag==0)
    {
        Switch = 0;
    }
    else if (GP->iPad_A == 1 && Old_iPad_A == 0 && scene_ == 0&&RuleFlag==0)
    {
        //scene_ = 1;
        RuleFlag = 1;
    }
    else if (GP->iPad_A == 1 && Old_iPad_A == 0 && scene_ == 2)
    {
        scene_ = 0;
    }
    else if (GP->iPad_A == 1 && Old_iPad_A == 0 && scene_ == 0 && RuleFlag == 1)
    {
        RuleFlag = 2;
    }
    else if (GP->iPad_A == 1 && Old_iPad_A == 0 && scene_ == 0 && RuleFlag == 2)
    {
        scene_ = 1;
        RuleFlag = 0;
    }
    else if (GP->iPad_A == 1 && Old_iPad_A == 0 && scene_ == 3)
    {
        scene_ = 0;
    }
    //  GP.vibration.wLeftMotorSpeed = 65535;

     // XInputSetState(0, &GP.vibration);

      //�g���K�[�����̂��߂̋L��
    Old_iPad_left = GP->iPad_left, Old_iPad_right = GP->iPad_right, iOld_Pad_up = GP->iPad_up, Old_iPad_down = GP->iPad_down;
    Old_iPad_leftshoulder = GP->iPad_leftshoulder, Old_iPad_rightshoulder = GP->iPad_rightshoulder;
    Old_iPad_A = GP->iPad_A, Old_iPad_B = GP->iPad_B, Old_iPad_X = GP->iPad_X, Old_iPad_Y = GP->iPad_Y;

   // if(Map_X)
   // 
   
    if (scene_ == 1)
    {

       


        if (GP->state.Gamepad.sThumbLX != 0 || GP->state.Gamepad.sThumbLY != 0)//�Q�[���p�b�h�A�i���O�X�e�B�b�N���͎�����
        {

            if (WrongFlag == 0)
            {
                //���̐���
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

                //�c�̐���

                if (Map_Y < 720 && Map_Y>-360 && Central_y <= 365 && Central_y >= 355)
                {
                    Map_Y -= static_cast<FLOAT>(GP->state.Gamepad.sThumbLY / 32767.0 * (2.0f + Effect_));
                }
                else
                {
                    if (Map_Y >= 720)Map_Y -= 1;
                    else if (Map_Y <= -360)Map_Y += 1;


                    if (Central_y > 45 && Central_y < 655)Central_y -= static_cast<FLOAT>(GP->state.Gamepad.sThumbLY / 32767.0 * (2.0f + Effect_));
                    else if (Central_y >= 655)Central_y -= 1;
                    else if (Central_y <= 45)Central_y += 1;
                }


            }
        }

        //��]
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
    }
  

    //�t���O�؂�ւ��ɂ��ʒu���]
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

    Exp2();
}

void Player::Initialize()
{
    //��]���邽�߂̒l
     timer = 0;
    //�؂�ւ��ϐ�
     Switch = 0;

    //�ԋ����W
     //Player_RedX = 0;
     //Player_RedY = 0;

     Red_R = 20;
     Blue_R = 20;

    //�������W
     //Player_BlueX = 0;
     //Player_BlueY = 0;

    //���̃t���O�֘A
     Red_Lv = 1;
     Blue_Lv = 1;

     Radius = 100;

     HP = 3;
     invincibleTime = 0;
     invincibleFlag = 0;

     invincible_armFlag = 0;
     invincible_armTime = 0;

     Map_X = 0;
     Map_Y = 0;


    // Effect_;
  //  float Effect_2;
   // float Effect_3;

   // int scene_ = 0;

     WrongFlag = 0;//�ԈႦ�t���b�O
     WrongTimer = 0;//�ԈႦ�S������

    //�o���l
     Exp = 0;
     Level = 1;
     Level_demo = 1;

     //��]����~�̑傫��
     Player_radius = 100;

     memset(Exp1, 0, sizeof(Exp1));

     //�\���̏��������
     for (int i = 0; i < EXP_NUM; i++)
     {
         Exp1[i] = {0,0,0,0,0,0,0};
     }

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

    //�p�b�h�̍X�V
    GP->Update();

    //�t���O����������K�莞�Ԃ܂Ők����
    if (WrongFlag == 1)
    {
        WrongTimer++;

        GP->vibration.wLeftMotorSpeed = 65535;

        XInputSetState(0, &GP->vibration);

        if (WrongTimer >= 20)
        {
            WrongFlag = 0;
            WrongTimer = 0;
            invincible_armFlag = 1;
        }
    }
}

void Player::invincible()
{
    //�{�̖̂��G����
    if (invincibleFlag == 1)
    {
        invincibleTime += 1;

        if (invincibleTime >= 100)
        {
            invincibleFlag = 0;
            invincibleTime = 0;
        }
    }

    //arm�̖��G����
    if (invincible_armFlag == 1)
    {
        invincible_armTime += 1;

        if (invincible_armTime >= 100)
        {
            invincible_armFlag = 0;
            invincible_armTime = 0;
        }
    }
    else
    {
        invincible_armTime = 0;
    }


}

void Player::Exp2()
{
    //Exp���𐶐�����
     //�o���l
    if (Exp > Level*12)
    {
       Exp = 0;
       Level += 1+Effect_3;

       //���ł̂݃����_���Ŕ\�͂�I��
       if (Level_demo == 1)
       {
           Red_Lv += 1;
       }
       else if (Level_demo == 2)
       {
           Blue_Lv += 1;
       }
       else
       {
           Player_radius += 20;
       }
    }
    else
    {
        Level_demo = rand() % 3 + 1;
    }

    for (int i = 0; i < EXP_NUM; i++)
    {
        if (Exp1[i].Flag == 0)
        {
           
            Exp1[i].R = 10;
            Exp1[i].X_rand = rand() % 2 + 1;
            if (Exp1[i].X_rand == 1)
            {
                Exp1[i].X = rand() % 600-300;
            }
            else
            {
                Exp1[i].X = rand() % 900+900;
            }
            Exp1[i].Y = rand() % 720;

            Exp1[i].Time++;
            if (Exp1[i].Time >= i * 500)
            {
                Exp1[i].Time = 0;
                Exp1[i].Flag = 1;

               
            }
        }
        else
        {

        }
    }
}

void Player::LevelUp()
{
}
