#ifndef CAMERA_H
#define CAMERA_H
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

class Camera{
	private:
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;

		glm::mat4 projection;
		glm::mat4 view;
		float fov;

	public:

		Camera(glm::vec3,glm::vec3,glm::vec3);
		void CambiarFov(float fov);
		void Actualizar(glm::vec3,glm::vec3,glm::vec3);

		void SetProjection();
		void SetView();
		glm::mat4 GetProjection();
		glm::mat4 GetView();
		void viewmat(GLuint shader_programme);
		void promat(GLuint shader_programme);
		void cargarSky(GLuint skybox_shader);
};


#endif