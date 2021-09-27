#OBJS specifies which files to compile as part of the project
OBJS = src/gulp.cpp src/engine.cpp src/gameobject.cpp src/component.cpp src/gamemanager.cpp src/timer.cpp src/displaymanager.cpp src/vector2.cpp src/particle.cpp src/force.cpp src/managers.cpp src/timemanager.cpp src/physicsmanager.cpp src/rigidbody.cpp src/renderer.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gulp

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
