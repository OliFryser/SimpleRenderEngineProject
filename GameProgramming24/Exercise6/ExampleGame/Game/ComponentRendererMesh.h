#pragma once

#include "Engine/Component.h"

class ComponentRendererMesh : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float deltaTime) override;
	void Render(sre::RenderPass& renderPass) override;

private:
	bool _initialized;

	static const int MESH_COUNT = 4;

	std::shared_ptr<sre::Mesh> _meshes[MESH_COUNT];
	std::shared_ptr<sre::Material> _material;
	std::shared_ptr<sre::Texture> _texture;

	// this should be metadata of the texture, but we are keeping them here for simplicity
	// challenge: associate a json to each texture, with their metadata?
	const glm::vec2 textureSize = glm::vec2(1039, 389);
	const glm::vec2 tileSize = glm::vec2(64, 64);
	const glm::vec2 tileSizeWithBorder = glm::vec2(65, 65);

	const glm::vec2 textureDim = glm::vec2((textureSize.x + 1) / tileSizeWithBorder.x, (textureSize.y + 1) / tileSizeWithBorder.y);

	/*
	  5------6
	 /|  	/|
	1------2 | 
	| |	   | |
	| 4----|-7
	|/	   |/
	0------3
	*/

	const std::vector<glm::vec3> positions[MESH_COUNT] =
	{ 
		// front
		{
			glm::vec3(-.5, -.5, .5), // 0
			glm::vec3(-.5, .5, .5), // 1
			glm::vec3(.5, .5, .5), // 2
			glm::vec3(.5, -.5, .5), // 3
		},
		// right
		{
			glm::vec3(.5, -.5, .5), // 3
			glm::vec3(.5, .5, .5), // 2
			glm::vec3(.5, .5, -.5), // 6
			glm::vec3(.5, -.5, -.5) // 7
		},
		// back
		{
			glm::vec3(.5, -.5, -.5), // 7
			glm::vec3(.5, .5, -.5), // 6
			glm::vec3(-.5, .5, -.5), // 5
			glm::vec3(-.5, -.5, -.5), // 4
		},
		// left
		{
			glm::vec3(-.5, -.5, -.5), // 4
			glm::vec3(-.5, .5, -.5), // 5
			glm::vec3(-.5, .5, .5), // 1
			glm::vec3(-.5, -.5, .5), // 0
		},
	};
	
	
	
	const std::vector<uint16_t> idxs =
	{ 
		3, 1, 0,
		3, 2, 1,
	};

	inline glm::vec2 IndexToVec(int index) 
	{
		return glm::vec2(fmodf(index, textureDim.x), floorf(index / textureDim.x));
	}
};