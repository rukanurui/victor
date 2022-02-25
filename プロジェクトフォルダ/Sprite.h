#pragma once
#include "SpriteCommon.h"

#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
using namespace Microsoft::WRL;


class Sprite
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

    // ���_�f�[�^
    struct VertexPosUv
    {
        XMFLOAT3 pos; // xyz���W
        XMFLOAT2 uv;  // uv���W
    };

    // �萔�o�b�t�@�p�f�[�^�\����
    struct ConstBufferData {
        XMFLOAT4 color; // �F (RGBA)
        XMMATRIX mat;   // �R�c�ϊ��s��
    };

    static Sprite* Create(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);


public:

    void Initialize(SpriteCommon* spriteCommon, UINT texNumber,XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

    //���_�o�b�t�@�̓]��
    void TransferVertexBuffer();

    void Draw();

    void Update();

    void SetPosition(const DirectX::XMFLOAT3& position) { positiona = position; }
    void SetRotation(float rotation) { rotationa = rotation; }
    void SetSize(const DirectX::XMFLOAT2& size) { sizea = size; }
    void SetTexLeftTop(const XMFLOAT2& texLeftTop) { texLeftTopa = texLeftTop ;}
    void SetTexSize(const XMFLOAT2& texSize) { texSizea = texSize; }

private:
    SpriteCommon* spriteCommona = nullptr;
    //���_�o�b�t�@;
    ComPtr<ID3D12Resource> vertBuffa;
    //���_�o�b�t�@�r���[;
    D3D12_VERTEX_BUFFER_VIEW vbViewa{};
    //�萔�o�b�t�@;
    ComPtr<ID3D12Resource> constBuffa;
    // Z�����̉�]�p
    float rotationa = 0.0f;
    // ���W
    XMFLOAT3 positiona = { 0,0,0 };
    // ���[���h�s��
    XMMATRIX matWorlda;
    // �F(RGBA)
    XMFLOAT4 colora = { 1, 1, 1, 1 };
    // �e�N�X�`���ԍ�
    UINT texNumbera = 0;
    // �傫��
    XMFLOAT2 sizea= { 100, 100 };
    // �A���J�[�|�C���g
    XMFLOAT2 anchorpointa = { 0.5f, 0.5f };
    // ���E���]
    bool isFlipXa = false;
    // �㉺���]
    bool isFlipYa = false;
    // �e�N�X�`��������W
    XMFLOAT2 texLeftTopa = { 0, 0 };
    // �e�N�X�`���؂�o���T�C�Y
    XMFLOAT2 texSizea = { 100, 100 };
    // ��\��
    bool isInvisiblea = false;
};

