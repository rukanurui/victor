#pragma once
#include "Player.h"

class Boss
{
      	float x;
		float y;

		int HP;

		float R;//���a
		int Flag;//�t���O
		int Color_Flag;//�F�̃t���O

		float Angle;

		int Patern;


        //��]����~�̑傫��
        float radius = 200;
        //��]���邽�߂̒l
        float timer = 0;
        //�؂�ւ��ϐ�
        int Switch = 0;

        int Switch_Flag = 0;
        int Switch_Count = 0;
        int Switch_Rand = 0;

        //�ԋ����W
        float RedX = 0;
        float RedY = 0;

        float Red_R = 25;
        float Blue_R = 25;

        //�������W
        float BlueX = 0;
        float BlueY = 0;

        int rotate = 0;

        int rotate_rand = 0;
        int rotate_time = 0;

    //�֐�
    void Initialize();//������

    void Update();//�X�V

    void RandSwitch();//�F�̈ʒu����AI

    void RandRotate();//��]AI

    void RandColor();//�F�̐؂�ւ�AI
};

