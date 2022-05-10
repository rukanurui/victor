#include "SpriteCommon.h"
#include <cassert>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <string>
#include <d3dx12.h>
#include<DirectXTex.h>
using namespace Microsoft::WRL;
using namespace DirectX;


void SpriteCommon::Initialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height)
{
    assert(dev);

    device_ = dev;
    cmdList_ = cmdList;

    HRESULT result = S_FALSE;



    //�ݒ�\��
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����
    descHeapDesc.NumDescriptors = spriteSRVCount;//�e�N�X�`������

    //�f�X�N���v�^�q�[�v�̐���
    result = device_->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap_));//����

    //�X�v���C�g�p�p�C�v���C������
    CreateSprite2dpipe();

    //���s���e�̎ˉe�s��ϊ�
    matProjection_ = XMMatrixOrthographicOffCenterLH(
        0.0f, (float)window_width, (float)window_height, 0.0f, 0.0f, 1.0f);


    // return spriteCommon;
}

void SpriteCommon::Initialize_Post(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height)
{
    assert(dev);

    device_ = dev;
    cmdList_ = cmdList;

    HRESULT result = S_FALSE;



    //�ݒ�\��
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����
    descHeapDesc.NumDescriptors = spriteSRVCount;//�e�N�X�`������

    //�f�X�N���v�^�q�[�v�̐���
    result = device_->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap_));//����

    //�X�v���C�g�p�p�C�v���C������
    CreateSprite2dpipe_Post();

    //���s���e�̎ˉe�s��ϊ�
    matProjection_ = XMMatrixOrthographicOffCenterLH(
        0.0f, (float)window_width, (float)window_height, 0.0f, 0.0f, 1.0f);


    // return spriteCommon;
}

void SpriteCommon::PreDraw()
{
    //�p�C�v���C���X�e�[�g�̐ݒ�
    cmdList_->SetPipelineState(pipelineSet_.pipelinestate.Get());

    //���[�g�V�O�l�`���̐ݒ�
    cmdList_->SetGraphicsRootSignature(pipelineSet_.rootsignature.Get());

    //�v���~�e�B�u�`���ݒ�
    cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    //�e�N�X�`���p�f�X�N���v�^�q�[�v
    ID3D12DescriptorHeap* ppHeaps[] = { descHeap_.Get() };
    cmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void SpriteCommon::SpriteCommonLoadTexture(UINT texnumber, const wchar_t* filename)
{
    assert(texnumber <= spriteSRVCount - 1);

    HRESULT result;

    TexMetadata metadata{};
    ScratchImage scratchImg{};


    result = LoadFromWICFile(
        filename,
        WIC_FLAGS_NONE,
        &metadata, scratchImg);

    const Image* img = scratchImg.GetImage(0, 0, 0);

    const int texWidth = 256;//�������s�N�Z��
    const int imageDataCount = texWidth * texWidth;//�z��̗v�f��


    CD3DX12_HEAP_PROPERTIES texheapProp{};//�e�N�X�`���q�[�v
    texheapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
    texheapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    texheapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;


    CD3DX12_RESOURCE_DESC texresDesc{};
    texresDesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
    texresDesc.Format = metadata.format;
    texresDesc.Width = metadata.width;//��
    texresDesc.Height = (UINT)metadata.height;//����
    texresDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
    texresDesc.MipLevels = (UINT16)metadata.mipLevels;
    texresDesc.SampleDesc.Count = 1;


    result = device_->CreateCommittedResource(//GPU���\�[�X�̐���
        &texheapProp,
        D3D12_HEAP_FLAG_NONE,
        &texresDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,//�e�N�X�`���p�w��
        nullptr,
        IID_PPV_ARGS(&texBuff_[texnumber]));

    //���\�[�X�ݒ�
    texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
        metadata.format,
        metadata.width,
        (UINT)metadata.height,
        (UINT16)metadata.arraySize,
        (UINT16)metadata.mipLevels);

    result = device_->CreateCommittedResource(//GPU���\�[�X�̐���
        &CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
        D3D12_HEAP_FLAG_NONE,
        &texresDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,//�e�N�X�`���p�w��
        nullptr,
        IID_PPV_ARGS(&texBuff_[texnumber]));


    //�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
    result = texBuff_[texnumber]->WriteToSubresource(
        0,
        nullptr,							//�S�̈�ɃR�s�[
        img->pixels,						//���f�[�^�A�h���X
        (UINT)img->rowPitch,				//1���C���T�C�Y
        (UINT)img->slicePitch);			//�S�T�C�Y


    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV =
        CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap_->GetCPUDescriptorHandleForHeapStart(),
            texnumber,
            device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV =
        CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap_->GetGPUDescriptorHandleForHeapStart(),
            texnumber,
            device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

    //�V�F�[�_�[���\�[�X�r���[�ݒ�
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
    //srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;//RGBA
    srvDesc.Format = metadata.format;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
    srvDesc.Texture2D.MipLevels = 1;

    //�q�[�v��?�ԖڂɃV�F�[�_�[���\�[�X�r���[�𐶐�
    device_->CreateShaderResourceView(texBuff_[texnumber].Get(),//�r���[�Ɗ֘A�t����o�b�t�@
        &srvDesc,//�e�N�X�`���ݒ���
        CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap_->GetCPUDescriptorHandleForHeapStart(), texnumber,
            device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

}

ID3D12Resource* SpriteCommon::GetTexBuff(int texNumber)
{
    assert(0 <= texNumber && texNumber < spriteSRVCount);

    return texBuff_[texNumber].Get();
}

void SpriteCommon::SetGraphicsRootDescriptorTable(UINT rootParameterIndex, UINT texnumber)
{
    cmdList_->SetGraphicsRootDescriptorTable(rootParameterIndex,
        CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap_->GetGPUDescriptorHandleForHeapStart(),
            texnumber,
            device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

}

void SpriteCommon::CreateSprite2dpipe()
{
    HRESULT result = S_OK;



    ComPtr<ID3DBlob> vsBlob;// ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> psBlob;//ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> errorBlob;//ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g

    // ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"Resources/shaders/SpriteVS.hlsl",  // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0,
        &vsBlob, &errorBlob);
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string errstr;
        errstr.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            errstr.begin());
        errstr += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(errstr.c_str());
        exit(1);
    }

    // �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"Resources/shaders/SpritePS.hlsl",   // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0,
        &psBlob, &errorBlob);
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string errstr;
        errstr.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            errstr.begin());
        errstr += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(errstr.c_str());
        exit(1);
    }


    // ���_���C�A�E�g
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        {
            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        }, // (1�s�ŏ������ق������₷��)


        {
            "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        }, // (1�s�ŏ������ق������₷��)
    };
    CD3DX12_DESCRIPTOR_RANGE  descRangeSRV;
    //descRangeCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);//b0 ���W�X�^
    descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);//t0 ���W�X�^


    CD3DX12_ROOT_PARAMETER rootparams[2];
    rootparams[0].InitAsConstantBufferView(0);//�萔�o�b�t�@�r���[�Ƃ��ď�����(b0�@���W�X�^)
    rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

    // �O���t�B�b�N�X�p�C�v���C���ݒ�
    D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
    gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

    //���_�V�F�[�_�@�s�N�Z���V�F�[�_
    gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
    gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());


    //�u�����h
//gpipeline.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA�S�Ẵ`�����l����`��
    D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = gpipeline.BlendState.RenderTarget[0];
    blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    //���ʐݒ�(BLEND)
    blenddesc.BlendEnable = true;					//�u�����h��L���ɂ���
    blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	//���Z
    blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		//�\�[�X�̒l��100%�g��
    blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	//�f�X�g�̒l��0%�g��

    //���Z����
    //blenddesc.BlendOp = D3D12_BLEND_OP_ADD;	 //���Z
    //blenddesc.SrcBlend = D3D12_BLEND_ONE;	 //�\�[�X�̒l��100%�g��
    //blenddesc.DestBlend = D3D12_BLEND_ONE;	 //�f�X�g�̒l��100%�g��

    //����������
    blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
    blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

    gpipeline.InputLayout.pInputElementDescs = inputLayout;
    gpipeline.InputLayout.NumElements = _countof(inputLayout);
    gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    gpipeline.NumRenderTargets = 1; // �`��Ώۂ�1��
    gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0�`255�w���RGBA
    gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

        //�W���I�Ȑݒ�(�|���S�����h��Ԃ� �[�x�N���b�s���O��L����)
    gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  // �w�ʂ��J�����O�Ȃ�

    //�f�v�X�X�e���V���X�e�[�g�̐ݒ�

    //�W���I�Ȑݒ�(�������݋���)
    gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);//��U�W���l���Z�b�g
    gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;//��ɏ㏑��
    gpipeline.DepthStencilState.DepthEnable = false;//�[�x�e�X�g���Ȃ�

    gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g

    //�f�X�N���v�^�e�[�u���̐ݒ�
    D3D12_DESCRIPTOR_RANGE descTblRange{};
    descTblRange.NumDescriptors = 1;
    descTblRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    descTblRange.BaseShaderRegister = 0;
    descTblRange.OffsetInDescriptorsFromTableStart =
        D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    //���[�g�p�����[�^
    D3D12_ROOT_PARAMETER rootparam = {};
    rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootparam.DescriptorTable.pDescriptorRanges = &descTblRange;
    rootparam.DescriptorTable.NumDescriptorRanges = 1;
    rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;



    //���[�g�V�O�l�`������
    ComPtr<ID3D12RootSignature> rootsignature;



    //���[�g�V�O�l�`���̐ݒ�
    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
    CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

    rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    // PipelineSet pipelineSet;

    ComPtr<ID3DBlob> rootSigBlob;

    result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
        &rootSigBlob, &errorBlob);

    result = device_->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
        IID_PPV_ARGS(&pipelineSet_.rootsignature));

    gpipeline.pRootSignature = pipelineSet_.rootsignature.Get();

    ComPtr<ID3D12PipelineState> pipelinestate;// ID3D12PipelineState* pipelinestate = nullptr;
    result = device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet_.pipelinestate));


}




void SpriteCommon::CreateSprite2dpipe_Post()
{
    HRESULT result = S_OK;



    ComPtr<ID3DBlob> vsBlob;// ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> psBlob;//ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> errorBlob;//ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g

    // ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"Resources/shaders/SpriteVS.hlsl",  // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0,
        &vsBlob, &errorBlob);
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string errstr;
        errstr.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            errstr.begin());
        errstr += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(errstr.c_str());
        exit(1);
    }

    // �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"Resources/shaders/PostPS.hlsl",   // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0,
        &psBlob, &errorBlob);
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string errstr;
        errstr.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            errstr.begin());
        errstr += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(errstr.c_str());
        exit(1);
    }


    // ���_���C�A�E�g
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        {
            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        }, // (1�s�ŏ������ق������₷��)


        {
            "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        }, // (1�s�ŏ������ق������₷��)
    };
    CD3DX12_DESCRIPTOR_RANGE  descRangeSRV;
    //descRangeCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);//b0 ���W�X�^
    descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);//t0 ���W�X�^


    CD3DX12_ROOT_PARAMETER rootparams[2];
    rootparams[0].InitAsConstantBufferView(0);//�萔�o�b�t�@�r���[�Ƃ��ď�����(b0�@���W�X�^)
    rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

    // �O���t�B�b�N�X�p�C�v���C���ݒ�
    D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
    gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

    //���_�V�F�[�_�@�s�N�Z���V�F�[�_
    gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
    gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());


    //�u�����h
//gpipeline.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA�S�Ẵ`�����l����`��
    D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = gpipeline.BlendState.RenderTarget[0];
    blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    //���ʐݒ�(BLEND)
    blenddesc.BlendEnable = true;					//�u�����h��L���ɂ���
    blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	//���Z
    blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		//�\�[�X�̒l��100%�g��
    blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	//�f�X�g�̒l��0%�g��

    //���Z����
    //blenddesc.BlendOp = D3D12_BLEND_OP_ADD;	 //���Z
    //blenddesc.SrcBlend = D3D12_BLEND_ONE;	 //�\�[�X�̒l��100%�g��
    //blenddesc.DestBlend = D3D12_BLEND_ONE;	 //�f�X�g�̒l��100%�g��

    //����������
    blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
    blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

    gpipeline.InputLayout.pInputElementDescs = inputLayout;
    gpipeline.InputLayout.NumElements = _countof(inputLayout);
    gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    gpipeline.NumRenderTargets = 1; // �`��Ώۂ�1��
    gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0�`255�w���RGBA
    gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

        //�W���I�Ȑݒ�(�|���S�����h��Ԃ� �[�x�N���b�s���O��L����)
    gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  // �w�ʂ��J�����O�Ȃ�

    //�f�v�X�X�e���V���X�e�[�g�̐ݒ�

    //�W���I�Ȑݒ�(�������݋���)
    gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);//��U�W���l���Z�b�g
    gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;//��ɏ㏑��
    gpipeline.DepthStencilState.DepthEnable = false;//�[�x�e�X�g���Ȃ�

    gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g

    //�f�X�N���v�^�e�[�u���̐ݒ�
    D3D12_DESCRIPTOR_RANGE descTblRange{};
    descTblRange.NumDescriptors = 1;
    descTblRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    descTblRange.BaseShaderRegister = 0;
    descTblRange.OffsetInDescriptorsFromTableStart =
        D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    //���[�g�p�����[�^
    D3D12_ROOT_PARAMETER rootparam = {};
    rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootparam.DescriptorTable.pDescriptorRanges = &descTblRange;
    rootparam.DescriptorTable.NumDescriptorRanges = 1;
    rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;



    //���[�g�V�O�l�`������
    ComPtr<ID3D12RootSignature> rootsignature;



    //���[�g�V�O�l�`���̐ݒ�
    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
    CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

    rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    // PipelineSet pipelineSet;

    ComPtr<ID3DBlob> rootSigBlob;

    result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
        &rootSigBlob, &errorBlob);

    result = device_->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
        IID_PPV_ARGS(&pipelineSet_.rootsignature));

    gpipeline.pRootSignature = pipelineSet_.rootsignature.Get();

    ComPtr<ID3D12PipelineState> pipelinestate;// ID3D12PipelineState* pipelinestate = nullptr;
    result = device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet_.pipelinestate));

}
