#pragma once

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\random.hpp>

#include <vector>
#include <map>
#include <string>
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Sphere.h"

class Dog {
public:
	Dog(glm::mat4 p_projection, std::vector<Mesh*>& p_meshList);
	void Render(Shader& p_shader, Camera& p_camera, std::vector<GLfloat>& p_rotations);

private:
	void ApplyColor(const glm::vec3& p_color);
	void ApplyModel(glm::mat4& p_model);

private:
	GLuint m_uniformModel, m_uniformProjection, m_uniformView, m_uniformColor;
	glm::mat4 m_projection;
	std::map<std::string, Mesh*> m_shapes;
	Sphere m_sphere;
};

