#include "mobiles_liste.h"

//TODO: Positionner limits en fct position personnage
void Mobiles_liste::draw() {
	for (std::list<Mobile*>::iterator it = liste_mobiles->begin(), end = liste_mobiles->end(); it != end; ++it) {
			(*it)->dessinerMobile();
	}
}

void Mobiles_liste::deplacerMobiles() {
	for (std::list<Mobile*>::iterator it = liste_mobiles->begin(), end = liste_mobiles->end(); it != end; ++it) {
		(*it)->deplacerMobile();
	}
}

void Mobiles_liste::computeCollisions(Carte* carte) {
	for (std::list<Mobile*>::iterator it = liste_mobiles->begin(), end = liste_mobiles->end(); it != end; ++it) {
		Vector3D* v = NULL;
		if((*it)->collision(carte, v)) {
			// On supprime le projectile
			(*it)->duree_vie = 0;
			// On créé une explosion
			Explosion *m = new Explosion((*it)->position-(*it)->direction * (*it)->speed , (*it)->direction,0);
			// On supprime le cube de la carte touché eventuellement
			if (v != NULL) {
				carte->modifierBloc((int)v->X, (int)v->Y, (int)v->Z, 0);
				carte->remplirListNonTransp();
				carte->remplirListTransp();
			}
			push_front(m);
			break;
		}
	}
}

void Mobiles_liste::supprMobilesMorts() {
	for (std::list<Mobile*>::iterator it = liste_mobiles->begin(), end = liste_mobiles->end(); it != end;) {
		if( (*it)->duree_vie == 0) {
			it = liste_mobiles->erase(it);
		} else {
			++it;
		}
	}
}

void Mobiles_liste::push_front(Mobile* m) {
	liste_mobiles->push_front(m);
}

void Mobiles_liste::remove(Mobile* m) {
	liste_mobiles->remove(m);
}
