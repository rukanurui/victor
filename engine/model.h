#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

class Model
{

public:
	//�ǂݍ���
	static Model* LoadFromOBJ(const std::string& modelname);



private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	// DirectX::����
	/*
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	*/
public: // �T�u�N���X
// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;  // uv���W
	};

	//�}�e���A��
	struct Material
	{
		std::string name;//�}�e���A����
		DirectX::XMFLOAT3 ambient;//�A���r�G���g�e���x
		DirectX::XMFLOAT3 diffuse;//�f�B�t���[�Y�e���x
		DirectX::XMFLOAT3 specular;//�X�y�L�����[�e���x
		float alpha;//��
		std::string textureFilename;//�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

	//�}�e���A��
	Material material;

	//�萔�o�b�t�@�p�f�[�^�\����B�P
	struct ConstBufferDataB1
	{
		DirectX::XMFLOAT3 ambient;//�A���r�G���g�W��
		float pad1;//�p�f�B���O
		DirectX::XMFLOAT3 diffuse;//�f�B�t���[�Y�W��
		float pad2;//�p�f�B���O
		DirectX::XMFLOAT3 specular;//�X�؃L�����[�W��
		float alpha;//��
	};

public:


	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

	static ID3D12Device* device;

	static void SetDevice(ID3D12Device* device) { Model::device = device; }

	//bool InitializeDescriptorHeap();

	void CreateBuffers();

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	/// <returns></returns>
	bool InitializeDescriptorHeap();

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);




	std::vector<unsigned short>indices;

	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;


private://�����o�ϐ�


	//ID3D12Device* device;

	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;

	//����J
	void LoadFromOBJInternal(const std::string& modelname);



	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@

};


