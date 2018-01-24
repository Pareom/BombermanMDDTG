#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BmpLib.h"
#include "GfxLib.h"
#include "Structures.h"
#include "Affichage.h"
void lireMap(FILE* fichier, int map[CoteMAP][CoteMAP])//lis la map du fichier txt(lancer une nouvelle partie)
{
	
	int i,j, carac =0;
	for(i=0; i<=CoteMAP; i++){
		for(j=0; j<=CoteMAP; j++){
			carac = fgetc(fichier);
			if(carac != EOF && carac != '\n' && carac != 0){//&& carac != '\n' && carac != ' '
				map[i][j] = carac-48;
			}
			else
				map[i][j] = 0;
		}
	}
}

void afficherTerrain(int map[CoteMAP][CoteMAP])
{
	int i,j;
	static rebondfeu=0;
	static rebondbombe=0;
	static DonneesImageRGB *imageCaisse = NULL;
	imageCaisse = lisBMPRGB("Caisse.bmp"); // L'image de chaque caisse
	static DonneesImageRGB *imageBlocHerbe = NULL;
	imageBlocHerbe = lisBMPRGB("BlocHerbe.bmp");
	static DonneesImageRGB *imageBlocSolid = NULL;
	imageBlocSolid = lisBMPRGB("BlocSolid.bmp");
	static DonneesImageRGB *imageBombe = NULL;
	imageBombe = lisBMPRGB("Bombe.bmp"); 
	static DonneesImageRGB *imageFeu = NULL;
	imageFeu = lisBMPRGB("Feu.bmp"); 
	static DonneesImageRGB *imageBonusFeu = NULL;
	imageBonusFeu = lisBMPRGB("bonus_feu.bmp");
	static DonneesImageRGB *imageBonusBombe = NULL;
	imageBonusBombe = lisBMPRGB("bonus_bombe.bmp");
	static DonneesImageRGB *imageBonusFeu2 = NULL; //rebond feu
	imageBonusFeu2 = lisBMPRGB("bonus_feu2.bmp");
	static DonneesImageRGB *imageBonusBombe2 = NULL; //rebond bombe
	imageBonusBombe2 = lisBMPRGB("bonus_bombe2.bmp");  
	static DonneesImageRGB *imageCaisseFeu = NULL;
	imageCaisseFeu = lisBMPRGB("Caissefeu.bmp");
	epaisseurDeTrait(10);
	static time_t chang=0;
	if(difftime(time(NULL),chang)>=0.02){
		chang=time(NULL);
		if(rebondbombe==0){rebondbombe=1;}
		else{rebondbombe=0;}
		if(rebondfeu==0){rebondfeu=1;}
		else{rebondfeu=0;}
	}
	
	for(i=0;i<CoteMAP;i++)
	{
		for(j=0;j<CoteMAP;j++)
		{
			switch(map[i][j])
			{
				case vHerbe:
					ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBlocHerbe->largeurImage, imageBlocHerbe->hauteurImage, imageBlocHerbe->donneesRGB);
					break;
				case vSolid:
					ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBlocSolid->largeurImage, imageBlocSolid->hauteurImage, imageBlocSolid->donneesRGB);
					break;
				case vCaisse:
					ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageCaisse->largeurImage, imageCaisse->hauteurImage, imageCaisse->donneesRGB);
					break;
				case vBombe:
					ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBombe->largeurImage, imageBombe->hauteurImage, imageBombe->donneesRGB);
					break;
				case vFeu:	
					ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageFeu->largeurImage, imageFeu->hauteurImage, imageFeu->donneesRGB);
					break;	
				case vBonusFeu:
					if(rebondfeu==0){ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBonusFeu->largeurImage, imageBonusFeu->hauteurImage, imageBonusFeu->donneesRGB);}
					else{ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBonusFeu2->largeurImage, imageBonusFeu2->hauteurImage, imageBonusFeu2->donneesRGB);}
					break;
				case vBonusBombe:
					if(rebondbombe==0){ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBonusBombe->largeurImage, imageBonusBombe->hauteurImage, imageBonusBombe->donneesRGB);}
					else{ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageBonusBombe2->largeurImage, imageBonusBombe2->hauteurImage, imageBonusBombe2->donneesRGB);}
					break;
				case vCaisse_Feu:
					ecrisImage(150+j*CASE,HauteurFenetre-(i+1)*CASE, imageCaisseFeu->largeurImage, imageCaisseFeu->hauteurImage, imageCaisseFeu->donneesRGB);
					break;
					
			}
			
			
		}
	}
	free(imageBombe);
	free(imageCaisse);
	free(imageBlocSolid);
	free(imageBlocHerbe);
	free(imageFeu);
	free(imageBonusFeu);
	free(imageBonusBombe);
	free(imageBonusFeu2);
	free(imageBonusBombe2);
	free(imageCaisseFeu);
}
void afficherperso(PERSO *player,int direction, int n_Perso)
{
	if(n_Perso==1){
		static DonneesImageRGB *imagepersobas1 = NULL;
		imagepersobas1 = lisBMPRGB("bas1.bmp");
		static DonneesImageRGB *imagepersobas2 = NULL;
		imagepersobas2 = lisBMPRGB("bas2.bmp");
		static DonneesImageRGB *imagepersohaut1 = NULL;
		imagepersohaut1 = lisBMPRGB("haut1.bmp");
		static DonneesImageRGB *imagepersohaut2 = NULL;
		imagepersohaut2 = lisBMPRGB("haut2.bmp");
		static DonneesImageRGB *imagepersodroite1 = NULL;
		imagepersodroite1 = lisBMPRGB("droite1.bmp");
		static DonneesImageRGB *imagepersodroite2 = NULL;
		imagepersodroite2 = lisBMPRGB("droite2.bmp");
		static DonneesImageRGB *imagepersogauche1 = NULL;
		imagepersogauche1 = lisBMPRGB("gauche1.bmp");
		static DonneesImageRGB *imagepersogauche2 = NULL;
		imagepersogauche2 = lisBMPRGB("gauche2.bmp");
		if(direction==0){ecrisImageTransparent((player->posX),(player->posY-8),imagepersobas1->largeurImage, imagepersobas1->hauteurImage, imagepersobas1->donneesRGB, 0, 255, 0);}
		if(direction==1){ecrisImageTransparent((player->posX),(player->posY-8),imagepersobas2->largeurImage, imagepersobas2->hauteurImage, imagepersobas2->donneesRGB, 0, 255, 0);}
		if(direction==2){ecrisImageTransparent((player->posX),(player->posY-8),imagepersohaut1->largeurImage, imagepersohaut1->hauteurImage, imagepersohaut1->donneesRGB, 0, 255, 0);}
		if(direction==3){ecrisImageTransparent((player->posX),(player->posY-8),imagepersohaut2->largeurImage, imagepersohaut2->hauteurImage, imagepersohaut2->donneesRGB, 0, 255, 0);}
		if(direction==4){ecrisImageTransparent((player->posX),(player->posY-8),imagepersodroite1->largeurImage, imagepersodroite1->hauteurImage, imagepersodroite1->donneesRGB, 0, 255, 0);}
		if(direction==5){ecrisImageTransparent((player->posX),(player->posY-8),imagepersodroite2->largeurImage, imagepersodroite2->hauteurImage, imagepersodroite2->donneesRGB, 0, 255, 0);}
		if(direction==6){ecrisImageTransparent((player->posX),(player->posY-8),imagepersogauche1->largeurImage, imagepersogauche1->hauteurImage, imagepersogauche1->donneesRGB, 0, 255, 0);}
		if(direction==7){ecrisImageTransparent((player->posX),(player->posY-8),imagepersogauche2->largeurImage, imagepersogauche2->hauteurImage, imagepersogauche2->donneesRGB, 0, 255, 0);}
	}
	if(n_Perso==2){
		static DonneesImageRGB *imagepersobas1 = NULL;
		imagepersobas1 = lisBMPRGB("2bas1.bmp");
		static DonneesImageRGB *imagepersobas2 = NULL;
		imagepersobas2 = lisBMPRGB("2bas2.bmp");
		static DonneesImageRGB *imagepersohaut1 = NULL;
		imagepersohaut1 = lisBMPRGB("2haut1.bmp");
		static DonneesImageRGB *imagepersohaut2 = NULL;
		imagepersohaut2 = lisBMPRGB("2haut2.bmp");
		static DonneesImageRGB *imagepersodroite1 = NULL;
		imagepersodroite1 = lisBMPRGB("2droite1.bmp");
		static DonneesImageRGB *imagepersodroite2 = NULL;
		imagepersodroite2 = lisBMPRGB("2droite2.bmp");
		static DonneesImageRGB *imagepersogauche1 = NULL;
		imagepersogauche1 = lisBMPRGB("2gauche1.bmp");
		static DonneesImageRGB *imagepersogauche2 = NULL;
		imagepersogauche2 = lisBMPRGB("2gauche2.bmp");
		if(direction==0){ecrisImageTransparent((player->posX),(player->posY-8),imagepersobas1->largeurImage, imagepersobas1->hauteurImage, imagepersobas1->donneesRGB, 0, 255, 0);}
		if(direction==1){ecrisImageTransparent((player->posX),(player->posY-8),imagepersobas2->largeurImage, imagepersobas2->hauteurImage, imagepersobas2->donneesRGB, 0, 255, 0);}
		if(direction==2){ecrisImageTransparent((player->posX),(player->posY-8),imagepersohaut1->largeurImage, imagepersohaut1->hauteurImage, imagepersohaut1->donneesRGB, 0, 255, 0);}
		if(direction==3){ecrisImageTransparent((player->posX),(player->posY-8),imagepersohaut2->largeurImage, imagepersohaut2->hauteurImage, imagepersohaut2->donneesRGB, 0, 255, 0);}
		if(direction==4){ecrisImageTransparent((player->posX),(player->posY-8),imagepersodroite1->largeurImage, imagepersodroite1->hauteurImage, imagepersodroite1->donneesRGB, 0, 255, 0);}
		if(direction==5){ecrisImageTransparent((player->posX),(player->posY-8),imagepersodroite2->largeurImage, imagepersodroite2->hauteurImage, imagepersodroite2->donneesRGB, 0, 255, 0);}
		if(direction==6){ecrisImageTransparent((player->posX),(player->posY-8),imagepersogauche1->largeurImage, imagepersogauche1->hauteurImage, imagepersogauche1->donneesRGB, 0, 255, 0);}
		if(direction==7){ecrisImageTransparent((player->posX),(player->posY-8),imagepersogauche2->largeurImage, imagepersogauche2->hauteurImage, imagepersogauche2->donneesRGB, 0, 255, 0);}
	}
	if(n_Perso==3){
		static DonneesImageRGB *imagepersobas1 = NULL;
		imagepersobas1 = lisBMPRGB("3bas1.bmp");
		static DonneesImageRGB *imagepersobas2 = NULL;
		imagepersobas2 = lisBMPRGB("3bas2.bmp");
		static DonneesImageRGB *imagepersohaut1 = NULL;
		imagepersohaut1 = lisBMPRGB("3haut1.bmp");
		static DonneesImageRGB *imagepersohaut2 = NULL;
		imagepersohaut2 = lisBMPRGB("3haut2.bmp");
		static DonneesImageRGB *imagepersodroite1 = NULL;
		imagepersodroite1 = lisBMPRGB("3droite1.bmp");
		static DonneesImageRGB *imagepersodroite2 = NULL;
		imagepersodroite2 = lisBMPRGB("3droite2.bmp");
		static DonneesImageRGB *imagepersogauche1 = NULL;
		imagepersogauche1 = lisBMPRGB("3gauche1.bmp");
		static DonneesImageRGB *imagepersogauche2 = NULL;
		imagepersogauche2 = lisBMPRGB("3gauche2.bmp");
		if(direction==0){ecrisImageTransparent((player->posX),(player->posY-8),imagepersobas1->largeurImage, imagepersobas1->hauteurImage, imagepersobas1->donneesRGB, 0, 255, 0);}
		if(direction==1){ecrisImageTransparent((player->posX),(player->posY-8),imagepersobas2->largeurImage, imagepersobas2->hauteurImage, imagepersobas2->donneesRGB, 0, 255, 0);}
		if(direction==2){ecrisImageTransparent((player->posX),(player->posY-8),imagepersohaut1->largeurImage, imagepersohaut1->hauteurImage, imagepersohaut1->donneesRGB, 0, 255, 0);}
		if(direction==3){ecrisImageTransparent((player->posX),(player->posY-8),imagepersohaut2->largeurImage, imagepersohaut2->hauteurImage, imagepersohaut2->donneesRGB, 0, 255, 0);}
		if(direction==4){ecrisImageTransparent((player->posX),(player->posY-8),imagepersodroite1->largeurImage, imagepersodroite1->hauteurImage, imagepersodroite1->donneesRGB, 0, 255, 0);}
		if(direction==5){ecrisImageTransparent((player->posX),(player->posY-8),imagepersodroite2->largeurImage, imagepersodroite2->hauteurImage, imagepersodroite2->donneesRGB, 0, 255, 0);}
		if(direction==6){ecrisImageTransparent((player->posX),(player->posY-8),imagepersogauche1->largeurImage, imagepersogauche1->hauteurImage, imagepersogauche1->donneesRGB, 0, 255, 0);}
		if(direction==7){ecrisImageTransparent((player->posX),(player->posY-8),imagepersogauche2->largeurImage, imagepersogauche2->hauteurImage, imagepersogauche2->donneesRGB, 0, 255, 0);}
	}
}


int afficherpersoanime(int direction,int n_Perso,int x,int y)
{
	if(n_Perso==1){
		static DonneesImageRGB *imagepersobas1 = NULL;
		imagepersobas1 = lisBMPRGB("bas1.bmp");
		static DonneesImageRGB *imagepersohaut1 = NULL;
		imagepersohaut1 = lisBMPRGB("haut1.bmp");
		static DonneesImageRGB *imagepersodroite1 = NULL;
		imagepersodroite1 = lisBMPRGB("droite1.bmp");;
		static DonneesImageRGB *imagepersogauche1 = NULL;
		imagepersogauche1 = lisBMPRGB("gauche1.bmp");
		if(direction==1){ecrisImageTransparent(x,y,imagepersobas1->largeurImage, imagepersobas1->hauteurImage, imagepersobas1->donneesRGB, 0, 255, 0);return 2;}
		if(direction==2){ecrisImageTransparent(x,y,imagepersohaut1->largeurImage, imagepersohaut1->hauteurImage, imagepersohaut1->donneesRGB, 0, 255, 0);return 3;}
		if(direction==3){ecrisImageTransparent(x,y,imagepersodroite1->largeurImage, imagepersodroite1->hauteurImage, imagepersodroite1->donneesRGB, 0, 255, 0);return 4;}
		if(direction==4){ecrisImageTransparent(x,y,imagepersogauche1->largeurImage, imagepersogauche1->hauteurImage, imagepersogauche1->donneesRGB, 0, 255, 0);return 1;}
	}
	if(n_Perso==3){
		static DonneesImageRGB *imagepersobas3 = NULL;
		imagepersobas3 = lisBMPRGB("bas3.bmp");
		static DonneesImageRGB *imagepersohaut3 = NULL;
		imagepersohaut3 = lisBMPRGB("haut3.bmp");
		static DonneesImageRGB *imagepersodroite3 = NULL;
		imagepersodroite3 = lisBMPRGB("droite3.bmp");;
		static DonneesImageRGB *imagepersogauche3 = NULL;
		imagepersogauche3 = lisBMPRGB("gauche3.bmp");
		if(direction==1){ecrisImageTransparent(x,y,imagepersobas3->largeurImage, imagepersobas3->hauteurImage, imagepersobas3->donneesRGB, 0, 255, 0);return 2;}
		if(direction==2){ecrisImageTransparent(x,y,imagepersohaut3->largeurImage, imagepersohaut3->hauteurImage, imagepersohaut3->donneesRGB, 0, 255, 0);return 3;}
		if(direction==3){ecrisImageTransparent(x,y,imagepersodroite3->largeurImage, imagepersodroite3->hauteurImage, imagepersodroite3->donneesRGB, 0, 255, 0);return 4;}
		if(direction==4){ecrisImageTransparent(x,y,imagepersogauche3->largeurImage, imagepersogauche3->hauteurImage, imagepersogauche3->donneesRGB, 0, 255, 0);return 1;}
	}
	if(n_Perso==2){
		static DonneesImageRGB *imagepersobas2 = NULL;
		imagepersobas2 = lisBMPRGB("bas2.bmp");
		static DonneesImageRGB *imagepersohaut2 = NULL;
		imagepersohaut2 = lisBMPRGB("haut2.bmp");
		static DonneesImageRGB *imagepersodroite2 = NULL;
		imagepersodroite2 = lisBMPRGB("droite2.bmp");;
		static DonneesImageRGB *imagepersogauche2 = NULL;
		imagepersogauche2 = lisBMPRGB("gauche2.bmp");
		if(direction==1){ecrisImageTransparent(x,y,imagepersobas2->largeurImage, imagepersobas2->hauteurImage, imagepersobas2->donneesRGB, 0, 255, 0);return 2;}
		if(direction==2){ecrisImageTransparent(x,y,imagepersohaut2->largeurImage, imagepersohaut2->hauteurImage, imagepersohaut2->donneesRGB, 0, 255, 0);return 3;}
		if(direction==3){ecrisImageTransparent(x,y,imagepersodroite2->largeurImage, imagepersodroite2->hauteurImage, imagepersodroite2->donneesRGB, 0, 255, 0);return 4;}
		if(direction==4){ecrisImageTransparent(x,y,imagepersogauche2->largeurImage, imagepersogauche2->hauteurImage, imagepersogauche2->donneesRGB, 0, 255, 0);return 1;}
	}
}
