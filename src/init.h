    /*-------------------------------// DEFINICIONES DE MALLAS Y MUNDO //-------------------------------*/
 malla *sky;
 malla *ball1;
 malla *ball2;
 malla *ball3;
 malla *ball4;
 malla *piso;
 malla *grada;
 malla *publicoo;
 malla *menu;
 btDiscreteDynamicsWorld* dynamicsWorld;
 bool m,me;
 bool pantallamenu;
 int estadomenu = 0;

void init(){

    m=true;
    me=true;
    pantallamenu=true;
    restart_gl_log ();
    start_gl ();
    glEnable (GL_DEPTH_TEST); 
    glDepthFunc (GL_LESS); 
    glEnable (GL_CULL_FACE); 
    glCullFace (GL_BACK); 
    glFrontFace (GL_CCW); 
    glClearColor (0.2, 0.2, 0.2, 1.0); 
    glViewport (0, 0, g_gl_width, g_gl_height);

   /*-------------------------------// CREA LAS MALLAS//-------------------------------*/

    ball1 = new malla((char*)"mallas/ball.obj");
    ball1->load_texture("textures/dragon1.png");

    ball2 = new malla((char*)"mallas/ball.obj");
    ball2->load_texture("textures/dragon2.png");

    ball3 = new malla((char*)"mallas/ball.obj");
    ball3->load_texture("textures/dragon3.png");

    ball4 = new malla((char*)"mallas/ball.obj");
    ball4->load_texture("textures/dragon4.png");

    piso = new malla((char*)"mallas/piso3.obj");
    piso->load_texture("textures/fondopisos.png");

    grada= new malla((char*)"mallas/grada.obj");
    grada->load_texture("textures/grada.jpg");

    publicoo= new malla((char*)"mallas/publico.obj");
    publicoo->load_texture("textures/publico.jpg");

    menu= new malla((char*)"mallas/telon16.obj");
    menu->load_texture("textures/menu1.jpeg");

    //skycielo= new malla((char*)"mallas/sky-s.obj");
   // skycielo->load_texture("textures/sky.jpg");


    /*-------------------------------// Configuracion inical del mundo fisico Bullet //-------------------------------*/
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    /*-------------------------------// Crea cuerpo fisica de los objetos //-------------------------------*/
    pisodef.CrearPiso(dynamicsWorld);
    esferadef.CrearEsfera(dynamicsWorld);
    esferadef1.CrearEsfera(dynamicsWorld);
    esferadef2.CrearEsfera(dynamicsWorld);
    esferadef3.CrearEsfera(dynamicsWorld);
    gradita.CrearGrada(dynamicsWorld);
    gradita2.CrearGrada(dynamicsWorld);
    publi.CrearPublico(dynamicsWorld);
    publi2.CrearPublico(dynamicsWorld);
    publi3.CrearPublico(dynamicsWorld);
}