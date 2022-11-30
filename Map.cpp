#include "Map.h"
#include "Noise.h"
#include <time.h>

void Map::CreateMap() {


	for (int i = 0; i < MapX; i++) {
		for (int j = 0; j < MapZ; j++) {
			//SetPosition({ 0,0,0 }, i, j);
			map[i][j] = { (float)1.1f + 5.01f * i, (float)0, (float)1.1f + 5.01f * j };
			float Mapx, Mapz;
			Mapx = GetPointPosition(i, j).x;
			Mapz = GetPointPosition(i, j).z;
			float yRand = rand() % 20 + 10;
			map[i][j] = { Mapx,noise->SecondPNoise(Mapx,Mapz)*yRand,Mapz };
		}
	}
	int k = 0;
	for (int i = 0; i < MapX; i++) {
		for (int j = 0; j < MapZ; j++) {
			block[k]->SetPosition(map[i][j]);
			isDraw[k] = true;
			k++;
		}
	}

}

void Map::CreateBlockAndSeed() {

	for (int i = 0; i < BlockNum; i++) {
		blockobj = ObjModel::LoadFromOBJ("block2");
		block[i] = Object3d::Create();
		block[i]->SetModel(blockobj);
		block[i]->SetScale({ 50,50,50 });
		block[i]->Update();
	}

	srand((unsigned)time(NULL));
	float Seed = rand() % 20;
	noise = new Noise();

	noise->SettingHash(Seed);

}

void Map::Draw()
{
	for (int i = 0; i < BlockNum; i++) {
		if (isDraw[i] == true) {
			block[i]->Draw();
		}
	}

}

void Map::Update()
{
	for (int i = 0; i < BlockNum; i++) {
		block[i]->Update();
	}
}


