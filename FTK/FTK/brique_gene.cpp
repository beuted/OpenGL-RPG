#include "brique_gene.h"
#include "vector3d.h"
#include <math.h>

void Brique_gene::dessinerBriqueRec() {
	std::vector<Brique_gene*> suivants = getListSuivants();
	glPushMatrix();
	// condition d'arret
	if (suivants.empty()) {
	} else {
	  for (std::vector<Brique_gene*>::iterator it = suivants.begin(); it != suivants.end(); ++it) {
	    glPushMatrix();
	    (*it)->dessinerBrique();
	    (*it)->dessinerBriqueRec();
	    glPopMatrix();
	  }
	}
	glPopMatrix();
}

/* ***** GETTERS ***** */

std::vector<Brique_gene*>& Brique_gene::getListSuivants() {
	return suivants;
}


/* ******** FONCTIONS DE COLLISION ******** */

bool Brique_gene::collisionArbreBriquesToBloc(int i, int j, int k) {
  

  if(collisionBriqueToBloc(i,j,k)) {
    return true;
  } else if(!suivants.empty()) {
    std::vector<Brique_gene*>::iterator it;
    for(it = suivants.begin(); it != suivants.end(); it++) {
	    if ((*it)->collisionArbreBriquesToBloc(i,j,k)) {
	  return true;
      }
    }
    
    return false;
  }
  return false;
}

bool Brique_gene::collisionBriqueToBloc(int i, int j, int k) {
  Vector3D normale_face1_obj1(1,0,0), normale_face2_obj1(0,1,0), normale_face3_obj1(0,0,1);
  Vector3D normale_face1_obj2(1,0,0), normale_face2_obj2(0,1,0), normale_face3_obj2(0,0,1);
  
  double ax = orientation[0];
  double ay = orientation[1];
  double az = orientation[2];  

  Vector3D rx_1(1,0,0);
  Vector3D rx_2(0,cos(ax),-sin(ax));
  Vector3D rx_3(0,sin(ax),cos(ax));

  Vector3D ry_1(cos(ay),0,sin(ay));
  Vector3D ry_2(0,1,0);
  Vector3D ry_3(-sin(ay),0,cos(ay));

  Vector3D rz_1(cos(az),-sin(az),0);
  Vector3D rz_2(sin(az),cos(az),0);
  Vector3D rz_3(0,0,1);

  // Rz * Normale1
  normale_face1_obj1.X = rz_1.scalarProduct(normale_face1_obj1);
  normale_face1_obj1.Y = rz_2.scalarProduct(normale_face1_obj1);
  normale_face1_obj1.Z = rz_3.scalarProduct(normale_face1_obj1);

  // Ry * Normale1
  normale_face1_obj1.X = ry_1.scalarProduct(normale_face1_obj1);
  normale_face1_obj1.Y = ry_2.scalarProduct(normale_face1_obj1);
  normale_face1_obj1.Z = ry_3.scalarProduct(normale_face1_obj1);

  // Rx * Normale1
  normale_face1_obj1.X = rx_1.scalarProduct(normale_face1_obj1);
  normale_face1_obj1.Y = rx_2.scalarProduct(normale_face1_obj1);
  normale_face1_obj1.Z = rx_3.scalarProduct(normale_face1_obj1);

  normale_face1_obj1.normalize();
			  
  // Rz * Normale2
  normale_face2_obj1.X = rz_1.scalarProduct(normale_face2_obj1);
  normale_face2_obj1.Y = rz_2.scalarProduct(normale_face2_obj1);
  normale_face2_obj1.Z = rz_3.scalarProduct(normale_face2_obj1);

  // Ry * Normale2
  normale_face2_obj1.X = ry_1.scalarProduct(normale_face2_obj1);
  normale_face2_obj1.Y = ry_2.scalarProduct(normale_face2_obj1);
  normale_face2_obj1.Z = ry_3.scalarProduct(normale_face2_obj1);

  // Rx * Normale2
  normale_face2_obj1.X = rx_1.scalarProduct(normale_face2_obj1);
  normale_face2_obj1.Y = rx_2.scalarProduct(normale_face2_obj1);
  normale_face2_obj1.Z = rx_3.scalarProduct(normale_face2_obj1);

  normale_face2_obj1.normalize();
			  
  // Rz * Normale3
  normale_face3_obj1.X = rz_1.scalarProduct(normale_face3_obj1);
  normale_face3_obj1.Y = rz_2.scalarProduct(normale_face3_obj1);
  normale_face3_obj1.Z = rz_3.scalarProduct(normale_face3_obj1);

  // Ry * Normale3
  normale_face3_obj1.X = ry_1.scalarProduct(normale_face3_obj1);
  normale_face3_obj1.Y = ry_2.scalarProduct(normale_face3_obj1);
  normale_face3_obj1.Z = ry_3.scalarProduct(normale_face3_obj1);

  // Rx * Normale3
  normale_face3_obj1.X = rx_1.scalarProduct(normale_face3_obj1);
  normale_face3_obj1.Y = rx_2.scalarProduct(normale_face3_obj1);
  normale_face3_obj1.Z = rx_3.scalarProduct(normale_face3_obj1);

  normale_face3_obj1.normalize();

  Vector3D L[15];

  L[0] = normale_face1_obj1;
  L[1] = normale_face2_obj1;
  L[2] = normale_face3_obj1;
  L[3] = normale_face1_obj2;
  L[4] = normale_face2_obj2;
  L[5] = normale_face3_obj2;
  L[6] = normale_face1_obj1.crossProduct(normale_face1_obj2);
  L[7] = normale_face1_obj1.crossProduct(normale_face2_obj2);
  L[8] = normale_face1_obj1.crossProduct(normale_face3_obj2);
  L[9] = normale_face2_obj1.crossProduct(normale_face1_obj2);
  L[10] = normale_face2_obj1.crossProduct(normale_face2_obj2);
  L[11] = normale_face2_obj1.crossProduct(normale_face3_obj2);
  L[12] = normale_face3_obj1.crossProduct(normale_face1_obj2);
  L[13] = normale_face3_obj1.crossProduct(normale_face2_obj2);
  L[14] = normale_face3_obj1.crossProduct(normale_face3_obj2);

  Vector3D T((i+(1/2))-position[0],(j+(1/2))-position[1],(k+(1/2))-position[2]); 

  bool find = false;
  int ind = 0;
  
  double res = 0;
  double sum1 = 0;
  double sum2 = 0;

  while(!find && ind < 15) {
    res = fabs(T.scalarProduct(L[ind]));
    sum1 = dimension[0]*fabs(normale_face1_obj1.scalarProduct(L[ind])) + dimension[1]*fabs(normale_face2_obj1.scalarProduct(L[ind])) + dimension[2]*fabs(normale_face3_obj1.scalarProduct(L[ind])); 
    sum2 = fabs(normale_face1_obj2.scalarProduct(L[ind])) + fabs(normale_face2_obj2.scalarProduct(L[ind])) + fabs(normale_face3_obj2.scalarProduct(L[ind]));
    if (res > sum1 + sum2) {
      find = true;
    }

    ind++;
  }

  return !find;
}
