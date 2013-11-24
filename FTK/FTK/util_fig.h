#ifndef UTIL_FIG_H
#define UTIL_FIG_H

#include "bloc.h"

void chargerTextures();
void dessinerCarre(const Bloc &bloc);

// Dessine un retangle

//          /-----/
//      b  /     / |
//        /     /  |
//       -------  /
//    c  |     | /
//       -------
//          a 
void dessinerRectangle(float a, float b, float c, GLuint* textures);

void supprimerTextures();



#endif //UTIL_FIG_H
