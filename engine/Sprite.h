#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

#include "SpriteCommon.h"

class Sprite
{
public:
    struct VertexPosUv
    {
        DirectX::XMFLOAT3 pos;//x y z�@���W
        DirectX::XMFLOAT2 uv;//u v ���W
    };

    //�萔�o�b�t�@�f�[�^�\����
    struct ConstBufferData8 {
        DirectX::XMFLOAT4 color8;//�F
        DirectX::XMMATRIX mat8;//3D�ϊ��s��
    };

    static Sprite* Create(SpriteCommon* spriteCommon, UINT texnumber,
        DirectX::XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlagX = false, bool isFlagY = false);


private:
    SpriteCommon* spriteCommon_ = nullptr;

    //���_�o�b�t�@
    Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff_;

    //���_�o�b�t�@�r���[
    D3D12_VERTEX_BUFFER_VIEW vbView_;

    //�萔�o�b�t�@
    Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;

    //XYZ������̉�]��
    DirectX::XMFLOAT3 rotation_ = { 0.0f,0.0f, 0.0f };

    //���W
    DirectX::XMFLOAT3 position_ = { 0,0,0 };

    //���[���h�s��
    DirectX::XMMATRIX matWorld_;

    //�F
    DirectX::XMFLOAT4 color_ = { 1,1,1,1 };

    //�e�N�X�`���ԍ�
    UINT texnumber_ = 0;

    //�傫��
    DirectX::XMFLOAT2 size_ = { 100, 100 };

    //�A���J�[�|�C���g
    DirectX::XMFLOAT2 anchorpoint_ = { 0.5f,0.5f };

    //���E���]
    bool isFlagX_ = false;

    //�㉺���]
    bool isFlagY_ = false;

    //�e�N�X�`��������W
    DirectX::XMFLOAT2 texLeftTop_ = { 0,0 };

    //�e�N�X�`���؂�o���T�C�Y
    DirectX::XMFLOAT2 texSize_ = { 100,100 };

    //��\��
    bool isInvisible_ = false;

public:
    void Initialize(SpriteCommon* spriteCommon, UINT texnumber,
        DirectX::XMFLOAT2 anchorpoint, bool isFlagX, bool isFlagY);

    void SpriteTransVertexBuffer();

    void  SpriteDraw();


    //�ʒu
    void SetPosition(const DirectX::XMFLOAT3& position) { position_ = position; }
    void SetRotation(const DirectX::XMFLOAT3& rotation) { rotation_ = rotation; }
    void SetSize(const DirectX::XMFLOAT2& size) { size_ = size; }
    void SettexLeftTop(const DirectX::XMFLOAT2& texLeftTop) { texLeftTop_ = texLeftTop; }
    void SettexSize(const DirectX::XMFLOAT2& texSize) { texSize_ = texSize; }
    void SetColor(const DirectX::XMFLOAT4& color) { color_ = color; }
    void SetAnchor(const DirectX::XMFLOAT2& anchorpoint) { anchorpoint_ = anchorpoint; }

    void Update();
};

