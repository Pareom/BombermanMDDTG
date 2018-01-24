#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Structures.h"

void sauvegardeMap(FILE *sauvegarde,int map[CoteMAP][CoteMAP],BOMBE bombes[CoteMAP][CoteMAP],FEU feux[CoteMAP][CoteMAP],PERSO** lObjets);
void sauvegardeObjets(FILE *sauvegarde, int nb_objets, PERSO** lObjets);

#endif
