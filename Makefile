CC=g++
#SRC=src/enemigo.cpp src/maths_funcs.cpp src/gl_utils.cpp src/main.cpp
SRC=src/*.cpp src/*.c src/sound/*.cpp
LIBS=`pkg-config --libs freealut` -lGL -lGLEW -lglfw -lassimp -lLinearMath -lBulletDynamics -lBulletCollision 
INCLUDE=-I/usr/include/bullet 
EXEC=bin/prog

all: 
	${CC} ${SRC} ${FLAGS}  ${INCLUDE} ${LIBS} -o ${EXEC} 


clear:
	rm bin/*
