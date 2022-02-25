#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

#include<vector>
#include<cassert>


using namespace std;

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;


class model
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;  // uv���W
	};


	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;//�A���r�G���g�W��
		float pad1;      //�p�f�B���O
		XMFLOAT3 diffuse;//�f�B�t���[�Y�W��
		float pad2;      //�p�f�B���O
		XMFLOAT3 specular;//�X�y�L�����[�W��
		float alpha;      //�A���t�@
	};


	//�}�e���A��
	struct Material
	{
		std::string name;//�}�e���A����
		DirectX::XMFLOAT3 ambient;//�A���r�G���g�e���x
		DirectX::XMFLOAT3 diffuse;//�f�B�t���[�Y�e���x
		DirectX::XMFLOAT3 specular; //�X�y�L�����[�e���x
		float alpha; //�A���t�@
		std::string textureFilename;//�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

public://�ÓI�����o�֐�
	//obj�t�@�C������3d���f����ǂݍ���
	static model* LoadFromOBJ(const std::string& modelname);
	//setter
	static void SetDevice(ID3D12Device* device) { model::device = device; }
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList*cmdList,UINT rootParamIndexMaterial);


private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;
	

private://�����o�ϐ�
	
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;

	// �R�}���h���X�g
	ID3D12GraphicsCommandList* cmdList;
	
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �r���[�s��
	XMMATRIX matView;
	// �ˉe�s��
	XMMATRIX matProjection;
	// ���_���W
	XMFLOAT3 eye;
	// �����_���W
	XMFLOAT3 target;
	// ������x�N�g��
	XMFLOAT3 up;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

	Material material;

	
	ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@
	// �F
	XMFLOAT4 color = { 1,1,1,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;

private://����J�̃����o�֐�
	//OBJ�t�@�C������3D���f����ǂݍ���
	void LoadFromOBJInternal(const std::string& modelname);
	//�}�e���A���ǂݍ���
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);
	//�e�N�X�`���ǂݍ���
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

	bool InitializeDescriptorHeap();

	void CreateBuffers();
};

