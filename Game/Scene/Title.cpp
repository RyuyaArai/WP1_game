#include "Title.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXBase.h"
#include "GamePlay.h"

Title::Title(SceneManager* sceneManager)
	:SceneBase(sceneManager)
{
}

void Title::Initialize() {
	SpriteBase* spriteCommon = SpriteBase::GetInstance();
	spriteCommon->LoadTexture(0, L"Resources/house.png");
	for (int i = 0; i < 20; i++)
	{
		int texNum = rand() % 2;

		sprite = Sprite::Create(texNum, { 0,0 }, false, false);

		sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });

		//sprite->SetRotation((float)(rand() % 360));

		sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });

		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
		//sprite->SetPosition({ 500,300,0 });

	}

}

void Title::Finalize() {
	delete sprite;
}

void Title::Update() {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_SPACE))     // スペースキーが押されていたら
	{
		// 画面クリアカラーの数値を書き換える
		//clearColor[1] = 1.0f;
	}
	if (input->TriggerKey(DIK_RETURN)) {
		SceneBase* scene = new GamePlay(sceneManager_);
		sceneManager_->SetNextScene(scene);
	}
	sprite->Update();
}

void Title::Draw() {
	SpriteBase::GetInstance()->PreDraw();
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}
