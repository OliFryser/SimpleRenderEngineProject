#pragma once

#include "Engine/Component.h"

class ComponentRendererMesh : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float deltaTime) override;
	void Render(sre::RenderPass& renderPass) override;

private:
	std::shared_ptr<sre::Mesh> _mesh;
	std::shared_ptr<sre::Material> _material;
	std::shared_ptr<sre::Texture> _texture;

	// this should be metadata of the texture, but we are keeping them here for simplicity
	// challenge: associate a json to each texture, with their metadata?
	const glm::vec2 textureSize = glm::vec2(1039, 389);
	const glm::vec2 tileSize = glm::vec2(64, 64);
	const glm::vec2 tileSizeWithBorder = glm::vec2(65, 65);

	const glm::vec2 min = glm::vec2(0 * tileSizeWithBorder.x, 6 * tileSizeWithBorder.y) / textureSize;
	const glm::vec2 max = min + tileSize / textureSize;

	const std::vector<glm::vec3> positions[4] =
	{ 
		// front
		{
			glm::vec3(-.5, -.5, .5),
			glm::vec3(-.5, .5, .5),
			glm::vec3(.5, .5, .5),
			glm::vec3(.5, -.5, .5),
		},
		// back
		{
			glm::vec3(-.5, -.5, -.5),
			glm::vec3(-.5, .5, -.5),
			glm::vec3(.5, .5, -.5),
			glm::vec3(.5, -.5, -.5)
		},
		 
	};
	
	const std::vector<glm::vec4> uvs = 
	{ 
		glm::vec4(min.x, min.y, 0, 0), 
		glm::vec4(min.x, max.y, 0, 0), 
		glm::vec4(max.x, max.y, 0, 0),
		glm::vec4(max.x, min.y, 0, 0),
		
		glm::vec4(max.x, min.y, 0, 0),
		glm::vec4(max.x, max.y, 0, 0),
		glm::vec4(min.x, max.y, 0, 0),
		glm::vec4(min.x, min.y, 0, 0),
	};
	
	const std::vector<uint16_t> idxs[4] =
	{ 
		// front face
		{
			3, 1, 0,
			3, 2, 1,
		},
		// right face
		{
			2, 3, 7,
			7, 6, 2,
		},
		// back face
		{
			7, 5, 6,
			7, 4, 5,
		},
		// left face
		{
			4, 0, 5,
			0, 1, 5
		}
	};
};