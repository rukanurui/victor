#include "Enemy.h"
#include "Player.h"
#include <cstdlib>   
#include <time.h>
//#include<math.h>
//#include <DirectXMath.h>
/*
Enemy::ENEMY1* Enemy::createCell(void)
{

    //1���̃��������m�ۂ��A�ꏊ��Ԃ�
    ENEMY1* newEnemy1;
    newEnemy1 = (ENEMY1*)malloc(sizeof(ENEMY1));


    return newEnemy1;
}

void Enemy::create(float x, float y, float r, int flag, int cr_flag,int id)
{

    ENEMY1* newEnemy, * current;

    int input_id;

    int input_x;
    int input_y;

    int input_R;
    int input_Flag;
    int input_Color_Flag = 0;

    // �V���G�̒��g���쐬�B(1)
    newEnemy = createCell();

    input_id = id;
    newEnemy->id = input_id;

    input_x = x;
    newEnemy->X = input_x;

    input_y = y;
    newEnemy->X = input_y;

    input_R = r;
    newEnemy->R = input_R;

    input_Flag=flag;
    newEnemy->Flag = input_Flag;


    input_Color_Flag = cr_flag;
    newEnemy->Color_Flag = input_Color_Flag;


    //�w�b�h�ɕύX����
    current = tail;
    if ((head == NULL) && (tail == NULL))
    {
        // ���X�g����
        // �V����Cell���A�擪�������ɂȂ�B
        head = newEnemy;
        tail = newEnemy;
    }
    else
    {
        // ���X�g��1���ȏ�Cell�����݂���ꍇ�B
        newEnemy->before = current;
        newEnemy->next = current->next;
        // ����Cell(tail)��next�ɁA�V����Cell�̏ꏊ���Z�b�g�B
        tail->next = newEnemy;


        // �ǉ������V����Cell��tail�Ƃ���B
        tail = newEnemy;
    }
    // ���̃f�[�^�͖����̂ŁAnext�ɂ�NULL���Z�b�g�B
    tail->next = NULL;
}

void Enemy::editCell(float x, float y, float r, int flag, int cr_flag, int id)
{
    ENEMY1* current;
    int input_id;

    int input_x;
    int input_y;

    int input_R;
    int input_Flag;
    int input_Color_Flag = 0;

    input_id = id;
    // ���X�g�̐擪����A�}�����T���܂��B
    current = head;
    while (current != NULL)
    {
        if (current->id == input_id)
        {
            break;
        }
        else
        {
            current = current->next;
        }
    }
    // �}���悪������Ȃ�������A��������return�B
    if (current == NULL)
    {

        return;
    }

    //���g�̕ҏW
    input_id = id;
    current->id = input_id;


    input_x = x;
    current->X = input_x;

    input_y = y;
    current->X = input_y;

    input_R = r;
    current->R = input_R;

    input_Flag = flag;
    current->Flag = input_Flag;


    input_Color_Flag = cr_flag;
    current->Color_Flag = input_Color_Flag;

}
*/

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
    if (Enemy1->Flag == 1)
    {
        //�G�̏o��������W�ƐF�̐ݒ�
    }

}

void Enemy::Intialize()//������
{

    memset(Enemy1, 0, sizeof(Enemy1));

    //�\���̏��������
    for (int i = 0; i++; i < 100)
    {
        Enemy1[i] = { 0,0,0,0,1,0,0,0,0 };
    }


    Enemy1[1].X = rand() % 800 + 400;
    Enemy1[1].Y = 0;
    Enemy1[1].R = 50;

    Enemy1->Flag = 1;

}

void Enemy::Flagged()//�t���O����
{

    Enemy1->Timer++;
    //  Enemy1->Flag = 1;

    for (int i = 0; i++; i < 100)
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
    Enemy1[1].Angle = atan2(player.Central_y - Enemy1[1].Y, player.Central_x - Enemy1[1].X);

    if (Enemy1->Flag == 1)
    {
        //�t���O�������Ă���Ƃ��Ɏ��@�Ɍ������Ă���
        Enemy1[1].X += cos(Enemy1[1].Angle) * 1;
        Enemy1[1].Y += sin(Enemy1[1].Angle) * 1;
    }
}

void Enemy::Rear()//�G�̌㏈��
{

}
