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
                Enemy1[i].X = rand() % 800;
                Enemy1[i].Y = rand() % 700;
                Enemy1[i].R = 50;
                Enemy1[i].Patern = rand() % 3 + 1;
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
        Enemy1[i] = { 0,0,0,0,1,0,0,1,0,0,0 };

       // Enemy1[i].Timer = rand() % 0 - 500;
       // Enemy1[i].Flag = 1;
    }


 

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        Enemy1[i].X = rand() % 1200;
        Enemy1[i].Y = rand() % 700;
        Enemy1[i].R = 50;
        Enemy1[i].Patern = rand() % 3 + 1;
        Enemy1[i].Color_Flag = rand() % 2 + 1;
    }
}

void Enemy::Flagged()//�t���O����
{

    Enemy1[0].Timer++;
    for (int i = 0; i<ENEMY_NUM;i++)
    {
        if (Enemy1[i].Flag == 0)
        {
           // Enemy1[i].Timer++;
            //�K������ɂȂ�����t���O������
            if (Enemy1[0].Timer >= 300*i)
            {
                if (i < 10&&Enemy1[i].Die==0)
                {
                    Enemy1[i].Flag = 1;
                    Enemy1[i].Timer = 0;
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
        Enemy1[i].Angle = atan2(P_Y - (Enemy1[i].Y-C_Y), P_X - (Enemy1[i].X-C_X));

        if (Enemy1[i].Flag == 1)
        {
            if (Enemy1[i].Patern == 1)
            {
                //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���
                Enemy1[i].X += cos(Enemy1[i].Angle) * 1;
                Enemy1[i].Y += sin(Enemy1[i].Angle) * 1;
            }
            else if (Enemy1[i].Patern == 2)
            {
                //�t���O�������Ă���Ƃ��Ɏ��@���痣��Ă���
                Enemy1[i].X -= cos(Enemy1[i].Angle) * 1;
                Enemy1[i].Y -= sin(Enemy1[i].Angle) * 1;
            }
            else if (Enemy1[i].Patern == 3)
            {
                //�����_��
                srand((unsigned)time(NULL));

                Enemy1[1].rnd = rand() % 4 + 1;

                if (Enemy1[1].rnd == 1)
                {
                    Enemy1[1].X += 0.01;
                }
                if (Enemy1[1].rnd == 2)
                {
                    Enemy1[1].X -= 0.01;
                }
                if (Enemy1[1].rnd == 3)
                {
                    Enemy1[1].Y += 0.01;
                }
                if (Enemy1[1].rnd == 4)
                {
                    Enemy1[1].Y -= 0.01;
                }
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
