#include "Item.h"
#include <vcruntime_string.h>
#include <stdlib.h>

//Player player;

void Item::Intialize()//������
{
    memset(Heart_, 0, sizeof(Heart_));

    //�\���̏��������
    for (int i = 0; i < 10; i++)
    {
        Heart_[i] = { -40,-40,0,0,0,0,0};
    }

    memset(Box_, 0, sizeof(Box_));

    //�\���̏��������
    for (int i = 0; i < 10; i++)
    {
        Box_[i] = { -40,-40,0,0,0,0,0,0,0};
    }
}

void Item::Update()//�X�V
{

    HEAL_Up();

    Box_Up();

    BarrierUp();
}

void Item::Leg_SpeedUp()//�����x�A�b�v
{

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

void Item::BarrierUp()
{

    if (BAR1.Flag == 1)
    {
        BAR1.Limit++;

        //�K�莞�ԂɂȂ�������ʂ��Ȃ���
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
        //����������쓮
        if (Box_[i].HitFlag == 1)
        {
            if (Box_[i].Select == 1)
            {
                //ARM���x
                ARM1.Effect2 = ARM1.Effect;
            }
            else  if (Box_[i].Select == 2)
            {
                //�����x
                LEG1.Effect2 = LEG1.Effect;
            }
            else  if (Box_[i].Select == 3)
            {
                //�G�ꔭ
                STU1.Effect2 = STU1.Effect;
            }
            else  if (Box_[i].Select == 4)
            {
                //�o���A
                BAR1.Flag = 1;
            }

            Box_[i].HitFlag = 0;
        }
        else
        {
            //�o���J�n�̃t���b�O
            if (Box_[i].Flag == 1)
            {
                
            }
            else
            {
                Box_[i].Time++;

                Box_[i].X_Rand = rand() % 2 + 1;
                Box_[i].Y_Rand = rand() % 2 + 1;

                //X���ǂ����ɏo����
                if (Box_[i].X_Rand == 1)
                {
                    Box_[i].X = rand() % 600 - 300;
                }
                else
                {
                    Box_[i].X = rand() % 600 + 600;
                }

                //Y���ǂ����ɏo����
                if (Box_[i].Y_Rand == 1)
                {
                    Box_[i].Y = rand() % 300 - 600;
                }
                else
                {
                    Box_[i].Y = rand() % 300 + 600;
                }

                //�K�莞�ԂɂȂ�����o��
                if (Box_[i].Time >= 3500 * (i + 1))
                {
                 
                    Box_[i].Time = 0;

                   

                    //�\�̓����_���I�����ł̂�
                    Box_[i].Select = rand() % 4 + 1;
                    //Box_[i].Select =4;

                    if (Box_[i].Select == 1)
                    {
                        //ARM���x
                        ARM1.Effect += 0.25;
                    }
                    else  if (Box_[i].Select == 2)
                    {
                        //�����x
                        LEG1.Effect += 2;
                    }
                    else  if (Box_[i].Select == 3)
                    {
                        //�o���l
                        STU1.Effect += 1;
                    }
                    else  if (Box_[i].Select == 4)
                    {
                        //�o���A
                    }
                    Box_[i].Flag = 1;

                }
            }
        }
    }
}
