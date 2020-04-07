OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/ans
SRCS1=main.cpp utility/cube.cpp utility/shader.cpp utility/camera.cpp utility/texturing.cpp

INCLUDES=

all: $(BIN1) 
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
		
clean:
	rm -f *~ *.o $(BIN1) 
