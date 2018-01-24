#ifndef MENUFINAL1_H
#define MENUFINAL1_H
#include "Structures.h"
void cercle(float centreX, float centreY, float rayon);
void OPTION(EvenementGfx evenement, int * pfenetre ,int * pmenuAct);
void MENU1(EvenementGfx evenement,int * pfenetre ,int * pmenuAct,int map[CoteMAP][CoteMAP],BOMBE bombes[CoteMAP][CoteMAP],FEU feux[CoteMAP][CoteMAP], int* n_Sbire,PERSO** lpObjets);
void MENU2(EvenementGfx evenement, int * pfenetre ,int *pmenuAct,int *pModeDeJeu);
void MENU3(EvenementGfx evenement, int * pfenetre ,int *pmenuAct,int *pDiffDuJeu,int *pModeDeJeu);
void MENU4(EvenementGfx evenement, int * pfenetre ,int *pmenuAct,int *pModeDeJeu,int *pDiffDuJeu);
void OPTIONCOMMANDE(EvenementGfx evenement,int *pfenetre,int * pmenuAct);
void OPTIONSKIN(EvenementGfx evenement,int *pfenetre,int * pmenuAct);

#endif
