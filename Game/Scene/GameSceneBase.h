#pragma once

#include<vector>

#include "Framework.h"


class GameSceneBase : public Framework
{
public:
	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;



private:
};

