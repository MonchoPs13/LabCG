#include "Dog.h"

Dog::Dog(glm::mat4 p_projection, std::vector<Mesh*>& p_meshList) 
	: m_projection(p_projection), m_sphere(1.0, 20, 20) {
	m_shapes["cube"] = p_meshList[0];
	m_shapes["pyramid-3"] = p_meshList[1];
	m_shapes["cylinder"] = p_meshList[2];
	m_shapes["cone"] = p_meshList[3];
	m_shapes["pyramid-4"] = p_meshList[4];

	m_sphere.init();
	m_sphere.load();
}

void Dog::Render(Shader& p_shader, Camera& p_camera, std::vector<GLfloat>& p_rotations) {
	p_shader.useShader();
	m_uniformModel = p_shader.getModelLocation();
	m_uniformProjection = p_shader.getProjectLocation();
	m_uniformView = p_shader.getViewLocation();
	m_uniformColor = p_shader.getColorLocation();

	glUniformMatrix4fv(m_uniformProjection, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_uniformView, 1, GL_FALSE, glm::value_ptr(p_camera.calculateViewMatrix()));

	glm::mat4 model(1.0f);
	glm::mat4 modelaux(1.0f);
	glm::mat4 modelHip(1.0f);
	glm::mat4 modelTorso(1.0f);

	/* Torso */
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
	modelaux = model;
	modelTorso = model;

	model = glm::scale(model, glm::vec3(3.0f, 2.0f, 2.0f));
	ApplyModel(model);
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	/* Cadera */
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.75f, 3.0f, 0.75f));
	ApplyColor(glm::vec3(0.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_shapes["cylinder"]->RenderMeshGeometry();
	model = modelaux;
	modelHip = model;

	/* Articulaciones cadera */
	size_t articulationIndex = 0;
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.5f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	// Segunda articulacion cadera
	model = glm::translate(model, glm::vec3(-1.0f - 0.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(-0.5f - 1.5f / 2.0f, 0.0f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	// Tercera articulacion cadera
	model = modelHip;
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, -0.5f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	// Cuarta articulacion cadera
	model = glm::translate(model, glm::vec3(-1.0f - 0.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(-0.5f - 1.5f / 2.0f, 0.0f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	/* Articulaciones torso */
	model = modelTorso;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.5f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	// Segunda articulacion torso
	model = glm::translate(model, glm::vec3(-1.0f - 0.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(-0.5f - 1.5f / 2.0f, 0.0f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	// Tercera articulacion torso
	model = modelTorso;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.0f, 1.5f, -0.5f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	// Cuarta articulacion cadera
	model = glm::translate(model, glm::vec3(-1.0f - 0.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(0.0f, 0.0f, 1.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::translate(model, glm::vec3(-0.5f - 1.5f / 2.0f, 0.0f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	/* Cuello y cabeza */
	model = modelTorso;
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
	ApplyColor(glm::vec3(0.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_shapes["cube"]->RenderMesh();
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.0f, 1.0f + 1.5f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	ApplyColor(glm::vec3(1.0f, 1.0f, 1.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	/* Cola */
	model = modelHip;
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
	model = glm::rotate(model, glm::radians(p_rotations[articulationIndex++]), glm::vec3(1.0f, 0.0f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ApplyColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_sphere.render();
	model = modelaux;

	model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	modelaux = model;
	model = glm::scale(model, glm::vec3(0.3f, 2.5f, 0.3f));
	ApplyColor(glm::vec3(0.0f, 0.0f, 0.0f));
	ApplyModel(model);
	m_shapes["cone"]->RenderMeshGeometry();
	model = modelaux;

}

void Dog::ApplyColor(const glm::vec3& p_color) { glUniform3fv(m_uniformColor, 1, glm::value_ptr(p_color)); }
void Dog::ApplyModel(glm::mat4& p_model) { glUniformMatrix4fv(m_uniformModel, 1, GL_FALSE, glm::value_ptr(p_model)); }
