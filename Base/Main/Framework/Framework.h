#pragma once
#include "Input.h"
#include "WindowsAPP.h"
#include "DirectXBase.h"
#include "Object3d.h"
#include "GameAudio.h"
#include "SpriteBase.h"
#include "DebugCamera.h"
#include "SceneManager.h"

#include "ObjModel.h"
#include"Sprite.h"

class Framework
{
public:

	void Run();

	virtual void Initialize();

	virtual void Finalize();

	virtual void Update();
	
	virtual void Draw();

	virtual bool GetGameloopEndReqest() { return gameloopEndReqest_; }


protected:
	bool gameloopEndReqest_ = false;
	WindowsAPP* winApp_ = nullptr;
	DirectXBase* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	SpriteBase* spriteCommon_ = nullptr;
	GameAudio* audio_ = nullptr;
	SceneManager* sceneManager_ = nullptr;
};

