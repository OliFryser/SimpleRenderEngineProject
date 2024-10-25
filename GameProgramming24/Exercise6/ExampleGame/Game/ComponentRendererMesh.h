#pragma once

#include "Engine/Component.h"

class ComponentRendererMesh : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float deltaTime) override;
	void Render(sre::RenderPass& renderPass) override;

private:
	static const int MESH_COUNT = 4;

	std::shared_ptr<sre::Mesh> _meshes[MESH_COUNT];
	std::shared_ptr<sre::Material> _material;
	std::shared_ptr<sre::Texture> _texture;

	// this should be metadata of the texture, but we are keeping them here for simplicity
	// challenge: associate a json to each texture, with their metadata?
	const glm::vec2 textureSize = glm::vec2(1039, 389);
	const glm::vec2 tileSize = glm::vec2(64, 64);
	const glm::vec2 tileSizeWithBorder = glm::vec2(65, 65);

	const glm::vec2 min = glm::vec2(0 * tileSizeWithBorder.x, 6 * tileSizeWithBorder.y) / textureSize;
	const glm::vec2 max = min + tileSize / textureSize;

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
	
	const std::vector<glm::vec4> uvs = 
	{ 
		glm::vec4(min.x, min.y, 0, 0), 
		glm::vec4(min.x, max.y, 0, 0), 
		glm::vec4(max.x, max.y, 0, 0),
		glm::vec4(max.x, min.y, 0, 0),
	};
	
	const std::vector<uint16_t> idxs =
	{ 
		3, 1, 0,
		3, 2, 1,
	};
};