#pragma once
//#pragma comment (lib, "xinput.lib")
//#include <xinput.h>
#include <DirectXMath.h>
#include "GamePad.h"
#include"Item.h"
#include"Input.h"


class Player
{
private:

public:
    //�ϐ�

   //�Z���^�[���W
    float Central_x = 640;
    float Central_y = 360;

    //��]����~�̑傫��
    float Player_radius = 200;
    //��]���邽�߂̒l
    float timer = 0;
    //�؂�ւ��ϐ�
    int Switch = 0;

    //�ԋ����W
    float Player_RedX = 0;
    float Player_RedY = 0;

    float Red_R = 25;
    float Blue_R = 25;

    //�������W
    float Player_BlueX = 0;
    float Player_BlueY = 0;

    //���̃t���O�֘A
    float Red_Lv = 1;
    float Blue_Lv = 1;

    int Radius = 100;

    float Map_X = 0;
    float Map_Y = 0;


    float Effect_;
    float Effect_2;
    float Effect_3;
  //  Item* item= nullptr;

    //�g���K�[�����̂��߂̕ϐ�
    int Old_iPad_left = 0, Old_iPad_right = 0, iOld_Pad_up = 0, Old_iPad_down = 0;
    int Old_iPad_leftshoulder = 0, Old_iPad_rightshoulder = 0;
    int Old_iPad_A = 0, Old_iPad_B = 0, Old_iPad_X = 0, Old_iPad_Y = 0;


    //�֐�
    void Controll();//�ʒu���]
    void Initialize();//������

    void setter(float Effect) { Effect_ = Effect; }

    void setter2(float Effect2) { Effect_2 = Effect2; }

    void setter3(float Effect3) { Effect_3= Effect3; }

    void Map_Setter(float X, float Y) { Map_X = X; Map_Y = Y; }
};

