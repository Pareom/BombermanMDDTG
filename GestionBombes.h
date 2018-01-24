#ifndef GESTIONBOMBES_H
#define GESTIONBOMBES_H

#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

void poseBombe(int map[CoteMAP][CoteMAP], BOMBE bombes[CoteMAP][CoteMAP],PERSO* lanceur);
void poseFeu(int map[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP],int x, int y, int nb_feu,BOMBE bombes[CoteMAP][CoteMAP]);
void explo(int map[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP],int x, int y,BOMBE bombes[CoteMAP][CoteMAP]);
void extinction(int map[CoteMAP][CoteMAP], FEU* pfeu,int x, int y);
void initbomb(BOMBE bombes[CoteMAP][CoteMAP]);
void initfeu(FEU feux[CoteMAP][CoteMAP]);
void verifbomb(int map[CoteMAP][CoteMAP], BOMBE bombes[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP]);
void veriffeu(int map[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP]);

#endif
