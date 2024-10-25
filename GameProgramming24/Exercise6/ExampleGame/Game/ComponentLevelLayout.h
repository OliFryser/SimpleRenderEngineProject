#pragma once

#include "Engine/Component.h"

class ComponentLevelLayout : public MyEngine::Component {
public:
	void Init(rapidjson::Value&) override;

private:
	int dimX;
	int dimY;
	void PrintLevel(std::vector<int>&);
	void CreateCube(int, int, int);
};