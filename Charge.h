#ifndef CHARGE_H
#define CHARGE_H

#include "Structures.h"

int TestSauvegarde();
void chargeMap(FILE *sauvegarde,int map[CoteMAP][CoteMAP],BOMBE bombes[CoteMAP][CoteMAP],FEU feux[CoteMAP][CoteMAP],PERSO** lObjets);
void chargeObjets(FILE *sauvegarde, int* nb_objets, PERSO** lpObjets);

#endif
