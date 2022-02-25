#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include"PipelineSet.h"



class SpriteCommon
{

private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::���ȗ�
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMMATRIX = DirectX::XMMATRIX;

public:
	// �e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;

private:
    // �p�C�v���C���Z�b�g
    PipelineSet pipelineSeta;
    // �ˉe�s��
    XMMATRIX matProjectiona{};
    // �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
    ComPtr<ID3D12DescriptorHeap> descHeapa;
    // �e�N�X�`�����\�[�X�i�e�N�X�`���o�b�t�@�j�̔z��
    ComPtr<ID3D12Resource> texBuffa[spriteSRVCount];

    ID3D12Device* devicea = nullptr;

    ID3D12GraphicsCommandList* cmdLista = nullptr;

private:
    void CreateGraphicsPipeline();

public://�����o�֐�
    //������
    void Initialize(ID3D12Device* devicea, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height);

    void PreDraw();

    void LoadTexture(UINT texnumber, const wchar_t* filename);

    void SetGraphicsRootDescriptorTabl(UINT rootParameterIndex,UINT texNumber);

    ID3D12Resource* GetTexBuff(int texnumber);

    ID3D12Device* GetDevice() { return devicea;};

    ID3D12GraphicsCommandList* GetCommandList() { return cmdLista; }

    const DirectX::XMMATRIX& GetMatProjection() { return matProjectiona; }



};

