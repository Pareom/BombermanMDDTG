#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Deplacement.h"


int deplacementhaut(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vyperso)
{	
	int i1,j1,i2,j2,k,l; 
	int p1x,p2x,p1y,p2y,posfinal; // positions
	int test1,test2;
	p1x=posX;p1y=posY+25;p2x=posX+24;p2y=posY+25;
	k=(HauteurFenetre-p1y)/CASE;
	p1y=p1y+vyperso-1;
	p2y=p2y+vyperso-1;
	i1=(HauteurFenetre-p1y)/CASE; //point 1
	l=i1;
	j1=(p1x-150)/CASE;
	test1=map[i1][j1];
	i2=(HauteurFenetre-p2y)/CASE; //point 2
	j2=(p2x-150)/CASE;
	test2=map[i2][j2];
	if((l!=k)&&((test1<=vBombe && test1>=vCaisse) || (test2<=vBombe && test2>=vCaisse))){return posY;}
	if(test1==vFeu || test2==vFeu){(p->vie)=0;return posY;}
	if(test1==vBonusBombe || test2==vBonusBombe)
	{
		(p->nb_max)++;posfinal=posY+vyperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_max)++;}
	}
	if(test1==vBonusFeu || test2==vBonusFeu)
	{
		(p->nb_feu)++;posfinal=posY+vyperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_feu)++;}
	}
	else {posfinal=posY+vyperso;}
	return posfinal;
}
int deplacementbas(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vyperso)
{	
	int i1,j1,i2,j2,k,l; 
	int p1x,p2x,p1y,p2y,posfinal; // positions
	int test1,test2;              //vcorrespondant sur la map
	p1x=posX;p1y=posY+1;p2x=posX+24;p2y=posY+1;
	k=(HauteurFenetre-p1y)/CASE; //point Dep
	p1y=p1y-vyperso;
	p2y=p2y-vyperso;
	i1=(HauteurFenetre-p1y)/CASE; //point 1
	l=i1;//garder pour test
	j1=(p1x-150)/CASE;
	test1=map[i1][j1];
	i2=(HauteurFenetre-p2y)/CASE; //point 2
	j2=(p2x-150)/CASE;
	test2=map[i2][j2];
	if((l!=k)&&((test1<=vBombe && test1>=vCaisse) || (test2<=vBombe && test2>=vCaisse))){return posY;}
	if(test1==vFeu || test2==vFeu){(p->vie)=0;return posY;}
	if(test1==vBonusBombe || test2==vBonusBombe)
	{
		(p->nb_max)++;posfinal=posY-vyperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_max)++;}
	}
	if(test1==vBonusFeu || test2==vBonusFeu)
	{
		(p->nb_feu)++;posfinal=posY-vyperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_feu)++;}
	}
	else {posfinal=posY-vyperso;}
	return posfinal;
}
int deplacementgauche(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vxperso)
{
	int i1,j1,i2,j2,k,l; 
	int p1x,p2x,p1y,p2y,posfinal; // positions
	int test1,test2;
	p1x=posX;p1y=posY+24;p2x=posX;p2y=posY+1;
	k=(p1x-150)/CASE;
	p1x=p1x-vxperso;
	p2x=p2x-vxperso;
	i1=(HauteurFenetre-p1y)/CASE; //point 1
	j1=(p1x-150)/CASE;
	l=j1;
	test1=map[i1][j1];
	i2=(HauteurFenetre-p2y)/CASE; //point 2
	j2=(p2x-150)/CASE;
	test2=map[i2][j2];
	if((l!=k)&&((test1<=vBombe && test1>=vCaisse) || (test2<=vBombe && test2>=vCaisse))){return posX;}
	if(test1==vFeu || test2==vFeu){(p->vie)=0;return posX;}
	if(test1==vBonusBombe || test2==vBonusBombe)
	{
		(p->nb_max)++;posfinal=posX-vxperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_max)++;}
	}
	if(test1==vBonusFeu || test2==vBonusFeu)
	{
		(p->nb_feu)++;posfinal=posX-vxperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_feu)++;}
	}
	else {posfinal=posX-vxperso;}
	return posfinal;
}
int deplacementdroite(int map[CoteMAP][CoteMAP],PERSO *p,int posX,int posY,int vxperso)
{	
	int i1,j1,i2,j2,k,l; 
	int p1x,p2x,p1y,p2y,posfinal; // positions
	int test1,test2;
	p1x=posX+25;p1y=posY+24;p2x=posX+25;p2y=posY+1;
	k=(p2x-151)/CASE;
	p1x=p1x+vxperso-1;
	p2x=p2x+vxperso-1;
	i1=(HauteurFenetre-p1y)/CASE; //point 1
	j1=(p1x-150)/CASE;
	test1=map[i1][j1];
	i2=(HauteurFenetre-p2y)/CASE; //point 2
	j2=(p2x-150)/CASE;
	l=j2;
	test2=map[i2][j2];
	if((l!=k)&&((test1<=vBombe && test1>=vCaisse) || (test2<=vBombe && test2>=vCaisse))){return posX;}
	if(test1==vFeu || test2==vFeu){(p->vie)=0;return posX;}
	if(test1==vBonusBombe || test2==vBonusBombe)
	{
		(p->nb_max)++;posfinal=posX+vxperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_max)++;}
	}
	if(test1==vBonusFeu || test2==vBonusFeu)
	{
		(p->nb_feu)++;posfinal=posX+vxperso;map[i1][j1]=vHerbe;map[i2][j2]=vHerbe;
		if(j1!=j2){(p->nb_feu)++;}
	}
	else {posfinal=posX+vxperso;}
	return posfinal;
}

