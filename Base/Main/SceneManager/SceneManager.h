#pragma once

#include "SceneBase.h"

//Scene管理

class SceneManager {
public:
	~SceneManager();

	void Update();

	void Draw();
public:
	//次シーン予約
	void SetNextScene(SceneBase* nextScene) { nextScene_ = nextScene; }
private:
	//今
	SceneBase* scene_ = nullptr;
	//次
	SceneBase* nextScene_ = nullptr;
};

