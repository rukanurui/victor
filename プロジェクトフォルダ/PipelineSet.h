#pragma once
#include <Windows.h>
#include <d3d12.h>

using namespace Microsoft::WRL;

struct PipelineSet
{
    // �p�C�v���C���X�e�[�g�I�u�W�F�N�g
    ComPtr<ID3D12PipelineState> pipelinestate;
    // ���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootsignature;
};

