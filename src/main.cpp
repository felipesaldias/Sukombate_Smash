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
#include "crear_y_mover.h"
#include "camera.h"
#include "publico.h"
#include "init.h"
#include "stb_image.h"
#include "./sound/sound.hpp"
#include "gltext.hpp"
// #include "logicas.h"

#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

///////////////////
#define SKYBOX_VERTEX_SHADER_FILE "shaders/sky_vert.glsl"
#define SKYBOX_FRAGMENT_SHADER_FILE "shaders/sky_frag.glsl"

#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

///////////////////////////////// 
// 1366 768
int g_gl_width = 1366;
int g_gl_height = 768;
GLFWwindow* g_window = NULL;

// timing
float deltaTime = 0.0f; 
float lastFrame = 0.0f;
sound *musica;
sound *musica2;
sound *muerte;
sound *lets_play;



int main(){

    init();


//////////////////////////////////////////////////////////////////////////////////////////

    float points[] = {
        -15.0f, 15.0f,  -15.0f, -15.0f, -15.0f, -15.0f, 15.0f,  -15.0f, -15.0f,
        15.0f,  -15.0f, -15.0f, 15.0f,  15.0f,  -15.0f, -15.0f, 15.0f,  -15.0f,

        -15.0f, -15.0f, 15.0f,  -15.0f, -15.0f, -15.0f, -15.0f, 15.0f,  -15.0f,
        -15.0f, 15.0f,  -15.0f, -15.0f, 15.0f,  15.0f,  -15.0f, -15.0f, 15.0f,

        15.0f,  -15.0f, -15.0f, 15.0f,  -15.0f, 15.0f,  15.0f,  15.0f,  15.0f,
        15.0f,  15.0f,  15.0f,  15.0f,  15.0f,  -15.0f, 15.0f,  -15.0f, -15.0f,

        -15.0f, -15.0f, 15.0f,  -15.0f, 15.0f,  15.0f,  15.0f,  15.0f,  15.0f,
        15.0f,  15.0f,  15.0f,  15.0f,  -15.0f, 15.0f,  -15.0f, -15.0f, 15.0f,

        -15.0f, 15.0f,  -15.0f, 15.0f,  15.0f,  -15.0f, 15.0f,  15.0f,  15.0f,
        15.0f,  15.0f,  15.0f,  -15.0f, 15.0f,  15.0f,  -15.0f, 15.0f,  -15.0f,

        -15.0f, -15.0f, -15.0f, -15.0f, -15.0f, 15.0f,  15.0f,  -15.0f, -15.0f,
        15.0f,  -15.0f, -15.0f, -15.0f, -15.0f, 15.0f,  15.0f,  -15.0f, 15.0f
    };
    GLuint vbosky;
    glGenBuffers( 1, &vbosky );
    glBindBuffer( GL_ARRAY_BUFFER, vbosky );
    glBufferData( GL_ARRAY_BUFFER, 3 * 36 * sizeof( GLfloat ), &points,
                                GL_STATIC_DRAW );

    GLuint vaosky;
    glGenVertexArrays( 1, &vaosky );
    glBindVertexArray( vaosky );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, vbosky );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );


     /*-------------------------------CREATE SHADERS-----------------------*/
        GLuint skybox_shader = create_programme_from_files ( SKYBOX_VERTEX_SHADER_FILE, SKYBOX_FRAGMENT_SHADER_FILE);
        glUseProgram (skybox_shader);
        camarita.cargarSky(skybox_shader);
    	glActiveTexture( GL_TEXTURE0 );
    	glGenTextures( 1, &cube_map_texture );

	     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "textures/back.tga" );
	     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "textures/front.tga"  );
	     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "textures/up.tga" ) ;
	     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "textures/down.tga"  );
	     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "textures/left.tga" ) ;
	     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_X, "textures/right.tga" ) ;

	    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
	    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

/////////////////////////////////////////////////////////////////////////////////////////////
       
     /*-------------------------------CAMARA-------------------------------*/
    GLuint shader_programme = create_programme_from_files (VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
    projection = camarita.GetProjection();
    view = camarita.GetView();
    glUseProgram (shader_programme);
    int model_mat_location = glGetUniformLocation (shader_programme, "model");
    camarita.viewmat(shader_programme);
    camarita.promat(shader_programme);
      /*-------------------------------MUSICA-------------------------------*/
    musica = new sound((char*)"audiowav/kir.wav");
    lets_play = new sound((char*)"audiowav/lets_play.wav");
    musica2 = new sound((char*)"audiowav/rick.wav");
    muerte = new sound((char*)"audiowav/muerte.wav");
    //lets_play->play();
    musica->play();


      /*-------------------------------WHILE-------------------------------*/
    menu->setPosition(glm::vec3(0.0f,0.0f,-5.0f));
    menu->setRotation(0.78f,glm::vec3(-5.0f,0.0f,0.0f));
    menu->setPosition(glm::vec3(0.0f,-2.0f,7.6f));

    while (!glfwWindowShouldClose(g_window)){
        dynamicsWorld->stepSimulation(1.f /2500.f, 10);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(g_window);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram (shader_programme);
    /*-------------------------------DIBUJA OBJETOS-------------------------------*/
        if(pantallamenu){
            model_mat_location = glGetUniformLocation (shader_programme, "model");
            menu->render_indices();
            menu->draw(model_mat_location);

        }
        else{
            DibujaEsfera1(ball1,shader_programme,model_mat_location);
            DibujaEsfera2(ball2,shader_programme,model_mat_location);
            DibujaEsfera3(ball3,shader_programme,model_mat_location);
            DibujaEsfera4(ball4,shader_programme,model_mat_location);
            DibujaGrada(grada,shader_programme,model_mat_location);
            DibujaPiso(piso,shader_programme,model_mat_location);
            DibujaPublico(publicoo,shader_programme,model_mat_location);
            /*-------------------------------LOGICA-------------------------------*/
            resetear();
            inicio_juego();
            calcular_ganador();
            
        }
        camarita.viewmat(shader_programme);
    	camarita.promat(shader_programme);

    	
    	
        
    	
        /*-------------------------------BIND------------------------------*/
        glUseProgram (skybox_shader);
        glDepthMask( GL_FALSE );
        glUseProgram( skybox_shader );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_CUBE_MAP, cube_map_texture );
        glBindVertexArray( vaosky );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glDepthMask( GL_TRUE );        
        glfwSwapBuffers(g_window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


