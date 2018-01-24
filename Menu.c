#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "Menu.h"
#include "Structures.h"
#include "Charge.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 8; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}
void OPTION(EvenementGfx evenement, int * pfenetre ,int * pmenuAct)
{	
	static int pointMENU = 1 ;
	static DonneesImageRGB *image=NULL;
	static int xBalle,yBalle;
	if (*pmenuAct!=*pfenetre)
				{ 
					*pmenuAct=*pfenetre;
					image = lisBMPRGB("MENUV2.bmp");			
					demandeTemporisation(20);
					xBalle = largeurFenetre()/4;
					yBalle = hauteurFenetre()/1.55;
				}
			switch (evenement)
			{	
			
				case Temporisation:
				rafraichisFenetre();
					break;
			
				case Affichage:
					effaceFenetre(255,255,255);
			// Affichage d'une image
					if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'imageq
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
					
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("COMMANDE", 30, largeurFenetre()/3.5, hauteurFenetre()/1.6);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("SKIN DU JOUEUR", 30, largeurFenetre()/3.5, hauteurFenetre()/2);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("AUDIO", 30, largeurFenetre()/3.5, hauteurFenetre()/2.666667);
				}
					couleurCourante(255, 255, 255);
					cercle(xBalle, yBalle, 10);
							
					break;
			
			case Clavier:
				
				switch (caractereClavier())
				{
					/* Pour sortir quelque peu proprement du programme */
					case 27:
						*pfenetre=fMenu1;
						libereDonneesImageRGB(&image);
						break;
					
					case 13:
					case 'p':// 1J VS IA
						if (pointMENU==1)
						{
						*pfenetre=OptionCommande;
						break;
						}
						else if (pointMENU==2)
						{
							
							*pfenetre=OptionSkin;
							break;
						}
						else
						{
							
							*pfenetre=fMenu4;
						}	
						break;	
					
				}	
				break;
			
			case ClavierSpecial:
				
				switch(toucheClavier())
				{
					case ToucheFlecheBas :
						if (pointMENU==1)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMENU=2;
							break;
						}
					 	else 
					 	{ 	
							pointMENU=3;
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/2.5;
							break;
						}
						
					case ToucheFlecheHaut :
						if (pointMENU==3)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMENU=2;
							break;
						}
					 	else if (pointMENU==2)
					 	{ 	
							
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.55;
							pointMENU=1;
							break;
						}
				}		
				break;
		
	}	
}	
void MENU1(EvenementGfx evenement,int * pfenetre ,int * pmenuAct,int map[CoteMAP][CoteMAP],BOMBE bombes[CoteMAP][CoteMAP],FEU feux[CoteMAP][CoteMAP], int* n_Sbire,PERSO** lpObjets)
{
	static int pointMenu=1;
	FILE* sauvegarde=NULL;
	static DonneesImageRGB *image=NULL;
	static int xBalle,yBalle;
	int n_Perso = 0;
	PERSO lObjets[10];
	 
	if (*pmenuAct!=*pfenetre)
			{ 	
				
				pointMenu=1;
				*pmenuAct=*pfenetre;
				image = lisBMPRGB("MENUV2.bmp");
				
				demandeTemporisation(20);
								
				xBalle = largeurFenetre()/4;
				yBalle = hauteurFenetre()/1.55;
			}
			switch (evenement)
			{	
				
				case Temporisation:  // RafraichiFenetre pour afficher les changements
				rafraichisFenetre();
				break;
			case Affichage:
				
				effaceFenetre(0,0,0);
				// Affichage d'une image
				
				if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'image
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
					
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(4);
					afficheChaine("NOUVELLE PARTIE", 30, largeurFenetre()/3.5, hauteurFenetre()/1.6);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(4);
					afficheChaine("CHARGER UNE PARTIE", 30, largeurFenetre()/3.5, hauteurFenetre()/2);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("OPTION", 30, largeurFenetre()/3.5, hauteurFenetre()/2.666667);
				}
				
				couleurCourante(255, 255, 255);
				cercle(xBalle, yBalle, 10);
				
				break;
			
			case Clavier:
				
				switch (caractereClavier())
				{
					 /* Pour sortir quelque peu proprement du programme */
					case 27://ECHAP
					libereDonneesImageRGB(&image); /* On libere la structure image,
					c'est plus propre, meme si on va sortir du programme juste apres */
					termineBoucleEvenements();
						break;
					case 13:
					case 'p':// NOUVELLE PARTIE
						if (pointMenu==1)
						{
						*pfenetre=fMenu2;
						break;
						}
						else if (pointMenu ==2)//ICI ON CHARGE
						{
							if(TestSauvegarde()==1){
								sauvegarde = fopen("sauvegarde.txt", "rb");
								fseek(sauvegarde,0,SEEK_SET);
								chargeMap(sauvegarde, map, bombes, feux, lpObjets);
								chargeObjets(sauvegarde,  &n_Perso, lpObjets);
								chargeObjets(sauvegarde,  n_Sbire, &lpObjets[2]);
								if(n_Perso==1)
									{*pfenetre=f1VIA;}
								else{
									if(*n_Sbire==0){*pfenetre=f1V1;}
									else{*pfenetre=f2VIA;}
								}
								fclose(sauvegarde);
							}
						 break;
						} 
						else 
						{
							*pfenetre=Option;
						}	
						break;
				}	
				break;
			
			case ClavierSpecial:
				switch (toucheClavier())
				{
					
					case ToucheFlecheBas :
						if (pointMenu==1)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMenu=2;
							break;
						}
					 	else 
					 	{ 	
							pointMenu=3;
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/2.5;
							break;
						}
						
					case ToucheFlecheHaut :
						if (pointMenu==3)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMenu=2;
							break;
						}
					 	else if (pointMenu==2)
					 	{ 	
							
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.55;
							pointMenu=1;
							break;
						}
				}	
				
				break;	
			
		}
			
}	
void MENU2(EvenementGfx evenement, int * pfenetre ,int *pmenuAct,int *pModeDeJeu)
{	static int pointMenu=1;
	static DonneesImageRGB *image=NULL;
	static int xBalle,yBalle;
	if (*pmenuAct!=*pfenetre)
				{ 
					*pmenuAct=*pfenetre;
					pointMenu=1;
					image = lisBMPRGB("MENUV2.bmp");			
					demandeTemporisation(20);
					xBalle = largeurFenetre()/4;
					yBalle = hauteurFenetre()/1.55;
				}
			switch (evenement)
			{	
			
			case Temporisation:
				rafraichisFenetre();
				break;
			
			case Affichage:
				effaceFenetre(255,255,255);
			// Affichage d'une image
				if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'imageq
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
					
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("JOUEUR VS IA", 30, largeurFenetre()/3.5, hauteurFenetre()/1.6);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("2 JOUEUR VS IA", 30, largeurFenetre()/3.5, hauteurFenetre()/2);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("JOUEUR VS JOUEUR", 30, largeurFenetre()/3.5, hauteurFenetre()/2.666667);
				}
				couleurCourante(255, 255, 255);
				cercle(xBalle, yBalle, 10);
							
			break;
			
			case Clavier:
				
				switch (caractereClavier())
				{
					 /* Pour sortir quelque peu proprement du programme */
					case 27:
						*pfenetre=fMenu1;
						libereDonneesImageRGB(&image);
						break;
					
					case 13:
					case 'p':// 1J VS IA
						if (pointMenu==1)
						{
							*pModeDeJeu=1;
							*pfenetre=fMenu3;
						break;
						}
						else if (pointMenu==2)
						{
							*pModeDeJeu=2;
							*pfenetre=fMenu3;
							break;
						}
						else
						{
							*pModeDeJeu=3;
							*pfenetre=f1V1;
						}	
						break;	
					
				}	
				break;
			
			case ClavierSpecial:
				
				switch(toucheClavier())
				{
					case ToucheFlecheBas :
						if (pointMenu==1)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMenu=2;
							break;
						}
					 	else 
					 	{ 	
							pointMenu=3;
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/2.5;
							break;
						}
						
					case ToucheFlecheHaut :
						if (pointMenu==3)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMenu=2;
							break;
						}
					 	else if (pointMenu==2)
					 	{ 	
							
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.55;
							pointMenu=1;
							break;
						}
				}		
				break;	
		}
}	
void MENU3(EvenementGfx evenement, int * pfenetre ,int *pmenuAct,int *pDiffDuJeu,int *pModeDeJeu)
{
	static int pointMenu=1;
	static DonneesImageRGB *image=NULL;
	static int xBalle,yBalle;
	if (*pmenuAct!=*pfenetre)
				{ // IL NE FAIT QU UNE FOIS
					*pmenuAct=*pfenetre;
					pointMenu=1;
					image = lisBMPRGB("MENUV2.bmp");
					xBalle = largeurFenetre()/4;
					yBalle = hauteurFenetre()/1.55;			
					demandeTemporisation(20);
				}
		
		switch (evenement)
			{	
			case Temporisation:
				rafraichisFenetre();
				break;
			
			case Affichage:
	
			// Affichage d'une image
				if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'image
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("FACILE", 30, largeurFenetre()/3.5, hauteurFenetre()/1.6);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("NORMAL", 30, largeurFenetre()/3.5, hauteurFenetre()/2);
					couleurCourante(255, 255, 255);
					epaisseurDeTrait(3);
					afficheChaine("DIFFICILE", 30, largeurFenetre()/3.5, hauteurFenetre()/2.666667);
				}
				couleurCourante(255, 255, 255);
				cercle(xBalle, yBalle, 10);
				break;
			
			case Clavier:
				
				switch (caractereClavier())
				{
					/* Pour sortir quelque peu proprement du programme */
					case 27:
						libereDonneesImageRGB(&image);
						*pfenetre=fMenu2;
						break;
						
					case 13:
					case 'p':
						if (pointMenu==1)
						{
							*pDiffDuJeu=1;
							*pfenetre=fMenu4;
							if(*pModeDeJeu==1)
								*pfenetre=f1VIA;
							if(*pModeDeJeu==2)
								*pfenetre=f2VIA;
							break;
						}
						else if	(pointMenu==2)
						{
							*pDiffDuJeu=2;
							*pfenetre=fMenu4;
							if(*pModeDeJeu==1)
								*pfenetre=f1VIA;
							if(*pModeDeJeu==2)
								*pfenetre=f2VIA;
							break;
						}
						else 
						{
							*pDiffDuJeu=3;
							*pfenetre=fMenu4;
							if(*pModeDeJeu==1)
								*pfenetre=f1VIA;
							if(*pModeDeJeu==2)
								*pfenetre=f2VIA;
							break;
						}
						break;
	
				}	
				break;
			
			case ClavierSpecial:
				
				switch(toucheClavier())
				{
					case ToucheFlecheBas :
						if (pointMenu==1)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMenu=2;
							break;
						}
					 	else 
					 	{ 	
							pointMenu=3;
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/2.5;
							break;
						}
						
					case ToucheFlecheHaut :
						if (pointMenu==3)
						{
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.9;
							pointMenu=2;
							break;
						}
					 	else if (pointMenu==2)
					 	{ 	
							
							xBalle = largeurFenetre()/4;
							yBalle = hauteurFenetre()/1.55;
							pointMenu=1;
							break;
						}
						
							
				}		
				break;
		
		
			
		}
}	
void MENU4(EvenementGfx evenement, int * pfenetre ,int *pmenuAct,int *pModeDeJeu,int *pDiffDuJeu)
{	static int pointMenu=1;
	static DonneesImageRGB *image=NULL;
	printf("menu4 MODE DE JEU %d\n DIFF DU JEU %d \n",*pModeDeJeu,*pDiffDuJeu);
	if (*pmenuAct!=*pfenetre)
				{ // IL NE FAIT QU UNE FOIS
					*pmenuAct=*pfenetre;
					pointMenu=1;
					image = lisBMPRGB("ISEN.bmp");			
					demandeTemporisation(20);
				}
		
			switch (evenement)
			{	
			
			case Temporisation:
				rafraichisFenetre();
				break;
			
			case Affichage:
	
			// Affichage d'une image
				if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'image
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			
			break;
			
			
			case ClavierSpecial:
				
				break;
		
		
			
		}
}	
void OPTIONCOMMANDE(EvenementGfx evenement,int *pfenetre,int * pmenuAct)
{
	static DonneesImageRGB *image=NULL;
	if (*pmenuAct!=*pfenetre)
				{ // IL NE FAIT QU UNE FOIS
					*pmenuAct=*pfenetre;
					image = lisBMPRGB("COMMANDE.bmp");			
					demandeTemporisation(20);
				}
		
			switch (evenement)
			{	
			
			case Temporisation:
				rafraichisFenetre();
				break;
			
			case Affichage:
	
			// Affichage d'une image
				if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'image
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			
			break;
			case Clavier:
				
				switch (caractereClavier())
				{
					/* Pour sortir quelque peu proprement du programme */
					case 27:
						libereDonneesImageRGB(&image);
						*pfenetre=Option;
						break;
				}
			break;		
		}
}
void OPTIONSKIN(EvenementGfx evenement,int *pfenetre,int * pmenuAct)
{
	static DonneesImageRGB *image=NULL;
	if (*pmenuAct!=*pfenetre)
				{ // IL NE FAIT QU UNE FOIS
					*pmenuAct=*pfenetre;
					image = lisBMPRGB("SKIN.bmp");			
					demandeTemporisation(20);
				}
		
			switch (evenement)
			{	
			
			case Temporisation:
				rafraichisFenetre();
				break;
			
			case Affichage:
	
			// Affichage d'une image
				if (image != NULL) // Si l'image a pu etre lue
				{
				// On affiche l'image
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			
			break;
			case Clavier:
				
				switch (caractereClavier())
				{
					/* Pour sortir quelque peu proprement du programme */
					case 27:
						libereDonneesImageRGB(&image);
						*pfenetre=Option;
						break;
				}
			break;		
		}
}
