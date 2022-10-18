#include "Map.h"
#include "Noise.h"
#include <time.h>

void Map::CreateMap() {
	for (int i = 0; i < BlockNum; i++) {
		blockobj[i] = ObjModel::LoadFromOBJ("block0");
	}

	srand((unsigned)time(NULL));
	float Seed = rand() % 20;
	noise = new Noise();

	noise->SettingHash(Seed);

	for (int i = 0; i < MapX; i++) {
		for (int j = 0; j < MapY; j++) {
			SetPosition({ (float)0 + 32 * i,(float)0,(float)0 + 32 * i }, i, j);
			float MapX, MapZ;
			MapX = GetPointPosition(i, j).x;
			MapZ = GetPointPosition(i, j).z;
			SetPosition({ MapX,noise->SecondPNoise(MapX,MapZ),MapZ }, i, j);
		}
	}

	for (int i = 0; i < MapX; i++) {
		for (int j = 0; j < MapY; j++) {
			for (int k = 0; k < BlockNum; k++) {
				block[k]->SetPosition(map->map[i][j]);
			}
		}
	}

}

void Map::Draw()
{
	for (int i = 0; i < BlockNum; i++) {
		if (map->isDraw[i] == true) {
			block[i]->Draw();
		}
	}

}


