#pragma once

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Model.h"
#include "Shader_m.h"
#include "Camera.h"

class Car {
public:
	Car();
	void Render(Shader& p_shader, Camera& p_camera, glm::mat4& p_projection, GLfloat deltaTime);
	void Advance();
	void Reverse();

private:
	void ApplyColor(const glm::vec3& p_color);
	void ApplyModel(glm::mat4& p_model);
	glm::vec3 CalculateVelocity();

public:
	GLfloat m_hoodAngle;
	GLfloat m_wheelAngle;
	GLfloat m_wheelRotation;

private:
	Model m_modelCar, m_modelHood, m_modelWheel;
	GLuint m_uniformModel, m_uniformProjection, m_uniformView, m_uniformColor;
	glm::vec2 m_pos;
	const GLfloat m_velocity = 0.2;
};

