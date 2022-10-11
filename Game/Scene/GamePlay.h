#pragma once
#include"SceneBase.h"
#include"Sprite.h"
#include"Object3d.h"
#include"FbxObject3d.h"
#include"DebugCamera.h"
#include "Player.h"


class DirectXBase;

class GamePlay : public SceneBase {
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;


public:
	GamePlay(SceneManager* sceneManager);
	
	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;
private:
	//初期化用処理
	void Create3D_object();
	void Create2D_object();
	void SpriteLoadTex();
	void CameraCreateSet();
	void VariableInitialize();
private:
	//更新
	void ChangeScene();
	void ClassUpdate();
	void CameraUpdate();

private:

	Player* player = nullptr;

	Sprite* sprite = nullptr;

	ObjModel* modelblock = nullptr;
	
	Object3d* objblock = nullptr;
	
	FbxModel* fbxModel1 = nullptr;
	
	FbxObject3d* fbxObject1 = nullptr;
	
	std::vector<Sprite*> sprites;

	DebugCamera* camera = nullptr;
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
	const float PI = 3.1415926f;
	const float ROT_UINT = 0.1f;
	float angleX = 0, angleY = 0, angleZ = 0;
	float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;

};

