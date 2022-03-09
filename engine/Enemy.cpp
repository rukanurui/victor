#include "Enemy.h"
#include "Player.h"
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
        Enemy1[i]={0,0,0,0,1,0,0,0};
    }

    Enemy1[1].X = 300;
    Enemy1[1].Y = 400;
}

void Enemy::Flagged()//�t���O����
{

    Enemy1->Timer++;
    Enemy1->Flag = 1;

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
    //���L�����Ɋ���Ă�
 
   // if (Enemy1[1].Flag == 0)
   // {
        double sb, sbx, sby, bx, by;

        bx = player.Central_x;
        by = player.Central_y;

        sbx = bx - Enemy1[1].X;
        sby = by - Enemy1[1].Y;

        // �����������߂�̂ɕW���֐��� sqrt ���g���A
        // ������g���ɂ� math.h ���C���N���[�h����K�v������
        sb = sqrt(sbx * sbx + sby * sby);

        // �P�t���[��������W�h�b�g�ړ�����悤�ɂ���
        Enemy1[1].SpeedX = sbx / sb * 1;
        Enemy1[1].SpeedY = sby / sb * 1;
  //  }

    if (Enemy1->Flag == 1)
    {
        Enemy1[1].X += Enemy1[1].SpeedX;
        Enemy1[1].Y += Enemy1[1].SpeedY;
    }
}

void Enemy::Rear()//�G�̌㏈��
{

}
