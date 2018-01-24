#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Charge.h"
#include "Structures.h"

int TestSauvegarde()
{
    FILE * f;
	f=fopen("sauvegarde.txt","rb");
	if (f==NULL){return 0;}
	else{return 1;}
}

void chargeMap(FILE *sauvegarde,int map[CoteMAP][CoteMAP],BOMBE bombes[CoteMAP][CoteMAP],FEU feux[CoteMAP][CoteMAP],PERSO** lObjets)
{
	int i, j;
	time_t avant;
	int assocP;
	fread(&avant,sizeof(time_t),1,sauvegarde);
	for(i=0;i<CoteMAP;i++){
		for(j=0;j<CoteMAP;j++){
			fread(&(map[i][j]),sizeof(int),1,sauvegarde);
		}
	}
	for(i=0;i<CoteMAP;i++){
		for(j=0;j<CoteMAP;j++){
			fread(&bombes[i][j],sizeof(BOMBE),1,sauvegarde);
			if(bombes[i][j].spawn!=0){
				bombes[i][j].spawn+=difftime(time(NULL),avant);
				if(bombes[i][j].Joueur!=NULL){
					fread(&assocP,sizeof(int),1,sauvegarde);
					bombes[i][j].Joueur= lObjets[assocP];
				}
			}
		}
	}
	for(i=0;i<CoteMAP;i++){
		for(j=0;j<CoteMAP;j++){
			fread(&feux[i][j],sizeof(FEU),1,sauvegarde);
			if(feux[i][j].spawn!=0)
				feux[i][j].spawn+=difftime(time(NULL),avant);
		}
	}
    printf("Les Maps sont chargés.\n");
}

void chargeObjets(FILE *sauvegarde, int* nb_objets, PERSO** lpObjets)//A utiliser pour les personnages et les monstres
{
	int i;
	fread(nb_objets,sizeof(int),1,sauvegarde);
	printf(":%d \n",*nb_objets);
	for(i=0;i<*nb_objets;i++){
		fread(lpObjets[i],sizeof(PERSO),1,sauvegarde);
	}
    printf("Les Perso/Objets sont chargés.\n");
}
