SOURCES =	main.cpp \
		sdlglutils.cpp \
		vector3d.cpp \
		freeflycamera.cpp \
		util_fig.cpp \
		carte.cpp \
		srcParticules.cpp \
		bloc.cpp \
		face.cpp \
		personnage.cpp
OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	sdlgl_09_freefly	
LIBS	=	$(shell sdl-config --libs) -lSDL_image -lGL -lGLU 
FLAG    =       -Wall -g -pedantic

all: $(OBJECTS)
	g++ $(FLAG)  $(LIBS) -o $(TARGET) $(OBJECTS)

%o: %cpp
	g++ $(FLAG) -o $@ -c $<

x: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

