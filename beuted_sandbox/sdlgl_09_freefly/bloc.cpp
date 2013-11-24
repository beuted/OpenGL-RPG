#include "bloc.h"
#include "util_fig.h"

Bloc::Bloc(int _type, Face* _face_top, Face* _face_bot, Face* _face_sud, Face* _face_nord, Face* _face_ouest, Face* _face_est) {
  type = type;
  face_sud = _face_sud;
  face_nord = _face_nord ;
  face_est = _face_est ;
  face_ouest = _face_ouest ;
  face_top = _face_top ;
  face_bot = _face_bot ;
} 

Bloc::Bloc() {
  type = 0;
  face_sud =   NULL;//  (new Face(false));
  face_nord =  NULL;
  face_est =   NULL;
  face_ouest = NULL;
  face_top =   NULL;
  face_bot =   NULL;
} 

Bloc::~Bloc() {
}

void Bloc::afficherBloc() {
  dessinerCarre(*this);
}

bool Bloc::isTransparent() {
  if (type == 0 || type == 4)
    return true;
  return false;
}
