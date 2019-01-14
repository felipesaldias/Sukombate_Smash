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
#include "publico.h"
#include <bullet/btBulletDynamicsCommon.h>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

using namespace std;


Publico::Publico(float _rad, float _altura, float _x, float _y, float _z, float _mass){
	rad= _rad;
	altura= _altura;
	x= _x;
	y= _y;
	z= _z;
    mass= _mass;
	body=NULL;
}

void Publico::CrearPublico(btDiscreteDynamicsWorld* dynamicsWorld)
{   
    btTransform t;  
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));  
    btCollisionShape* cono=new btConeShape(btScalar(rad),btScalar(altura));  
    btVector3 inertia(0,0,0);   
    if(mass!=0.0)
        cono->calculateLocalInertia(mass,inertia);   
    btMotionState* motion=new btDefaultMotionState(t);  
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,cono,inertia); 
    info.m_restitution = 1.0f; 
    body=new btRigidBody(info);
    body->setActivationState(DISABLE_DEACTIVATION);    
    dynamicsWorld->addRigidBody(body);  
}

void Publico::Dibujar(malla *conito, GLuint shader_programme, int model_mat_location)
{
    model_mat_location = glGetUniformLocation (shader_programme, "model");
    glm::mat4 auxiliar;
    btTransform x;
    body->getMotionState()->getWorldTransform(x);
    x.getOpenGLMatrix(&auxiliar[0][0]);
    conito->setModelMatrix(auxiliar);
    conito->render_indices();
    conito->draw(model_mat_location);
}
