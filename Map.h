#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include "ObjModel.h"
#include "Noise.h"


class Map
{
private:
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	static const int MapX = 50, MapZ = 50;
	static const int BlockNum = MapX * MapZ;



public:
	void CreateMap();

	void CreateBlockAndSeed();

	void SetPosition(XMFLOAT3 pos,int i,int j) { this->map[i][j] = pos; }

	XMFLOAT3 GetPointPosition(int i, int j) { return map[i][j]; }

	void Draw();

	void Update();

public:

	Object3d* block[BlockNum] = { nullptr };
	//ObjModel* blockobj[BlockNum] = { nullptr };
	ObjModel* blockobj = nullptr;

	Noise* noise = nullptr;

	XMFLOAT3 map[MapX][MapZ] = {};
	bool isDraw[BlockNum] = { false };

};

