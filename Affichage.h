#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

void lireMap(FILE* fichier, int map[CoteMAP][CoteMAP]);
void afficherTerrain(int map[CoteMAP][CoteMAP]);
void afficherperso(PERSO *player,int direction, int n_Perso);
int afficherpersoanime(int direction,int n_Perso,int x,int y);

#endif
