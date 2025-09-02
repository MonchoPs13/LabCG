//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <glew.h>
#include <glfw3.h>
//glm
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, -0.25f,
		0.0f, -1.0f, -0.5f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
			-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,18);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);
}

/* Inicio lógica para renderizar la casa */
std::map<std::string, Mesh*> shapes3D;
void initHouseShapes() {
	shapes3D["pyramid"] = meshList[0];
	shapes3D["cube"] = meshList[1];
}

std::map<std::string, Shader> shaders3D;
void initShaders() {
	std::vector<std::pair<const char*, std::string>> shaderFiles{
		{"shaders/shaderBlue.vert", "blue"},
		{"shaders/shaderBrown.vert", "brown"},
		{"shaders/shaderDarkGreen.vert", "green-dark"},
		{"shaders/shaderGreen.vert", "green"},
		{"shaders/shaderRed.vert", "red"}
	};
	
	for (size_t i = 0; i < shaderFiles.size(); i++) {
		Shader* shader = new Shader();
		shader->CreateFromFiles(shaderFiles[i].first, fShader);
		shaders3D[shaderFiles[i].second] = *shader;
	}
}

void renderHouse() {
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	auto renderShape = [&projection](const std::string& shape, const std::string& shader, const glm::mat4& model) {
		shaders3D[shader].useShader();
		GLuint uniformModel = shaders3D[shader].getModelLocation();
		GLuint uniformProjection = shaders3D[shader].getProjectLocation();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		shapes3D[shape]->RenderMesh();
		};

	glm::mat4 model = glm::mat4(1.0);
	model = glm::scale(model, glm::vec3(0.9f, 1.3f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -0.28f, -2.0f));
	renderShape("cube", "red", model);

	model = glm::mat4(1.0);
	model = glm::scale(model, glm::vec3(0.30f, 0.42f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.7f, 0.0f, -1.0f));
	renderShape("cube", "green", model);

	model = glm::mat4(1.0);
	model = glm::scale(model, glm::vec3(0.30f, 0.42f, 1.0f));
	model = glm::translate(model, glm::vec3(0.7f, 0.0f, -1.0f));
	renderShape("cube", "green", model);

	model = glm::mat4(1.0);
	model = glm::scale(model, glm::vec3(0.30f, 0.42f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -1.9f, -1.0f));
	renderShape("cube", "green", model);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 0.595f, -2.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.3f, 1.0f));
	renderShape("pyramid", "blue", model);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-0.75f, -0.85, -2.0f));
	model = glm::scale(model, glm::vec3(0.225f, 0.3f, 1.0f));
	renderShape("cube", "brown", model);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-0.75f, -0.35, -1.0f));
	model = glm::scale(model, glm::vec3(0.225f, 0.35f, 1.0f));
	renderShape("pyramid", "green-dark", model);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.75f, -0.85, -2.0f));
	model = glm::scale(model, glm::vec3(0.225f, 0.3f, 1.0f));
	renderShape("cube", "brown", model);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.75f, -0.35, -1.0f));
	model = glm::scale(model, glm::vec3(0.225f, 0.35f, 1.0f));
	renderShape("pyramid", "green-dark", model);
}
/* Fin lógica de casa */

/* Inicio lógica para renderizar las letras */
std::map<std::string, MeshColor*> letters;

template <size_t N>
void shapeFactoryRGB(const std::string& letterAlias, GLfloat(&vertices)[N], float R, float G, float B) {
	std::vector<GLfloat> verticesRGB;
	for (size_t i = 0; i < N; i++) {
		verticesRGB.push_back(vertices[i]);
		if (i % 3 == 2) {
			verticesRGB.push_back(R);
			verticesRGB.push_back(G);
			verticesRGB.push_back(B);
		}
	}

	GLfloat* verticesArr = new GLfloat[verticesRGB.size()];
	std::copy(verticesRGB.begin(), verticesRGB.end(), verticesArr);

	MeshColor* shape = new MeshColor();
	shape->CreateMeshColor(verticesArr, verticesRGB.size());
	letters[letterAlias] = shape;

	delete[] verticesArr;
}

void initLetters() {
	GLfloat verticesA[] = {
		-1.75f, -0.5f, 0.5f,
		-1.5f, -0.5f, 0.5f,
		-1.5f, 0.5f, 0.5f,

		-1.5f, 0.25f, 0.5f,
		-1.5f, 0.5f, 0.5f,
		-1.25f, 0.25f, 0.5f,
		-1.25f, 0.25f, 0.5f,
		-1.25f, 0.5f, 0.5f,
		-1.5f, 0.5f, 0.5f,

		-1.5f, -0.25f, 0.5f,
		-1.5f, 0.0f, 0.5f,
		-1.25f, -0.25f, 0.5f,
		-1.25f, -0.25f, 0.5f,
		-1.25f, 0.0f, 0.5f,
		-1.5f, 0.0f, 0.5f,

		-1.25f, 0.5f, 0.5f,
		-1.25f, -0.5f, 0.5f,
		-1.0f, -0.5f, 0.5f
	};

	GLfloat verticesM[] = {
		-0.75f, -0.5f, 0.5f,
		-0.75f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.75f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.25f, 0.5f,
		-0.25f, 0.25f, 0.5f,
		-0.5f, 0.25f, 0.5f,
		-0.25f, 0.25f, 0.5f,
		-0.25f, 0.0f, 0.5f,

		-0.25f, 0.25f, 0.5f,
		-0.25f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		-0.25f, 0.25f, 0.5f,
		0.0f, 0.25f, 0.5f,
		0.0f, 0.0f, 0.5f,

		0.0f, 0.0f, 0.5f,
		0.0f, 0.25f, 0.5f,
		0.25f, 0.25f, 0.5f,
		0.0f, 0.25f, 0.5f,
		0.25f, 0.25f, 0.5f,
		0.25f, 0.5f, 0.5f,

		0.25f, -0.5f, 0.5f,
		0.25f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.25f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
	};

	GLfloat verticesL[] = {
		0.75f, -0.5f, 0.5f,
		0.75f, 0.5f, 0.5f,
		1.0f, -0.5f, 0.5f,
		0.75f, 0.5f, 0.5f,
		1.0f, 0.5f, 0.5f,
		1.0f, -0.5f, 0.5f,

		1.0f, -0.5f, 0.5f,
		1.0f, -0.25f, 0.5f,
		1.5f, -0.5f, 0.5f,
		1.0f, -0.25f, 0.5f,
		1.5f, -0.25f, 0.5f,
		1.5f, -0.5f, 0.5f,
	};

	shapeFactoryRGB("A-red", verticesA, 1.0f, 0.0f, 0.0f);
	shapeFactoryRGB("A-purple", verticesA, 0.5f, 0.0f, 0.5f);
	shapeFactoryRGB("M-blue", verticesM, 0.0f, 0.0f, 1.0f);
	shapeFactoryRGB("M-yellow", verticesM, 1.0f, 1.0f, 0.0f);
	shapeFactoryRGB("L-green", verticesL, 0.0f, 1.0f, 0.0f);
	shapeFactoryRGB("L-white", verticesL, 1.0f, 1.0f, 1.0f);
}

void renderLetters() {
	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);

	auto renderShape = [&projection](const std::string& shape, const glm::mat4& model) {
		shaderList[1].useShader();
		GLuint uniformModel = shaderList[1].getModelLocation();
		GLuint uniformProjection = shaderList[1].getProjectLocation();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		letters[shape]->RenderMeshColor();
		};

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 0.0, -2.0f));
	renderShape("A-purple", model);
	renderShape("M-yellow", model);
	renderShape("L-white", model);
}
/* Fin lógica de letras */

void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	//glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	initHouseShapes();
	initShaders();
	initLetters();

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//renderLetters();
		renderHouse();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/