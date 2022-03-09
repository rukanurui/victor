#pragma once

#include <wrl.h>
#include<d3d12.h>



struct PipeLineSet
{
	Microsoft::WRL::ComPtr<ID3D12PipelineState>pipelinestate;

	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootsignature;
};

