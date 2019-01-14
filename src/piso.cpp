#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "gl_utils.h"
#include "tools.h"
#include "malla.h"
#include "GLDebugDrawer.hpp"
#include "esfera.h"
#include "piso.h"
#include <bullet/btBulletDynamicsCommon.h>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

using namespace std;


Piso::Piso(float _radx, float _largo , float _radz, float _x, float _y, float _z, float _mass){
	radx= _radx;
	largo= _largo;
    radz=_radz;
	x= _x;
	y= _y;
	z= _z;
    mass= _mass;
	body=NULL;
}

void Piso::CrearPiso(btDiscreteDynamicsWorld* dynamicsWorld)
{
    btTransform t;  
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));  
    btCollisionShape* base = new btCylinderShape(btVector3(radx,largo,radz+1.0));  
    btVector3 inertia(0,0,0);   
    if(mass!=0.0)
        base->calculateLocalInertia(mass,inertia);   
    btMotionState* motion=new btDefaultMotionState(t);  
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,base,inertia);   
    body=new btRigidBody(info);
    body->setActivationState(DISABLE_DEACTIVATION);    
    dynamicsWorld->addRigidBody(body);  
}

void Piso::Dibujar(malla *piso, GLuint shader_programme, int model_mat_location)
{
    model_mat_location = glGetUniformLocation (shader_programme, "model");
    glm::mat4 auxiliar;
    btTransform x;
    body->getMotionState()->getWorldTransform(x);
    x.getOpenGLMatrix(&auxiliar[0][0]);
    piso->setModelMatrix(auxiliar);
    piso->render_indices();
    piso->draw(model_mat_location);
}
