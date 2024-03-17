#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helper/torus.h"
#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/cube.h"


class SceneBasic_Uniform : public Scene
{
private:
    //Torus torus;
    Plane plane;
    Cube cube;
    std::unique_ptr<ObjMesh> mesh;
    std::unique_ptr<ObjMesh> barn;
    GLSLProgram prog;
    float angle;
    float tPrev;
    void setMatrics();
    void compile();

public:
    SceneBasic_Uniform();

    void initScene();
    //updated update to take in more variables to its able to adjust the camera with key inputs.
    void update( float t ,glm::vec3 x, glm::vec3 pos, glm::vec3 y);
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
