#ifndef PISO_H
#define PISO_H
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

class Piso
{
	private:
		float radx;
		float largo;
		float radz;
		float x;
		float y;
		float z;
		float mass;


	public:
		 btRigidBody* body;
		 
		 Piso(float,float,float,float,float,float,float);

		 void CrearPiso(btDiscreteDynamicsWorld* dynamicsWorld);

		 void Dibujar(malla *esfera,GLuint shader_programme, int model_mat_location);

};

#endif
