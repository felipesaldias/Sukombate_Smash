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
#include <bullet/btBulletDynamicsCommon.h>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

using namespace std;


Esfera::Esfera(float _rad, float _x , float _y, float _z, float _mass){
	rad= _rad;
	x= _x;
	y= _y;
	z= _z;
	mass= _mass;
	body=NULL;
}

void Esfera::CrearEsfera(btDiscreteDynamicsWorld* dynamicsWorld)
{	
    btTransform t;  
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));  
    btCollisionShape* sphere=new btSphereShape(rad);   
    inertia=  btVector3(0,0,0);
    if(mass!=0.0)
        sphere->calculateLocalInertia(mass,inertia);   
    
    motion=new btDefaultMotionState(t); 
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia); 
    info.m_restitution = 0.0f;
    body=new btRigidBody(info);
    body->setActivationState(DISABLE_DEACTIVATION);    
    dynamicsWorld->addRigidBody(body);  
}

void Esfera::reposition(btVector3 position) {
    btTransform initialTransform;
    initialTransform.setIdentity();

    initialTransform.setOrigin(position);

    body->setWorldTransform(initialTransform);
    body->setAngularVelocity(btVector3(0.0f,0.0f,0.0f));
    body->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
    motion->setWorldTransform(initialTransform);
    body->setActivationState(DISABLE_DEACTIVATION);
}


void Esfera::Dibujar(malla *esfera, GLuint shader_programme, int model_mat_location)
{
    model_mat_location = glGetUniformLocation (shader_programme, "model");
    glm::mat4 auxiliar;
    btTransform x;
    body->getMotionState()->getWorldTransform(x);
    x.getOpenGLMatrix(&auxiliar[0][0]);
    esfera->setModelMatrix(auxiliar);
    esfera->render_indices();
    esfera->draw(model_mat_location);
}

btVector3 Esfera::getPos(){
    btVector3 pos = body->getCenterOfMassPosition();
    return pos;
}
