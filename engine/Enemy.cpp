#include "Enemy.h"
#include "Player.h"
#include <cstdlib>   
#include <time.h>

Player player;


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
    if (Enemy1->Flag == 0)
    {
        //�G�̏o��������W�ƐF�̐ݒ�
        for (int i = 0; i<100;i++)
        {
            Enemy1[i].X = rand() % 800;
            Enemy1[i].Y = rand() % 700;
            Enemy1[i].R = 50;
        }
    }

}

void Enemy::Intialize()//������
{

    memset(Enemy1, 0, sizeof(Enemy1));

    //�\���̏��������
    for (int i = 0; i<100; i++)
    {
        Enemy1[i] = { 0,0,0,0,1,0,0,0,0,3 };
    }


    
    Enemy1[0].X = rand() % 800 + 400;
    Enemy1[0].Y = rand() % 700;
    Enemy1[0].R = 50;


    Enemy1->Flag = 1;

}

void Enemy::Flagged()//�t���O����
{

    Enemy1->Timer++;
    //  Enemy1->Flag = 1;

    for (int i = 0; i<100;i++)
    {

        //�K������ɂȂ�����t���O������
        if (Enemy1->Timer >= 360 * i)
        {

        }
    }
}

void Enemy::Move()//�G�̓���
{
    //�L�����̍��W���t���[���m�F
    player.Controll();

    //���L�����Ɋ���Ă�
    //���ƓG�̕������m�F����
    for (int i = 0; i<100; i++)
   {
        Enemy1[i].Angle = atan2(player.Central_y - Enemy1[i].Y, player.Central_x - Enemy1[i].X);

        if (Enemy1->Flag == 1)
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
