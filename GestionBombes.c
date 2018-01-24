#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "BmpLib.h"
#include "GfxLib.h"
#include "ESLib.h"
#include "Structures.h"
#include "GestionBombes.h"

void poseBombe(int map[CoteMAP][CoteMAP], BOMBE bombes[CoteMAP][CoteMAP],PERSO* lanceur)
{
	int j = (lanceur->posX+12.5-150)/CASE;
	int i = ((HauteurFenetre-lanceur->posY+12.5)/CASE)-1;
	if(map[i][j] != vBombe && lanceur->nb_bombe<lanceur->nb_max){
		map[i][j] = vBombe;
		
		bombes[i][j].nb_feu = lanceur->nb_feu;
		bombes[i][j].spawn = time(NULL);
		bombes[i][j].Joueur = lanceur;
		lanceur->nb_bombe ++;
	}
}

void poseFeu(int map[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP],int x, int y, int nb_feu, BOMBE bombes[CoteMAP][CoteMAP])
{
	int i;
	for(i=0; i<=nb_feu; i++){
		switch(map[x-i][y])
		{
			case vSolid:
			case vCaisse_Feu:
				i=nb_feu+1;
				break;
			case vCaisse:
				map[x-i][y]=vCaisse_Feu;
				feux[x-i][y].spawn = time(NULL);
				i=nb_feu+1;
				break;
			case vBombe:
				if(i!=0){
					explo(map,feux,x-i,y,bombes);
					i=nb_feu+1;
				}
				else{
					map[x-i][y]=vFeu;
					feux[x-i][y].spawn = time(NULL);
				}
				break;
			default:
				map[x-i][y]=vFeu;
				feux[x-i][y].spawn = time(NULL);
				break;
		}
	}
	for(i=0; i<=nb_feu; i++){
		switch(map[x][y-i])
		{
			case vSolid:
				i=nb_feu+1;
				break;
			case vCaisse:
				map[x][y-i]=vCaisse_Feu;
				feux[x][y-i].spawn = time(NULL);
				i=nb_feu+1;
				break;
			case vBombe:
				if(i!=0){
					explo(map,feux,x,y-i,bombes);
					i=nb_feu+1;
				}
				else{
					map[x][y-i]=vFeu;
					feux[x][y-i].spawn = time(NULL);
				}
				break;
			default:
				map[x][y-i]=vFeu;
				feux[x][y-i].spawn = time(NULL);
				break;
		}
	}
	for(i=0; i<=nb_feu; i++){
		switch(map[x+i][y])
		{
			case vSolid:
				i=nb_feu+1;
				break;
			case vCaisse:
				map[x+i][y]=vCaisse_Feu;
				feux[x+i][y].spawn = time(NULL);
				i=nb_feu+1;
				break;
			case vBombe:
				if(i!=0){
					explo(map,feux,x+i,y,bombes);
					i=nb_feu+1;
				}
				else{
					map[x+i][y]=vFeu;
					feux[x+i][y].spawn = time(NULL);
				}
				
				break;
			
			default:
				map[x+i][y]=vFeu;
				feux[x+i][y].spawn = time(NULL);
				break;
		}
	}
	for(i=0; i<=nb_feu; i++){
		switch(map[x][y+i])
		{
			case vSolid:
				i=nb_feu+1;
				break;
			case vCaisse:
				map[x][y+i]=vCaisse_Feu;
				feux[x][y+i].spawn = time(NULL);
				i=nb_feu+1;
				break;
			case vBombe:
				if(i!=0){
					explo(map,feux,x,y+i,bombes);
					i=nb_feu+1;
				}
				else{
					map[x][y+i]=vFeu;
					feux[x][y+i].spawn = time(NULL);
				}
				break;
			
			default:
				map[x][y+i]=vFeu;
				feux[x][y+i].spawn = time(NULL);
				break;
		}
	}
}

void explo(int map[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP],int x, int y,BOMBE bombes[CoteMAP][CoteMAP])
{
	int nb_feu = bombes[x][y].nb_feu;
	bombes[x][y].spawn=0;
	(bombes[x][y].Joueur)->nb_bombe --;
	bombes[x][y].Joueur=NULL;
	poseFeu(map, feux,x, y, nb_feu, bombes);
}
	
void extinction(int map[CoteMAP][CoteMAP], FEU* pfeu,int x, int y)
{
	int bonus;
	if(map[x][y]==vFeu){
		map[x][y]=vHerbe;
	}
	else{
		bonus=floor(valeurAleatoire()*10);
		switch (bonus)
		{
			case 1:
			case 2:
			case 3:
				map[x][y]=vBonusBombe;
				break;
			case 4:
			case 5:
				map[x][y]=vBonusFeu;
				break;
			default:
				map[x][y]=vHerbe;
				break;
		}
	}
	pfeu->spawn = 0;
}

//
void initbomb(BOMBE bombes[CoteMAP][CoteMAP])
{
	int i,j;
	for (i=0; i<CoteMAP;i++)
	{
		for (j=0; j<CoteMAP;j++)
		{
			bombes[i][j].spawn = 0;
			bombes[i][j].detente = 4;
			bombes[i][j].nb_feu = 1;
			bombes[i][j].Joueur = NULL;
		}
	}
}
void initfeu(FEU feux[CoteMAP][CoteMAP])
{
	int i,j;
	for (i=0; i<CoteMAP;i++)
	{
		for (j=0; j<CoteMAP;j++)
		{
			feux[i][j].spawn = 0;
			feux[i][j].detente = 0.5;
		}
	}
}
void verifbomb(int map[CoteMAP][CoteMAP], BOMBE bombes[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP])
{
	int i,j;
	for (i=0; i<CoteMAP;i++)
	{
		for (j=0; j<CoteMAP;j++)
		{
			if (bombes[i][j].spawn != 0)
			{
				if (difftime(time(NULL),bombes[i][j].spawn) > bombes[i][j].detente)
				{
						explo(map,feux,i,j,bombes);
				}	
			}
		}
	}
}
void veriffeu(int map[CoteMAP][CoteMAP], FEU feux[CoteMAP][CoteMAP])
{
	int i,j;
	for (i=0; i<CoteMAP;i++)
	{
		for (j=0; j<CoteMAP;j++)
		{
			if (feux[i][j].spawn != 0)
			{
				if (difftime(time(NULL),feux[i][j].spawn) > feux[i][j].detente)
				{
					extinction(map,&(feux[i][j]),i,j);
				}
			}
		}
	}
}
