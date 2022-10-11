#include "Player.h"
#include "DirectXBase.h"
#include "Input.h"


void Player::Initialize() {
	FbxObject3d::SetDevice(DirectXBase::GetInstance()->GetDev());
	FbxObject3d::CreateGraphicsPipeline();

	jump.isJump = false;
	jump.isDouble = false;
	jump.isglide = false;
	jump.fallSpeed = 2.0f;


	modelChr = ObjModel::LoadFromOBJ("chr_sword");
	objChr = Object3d::Create();
	objChr->SetModel(modelChr);
	objChr->SetPosition({ +10,50,+5 });
	objChr->Update();


}

void Player::Finalize() {
	delete modelChr;
	delete objChr;
}

void Player::Update() {
	Input* input = Input::GetInstance();

	if (objChr->GetPosition().y > 0.0f) {
		XMFLOAT3 chrpos = objChr->GetPosition();

		if (jump.isglide == true) {
			if (jump.fallSpeed <= 0.3f) {
				jump.fallSpeed += 0.1f;
			}
			if (jump.fallSpeed >= 0.3f) {
				jump.fallSpeed -= 0.03f;
			}
		}
		else {
			jump.fallSpeed += 0.3f;

		}
		objChr->SetPosition({ chrpos.x,chrpos.y - jump.fallSpeed,chrpos.z });

	}

	if (objChr->GetPosition().y <= 0.0f) {
		objChr->SetPosition({ objChr->GetPosition().x, 0, objChr->GetPosition().z });
		jump.isJump = false;
		jump.isDouble = false;
		jump.isglide = false;
		jump.fallSpeed = 0.0f;
	}

	if (input->TriggerKey(DIK_SPACE)) {
		XMFLOAT3 chrpos = objChr->GetPosition();

		if (jump.isglide == false && jump.isDouble == true) {
			jump.isglide = true;
		}
		else if (jump.isglide == true) {
			jump.isglide = false;
		}

		if (jump.isDouble == false && jump.isJump == true) {
			jump.isDouble = true;
			jump.fallSpeed -= 6.0f;
		}

		if (jump.isJump == false) {
			jump.isJump = true;
			jump.fallSpeed -= 6.0f;
		}

		objChr->SetPosition({ chrpos.x,chrpos.y - jump.fallSpeed,chrpos.z });

	}


	// À•W‘€ì
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) ||
		input->PushKey(DIK_D) || input->PushKey(DIK_A)) {

		float move = 3.0;
		XMFLOAT3 chrpos = objChr->GetPosition();

		
		if (input->PushKey(DIK_D)) {
			chrpos.x += move;
			if (jump.isglide == true) {
				objChr->SetRotation({ 0,0,-20 });
			}
		}
		if (input->PushKey(DIK_A)) {
			chrpos.x -= move;
			if (jump.isglide == true) {
				objChr->SetRotation({ 0,0,20 });
			}
		}
		if (input->PushKey(DIK_W)) {
			chrpos.z += move;
			if (jump.isglide == true) {
				objChr->SetRotation({ 20,0,0 });
			}
		}
		if (input->PushKey(DIK_S)) {
			chrpos.z -= move;
			if (jump.isglide == true) {
				objChr->SetRotation({ -20,0,0 });
			}
		}

		objChr->SetPosition(chrpos);
		if (jump.isglide == false) {
			objChr->SetRotation({ 0,0,0 });
		}
	}
	else {
		objChr->SetRotation({ 0,0,0 });
	}

	objChr->Update();
}

void Player::Draw() {
	Object3d::PreDraw(DirectXBase::GetInstance()->GetCmdList());
	objChr->Draw();
	Object3d::PostDraw();
}
