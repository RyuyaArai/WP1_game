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
	static const int MapX = 20, MapY = 20;
	static const int BlockNum = MapX * MapY;

	struct MapOption
	{
		XMFLOAT3 map[20][20] = {};
		bool isDraw[BlockNum] = { false };
	};

public:
	void CreateMap();

	void SetPosition(XMFLOAT3 pos,int i,int j) { this->map->map[i][j] = pos; }

	XMFLOAT3 GetPointPosition(int i, int j) { return map->map[i][j]; }

	void Draw();

public:
	MapOption* map = nullptr;

	Object3d* block[BlockNum] = { nullptr };
	ObjModel* blockobj[BlockNum] = { nullptr };
	Noise* noise = nullptr;



};

