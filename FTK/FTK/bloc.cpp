#include "bloc.h"
#include "util_fig.h"

Bloc::Bloc(int _type, Face* _face_top, Face* _face_bot, Face* _face_sud,
		Face* _face_nord, Face* _face_ouest, Face* _face_est) {
	type = type;
	face_sud = _face_sud;
	face_nord = _face_nord;
	face_est = _face_est;
	face_ouest = _face_ouest;
	face_top = _face_top;
	face_bot = _face_bot;
}

Bloc::Bloc() {
	type = 0;
	face_sud = NULL;
	face_nord = NULL;
	face_est = NULL;
	face_ouest = NULL;
	face_top = NULL;
	face_bot = NULL;
}

Bloc::~Bloc() {
	if (face_sud != NULL)
		delete face_sud;
	if (face_nord != NULL)
		delete face_nord;
	if (face_est != NULL)
		delete face_est;
	if (face_ouest != NULL)
		delete face_ouest;
	if (face_top != NULL)
		delete face_top;
	if (face_bot != NULL)
		delete face_bot;
}

void Bloc::afficherBloc() {
	dessinerCarre(*this);
}

bool Bloc::isTransparent() const {
	if (type == 0 || type == 4)
		return true;
	return false;
}

bool Bloc::isTransparent() {
	if (type == 0 || type == 4)
		return true;
	return false;
}

