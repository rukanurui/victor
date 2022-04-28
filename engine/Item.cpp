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

    LEG1 = { 0,0,0,0,0,0 };
    ARM1 = { 0,0,0,0,0,0 };
    STR1 = { 0,0,0,0,0,0 };
    STU1 = { 0,0,0,0,0,0,};
    BAR1 = { 0,0,0,0,0,0,};
    DESTROY_ = { 0,0,0,0,0 };
    ROLL1 = { 0,0,0,0,0 };
    ATT1 = { 0,0,0,0,0,0,0,0,0 };
}

void Item::Update()//�X�V
{

    HEAL_Up();

    Box_Up();

    BarrierUp();

    AttackUp();

    StrongArm();

    SelectUp();

   // Destroy();
}

void Item::Leg_SpeedUp()//�����x�A�b�v
{

}

void Item::Arm_SpeedUp()//�r���x�A�b�v
{
   
}

void Item::StrongArm()//�G���ꔭ�œ|��
{
    if (STR1.Flag == 1)
    {
        STR1.Effect = 1;
    }
    else
    {
        STR1.Effect = 0;
    }
}

void Item::StudyUp()//�擾�o���l�A�b�v
{
    
}

void Item::DestroyUp()//��ʓ��̓G��|��
{
    if (DESTROY_.Flag == 1)
    {
        //DESTROY_.Flag = 0;
    }
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



            
            //���ʏ����������ɋl�߂�
            if (UI_Flag != BAR1.UI)
            {

                if (BAR1.UI == 1)
                {


                    if (ARM1.UI > 3)
                    {
                        ARM1.UI -= 1;
                    }
                    else if (LEG1.UI > 3)
                    {
                        LEG1.UI -= 1;
                    }
                    else if (STU1.UI > 3)
                    {
                        STU1.UI -= 1;
                    }
                    else if (ATT1.UI > 3)
                    {
                        ATT1.UI -= 1;
                    }
                    else if (STR1.UI > 3)
                    {
                        STR1.UI -= 1;
                    }
                    else if (ROLL1.UI > 3)
                    {
                        ROLL1.UI -= 1;
                    }
                }
                else
                {
                    if (ARM1.UI > 2 && ARM1.UI != 1)
                    {
                        ARM1.UI -= 1;
                    }
                    else if (LEG1.UI > 2 && LEG1.UI != 1)
                    {
                        LEG1.UI -= 1;
                    }
                    else if (STU1.UI > 2 && STU1.UI != 1)
                    {
                        STU1.UI -= 1;
                    }
                    else if (ATT1.UI > 2 && ATT1.UI != 1)
                    {
                        ATT1.UI -= 1;
                    }
                    else if (STR1.UI > 2 && STR1.UI != 1)
                    {
                        STR1.UI -= 1;
                    }
                    else if (ROLL1.UI > 2 && ROLL1.UI != 1)
                    {
                        ROLL1.UI -= 1;
                    }
                }
            }
            BAR1.UI = 0;
            if (UI_Flag != 0)UI_Flag -= 1;

        }
    }

}

void Item::AttackUp()
{
    if (ATT1.Flag == 1)
    {
        if (ATT1.Effect == 1)
        {
            ATT1.Limit++;
            if (ATT1.Limit >= 100)
            {
                ATT1.Effect = 0;
                ATT1.Limit = 0;
            }
        }
        else
        {
            ATT1.Limit++;
            if (ATT1.Limit >= 1000 - (ATT1.lv * 100))
            {
                ATT1.Effect = 1;
                ATT1.Limit = 0;
            }
        }
    }
}

void Item::RollUp()
{
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
            if (SelectTime == 0)Heart_[i].Time++;

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
            NowAbility=Box_[i].Select;

            
            if (Box_[i].Select == 1)
            {
                //ARM���x
                if(Add==1)ARM1.Effect += 0.25;

                Add = 0;

                //   NowAbility = 1;

            }
            else  if (Box_[i].Select == 2)
            {
                //�����x
                if (Add == 1) LEG1.Effect += 2;

                Add = 0;
                //  NowAbility = 2;

            }
            else  if (Box_[i].Select == 3)
            {
                //�o���l
                if (Add == 1)STU1.Effect += 1;
                Add = 0;
                //  NowAbility = 3;

            }
            else  if (Box_[i].Select == 4)
            {
                //�o���A
              //  NowAbility = 4;
                Add = 0;
            }
            else  if (Box_[i].Select == 5)
            {
                //�o���A
             //   NowAbility = 5;
                Add = 0;
            }
            else if (Box_[i].Select == 6)
            {
                //  NowAbility = 6;
                if (Add == 1)STR1.Effect += 1;
                Add = 0;
            }
            else if (Box_[i].Select == 7)
            {
                if (Add == 1)ROLL1.Effect += 20;
                Add = 0;
                //  NowAbility = 7;

            }
            else if (Box_[i].Select == 8)
            {
                //�S�j��
              //  NowAbility = 8;
                Add = 0;
            }

            if (Box_[i].Select == 1&&SelectTime==0&&ARM1.Select!=0)
            {
                //ARM���x
                ARM1.Effect2 = ARM1.Effect;
            }
            else  if (Box_[i].Select == 2 && SelectTime == 0&&LEG1.Select!=0)
            {
                //�����x
                LEG1.Effect2 = LEG1.Effect;
            }
            else  if (Box_[i].Select == 3 && SelectTime == 0&&STU1.Select!=0)
            {
                //�G�ꔭ
                STU1.Effect2 = STU1.Effect;
            }
            else  if (Box_[i].Select == 4 && SelectTime == 0&&BAR1.Select!=0)
            {
                //�o���A
                BAR1.Flag = 1;
            }
            else  if (Box_[i].Select == 5 && SelectTime == 0&&ATT1.Select!=0)
            {
                //�r��
                ATT1.Flag = 1;
                ATT1.Effect = 1;
            }
            else  if (Box_[i].Select == 6 && SelectTime == 0&&STR1.Select!=0)
            {
                //�ꔭ
                STR1.Flag = 1;
                STR1.Effect2 = STR1.Effect;
            }
            else if (Box_[i].Select == 7 && SelectTime == 0&&ROLL1.Select!=0)
            {
                ROLL1.Effect2 =ROLL1.Effect;
                ROLL1.Flag = 1;
            }
            else if (Box_[i].Select == 8 && SelectTime == 0&&DESTROY_.Select!=0)
            {
                DESTROY_.Flag = 1;
                DESTROY_.Select = 0;
            }






            //�I�яI�������J�n
            if (SelectTime == 0)
            {
                Box_[i].HitFlag = 0;
            }
        }
        else
        {
            //�o���J�n�̃t���b�O
            if (Box_[i].Flag == 1)
            {
                
            }
            else
            {
                if(SelectTime==0)Box_[i].Time++;

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
                if (Box_[i].Time >= 1500 * (i + 1))
                {
                 
                    Box_[i].Time = 0;

                   

                    
                    Box_[i].Flag = 1;

                }
            }
        }
    }
}

void Item::SelectUp()
{
    //�I��������
    if (SelectTime == 1)
    {
       // Decision = deci_;
       // Decision = 1;

        if (NowAbility == 1&&Decision==1)
        {
            ARM1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
           // UI_Flag += 1;
            
            if (ARM1.UI == 0)
            {
                UI_Flag += 1;


                ARM1.UI = UI_Flag;
              
            }
        }
        else  if (NowAbility == 2 && Decision == 1)
        {
            LEG1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
           
            if (LEG1.UI == 0)
            {
                UI_Flag += 1;


                LEG1.UI = UI_Flag;
               
            }
        }
        else  if (NowAbility == 3 && Decision == 1)
        {
            STU1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
          
            if (STU1.UI == 0)
            {
                UI_Flag += 1;

                STU1.UI = UI_Flag;
            }
        }
        else  if (NowAbility == 4 && Decision == 1)
        {
            BAR1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
           // 
            SelectTime = 0;

            if (BAR1.UI == 0)
            {
                UI_Flag += 1;
                BAR1.UI = UI_Flag;
            }
        }
        else  if (NowAbility == 5 && Decision == 1)
        {
            ATT1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
           
            if (ATT1.UI == 0)
            {
                UI_Flag += 1;

                ATT1.UI = UI_Flag;
            }
        }
        else  if (NowAbility == 6 && Decision == 1)
        {
            STR1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
            
            if (STR1.UI == 0)
            {
                UI_Flag += 1;

                STR1.UI = UI_Flag;
            }
        }
        else  if (NowAbility == 7 && Decision == 1)
        {
            ROLL1.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
           
            if (ROLL1.UI == 0)
            {
                UI_Flag += 1;

                ROLL1.UI = UI_Flag;
            }

        }
        else  if (NowAbility == 8 && Decision == 1)
        {
            DESTROY_.Select = 1;//�擾������������{�^���������ꂽ������
            Decision = 0;
            SelectTime = 0;
            
            if (DESTROY_.UI == 0)
            {
                UI_Flag += 1;

                DESTROY_.UI = UI_Flag;
            }
        }

        if (Decision == 2)//�擾���Ȃ�
        {
            Decision = 0;
            SelectTime = 0;

        }

    }
    else
    {
        NowAbility = 0;
    }
}
