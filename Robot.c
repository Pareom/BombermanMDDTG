#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Structures.h"
#include "Robot.h"
int verifposebombe(int map[CoteMAP][CoteMAP],PERSO *p,int ModeDeJeu,PERSO *p1,PERSO *p2)
{
	int i,j,i1,j1,i2,j2,blocs=0;
	i=(HauteurFenetre-(p->posY))/CASE; 
	j=((p->posX)-150)/CASE;
	i1=(HauteurFenetre-(p1->posY))/CASE; 
	j1=((p1->posX)-150)/CASE;
	i2=(HauteurFenetre-(p2->posY))/CASE; 
	j2=((p2->posX)-150)/CASE;
	if(ModeDeJeu==f1VIA)
	{
		if(i==i1 && j==j1){return 1;}
	}
	if(ModeDeJeu==f2VIA)
	{
		if(i==i1 && j==j1){return 1;}
		if(i==i2 && j==j2){return 1;}
	}
	if(map[i+1][j]==vCaisse || map[i+1][j]==vSolid){blocs=blocs+1;}
	if(map[i-1][j]==vCaisse || map[i-1][j]==vSolid){blocs=blocs+1;}
	if(map[i][j+1]==vCaisse || map[i][j+1]==vSolid){blocs=blocs+1;}
	if(map[i][j-1]==vCaisse || map[i][j-1]==vSolid){blocs=blocs+1;}
	if(blocs==3){return 1;}
	return 0;
}
int verifmortrobot(int map[CoteMAP][CoteMAP],PERSO *p)
{
	int i=(HauteurFenetre-(p->posY))/CASE; 
	int j=((p->posX)-150)/CASE;
	if(map[i][j]==vFeu){(p->vie)=(p->vie)-1;}
	if(map[i][j]==vBonusBombe){(p->nb_max)=(p->nb_max)+1;map[i][j]=vHerbe;}
	if(map[i][j]==vBonusFeu){(p->nb_feu)=(p->nb_feu)+1;map[i][j]=vHerbe;}
	if((p->vie)<=0){return 1;}
	return 0;
}
void deplacementrobot(int direction,PERSO *p)
{
	if(direction==1)
	{
		int posfinale=(p->posY)+30;
		while((p->posY)!=posfinale){(p->posY)=(p->posY)+5;}
	}
	if(direction==2)
	{
		int posfinale=(p->posX)+30;
		while((p->posX)!=posfinale){(p->posX)=(p->posX)+5;}
	}
	if(direction==3)
	{
		int posfinale=(p->posY)-30;
		while((p->posY)!=posfinale){(p->posY)=(p->posY)-5;}
	}
	if(direction==4)
	{
		int posfinale=(p->posX)-30;
		while((p->posX)!=posfinale){(p->posX)=(p->posX)-5;}
	}
	
}
int verifrobot(int map[CoteMAP][CoteMAP],PERSO *p,int lastmove)
{
	//demandeTemporisation(200);
	int i=(HauteurFenetre-(p->posY))/CASE; 
	int j=((p->posX)-150)/CASE;
	if(verifbombehaut(map,i,j)==1)
	{
		if(vdeplacementdroite(map,i,j)==1 && lastmove!=4){return 2;}
		if(vdeplacementgauche(map,i,j)==1 && lastmove!=2){return 4;}
		if(vdeplacementbas(map,i,j)==1){return 3;}
	}
	if(verifbombebas(map,i,j)==1)
	{
		if(vdeplacementdroite(map,i,j)==1 && lastmove!=4){return 2;}
		if(vdeplacementgauche(map,i,j)==1 && lastmove!=2){return 4;}
		if(vdeplacementhaut(map,i,j)==1){return 1;}
	}
	if(verifbombedroite(map,i,j)==1)
	{
		if(vdeplacementhaut(map,i,j)==1 && lastmove!=3){return 1;}
		if(vdeplacementbas(map,i,j)==1 && lastmove!=1){return 3;}
		if(vdeplacementgauche(map,i,j)==1){return 4;}
	}
	if(verifbombegauche(map,i,j)==1)
	{
		if(vdeplacementhaut(map,i,j)==1 && lastmove!=3){return 1;}
		if(vdeplacementbas(map,i,j)==1 && lastmove!=1){return 3;}
		if(vdeplacementdroite(map,i,j)==1){return 2;}
	}
	if(vdeplacementhaut(map,i,j)==1){return 1;}
	if(vdeplacementdroite(map,i,j)==1){return 2;}
	if(vdeplacementbas(map,i,j)==1){return 3;}
	if(vdeplacementgauche(map,i,j)==1){return 4;}
	return 0;
}
int verifbombehaut(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int i=posi;
	int vtest=map[i][posj];
	while(vtest!=vCaisse || vtest!=vSolid)
	{
		vtest=map[i][posj];
		if(vtest==vBombe){return 1;}
		i--;	
	}
	return 0;
}
int verifbombebas(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int i=posi;
	int vtest=map[i][posj];
	while(vtest!=vCaisse || vtest!=vSolid)
	{
		vtest=map[i][posj];
		if(vtest==vBombe){return 1;}
		i++;	
	}
	return 0;
}
int verifbombedroite(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int j=posj;
	int vtest=map[posi][j];
	while(vtest!=vCaisse || vtest!=vSolid)
	{
		vtest=map[posi][j];
		if(vtest==vBombe){return 1;}
		j++;	
	}
	return 0;
}
int verifbombegauche(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int j=posj;
	int vtest=map[posi][j];
	while(vtest!=vCaisse || vtest!=vSolid)
	{
		vtest=map[posi][j];
		if(vtest==vBombe){return 1;}
		j--;	
	}
	return 0;
}
int vdeplacementhaut(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int j=posj;
	int vtest=map[posi-1][j];
	if(vtest==vCaisse || vtest==vSolid || vtest==vCaisse_Feu || vtest==vFeu || vtest==vBombe){return 0;}
	for(j=1;j<3;j++)
	{
		vtest=map[posi-1][posj+j];
		if(vtest==vBombe && map[posi-1][posj+j-1]==0){return 0;}
		vtest=map[posi-1][posj-j];
		if(vtest==vBombe && map[posi-1][posj-j-1]==0){return 0;}
	}
	return 1;
}
int vdeplacementbas(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int j=posj;
	int vtest=map[posi+1][j];//printf("%d",vtest);
	if(vtest==vCaisse || vtest==vSolid || vtest==vCaisse_Feu || vtest==vFeu || vtest==vBombe){return 0;}
	for(j=1;j<3;j++)
	{
		vtest=map[posi+1][posj+j];
		if(vtest==vBombe && map[posi+1][posj+j-1]==0){return 0;}
		vtest=map[posi+1][posj-j];
		if(vtest==vBombe && map[posi+1][posj-j+1]==0){return 0;}
	}
	return 1;
}
int vdeplacementdroite(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int i=posi;
	int vtest=map[i][posj+1];
	if(vtest==vCaisse || vtest==vSolid || vtest==vCaisse_Feu|| vtest==vFeu || vtest==vBombe){return 0;}
	for(i=1;i<3;i++)
	{
		vtest=map[posi+i][posj+1];
		if(vtest==vBombe && map[posi+i-1][posj+1]==0){return 0;}
		vtest=map[posi-i][posj+1];
		if(vtest==vBombe && map[posi-i+1][posj+1]==0){return 0;}
	}
	return 1;
}
int vdeplacementgauche(int map[CoteMAP][CoteMAP],int posi,int posj)
{
	int i=posi;
	int vtest=map[i][posj-1];
	if(vtest==vCaisse || vtest==vSolid || vtest==vCaisse_Feu || vtest==vFeu || vtest==vBombe){return 0;}
	for(i=1;i<3;i++)
	{
		vtest=map[posi+i][posj-1];
		if(vtest==vBombe && map[posi+i-1][posj-1]==0){return 0;}
		vtest=map[posi-i][posj-1];
		if(vtest==vBombe && map[posi-i+1][posj-1]==0){return 0;}
	}
	return 1;
}
