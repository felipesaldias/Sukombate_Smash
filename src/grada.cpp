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
#include "grada.h"
#include <bullet/btBulletDynamicsCommon.h>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

using namespace std;


Grada::Grada(float _tamx, float _tamy , float _tamz, float _x, float _y, float _z, float _mass){
	tamx= _tamx;
	tamy= _tamy;
    tamz=_tamz;
	x= _x;
	y= _y;
	z= _z;
    mass= _mass;
	body=NULL;
}

void Grada::CrearGrada(btDiscreteDynamicsWorld* dynamicsWorld)
{   
    btTransform t;  
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));  
   btCollisionShape* grada=new btBoxShape(btVector3(tamx,tamy,tamz));  
    btVector3 inertia(0,0,0);   
    if(mass!=0.0)
        grada->calculateLocalInertia(mass,inertia);   
    btMotionState* motion=new btDefaultMotionState(t);  
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,grada,inertia); 
    body=new btRigidBody(info);
    body->setActivationState(DISABLE_DEACTIVATION);    
    dynamicsWorld->addRigidBody(body);  
}

void Grada::Dibujar(malla *plano, GLuint shader_programme, int model_mat_location)
{
    model_mat_location = glGetUniformLocation (shader_programme, "model");
    glm::mat4 auxiliar;
    btTransform x;
    body->getMotionState()->getWorldTransform(x);
    x.getOpenGLMatrix(&auxiliar[0][0]);
    plano->setModelMatrix(auxiliar);
    plano->render_indices();
    plano->draw(model_mat_location);
}
