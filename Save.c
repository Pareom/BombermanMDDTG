#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Save.h"
#include "Structures.h"

void sauvegardeMap(FILE *sauvegarde,int map[CoteMAP][CoteMAP],BOMBE bombes[CoteMAP][CoteMAP],FEU feux[CoteMAP][CoteMAP],PERSO** lObjets)
{
	int i, j;
	int assocP;
	time_t mnt = time(NULL);
	fwrite(&mnt,sizeof(time_t),1,sauvegarde);
	for(i=0;i<CoteMAP;i++){
		for(j=0;j<CoteMAP;j++){
			fwrite(&map[i][j],sizeof(int),1,sauvegarde);
		}
	}
	for(i=0;i<CoteMAP;i++){
		for(j=0;j<CoteMAP;j++){
			assocP=0;
			fwrite(&bombes[i][j],sizeof(BOMBE),1,sauvegarde);
			if(bombes[i][j].Joueur!=NULL){
				while(bombes[i][j].Joueur!= lObjets[assocP]){assocP++;}
				fwrite(&assocP,sizeof(int),1,sauvegarde);
			}
		}
	}
	for(i=0;i<CoteMAP;i++){
		for(j=0;j<CoteMAP;j++){
			fwrite(&feux[i][j],sizeof(FEU),1,sauvegarde);
		}
	}
    printf("Les Maps sont enregistrées.\n");
}

void sauvegardeObjets(FILE *sauvegarde, int nb_objets, PERSO** lObjets)//A utiliser pour les personnages et les monstres
{
	int i;
	fwrite(&nb_objets,sizeof(int),1,sauvegarde);
	printf(":%d \n",nb_objets);
	for(i=0;i<nb_objets;i++){
		fwrite(lObjets[i],sizeof(PERSO),1,sauvegarde);
	}
    printf("Les Perso/Sbires sont enregistré.\n");
}
