#ifndef ROBOT_H
#define ROBOT_H
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Affichage.h"
int verifposebombe(int map[CoteMAP][CoteMAP],PERSO *p,int ModeDeJeu,PERSO *p1,PERSO *p2);
int verifmortrobot(int map[CoteMAP][CoteMAP],PERSO *p);
void deplacementrobot(int direction,PERSO *p);
int verifrobot(int map[CoteMAP][CoteMAP],PERSO *p,int lastmove);
int verifbombehaut(int map[CoteMAP][CoteMAP],int posi,int posj);
int verifbombebas(int map[CoteMAP][CoteMAP],int posi,int posj);
int verifbombedroite(int map[CoteMAP][CoteMAP],int posi,int posj);
int verifbombegauche(int map[CoteMAP][CoteMAP],int posi,int posj);
int vdeplacementhaut(int map[CoteMAP][CoteMAP],int posi,int posj);
int vdeplacementbas(int map[CoteMAP][CoteMAP],int posi,int posj);
int vdeplacementdroite(int map[CoteMAP][CoteMAP],int posi,int posj);
int vdeplacementgauche(int map[CoteMAP][CoteMAP],int posi,int posj);
#endif
