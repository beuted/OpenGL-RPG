SOURCES =	main.cpp \
		parameter_analyser.cpp \
		game.cpp \
		engine.cpp \
		graphics_engine.cpp \
		game_engine.cpp \
		personnage.cpp \
		projectile.cpp \
		explosion.cpp \
		mobile.cpp \
		mobiles_liste.cpp \
		brique_gene.cpp \
		brique.cpp\
		brique_particulaire.cpp\
		face.cpp \
		bloc.cpp \
		carte.cpp \
		freeflycamera.cpp \
		vector3d.cpp \
		util_fig.cpp \
		sdlglutils.cpp \
		gestion_textures.cpp \
		playercamera.cpp \
		skybox.cpp

OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	ftk
LIBS	=	$(shell sdl-config --libs --cflags) -lGL -lGLU -lSDL -lSDL_image -I ../lib/boost_1_53_0/boost/system -lboost_serialization
FLAG    =       -Wall -g -pedantic

all: $(OBJECTS)
	g++ $(FLAG) -o $(TARGET) $(OBJECTS) $(LIBS)

%o: %cpp
	g++ $(FLAG) -o $@ -c $< $(LIBS)

x: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

