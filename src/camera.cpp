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
#include "camera.h"
#include <bullet/btBulletDynamicsCommon.h>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

using namespace std;

Camera::Camera(glm::vec3 cameraPos_ ,glm::vec3 cameraFront_ ,glm::vec3 cameraUp_){
	cameraPos= cameraPos_;
	cameraFront= cameraFront_;
	cameraUp= cameraUp_;
	fov = 45.0f;
	projection=glm::perspective(glm::radians(fov), (float)g_gl_width / (float)g_gl_height, 0.1f, 100.0f);
	view=glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::CambiarFov(float fov_){
	fov=fov_;
}

void Camera::Actualizar(glm::vec3 cameraPos_ ,glm::vec3 cameraFront_ ,glm::vec3 cameraUp_){
	cameraPos= cameraPos_;
	cameraFront= cameraFront_;
	cameraUp= cameraUp_;
}

void Camera::SetProjection(){
	projection=glm::perspective(glm::radians(fov), (float)g_gl_width / (float)g_gl_height, 0.1f, 100.0f);
}
void Camera::SetView(){
	view= glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::GetProjection(){
	return projection;
}

glm::mat4 Camera::GetView(){
	return view;
}

void Camera::viewmat(GLuint shader_programme){
	int view_mat_location = glGetUniformLocation (shader_programme, "view");
    glUseProgram (shader_programme);
    glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, &view[0][0]);
	}

void Camera::promat(GLuint shader_programme){
	glUseProgram (shader_programme);
	int proj_mat_location = glGetUniformLocation (shader_programme, "proj");
    glUseProgram (shader_programme);
    glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, &projection[0][0]);
	}
void Camera::cargarSky(GLuint skybox_shader)
{
	
	glUseProgram (skybox_shader);

	int view_skybox = glGetUniformLocation (skybox_shader, "view");
	int proj_skybox = glGetUniformLocation (skybox_shader, "proj");
	glUniformMatrix4fv (view_skybox, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv (proj_skybox, 1, GL_FALSE, &projection[0][0]);
	//int posc_skybox = glGetUniformLocation (skybox_shader, "poscam");
	//glUniform3f(posc_skybox, 1, GL_FALSE, cameraPos[0]);


}