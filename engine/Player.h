#pragma once
//#pragma comment (lib, "xinput.lib")
//#include <xinput.h>
#include <DirectXMath.h>
#include "GamePad.h"


class Player
{
private:
   
public:
    //�ϐ�

   //�Z���^�[���W
    float Central_x = 0;
    float Central_y = 0;

    //��]����~�̑傫��
    float Player_radius = 200;
    //��]���邽�߂̒l
    float timer = 0;
    //�؂�ւ��ϐ�
    int Switch = 0;

    //�ԋ����W
    float Player_RedX = 0;
    float Player_RedY = 0;
    //�������W
    float Player_BlueX = 0;
    float Player_BlueY = 0;

    //���̃t���O�֘A
    int Red_Lv = 1;
    int Blue_Lv = 1;

    int Radius = 100;



    //�g���K�[�����̂��߂̕ϐ�
    int Old_iPad_left = 0, Old_iPad_right = 0, iOld_Pad_up = 0, Old_iPad_down = 0;
    int Old_iPad_leftshoulder = 0, Old_iPad_rightshoulder = 0;
    int Old_iPad_A = 0, Old_iPad_B = 0, Old_iPad_X = 0, Old_iPad_Y = 0;


    //�֐�
    void Controll();//�ʒu���]

};

