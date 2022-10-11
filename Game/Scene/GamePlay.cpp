#include "GamePlay.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXBase.h"
#include "Title.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Noise.h"

using namespace DirectX;

GamePlay::GamePlay(SceneManager* sceneManager)
	:SceneBase(sceneManager)
{
}

void GamePlay::Initialize() {


	VariableInitialize();
	CameraCreateSet();
	SpriteLoadTex();
	Create2D_object();
	Create3D_object();

}

void GamePlay::Finalize() {
	for (auto& sprite : sprites)
	{
		delete sprite;
	}
	//delete sprite;
	delete modelblock;
	delete objblock;
	delete camera;
	//delete fbxModel1;
	//delete fbxObject1;

}

void GamePlay::Update() {
	Input* input = Input::GetInstance();

	ClassUpdate();

	//----------デバッグ用-----------------------------
	if (input->TriggerKey(DIK_RETURN)) {
		ChangeScene();
	}
	//----------ここまで-------------------------------
}

void GamePlay::Draw() {
	Object3d::PreDraw(DirectXBase::GetInstance()->GetCmdList());
	objblock->Draw();
	//fbxObject1->Draw(DirectXBase::GetInstance()->GetCmdList());
	Object3d::PostDraw();
	player->Draw();
	SpriteBase::GetInstance()->PreDraw();
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}

void GamePlay::Create3D_object() {

	FbxObject3d::SetDevice(DirectXBase::GetInstance()->GetDev());
	FbxObject3d::CreateGraphicsPipeline();

	modelblock = ObjModel::LoadFromOBJ("block");

	objblock = Object3d::Create();

	objblock->SetModel(modelblock);

	objblock->SetPosition({ 0,-2,0 });

	XMFLOAT3 scale = { 50.0,1.0,50.0 };
	objblock->SetScale(scale);

	objblock->Update();
	player = new Player();
	player->Initialize();

	//fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//fbxObject1 = new FbxObject3d;
	//fbxObject1->Initialize();
	//fbxObject1->SetModel(fbxModel1);
	//fbxObject1->SetRotation()


}

void GamePlay::Create2D_object() {

	//Sprite* sprite = Sprite::Create(0, { 0,0, }, false, false);
	//sprites.push_back(sprite);
	//sprite->SetPosition({ 500,300,0 });

	//for (int i = 0; i < 20; i++) {
	//	int texNum = rand() % 2;

	//	sprite = Sprite::Create(texNum, { 0,0 }, false, false);

	//	sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });

	//	//sprite->SetRotation((float)(rand() % 360));

	//	sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });

	//	sprite->TransferVertexBuffer();

	//	sprites.push_back(sprite);
	//	//sprite->SetPosition({ 500,300,0 });

	//}
}

void GamePlay::SpriteLoadTex() {
	SpriteBase* spriteCommon = SpriteBase::GetInstance();
	spriteCommon->LoadTexture(0, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/house.png");

}

void GamePlay::CameraCreateSet() {
	camera = new DebugCamera(WindowsAPP::window_width, WindowsAPP::window_height);

	Object3d::SetCamera(camera);
	FbxObject3d::SetCamera(camera);

	camera->SetTarget({ 0,0,0 });
	camera->SetDistance(20.0f);
	camera->SetEye({ 0,0,0 });
}

void GamePlay::VariableInitialize() {

}

void GamePlay::CameraUpdate() {

	XMFLOAT3 chrpos = player->GetPosition();
	XMVECTOR vTargetEye = { 0.0f,40.0f,60.0f,1.0f };
	XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };
	vTargetEye = XMVector3Transform(vTargetEye, matRot);
	vUp = XMVector3Transform(vUp, matRot);
	float length = 0;
	XMFLOAT3 target1 = camera->GetTarget();
	camera->SetEye(
		{
			target1.x + vTargetEye.m128_f32[0],
			target1.y + vTargetEye.m128_f32[1],
			target1.z + vTargetEye.m128_f32[2]
		});
	camera->SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });
	// 注視点からずらした位置に視点座標を決定
	XMFLOAT3 target2 = camera->GetTarget();
	XMFLOAT3 eye = camera->GetEye();

	XMFLOAT3 fTargetEye = { 0.0f, 0.0f, 0.0f };

	// 大きさ計算
	length = sqrtf(pow(target2.x - eye.x, 2) + pow(target2.y - eye.y, 2) + pow(target2.z - eye.z, 2));
	fTargetEye.x = eye.x - target2.x;
	fTargetEye.y = eye.y - target2.y;
	fTargetEye.z = eye.z - target2.z;

	fTargetEye.x /= length;
	fTargetEye.y /= length;
	fTargetEye.z /= length;

	fTargetEye.x *= 17;
	fTargetEye.y *= 17;
	fTargetEye.z *= 17;

	//camera->SetTarget({ chrpos.x,chrpos.y + 40.0f,chrpos.z - 60.0f });
	//camera->SetDistance(20.0f);
	//camera->SetEye({ chrpos.x,chrpos.y,chrpos.z });
	camera->Update();
}

void GamePlay::ChangeScene() {

	SceneBase* scene = new Title(sceneManager_);
	sceneManager_->SetNextScene(scene);
}

void GamePlay::ClassUpdate() {
	player->Update();
	objblock->Update();
	//fbxObject1->Update();
	for (auto& sprite : sprites)
	{
		sprite->Update();
	}
	CameraUpdate();
}
