#pragma once
#include "SpriteCommon.h"
#include "Sprite.h"
class particle
{

public:

	void createblue(float x, float y, float vecx, float vecy);
	void createred(float x, float y, float vecx, float vecy);

	void moveblue(float x, float y, float velx, float vely);
	void movered(float x, float y, float velx, float vely);

	void Initialize();
	void Update(int flag);
	void Finalizeblue(int& flag);
	void Finalizered(int& flag);

	const int PART_NUM = 100;

	typedef struct partb
	{
		int flag;
		float x, y;	// �p�[�e�B�N���̈ʒu
		float velx, vely;	// �p�[�e�B�N���̈ړ���
		float G=9.8/60;		// �p�[�e�B�N���̏d��
		int count = 0;
	} PARTB;

	PARTB PARTb[100];	// �p�[�e�B�N���f�[�^

	typedef struct partr
	{
		int flag;
		float x, y;	// �p�[�e�B�N���̈ʒu
		float velx, vely;	// �p�[�e�B�N���̈ړ���
		float G = 9.8 / 60;		// �p�[�e�B�N���̏d��
		int count = 0;
	} PARTR;

	PARTR PARTr[100];	// �p�[�e�B�N���f�[�^

};

