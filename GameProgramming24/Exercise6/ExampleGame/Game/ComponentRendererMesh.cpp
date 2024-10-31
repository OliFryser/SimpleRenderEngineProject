#include "ComponentRendererMesh.h"

#include "glm/gtx/transform.hpp"

void ComponentRendererMesh::Init(rapidjson::Value& serializedData) {
    // don't init twice, might not be necessary
    if (_initialized) return;

    int index = serializedData["textureIndex"].GetInt();
    glm::vec2 indices = IndexToVec(index);

    //std::cout << "Index: " << index << ", x: " << indices.x << ", y: " << indices.y << std::endl;

    const glm::vec2 min = glm::vec2(indices.x * tileSizeWithBorder.x, indices.y * tileSizeWithBorder.y) / textureSize;
    const glm::vec2 max = min + tileSize / textureSize;

    const std::vector<glm::vec4> uvs = {
        glm::vec4(min.x, min.y, 0, 0),
        glm::vec4(min.x, max.y, 0, 0),
        glm::vec4(max.x, max.y, 0, 0),
        glm::vec4(max.x, min.y, 0, 0),
    };

    for (int i = 0; i < MESH_COUNT; i++) 
    {
        _meshes[i] = sre::Mesh::create()
            .withPositions(positions[i])
            .withUVs(uvs)
            .withIndices(idxs, sre::MeshTopology::Triangles, 0)
            .build();
    }

    _material = sre::Shader::getUnlit()->createMaterial();

    // we are hardcoding the texture that we want to use here and some if its metadata.
    // Good candidate for properties(yes, those SHOULD be properties) worth moving into a data asset
    _texture = sre::Texture::create().withFile("data/level0.png")
        .withGenerateMipmaps(false)
        .withFilterSampling(false)
        .build();
    _material->setTexture(_texture);

    _initialized = true;
}

void ComponentRendererMesh::Update(float deltaTime) {
    //// uncomment this block to rotate the mesh (useful to see all sides of the cube you are creating, for instance)
    
    /*
    MyEngine::GameObject* gameObject = GetGameObject();
    assert(gameObject);
    
    glm::mat4 transform = gameObject->GetTransform();
    transform = glm::rotate(transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
    gameObject->SetTransform(transform);
    */
    
    // // challenge: this way of of getting a property, updating it, and setting it again, is very verbose.
    // // How could we use pointers to make it more councise? What are the consequences of this choice? (there are pro and cons)
}

void ComponentRendererMesh::Render(sre::RenderPass& renderPass) {
    MyEngine::GameObject* gameObject = GetGameObject();
    assert(gameObject);

    glm::mat4 parentTransform = gameObject->GetTransform();

    for (int i = 0; i < MESH_COUNT; i++)
    {
        renderPass.draw(_meshes[i], parentTransform, _material);
    }
}
