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
#include "gltext.hpp"
#include <string>
#include <sstream>
#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"


extern Esfera esferadef;
extern Esfera esferadef1;
extern Esfera esferadef2;
extern Esfera esferadef3;
extern Camera camarita;
extern sound *muerte;
extern sound *lets_play;
///////////////
extern malla *menu;
extern bool pantallamenu;
extern int estadomenu;

int vidas= 3;
int vida_esfera1= vidas;
int vida_esfera2= vidas;
int vida_esfera3= vidas;
int vida_esfera4= vidas;
bool reponer_ono = false;

void inicio_juego(){


    btVector3 posicion1 = esferadef.body->getCenterOfMassPosition();
    btVector3 posicion2 = esferadef1.body->getCenterOfMassPosition();
    btVector3 posicion3 = esferadef2.body->getCenterOfMassPosition();
    btVector3 posicion4 = esferadef3.body->getCenterOfMassPosition();

		gltInit();
    	GLTtext *label= gltCreateText();
        string puntaje("VIDAS-AMARILLO: ");
        string contador;
        contador = static_cast<std::ostringstream*>(&(std::ostringstream() << vida_esfera1))->str();
        gltSetText(label, (puntaje+contador).c_str());
        gltColor(1.f, 1.f, 1.f, 1.f);
        gltDrawText2D(label, 2.0f, 2.f,1.3f);


		gltInit();
    	GLTtext *label2= gltCreateText();
        string puntaje2("VIDAS-AZUL: ");
        string contador2;
        contador2 = static_cast<std::ostringstream*>(&(std::ostringstream() << vida_esfera2))->str();
        gltSetText(label2, (puntaje2+contador2).c_str());
        gltColor(1.f, 1.f, 1.f, 1.f);
        gltDrawText2D(label2, 1220.0f, 2.f,1.3f);


        gltInit();
    	GLTtext *label3= gltCreateText();
        string puntaje3("VIDAS-ROJA: ");
        string contador3;
        contador3 = static_cast<std::ostringstream*>(&(std::ostringstream() << vida_esfera3))->str();
        gltSetText(label3, (puntaje3+contador3).c_str());
        gltColor(1.f, 1.f, 1.f, 1.f);
        gltDrawText2D(label3, 2.0f, 730.f,1.3f);


        gltInit();
    	GLTtext *label4= gltCreateText();
        string puntaje4("VIDAS-VERDE: ");
        string contador4;
        contador4 = static_cast<std::ostringstream*>(&(std::ostringstream() << vida_esfera4))->str();
        gltSetText(label4, (puntaje4+contador4).c_str());
        gltColor(1.f, 1.f, 1.f, 1.f);
        gltDrawText2D(label4, 1200.0f, 730.f,1.3f);


    if( posicion1.getY() <-7 && vida_esfera1>0){
        vida_esfera1= vida_esfera1-1;
        esferadef.reposition(btVector3(-6.0f,1.0f,0.0f));

        if (posicion1.getY() <-0.1){
            muerte->play(); 
            } 
        if (vida_esfera1 == 0) {esferadef.reposition(btVector3(-6.0f,-20.0f,0.0f)); } }

    if( posicion2.getY() <-7 && vida_esfera2>0){
        vida_esfera2= vida_esfera2-1;
        esferadef1.reposition(btVector3(6.0f,1.0f,0.0f));

        if (posicion2.getY() <-0.1){
            muerte->play(); 
            } 
        if (vida_esfera2 == 0) {esferadef1.reposition(btVector3(-6.0f,-20.0f,0.0f)); } }

    if( posicion3.getY() <-7 && vida_esfera3>0){
        vida_esfera3= vida_esfera3-1;
        esferadef2.reposition(btVector3(0.0f,1.0f,5.0f));

        if (posicion3.getY() <-0.1){
            muerte->play(); 
            } 
 
        if (vida_esfera3 == 0) {esferadef2.reposition(btVector3(-6.0f,-20.0f,0.0f));} }

    if( posicion4.getY() <-7 && vida_esfera4>0){
        vida_esfera4= vida_esfera4-1;
        esferadef3.reposition(btVector3(0.0f,1.0f,-5.0f));

        if (posicion4.getY() <-0.1){
            muerte->play(); 
            } 

        if (vida_esfera4 == 0) {esferadef3.reposition(btVector3(-6.0f,-20.0f,0.0f));} }
}

void calcular_ganador(){
    int ve1 = vida_esfera1;
    int ve2 = vida_esfera2;
    int ve3 = vida_esfera3;
    int ve4 = vida_esfera4;

    if (ve1>0 && ve2==0 && ve3==0 && ve4==0){
        menu->load_texture("textures/ganador1.jpeg");
        pantallamenu=true;
        estadomenu=5;
       }

    if (ve2>0 && ve1==0 && ve3==0 && ve4==0){
        menu->load_texture("textures/ganador2.jpeg");
        pantallamenu=true;
        estadomenu=5;
        
    }

    if (ve3>0 && ve2==0 && ve1==0 && ve4==0){
        menu->load_texture("textures/ganador3.jpeg");
        pantallamenu=true;
        estadomenu=5;
        
    }

    if (ve4>0 && ve2==0 && ve3==0 && ve1==0){
        menu->load_texture("textures/ganador4.jpeg");
        pantallamenu=true;
        estadomenu=5;
        
    }
}

void resetear(){

    if(reponer_ono==true){
        esferadef.reposition(btVector3(-6.0f,1.0f,0.0f));
        esferadef1.reposition(btVector3(6.0f,1.0f,0.0f));
        esferadef2.reposition(btVector3(0.0f,1.0f,5.0f));
        esferadef3.reposition(btVector3(0.0f,1.0f,-5.0f));
        reponer_ono=false;

        vida_esfera1= vidas;
        vida_esfera2= vidas;
        vida_esfera3= vidas;
        vida_esfera4= vidas;
        lets_play->play();
    }
}