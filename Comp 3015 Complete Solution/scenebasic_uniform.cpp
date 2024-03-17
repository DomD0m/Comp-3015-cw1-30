#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include "helper/texture.h"

using glm::vec3;
using glm::mat4;
using glm::vec4;
using glm::mat3;
// declaring the Textures variables
GLuint grass; 
GLuint TexID;
GLuint barntex;

SceneBasic_Uniform::SceneBasic_Uniform() : tPrev(0),plane(6.0f,6.0f,50,50)  {
	//loading the meshes
	mesh = ObjMesh::load("media/bread_cat.obj",true);
	barn = ObjMesh::load("media/house.obj", true);
}

void SceneBasic_Uniform::initScene()
{
	// setting up the uniforms and view, projection(aka the FOV).
    compile();
	glEnable(GL_DEPTH_TEST);
	model = mat4(1.0f);
	view = glm::lookAt(vec3(0.0f, 1.25f, 1.25f), vec3(0.0f, 0.2f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(45.0,4.0/3.0,1.0,50.0);
	angle = 0.0f;
	
	prog.setUniform("Light.L", vec3(1.0f));
	prog.setUniform("Light.La", vec3(0.05f));
	prog.setUniform("ModelMatrix", model);
	prog.setUniform("ViewMatrix", view);
	prog.setUniform("ProjectionMatrix", projection);

	// loading the textures from the media file.
	TexID = Texture::loadTexture("media/texture/fire.png");
	grass = Texture::loadTexture("media/texture/moss.png");
	barntex = Texture::loadTexture("media/texture/barn.png");



	// declaring the fog variable numbers.
	prog.setUniform("Fog.MaxDist", 20.0f);
	prog.setUniform("Fog.MinDist", 1.0f);
	prog.setUniform("Fog.Color", vec3(0.5f,0.5f,0.5f));

}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t, glm::vec3 x, glm::vec3 position, glm::vec3 y)
{
	//update code this is able to animate the light to move and the set up the keyboard movement on the camera.
	float deltaT = t - tPrev;
	if (tPrev == 0.0f) deltaT;
	tPrev = t;
	angle += 0.1f * deltaT;
	if (angle > glm::two_pi<float>())angle -= glm::two_pi<float>();
	prog.setUniform("ViewMatrix", view);
	view = glm::lookAt(position, position + x, y);
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//position of the light being declared and using the angle to rotate it.
	vec4 lightpos = vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
	prog.setUniform("Light.Position", vec4(view * lightpos));

	// binding the tex to the model underneath
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexID);
	prog.setUniform("Material.Kd", vec3(0.2f, 0.55f, 0.9f));
	prog.setUniform("Material.Ka", vec3(0.95f, 0.95f, 0.95f));
	prog.setUniform("Material.Ks", vec3(0.2f * 0.3, 0.55f * 0.3, 0.9f * 0.3f));
	prog.setUniform("Material.Shininess", 100.0f);


	model = mat4(1.0f);
	// glm modifiers to be able to rotate the model and translate and scale it to make it fit the scene.
	model = glm::rotate(model, glm::radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, vec3(0.5f, 0.1f, 0.0f));
	model = glm::scale(model, vec3(0.1f, 0.1f, 0.1f));
	setMatrics();
	mesh->render();

	// binding the grass tex to the plane.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grass);
	prog.setUniform("Material.Kd", vec3(0.2f, 0.55f, 0.9f));
	prog.setUniform("Material.Ka", vec3(0.95f, 0.95f, 0.95f));
	prog.setUniform("Material.Ks", vec3(0.7f, 0.7f, 0.7f));
	prog.setUniform("Material.Shininess", 180.0f);


	model = mat4(1.0f);
	setMatrics();
	plane.render();

	// binding the barn tex to the barn mesh.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, barntex);
	prog.setUniform("Material.Kd", vec3(0.2f, 0.55f, 0.9f));
	prog.setUniform("Material.Ka", vec3(0.95f, 0.95f, 0.95f));
	prog.setUniform("Material.Ks", vec3(0.7f, 0.7f, 0.7f));
	prog.setUniform("Material.Shininess", 180.0f);


	model = mat4(1.0f);
	model = glm::scale(model, vec3(0.5f, 0.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, vec3(5.0f, 2.7f, 0.0f));
	
	
	setMatrics();
	barn->render();
}

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
    width = w;
    height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic_Uniform::setMatrics() {
	mat4 mv = view*model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))) ;
	prog.setUniform("MVP", projection*mv);
}