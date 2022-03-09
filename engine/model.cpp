﻿#include "Model.h"

#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>

using namespace DirectX;
using namespace std;

#include <DirectXMath.h>
#include <vector>

//#include "3d/Object3d.h"
#include <d3dcompiler.h>

#include <DirectXTex.h>

ID3D12Device* Model::device = nullptr;

std::vector<Model::VertexPosNormalUv>vertices;
std::vector<unsigned short>indices;
Model::Material material;
using namespace Microsoft::WRL;

ComPtr<ID3D12Resource>texbuff;
CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
//ComPtr<ID3D12DescriptorHeap> descHeap;
ComPtr<ID3D12DescriptorHeap> descHeap;
UINT descriptorHandleIncrementSize = 0;
D3D12_VERTEX_BUFFER_VIEW vbView{};
D3D12_INDEX_BUFFER_VIEW ibView{};
ComPtr<ID3D12Resource> vertBuff;
ComPtr<ID3D12Resource> indexBuff;
//Model::device = nullptr;

Model* Model::LoadFromOBJ(const std::string& modelname)
{

	//インスタンスnew
	Model* model = new Model();
	//OBJからデータ読み込み

	model->InitializeDescriptorHeap();


	//読み込んだデータをもとにバッファ生成
	model->LoadFromOBJInternal(modelname);

	model->CreateBuffers();

	return model;
}

void Model::LoadFromOBJInternal(const std::string& modelname)
{
	HRESULT result = S_FALSE;

	//ファイルストリーム
	std::ifstream file;

	//const string modelname = "skydome";
	const string filename = modelname + ".obj";
	const string directoryPath = "Resources/" + modelname + "/";
	file.open(directoryPath + filename);


	//オープン失敗をチェック
	if (file.fail())
	{
		assert(0);
	}

	vector<XMFLOAT3> positions;//頂点座標
	vector<XMFLOAT3> normals;//法線ベクトル
	vector<XMFLOAT2>texcoords;//テクスチャUV

	//１行ずつ読み込む
	string line;
	while (getline(file, line)) {
		//文字列をストリームに変換
		std::istringstream line_stream(line);

		//半角スペース区切りで先頭文字列取得
		string key;
		getline(line_stream, key, ' ');

		//先頭文字がmtllibならマテリアル
		if (key == "mtllib")
		{
			//マテリアルファイルの読み込み
			string filename;
			line_stream >> filename;
			//マテリアル読み込み
			LoadMaterial(directoryPath, filename);
		}

		//先頭文字がｖなら頂点座標
		if (key == "v")
		{
			//Ｘ，Ｙ，Ｚ読み込み
			XMFLOAT3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//座標データに追加
			positions.emplace_back(position);
			//頂点データに追加
		//	VertexPosNormalUv vertex{};
		//	vertex.pos = position;
		//	vertices.emplace_back(vertex);


		}

		//先頭文字がVTならテクスチャ
		if (key == "vt")
		{
			//U,V成分読み込み
			XMFLOAT2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V方向転換
			texcoord.y = 1.0f - texcoord.y;
			//テクスチャ座標データに追加
			texcoords.emplace_back(texcoord);
		}

		//先頭文字がvnなら法線ベクトル
		if (key == "vn")
		{
			//X,Y,Z成分読み込み
			XMFLOAT3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;
			//法線ベクトルデータに追加
			normals.emplace_back(normal);
		}



		//先頭文字がｆならポリゴン（三角形）
		if (key == "f")
		{
			//半角スペース区切りで行の続きを読み込む
			string index_string;
			while (getline(line_stream, index_string, ' '))
			{
				//頂点インデックス1個分の文字列をストリームに変換
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				index_stream >> indexPosition;
				index_stream.seekg(1, ios_base::cur);//スラッシュを飛ばす
				index_stream >> indexTexcoord;
				index_stream.seekg(1, ios_base::cur);///スラッシュを飛ばす
				index_stream >> indexNormal;
				//頂点データの追加
				Model::VertexPosNormalUv vertex{};
				vertex.pos = positions[indexPosition - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				vertices.emplace_back(vertex);
				//インデックスデータに追加
				indices.emplace_back((unsigned short)indices.size());
				//頂点インデックスに追加
			//	indices.emplace_back(indexPosition - 1);
			}
		}
	}

	//ファイルを閉じる
	file.close();


}

void Model::LoadMaterial(const std::string& directoryPath, const std::string& filename)
{
	//ファイルストリーム
	std::ifstream file;
	//マテリアルファイルを開く
	file.open(directoryPath + filename);
	//ファイルオープン失敗☑
	if (file.fail())
	{
		assert(0);
	}

	//1行ずつ読み込む
	string line;
	while (getline(file, line))
	{
		//1行分の文字列をストリームに変換
		std::istringstream line_stream(line);

		//半角スペース区切りで行の先頭文字を取得
		string key;
		getline(line_stream, key, ' ');

		//戦闘のタブ文字は無視する
		if (key[0] == '\t')
		{
			key.erase(key.begin());
		}

		//先頭文字がnewmtlならマテリアル名
		if (key == "newmtl")
		{
			//マテリアル名読み込み
			line_stream >> material.name;
		}

		//先頭文字がKaならアンビエント白
		if (key == "Ka")
		{
			line_stream >> material.ambient.x;
			line_stream >> material.ambient.y;
			line_stream >> material.ambient.z;
		}

		//先頭文字がKdならディフーズ名
		if (key == "Kd")
		{
			line_stream >> material.diffuse.x;
			line_stream >> material.diffuse.y;
			line_stream >> material.diffuse.z;
		}

		//先頭文字がKsならスペキュラー色
		if (key == "Ks")
		{
			line_stream >> material.specular.x;
			line_stream >> material.specular.y;
			line_stream >> material.specular.z;
		}

		//先頭文字がmap_kdならテクスチャファイル名
		if (key == "map_Kd")
		{
			//ファイル名読み込み
			line_stream >> material.textureFilename;
			//テクスチャ読み込み
			LoadTexture(directoryPath, material.textureFilename);
		}
	}
	//ファイルを閉じる
	file.close();

}

bool Model::LoadTexture(const std::string& directoryPath, const std::string& filename)
{
	HRESULT result = S_FALSE;

	//ファイルパスを結合
	string filepath = directoryPath + filename;

	//ユニコード文字列に変換する
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0,
		filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};


	//directoryPath + filename;

	/*
	result = LoadFromWICFile(
		L"Resources/tex1.png", WIC_FLAGS_NONE,
		&metadata, scratchImg);
		*/
	result = LoadFromWICFile(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);


	if (FAILED(result)) {
		return result;
	}


	const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出

	// リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// テクスチャ用バッファの生成
	result = Model::device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texbuff));
	if (FAILED(result)) {
		return result;
	}

	// テクスチャバッファにデータ転送
	result = texbuff->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		img->pixels,    // 元データアドレス
		(UINT)img->rowPitch,  // 1ラインサイズ
		(UINT)img->slicePitch // 1枚サイズ
	);
	if (FAILED(result)) {
		return result;
	}

	// シェーダリソースビュー作成
	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	Model::device->CreateShaderResourceView(texbuff.Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		cpuDescHandleSRV
	);

	return true;
}

bool Model::InitializeDescriptorHeap()
{
	HRESULT result = S_FALSE;

	// デスクリプタヒープを生成	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NumDescriptors = 1; // シェーダーリソースビュー1つ
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//生成
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	// デスクリプタサイズを取得
	descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	return true;
}


void Model::CreateBuffers()
{
	HRESULT result = S_FALSE;



	std::vector<VertexPosNormalUv> realVertices;

	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());


	// 頂点バッファ生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		//&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices)),
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// インデックスバッファ生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		//&CD3DX12_RESOURCE_DESC::Buffer(sizeof(indices)),
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// 頂点バッファへのデータ転送
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		//memcpy(vertMap, vertices, sizeof(vertices));
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}

	// インデックスバッファへのデータ転送
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {

		// 全インデックスに対して
		//for (int i = 0; i < _countof(indices); i++)
	//	{
	//		indexMap[i] = indices[i];	// インデックスをコピー
	//	}
		std::copy(indices.begin(), indices.end(), indexMap);

		indexBuff->Unmap(0, nullptr);
	}

	// 頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//	vbView.SizeInBytes = sizeof(vertices);
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	// インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	//ibView.SizeInBytes = sizeof(indices);
	ibView.SizeInBytes = sizeIB;



	//定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1)
	);



	// 定数バッファへデータ転送
	ConstBufferDataB1* constMap1 = nullptr;
	result = constBuffB1->Map(0, nullptr, (void**)&constMap1);
	constMap1->ambient = material.ambient;
	constMap1->diffuse = material.diffuse;
	constMap1->specular = material.specular;
	constMap1->alpha = material.alpha;

	constBuffB1->Unmap(0, nullptr);




}

void Model::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial)
{
	// 頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// インデックスバッファの設定
	cmdList->IASetIndexBuffer(&ibView);

	cmdList->SetGraphicsRootConstantBufferView(rootParamIndexMaterial,
		constBuffB1->GetGPUVirtualAddress());

	// デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// 定数バッファビューをセット
	//cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	// シェーダリソースビューをセット
	//cmdList->SetGraphicsRootDescriptorTable(1, gpuDescHandleSRV);

	if (material.textureFilename.size() > 0) {

		// シェーダリソースビューをセット
		cmdList->SetGraphicsRootDescriptorTable(2, gpuDescHandleSRV);
	}

	// 定数バッファビューをセット
	//cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	//cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());

	// シェーダリソースビューをセット
	//cmdList->SetGraphicsRootDescriptorTable(2, gpuDescHandleSRV);


	// 描画コマンド
	//cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}

