#pragma once
#include "Player.h"

class Boss
{

public:
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

        float C_X;//getter Central_X�p
        float C_Y;//���Y��


        float P_X;//getter Central_X�p
        float P_Y;//���Y��

    //�֐�
    void Initialize();//������

    void Update();//�X�V

    void Move();

    void RandSwitch();//�F�̈ʒu����AI

    void RandRotate();//��]AI

    void RandColor();//�F�̐؂�ւ�AI

    void Getter_X(float X) { C_X = X; }
    void Getter_Y(float Y) { C_Y = Y; }

    void Central_X_Get(float X) { P_X = X; }
    void Central_Y_Get(float Y) { P_Y = Y; }
};

