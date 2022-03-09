#pragma once

#include<Windows.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include "WinApp.h"

//DirectX���
class DirectXCommon
{
public://�����o�֐�

	//������
	void Initialize(WinApp* win);

	void PreDraw();

	void PostDraw();

	//Microsoft::WRL::ComPtr<ID3D12Device> GetDev() { return dev; }

	ID3D12Device* GetDev() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }



private:



	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapchain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();



	//�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> dev;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	//WindowsAPI
	WinApp* winApp = nullptr;
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;





private: // �����o�ϐ�
// �E�B���h�E�Y�A�v���P�[�V�����Ǘ�
	//WinApp* winApp;

	// Direct3D�֘A
	//ComPtr<IDXGIFactory6> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapchain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>cmdQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvHeaps;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;
	Microsoft::WRL::ComPtr<ID3D12Fence>fence;

	//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	//UINT64 fenceVal = 0;


	UINT64 fenceVal = 0;


};

