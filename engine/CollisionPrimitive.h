#pragma once
//�����蔻��

#include <DirectXMath.h>

//��

struct Sphere
{
	//���S���W
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//���a
	float redius = 1.0f;
};

//����

struct Plane
{
	//�@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//���_����̋��
	float distance = 0.0f;
};

//�@���t���O�p�`

class Triangle
{
public:
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;

	DirectX::XMVECTOR normal;

	void ComputeNormal();
};

//���C

struct Ray
{
	//�n�_���W
	DirectX::XMVECTOR start = { 0,0,0,1 };

	//����
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};
