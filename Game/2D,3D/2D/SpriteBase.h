#pragma once
#include"PipelineSet.h"
#include <DirectXMath.h>


class SpriteBase
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static const int SpriteSRVCount = 512;

public:
	static SpriteBase* GetInstance();

private:

	PipelineSet pipelineSet;

	DirectX::XMMATRIX matProjection{};

	ComPtr<ID3D12DescriptorHeap> descHeap;

	ComPtr<ID3D12Resource> texBuff[SpriteSRVCount];

	ID3D12Device* Device = nullptr;

	ID3D12GraphicsCommandList* CmdList = nullptr;

	SpriteBase() = default;

	~SpriteBase() = default;

	SpriteBase(const SpriteBase& obj) = delete;

	void operator=(const SpriteBase& obj) = delete;

public:

	void initialize(ID3D12Device* device,ID3D12GraphicsCommandList* cmdList, int window_width, int window_height);

	void PreDraw();

	void LoadTexture( UINT texnumber, const wchar_t* filename);

	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex,UINT texnumber);

	ID3D12Resource* GetTexBuff(int texnumber);

	ID3D12Device* GetDevice() { return Device; }

	const DirectX::XMMATRIX& GetMatProjection() { return matProjection; }

	ID3D12GraphicsCommandList* GetCmd() { return CmdList; }

private:
	void CreateGraphicsPipeline();

};