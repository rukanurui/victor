#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#include "Player.h"

class Enemy
{
public:

	typedef struct Enemy1//�U�R1
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
	}ENEMY1;

	ENEMY1 Enemy1[100];



	//ENEMY1* head = NULL; // ���X�g�̐擪
	//ENEMY1* tail = NULL; // ���X�g�̖���


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
};

