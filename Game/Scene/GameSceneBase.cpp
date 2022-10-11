#include "GameSceneBase.h"
#include "GamePlay.h"
#include "Title.h"

void GameSceneBase::Initialize() {

	Framework::Initialize();
	SceneBase* scene = new GamePlay(sceneManager_);
	sceneManager_->SetNextScene(scene);
}

void GameSceneBase::Finalize() {

	Framework::Finalize();
}

void GameSceneBase::Update() {

	Framework::Update();
}

void GameSceneBase::Draw() {
	Framework::Draw();
}
