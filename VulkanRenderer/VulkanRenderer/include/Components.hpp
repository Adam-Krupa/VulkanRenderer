#pragma once
#include<vector>
#include<glm/glm.hpp>
class Vertex;


struct MeshComponent
{
	std::vector<Vertex> verticies;
	std::vector<uint32_t> indices;
};

struct TransformComponent {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};