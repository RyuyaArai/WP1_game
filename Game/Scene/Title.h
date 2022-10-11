#pragma once
#include"SceneBase.h"
#include"Sprite.h"
#include"Object3d.h"

class Title : public SceneBase {

public:
	Title(SceneManager* sceneManager);

	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:
	Sprite* sprite = nullptr;
	std::vector<Sprite*> sprites;
};

