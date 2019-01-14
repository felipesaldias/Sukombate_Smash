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
#include "camera.h"
#include "grada.h"
#include "publico.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <stdlib.h>
#include <time.h>
#include "skybox.h"
#include "stb_image.h"
#include <iostream>
#include "./sound/sound.hpp"
#include "arbitro.h"
#include <unistd.h>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

GLuint cube_map_texture;
extern sound *musica;
extern sound *musica2;
extern malla *menu;
extern bool m,me,pantallamenu;
extern int estadomenu;
////////////////////////////////////////////////////////////

bool load_cube_map_side( GLuint texture, GLenum side_target, const char *file_name ) {
    
    glBindTexture( GL_TEXTURE_CUBE_MAP, texture );

    int x, y, n;
    int force_channels = 4;
    unsigned char *image_data = stbi_load( file_name, &x, &y, &n, force_channels );
    if ( !image_data ) {
        fprintf( stderr, "ERROR: could not load %s\n", file_name );
        return false;
    }
    // non-power-of-2 dimensions check
    if ( ( x & ( x - 1 ) ) != 0 || ( y & ( y - 1 ) ) != 0 ) {
        fprintf( stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name );
    }

    // copy image data into 'target' side of cube map
    glTexImage2D( side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data );
    free( image_data );
    return true;
}

////////////////////////////////////////////////////

/*-------------------------------// CREA OBJETOS // -----------------------------*/
 Esfera esferadef(1.0,-6,0.1,0,1.0);
 Esfera esferadef1(1.0,6,0.1,0,1.0);
 Esfera esferadef2(1.0,0,0.1,5,1.0);
 Esfera esferadef3(1.0,0,0.1,-5,1.0);
 Piso pisodef(8,0,6.5,0,0,-2,0);
 Grada gradita(4.0f,0.1f,2.0f,0.0f,6.0f,-5.0f,0.0f);
 Grada gradita2(4.0f,0.1f,2.0f,0.0f,8.0f,-5.0f,0.0f);
 Publico publi(1.0f,1.6f,-2.5f,7.0f,-5.0f,1.0f);
 Publico publi2(1.0f,1.6f,0.0f,7.0f,-5.0f,1.0f);
 Publico publi3(1.0f,1.6f,2.5f,7.0f,-5.0f,1.0f);
 SkyBox cielo(0.0);

 glm::mat4 projection;
 glm::mat4 view;
 extern bool reponer_ono;
 

/*-------------------------------// CREA OBJETO CAMARA //-------------------------------*/
 Camera camarita(glm::vec3(0.0f, 10.0f, 11.0f),glm::vec3(-0.0026795f, -0.714323f, -0.714323f),glm::vec3(0.0f, 10.0f, 0.0f));

 

void processInput(GLFWwindow *window){

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        reponer_ono=true;
        resetear();

    //PELOTA 1

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        esferadef.body->applyForce(btVector3(0,0,-10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        esferadef.body->applyForce(btVector3(0,0,10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        esferadef.body->applyForce(btVector3(-10,0,0),btVector3(1, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      	esferadef.body->applyForce(btVector3(10,0,0),btVector3(1, 0, 0));

    //PELOTA 2

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        esferadef1.body->applyForce(btVector3(0,0,-10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        esferadef1.body->applyForce(btVector3(0,0,10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        esferadef1.body->applyForce(btVector3(-10,0,0),btVector3(1, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        esferadef1.body->applyForce(btVector3(10,0,0),btVector3(1, 0, 0));

    //PELOTA 3

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        esferadef2.body->applyForce(btVector3(0,0,-10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        esferadef2.body->applyForce(btVector3(0,0,10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        esferadef2.body->applyForce(btVector3(-10,0,0),btVector3(1, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        esferadef2.body->applyForce(btVector3(10,0,0),btVector3(1, 0, 0));

    //PELOTA 4

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        esferadef3.body->applyForce(btVector3(0,0,-10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
       esferadef3.body->applyForce(btVector3(0,0,10),btVector3(0, 0, 1));

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        esferadef3.body->applyForce(btVector3(-10,0,0),btVector3(1, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
       esferadef3.body->applyForce(btVector3(10,0,0),btVector3(1, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
       esferadef3.body->applyForce(btVector3(10,0,0),btVector3(1, 0, 0));

   	//Diferentes vistas de camara

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
       camarita.CambiarFov(45.0f);
   	   camarita.SetProjection();
   	   projection= camarita.GetProjection();
    }

   	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
       camarita.CambiarFov(55.0f);
   	   camarita.SetProjection();
   	   projection= camarita.GetProjection();
    }


   	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
   		camarita.Actualizar(glm::vec3(0.0f, 10.0f, 11.0f),glm::vec3(-0.0026795f, -0.714323f, -0.714323f),glm::vec3(0.0f, 10.0f, 0.0f));
        camarita.SetView();
        view=camarita.GetView();
    }

   	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){
   		camarita.Actualizar(glm::vec3(0.0f, 10.0f, 14.0f),glm::vec3(-0.0026795f, -0.514323f, -0.914323f),glm::vec3(0.0f, 10.0f, 0.0f));
        camarita.SetView();
        view=camarita.GetView();
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "textures/back1.tga" );
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "textures/front1.tga"  );
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "textures/up1.tga" ) ;
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "textures/down1.tga"  );
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "textures/left1.tga" ) ;
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_X, "textures/right1.tga" ) ;
     musica2->stop();
     musica->stop();
     musica2->play();
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "textures/back.tga" );
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "textures/front.tga"  );
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "textures/up.tga" ) ;
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "textures/down.tga"  );
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "textures/left.tga" ) ;
     load_cube_map_side( cube_map_texture, GL_TEXTURE_CUBE_MAP_POSITIVE_X, "textures/right.tga" ) ;
     musica->stop();
     musica2->stop();
     musica->play();
    }
    
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        if(m){
            estadomenu=(estadomenu+1)%3;
            if(estadomenu==0){
                menu->load_texture("textures/menu1.jpeg");
            }
            if(estadomenu==1){
                menu->load_texture("textures/menu2.jpeg");
            }
            if(estadomenu==2){
                menu->load_texture("textures/menu3.jpeg");
            }
            m=false;
        }
        
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE){
        m=true;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE){
        me=true;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
        if(me){
             me=false;
            if(pantallamenu){
                
                if(estadomenu==0){
                    pantallamenu=false;
                    reponer_ono=true;
                    //resetear();
                }
                else if(estadomenu==1){
                    menu->load_texture("textures/menu4.jpeg");
                    estadomenu=4;
                }
                else if(estadomenu==2){
                    glfwSetWindowShouldClose(window, true);
                }
                else if(estadomenu==4){
                    menu->load_texture("textures/menu1.jpeg");
                    estadomenu=0;
                }
                if(estadomenu==5){
                    menu->load_texture("textures/menu1.jpeg");
                    estadomenu=0;
                }
            }
        }


    }
     
    


  //para el publico
    srand(time(NULL));
    int x=1;
    int ale=rand()%3;
    int ale2=rand()%2;
    int ale3=rand()%4;
    	if (x==ale)
        	publi.body->applyCentralImpulse(btVector3(0,0.2,0));
        if (x==ale2)
        	publi2.body->applyCentralImpulse(btVector3(0,0.2,0));
        if (x==ale3)
        	publi3.body->applyCentralImpulse(btVector3(0,0.2,0));

}

void DibujaEsfera1(malla*ball1,GLuint shader_programme, int model_mat_location ){

        esferadef.Dibujar(ball1,shader_programme, model_mat_location);
}

void DibujaEsfera2(malla*ball2,GLuint shader_programme, int model_mat_location ){

        esferadef1.Dibujar(ball2,shader_programme, model_mat_location);
}

void DibujaEsfera3(malla*ball3,GLuint shader_programme, int model_mat_location ){

        esferadef2.Dibujar(ball3,shader_programme, model_mat_location);
}

void DibujaEsfera4(malla*ball4,GLuint shader_programme, int model_mat_location ){

        esferadef3.Dibujar(ball4,shader_programme, model_mat_location);
}

void DibujaPiso(malla*piso,GLuint shader_programme, int model_mat_location ){

        pisodef.Dibujar(piso,shader_programme,model_mat_location);

}

void DibujaGrada(malla*grada,GLuint shader_programme, int model_mat_location ){

        gradita.Dibujar(grada,shader_programme,model_mat_location);
        gradita2.Dibujar(grada,shader_programme,model_mat_location);
}

void DibujarCielo(malla*skycielo,GLuint shader_programme, int model_mat_location){
		cielo.Dibujar(skycielo,shader_programme,model_mat_location);
}


void DibujaPublico(malla*publicoo,GLuint shader_programme, int model_mat_location ){

        publi.Dibujar(publicoo,shader_programme,model_mat_location);
        publi2.Dibujar(publicoo,shader_programme,model_mat_location);
        publi3.Dibujar(publicoo,shader_programme,model_mat_location);

}



