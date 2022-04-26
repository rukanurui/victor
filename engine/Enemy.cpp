#include "Enemy.h"
#include <cstdlib>   
#include <time.h>

//��������z��Ver
void Enemy::Update()
{
    Generation();//�t���O���������琶������

    Move();//�Q�[�����̓���


}

void Enemy::Generation()//����
{

    Flagged();//��������������t���O������

    //��������
    //�G�̏o��������W�ƐF�̐ݒ�
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

                Enemy1[i].Type = rand() % TypeKinds + 1;//1:����2�F2��3:
      //Enemy1[i].Type =1;

      //�̗͐U�蕪��
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

void Enemy::Intialize()//������
{
    //�����_��
    srand((unsigned)time(NULL));

    memset(Enemy1, 0, sizeof(Enemy1));

    //�\���̏��������
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
        //Enemy1[i].Patern = 3;//�f�o�b�N�p
        Enemy1[i].Color_Flag = rand() % 2 + 1;
        Enemy1[i].Type = rand() % TypeKinds + 1;//1:����2�F2��3:
        //Enemy1[i].Type =1;
        Enemy_Ge = 150;
       
        //�̗͐U�蕪��
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

void Enemy::Flagged()//�t���O����
{

  
    for (int i = 0; i<ENEMY_NUM;i++)
    {
        if (Enemy1[i].Flag == 0)
        {
            Enemy1[i].Timer++;
           // Enemy1[i].Timer++;
            //�K������ɂȂ�����t���O������
            if (Enemy1[i].Timer >=(Enemy_Ge*i)-(i*0.5+TimeLost))
            {
                if (Enemy1[i].Die==0)
                {
                    //�}�b�v���Ȃ�O�ɔ�΂��Ă���o��
                    if (Enemy1[i].X - C_X > 0 || Enemy1[i].X-C_X < 1280)
                    {
                        //Enemy1[i].X = -400;
                    }

                    Enemy1[i].Flag = 1;
                    Enemy1[i].Timer = 0;

                    //�p�^�[���R�̏ꍇ�̂ݖ��t���[�����@�̍��W�����Ȃ�
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

void Enemy::Move()//�G�̓���
{
    //�L�����̍��W���t���[���m�F
    //player.Controll();

    //���L�����Ɋ���Ă�
    //���ƓG�̕������m�F����
    for (int i = 0; i<ENEMY_NUM; i++)
   {
       // Enemy1[i].Angle = atan2(P_Y - (Enemy1[i].Y-C_Y), P_X - (Enemy1[i].X-C_X));
        //�p�^�[���R�ȊO���t���[�����@�̍��W������
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
                    //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 1.3;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 1.3;
                }
                Enemy1[i].R = 30;
            }
            else if (Enemy1[i].Patern == 2)
            {
                if (Stop_ == 0)
                {
                    //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 0.7;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 0.7;
                }
                Enemy1[i].R = 30;
            }
            else if (Enemy1[i].Patern == 3)
            {
                if (Stop_ == 0)
                {
                    //�t���O�������Ă���Ƃ��ɍŏ��ɋL���������@�̈ʒu�Ɍ������Ă����i�ǔ����Ȃ��j
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 2.0;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 2.0;
                }
                Enemy1[i].R = 20;
            }
            else if (Enemy1[i].Patern == 4)
            {
                if (Stop_ == 0)
                {
                    //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���(�ł���)
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 1.3;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 1.3;
                }
                Enemy1[i].R = 60;
            }
            else if (Enemy1[i].Patern == 5)
            {
                if (Stop_ == 0)
                {
                    //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���
                    Enemy1[i].X += cos(Enemy1[i].Angle) * 1.6;
                    Enemy1[i].Y += sin(Enemy1[i].Angle) * 1.6;
                }
                Enemy1[i].R = 40;
            }
            else if (Enemy1[i].Patern == 6)
            {
                if (Stop_ == 0)
                {
                    //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���
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

void Enemy::Rear()//�G�̌㏈��
{

}

void Enemy::LittleBoss_Generation()//��������
{

}

void Enemy::LittleBoss_Flagged()//�t���O�����܂ł̏���
{

}

void Enemy::LittleBoss_Move()//����
{

}
