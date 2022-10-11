#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "FbxModel.h"
#include "Camera.h"
//#include"PipelineSet.h"

/// 3Dオブジェクト
class FbxObject3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//ボーンの最大数
	static const int MAX_BONES = 32;

public:
	struct constBufferDataTransform	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};

	struct ConstBufferDataSkin {
		XMMATRIX bones[MAX_BONES];
	};

public:
	void Initialize();
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void PlayAnimation();

	void SetModel(FbxModel* fbxModel) { this->fbxModel = fbxModel; }
	void SetRotation(XMFLOAT3 rota) { this->rotation = rota; }

public:
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera = camera; }
	//グラフィックパイプラインの生成
	static void CreateGraphicsPipeline();

private:
	static ID3D12Device* device;
	static Camera* camera;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;



private:
	// ローカルスケール
	XMFLOAT3 scale = { 1.0,1.0,1.0 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,1 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FbxModel* fbxModel = nullptr;
	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;


protected:
	ComPtr<ID3D12Resource> constBuffTransform;
};