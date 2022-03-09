#include "DirectXCommon.h"

#include<cassert>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace Microsoft::WRL;



void DirectXCommon::Initialize(WinApp* winApp)
{
    //NULL���o
    assert(winApp);

    //�����o�ϐ��ɋL�^
    this->winApp = winApp;

    //�f�o�C�X�̐���
    InitializeDevice();
    //�R�}���h�֘A�̏�����
    InitializeCommand();
    //�������Ճ`�F�[���̏�����
    InitializeSwapchain();
    //�����_�\�^�[�Q�b�g�r���[�̏�����
    InitializeRenderTargetView();
    //�[�x�o�b�t�@�̏�����
    InitializeDepthBuffer();
    //�t�F���X�̏�����K
    InitializeFence();

}



void DirectXCommon::InitializeDevice()
{
    HRESULT result;

    //ComPtr<IDXGIFactory6> dxgiFactory;

#ifdef _DEBUG
    //�f�o�b�O���C���[���I����
    ID3D12Debug* debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
    }
#endif

    // DXGI�t�@�N�g���[�̐���
    result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    // �A�_�v�^�[�̗񋓗p
    std::vector<ComPtr<IDXGIAdapter1>> adapters;
    // �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
    ComPtr<IDXGIAdapter1>tmpAdapter;
    for (int i = 0;
        dxgiFactory->EnumAdapters1(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND;
        i++)
    {
        adapters.push_back(tmpAdapter); // ���I�z��ɒǉ�����
    }

    for (int i = 0; i < adapters.size(); i++)
    {
        DXGI_ADAPTER_DESC1 adesc;
        adapters[i]->GetDesc1(&adesc);

        if (adesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            continue;
        }

        std::wstring strDesc = adesc.Description;
        if (strDesc.find(L"Intel") == std::wstring::npos)
        {
            tmpAdapter = adapters[i];
            break;
        }
    }

    D3D_FEATURE_LEVEL levels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    D3D_FEATURE_LEVEL featureLevel;

    for (int i = 0; i < _countof(levels); i++)
    {
        // �̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
        result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&dev));
        if (result == S_OK)
        {
            // �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
            featureLevel = levels[i];
            break;
        }
    }

}

void DirectXCommon::InitializeCommand()
{
    HRESULT result;

    // �R�}���h�A���P�[�^�𐶐�
    result = dev->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&cmdAllocator));

    // �R�}���h���X�g�𐶐�
    result = dev->CreateCommandList(0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        cmdAllocator.Get(), nullptr,
        IID_PPV_ARGS(&cmdList));

    // �W���ݒ�ŃR�}���h�L���[�𐶐�
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};

    dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));
}

void DirectXCommon::InitializeSwapchain()
{
    HRESULT result;

    // �e��ݒ�����ăX���b�v�`�F�[���𐶐�
    DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
    swapchainDesc.Width = 1280;
    swapchainDesc.Height = 720;
    swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �F���̏���
    swapchainDesc.SampleDesc.Count = 1; // �}���`�T���v�����Ȃ�
    swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // �o�b�N�o�b�t�@�p
    swapchainDesc.BufferCount = 2;  // �o�b�t�@�����Q�ɐݒ�
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // �t���b�v��͔j��
    swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ComPtr<IDXGISwapChain1> swapchain1;
    HWND hwnd = winApp->GetHwnd();
    result = dxgiFactory->CreateSwapChainForHwnd(
        cmdQueue.Get(),
        winApp->GetHwnd(),
        &swapchainDesc,
        nullptr,
        nullptr,
        &swapchain1);

    swapchain1.As(&swapchain);
}

void DirectXCommon::InitializeRenderTargetView()
{
    //���\��2��
    backBuffers.resize(2);
    HRESULT result;
    for (int i = 0; i < 2; i++)
    {
        // �e��ݒ�����ăf�X�N���v�^�q�[�v�𐶐�
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
        heapDesc.NumDescriptors = 2;    // ���\�̂Q��
        dev->CreateDescriptorHeap(&heapDesc,
            IID_PPV_ARGS(&rtvHeaps));

        // ���\�̂Q���ɂ���
        //std::vector<ComPtr<ID3D12Resource>> backBuffers(2);
        for (int i = 0; i < 2; i++)
        {
            // �X���b�v�`�F�[������o�b�t�@���擾
            result = swapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));
            // �f�X�N���v�^�q�[�v�̃n���h�����擾
            D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
            // �����\���ŃA�h���X�������
            handle.ptr += i * dev->GetDescriptorHandleIncrementSize(heapDesc.Type);
            // �����_�[�^�[�Q�b�g�r���[�̐���
            dev->CreateRenderTargetView(
                backBuffers[i].Get(),
                nullptr,
                handle);
        }
    }
}

void DirectXCommon::InitializeDepthBuffer()
{
    HRESULT result;

    CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
        DXGI_FORMAT_D32_FLOAT,
        WinApp::window_width,
        WinApp::window_height,
        1, 0,
        1, 0,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
    );

    result = dev->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &depthResDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
        IID_PPV_ARGS(&depthBuffer)
    );





    //�[�x�r���[�ŃX�N���v�^�q�[�v
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    //  ComPtr< ID3D12DescriptorHeap>dsvHeap;
    result = dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

    //�[�x�r���[�쐬
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dev->CreateDepthStencilView(
        depthBuffer.Get(),
        &dsvDesc,
        dsvHeap->GetCPUDescriptorHandleForHeapStart()
    );


}

void DirectXCommon::InitializeFence()
{
    HRESULT result;


    result = dev->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

void DirectXCommon::PreDraw()
{

    UINT bbIndex = swapchain->GetCurrentBackBufferIndex();

    cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
        D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

    // �����_�[�^�[�Q�b�g�r���[�p�f�B�X�N���v�^�q�[�v�̃n���h�����擾
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeaps->GetCPUDescriptorHandleForHeapStart(), bbIndex,
        dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));


    // cmdList->OMSetRenderTargets(1, &rtvH, false, nullptr);
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvHeap->GetCPUDescriptorHandleForHeapStart());
    cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

    // �R�D��ʃN���A           R     G     B    A
    float clearColor[] = { 0,0, 0,1 }; // ���ۂ��F
    cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
    cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);




    cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, WinApp::window_width, WinApp::window_height));



    cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, WinApp::window_width, WinApp::window_height));
}

void DirectXCommon::PostDraw()
{

    UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
    // �T�D���\�[�X�o���A��߂�
        //barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`��
        //barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;   // �\����
        //cmdList->ResourceBarrier(1, &barrierDesc);
    cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
        D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

    // ���߂̃N���[�Y
    cmdList->Close();
    // �R�}���h���X�g�̎��s
    ID3D12CommandList* cmdLists[] = { cmdList.Get() }; // �R�}���h���X�g�̔z��
    cmdQueue->ExecuteCommandLists(1, cmdLists);
    // �R�}���h���X�g�̎��s������҂�
    cmdQueue->Signal(fence.Get(), ++fenceVal);
    if (fence->GetCompletedValue() != fenceVal) {
        HANDLE event = CreateEvent(nullptr, false, false, nullptr);
        fence->SetEventOnCompletion(fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }

    cmdAllocator->Reset(); // �L���[���N���A
    cmdList->Reset(cmdAllocator.Get(), nullptr);  // �ĂуR�}���h���X�g�𒙂߂鏀��

    // �o�b�t�@���t���b�v�i���\�̓��ւ��j
    swapchain->Present(1, 0);
}