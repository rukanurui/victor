#include "Item.h"
#include <vcruntime_string.h>
#include <stdlib.h>

//Player player;

void Item::Intialize()//������
{
  //  memset(LEG_, 0, sizeof(LEG_));

    //�\���̏��������
   /// for (int i = 0; i<10; i++)
  //  {
        LEG_ = { 0,0,0,200,200 };
   // }

    LEG_.X = 300;
    LEG_.Y = 500;

    memset(ARM_, 0, sizeof(ARM_));

    //�\���̏��������
    for (int i = 0; i<10;i++)
    {
        ARM_[i] = { 0,0,0,0,0 };
    }

    memset(STRONG_, 0, sizeof(STRONG_));

    //�\���̏��������
    for (int i = 0; i<10; i++)
    {
        STRONG_[i] = { 0,0,0,0,0 };
    }

    memset(STUDY_, 0, sizeof(STUDY_));

    //�\���̏��������
    for (int i = 0; i<10;i++)
    {
        STUDY_[i] = { 0,0,0,0,0 };
    }

    memset(Heart_, 0, sizeof(Heart_));

    //�\���̏��������
    for (int i = 0; i < 10; i++)
    {
        Heart_[i] = { 0,0,0,0,0,0,0};
    }

    /*
    memset(DESTOROY_, 0, sizeof(DESTOROY_));

    //�\���̏��������
    for (int i = 0; i++; i < 10)
    {
        DESTOROY_[i] = { 0,0,0,0};
    }
    */
}

void Item::Update()//�X�V
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

void Item::Leg_SpeedUp()//�����x�A�b�v
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

void Item::Arm_SpeedUp()//�r���x�A�b�v
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

void Item::StrongArm()//�G���ꔭ�œ|��
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

void Item::StudyUp()//�擾�o���l�A�b�v
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

void Item::Destroy()//��ʓ��̓G��|��
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
