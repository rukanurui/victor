#include "Item.h"
#include <vcruntime_string.h>

//Player player;

void Item::Intialize()//������
{
    memset(LEG_, 0, sizeof(LEG_));

    //�\���̏��������
    for (int i = 0; i<10; i++)
    {
        LEG_[i] = { 0,0,0,200,200 };
    }

    LEG_[0].X = 300;
    LEG_[0].Y = 500;

    memset(ARM_, 0, sizeof(ARM_));

    //�\���̏��������
    for (int i = 0; i++; i < 10)
    {
        ARM_[i] = { 0,0,0,0,0 };
    }

    memset(STRONG_, 0, sizeof(STRONG_));

    //�\���̏��������
    for (int i = 0; i++; i < 10)
    {
        STRONG_[i] = { 0,0,0,0,0 };
    }

    memset(STUDY_, 0, sizeof(STUDY_));

    //�\���̏��������
    for (int i = 0; i++; i < 10)
    {
        STUDY_[i] = { 0,0,0,0,0 };
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
    if(LEG_->Flag==1)
    Leg_SpeedUp();

    if (ARM_->Flag == 1)
        Arm_SpeedUp();

    if (STRONG_->Flag == 1)
        StrongArm();

    if (STUDY_->Flag == 1)
        StudyUp();

    // player.Controll();
    // if(DESTOROY_->Flag==1)
    // Destroy();
}

void Item::Leg_SpeedUp()//�����x�A�b�v
{
 
        LEG_->Limit++;
        LEG_->Effect = 5;
    


    if (LEG_->Limit >= 600)
    {
        LEG_->Flag = 0;
        LEG_->Limit = 0;
    }
}

void Item::Arm_SpeedUp()//�r���x�A�b�v
{

}

void Item::StrongArm()//�G���ꔭ�œ|��
{

}

void Item::StudyUp()//�擾�o���l�A�b�v
{

}

void Item::Destroy()//��ʓ��̓G��|��
{

}
