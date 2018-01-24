#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "Structures.h"
int deplacementhaut(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vyperso);
int deplacementbas(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vyperso);
int deplacementgauche(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vxperso);
int deplacementdroite(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vxperso);

#endif
