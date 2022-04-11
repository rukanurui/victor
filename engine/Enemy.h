#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class Enemy
{
public:

	const int ENEMY_NUM = 10;

	typedef struct Enemy1//�U�R1
	{
		float X=0;//�����W
		float Y=0;//�����W

		float R=0;//���a
		int Flag=0;//�t���O
		int Color_Flag=0;//�F�̃t���O

		int Timer=0;//�t���O�𗧂����邽�߂̎���


		float Angle=0;

		int Patern=0;

		float rnd=0;

		int Die=0;
		
		int Type = 0;
	}ENEMY1;

	ENEMY1 Enemy1[10];

	typedef struct Enemy2//�U�R1
	{
		float X;//�����W
		float Y;//�����W

		float R;//���a
		int Flag;//�t���O
		int Color_Flag;//�F�̃t���O

		//int id;//�z��̗v�f

		int Timer;//�t���O�𗧂����邽�߂̎���

		int SpeedX;
		int SpeedY;

		float Angle;

		int Patern;

		float rnd;

		int Die;
		//struct Enemy1* next;
		//struct Enemy1* before;//�O�̃f�[�^������ꏊ
	}ENEMY2;

	//ENEMY1* head = NULL; // ���X�g�̐擪
	//ENEMY1* tail = NULL; // ���X�g�̖���

	float C_X;//getter Central_X�p
	float C_Y;//���Y��


	float P_X;//getter Central_X�p
	float P_Y;//���Y��


	void Getter_X(float X) { C_X = X; }
	void Getter_Y(float Y) { C_Y = Y; }

	void Central_X_Get(float X) { P_X = X; }
	void Central_Y_Get(float Y) { P_Y = Y; }


	//�֐�
//	ENEMY1* createCell(void);//�v�f�̍쐬
	//void create(float x,float y,float r,int flag,int cr_flag,int id);//�Ō���Ƀ��X�g��ǉ�
	//void editCell(float x, float y, float r, int flag, int cr_flag, int id);//���g��ҏW


	//��������z��Ver
	void Intialize();//������	

	void Update();//�X�V

	void Generation();//�I�u�W�F�N�g�̐���

	void Flagged();//�t���O������

	void Move();//�G�̓���

	void Rear();//�㏈��

	//���{�X

	void LittleBoss_Generation();

	void LittleBoss_Flagged();

	void LittleBoss_Move();
};

