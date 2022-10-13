#pragma once
#include<d3d12.h>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3dcompiler.lib")

//using namespace Microsoft::WRL;

class CreGraPl
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static D3D12_RENDER_TARGET_BLEND_DESC RenderTargetBlendSet();
	static D3D12_GRAPHICS_PIPELINE_STATE_DESC Gpipeline(ComPtr<ID3DBlob> vsBlob, ComPtr<ID3DBlob> psBlob);
private:
};

