#include "Car.h"

Car::Car() {
	m_modelCar = Model();
	m_modelCar.LoadModel("Models/car_body.obj");

	m_modelHood = Model();
	m_modelHood.LoadModel("Models/car_hood.obj");

	m_modelWheel = Model();
	m_modelWheel.LoadModel("Models/car_wheel.obj");
}

void Car::Render(Shader& p_shader, Camera& p_camera, glm::mat4& p_projection, GLfloat deltaTime) {
	p_shader.UseShader();
	m_uniformModel = p_shader.GetModelLocation();
	m_uniformProjection = p_shader.GetProjectionLocation();
	m_uniformView = p_shader.GetViewLocation();
	m_uniformColor = p_shader.getColorLocation();

	glUniformMatrix4fv(m_uniformProjection, 1, GL_FALSE, glm::value_ptr(p_projection));
	glUniformMatrix4fv(m_uniformView, 1, GL_FALSE, glm::value_ptr(p_camera.calculateViewMatrix()));

	glm::mat4 model(1.0f);
	glm::mat4 modelaux(1.0f);

	// Body
	model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.0f + m_pos.x));
	ApplyColor(glm::vec3(0.2f, 0.2f, 0.2f));
	ApplyModel(model);
	m_modelCar.RenderModel();
	modelaux = model;

	// Hood
	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, 0.6f, -1.5f));
	model = glm::rotate(model, glm::radians(m_hoodAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_modelHood.RenderModel();

	// Front left wheel
	glm::vec3 colorBlack(0.0f, 0.0f, 0.0f);
	model = modelaux;
	model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -2.1f));
	model = glm::rotate(model, glm::radians(m_wheelAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyColor(colorBlack);
	ApplyModel(model);
	m_modelWheel.RenderModel();

	// Front right wheel
	model = modelaux;
	model = glm::translate(model, glm::vec3(1.0f, -0.5f, -2.1f));
	model = glm::rotate(model, glm::radians(m_wheelAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyColor(colorBlack);
	ApplyModel(model);
	m_modelWheel.RenderModel();

	// Back left wheel
	model = modelaux;
	model = glm::translate(model, glm::vec3(-1.0f, -0.5f, 1.5f));
	model = glm::rotate(model, glm::radians(m_wheelAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyColor(colorBlack);
	ApplyModel(model);
	m_modelWheel.RenderModel();

	// Back right wheel
	model = modelaux;
	model = glm::translate(model, glm::vec3(1.0f, -0.5f, 1.5f));
	model = glm::rotate(model, glm::radians(m_wheelAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyColor(colorBlack);
	ApplyModel(model);
	m_modelWheel.RenderModel();
}

glm::vec3 Car::CalculateVelocity() {
	return glm::vec3(0, 0, 0);
}

void Car::Advance() {
	m_pos.x -= m_velocity;
}

void Car::Reverse() { m_pos.x += m_velocity; }

void Car::ApplyColor(const glm::vec3& p_color) { glUniform3fv(m_uniformColor, 1, glm::value_ptr(p_color)); }
void Car::ApplyModel(glm::mat4& p_model) { glUniformMatrix4fv(m_uniformModel, 1, GL_FALSE, glm::value_ptr(p_model)); }