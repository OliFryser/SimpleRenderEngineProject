#pragma once

#include "Engine/Component.h"

class ComponentLevelLayout : public MyEngine::Component {
public:
	void Init(rapidjson::Value&) override;

private:
	void CreateCube(int, int, int);
};