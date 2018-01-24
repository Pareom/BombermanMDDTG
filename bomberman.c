#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()
#include "Structures.h"
#include "GestionBombes.h"
#include "Deplacement.h"
#include "Affichage.h"
#include "Menu.h"
#include "Robot.h"
#include "Save.h"
#include "Charge.h"

void gestionEvenement(EvenementGfx evenement);
int main(int argc, char **argv)
{
	static Mix_Music *music = NULL;
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("SUPER BOMBERMAN", LargeurFenetre, HauteurFenetre);
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	music = Mix_LoadMUS("theme.mp3");
	if (music==NULL)
	{
		return 0;
	}
	Mix_PlayMusic(music, -1);
	lanceBoucleEvenements();
	
	Mix_CloseAudio();
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
	//static = variable persitant
	static bool pleinEcran = false;
	FILE* fichier = NULL;
	FILE* sauvegarde = NULL;
	static int map[CoteMAP][CoteMAP];
	static BOMBE bombes[CoteMAP][CoteMAP];
	static FEU feux[CoteMAP][CoteMAP];
	static char J1H = 'z'; 
	static char J1B = 's';
	static char J1D = 'd'; 
	static char J1G = 'q'; 
	static char J2H = 'i'; 
	static char J2B = 'k'; 
	static char J2D = 'l'; 
	static char J2G = 'j';
	static char J1Bombe = 'a'; 
	static char J2Bombe = 'o'; 
	static PERSO j1;
	static PERSO j2;
	static PERSO rob1;
	static PERSO rob2;
	static PERSO rob3;
	static PERSO rob4;
	static PERSO *p1=&j1;
	static PERSO *p2=&j2;
	static PERSO *prob1=&rob1;
	static PERSO *prob2=&rob2;
	static PERSO *prob3=&rob3;
	static PERSO *prob4=&rob4;
	static PERSO** lpObjets = NULL;
	static int vxperso = 5,vyperso = 5;
	static int direcj1=0; //direction de j1 (affichage)
	static int direcj2=0;
	static int direcrob1=0;
	static int direcrob2=0;
	static int direcrob3=0;
	static int direcrob4=0;
	static int fenetre = fMenu1;
	static int ModeDeJeu = 0;
	static int DiffDuJeu = 1;
	static int menuAct=fMenu2;
	static time_t timeA;
	static int pass;
	static int direcanime=0;
	static int toucheAppuyee[255]; //A rajouter lors de l’initialisation des variables au début
	static int nbperso=0;
	int * pfenetre =&fenetre;
	int * pmenuAct =&menuAct;
	int * pModeDeJeu=&ModeDeJeu;
	int * pDiffDuJeu=&DiffDuJeu;
	static int nSbires = 0;
	int i,j;
	
	switch (fenetre)
	{
		case f1V1:
			if (menuAct!=fenetre)
			{ 	
				if (menuAct!=fMenu1){
					fichier = fopen("map1.txt", "r+");
					if(fichier!=NULL){
						lireMap(fichier, map);
						fclose(fichier);
					}
					else
					{ 
						printf("Probleme a l'ouvertuee de la map txt 1V1");
						termineBoucleEvenements();
					}
					j1.posX = 180,j2.posX=485;
					j1.posY = 545,j2.posY=240;
					j1.nb_feu=1;
					j1.vie=1;
					j1.nb_bombe=0;
					j1.nb_max=1;
					j2.nb_feu=1;
					j2.vie=1;
					j2.nb_bombe=0;
					j2.nb_max=1;
					initbomb(bombes);
					initfeu(feux);
				}
				toucheAppuyee[(int)J1H] = 0;
				toucheAppuyee[(int)J1B] = 0;
				toucheAppuyee[(int)J1D] = 0;
				toucheAppuyee[(int)J1G] = 0;
				toucheAppuyee[(int)J2H] = 0;
				toucheAppuyee[(int)J2B] = 0;
				toucheAppuyee[(int)J2D] = 0;
				toucheAppuyee[(int)J2G] = 0;
				menuAct=fenetre;
				demandeTemporisation(20);
			}
			switch (evenement)
			{
				case Initialisation:	
					
					break;
				case Temporisation:
					if(j1.vie==1){
						if (toucheAppuyee[(int)J1H] == 1)//Z 'z'
						{
							if(direcj1==2){direcj1=3;}
							else{direcj1=2;}
							j1.posY=deplacementhaut(map,p1,j1.posX,j1.posY,vyperso);
						}
						if (toucheAppuyee[(int)J1D] == 1)//D
						{
							if(direcj1==4){direcj1=5;}
							else{direcj1=4;}
							j1.posX=deplacementdroite(map,p1,j1.posX,j1.posY,vxperso);
						}
						if(toucheAppuyee[(int)J1G] == 1)//Q
						{
							if(direcj1==6){direcj1=7;}
							else{direcj1=6;}
							j1.posX=deplacementgauche(map,p1,j1.posX,j1.posY,vxperso);
						}
						if (toucheAppuyee[(int)J1B] == 1)//S
						{
							if(direcj1==0){direcj1=1;}
							else{direcj1=0;}
							j1.posY=deplacementbas(map,p1,j1.posX,j1.posY,vyperso);
						}
					}
					if(j1.vie==1){
						if (toucheAppuyee[(int)J2H] == 1)
						{
							if(direcj2==2){direcj2=3;}
							else{direcj2=2;}
							j2.posY=deplacementhaut(map,p2,j2.posX,j2.posY,vyperso);
						}
						if (toucheAppuyee[(int)J2D] == 1)
						{
							if(direcj2==4){direcj2=5;}
							else{direcj2=4;}
							j2.posX=deplacementdroite(map,p2,j2.posX,j2.posY,vxperso);
						}
						if(toucheAppuyee[(int)J2G] == 1)
						{
							if(direcj2==6){direcj2=7;}
							else{direcj2=6;}
							j2.posX=deplacementgauche(map,p2,j2.posX,j2.posY,vxperso);
						}
						if (toucheAppuyee[(int)J2B] == 1)
						{
							if(direcj2==0){direcj2=1;}
							else{direcj2=0;}
							j2.posY=deplacementbas(map,p2,j2.posX,j2.posY,vyperso);
						}
					}
					verifbomb(map, bombes, feux);
					veriffeu(map, feux);
					if((j1.vie==0 || j2.vie==0)&& pass == 0){
					timeA = time(NULL);
					pass=1;
					}
					if((j1.vie==0 || j2.vie==0)&& (pass == 1 && difftime(time(NULL),timeA)>3)){
					fenetre=fMenu1;
					pass=0;
					}
					
					rafraichisFenetre();
					break;
				case Affichage:
					effaceFenetre (0,0,0);
					afficherTerrain(map);
					if((p1->vie)<=1){afficherperso(p1,direcj1,1);}
					if((p2->vie)==1){afficherperso(p2,direcj2,2);}
					couleurCourante(255,0,0);
					epaisseurDeTrait(10);
					if(j1.vie==0){afficheChaine("Victoire du joueur 2", 50, 150, 80);direcanime=afficherpersoanime(direcanime,1,62,288);}
					if(j2.vie==0){afficheChaine("Victoire du joueur 1", 50, 150, 80);}
					break;
					
				case Clavier:
					toucheAppuyee[(int)caractereClavier()] = 1;
					//printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
					if(caractereClavier()== 27){//Echap
						sauvegarde = fopen("sauvegarde.txt", "wb");
						if(sauvegarde!=NULL){
							fseek(sauvegarde,0,SEEK_SET);
							if(lpObjets==NULL){lpObjets=(PERSO**)malloc(sizeof(PERSO*)*2);}
							lpObjets[0]=&j1;
							lpObjets[1]=&j2;
							for(i=0;i<CoteMAP;i++){
								for(j=0;j<CoteMAP;j++){
									if(map[i][j]==vBombe){printf("Bombe\n");}
								}
							}
							sauvegardeMap(sauvegarde,map,bombes,feux,lpObjets);
							sauvegardeObjets(sauvegarde, 2, lpObjets);
							sauvegardeObjets(sauvegarde, 0, NULL);
							fclose(sauvegarde);
						}
						else
						{ 
							printf("Probleme Sauvegarde 1v1 txt");
							termineBoucleEvenements();
						}
						fenetre = fMenu1;
					}
					if(caractereClavier()=='F'||caractereClavier()=='f'){
						pleinEcran = !pleinEcran; // Changement de mode plein ecran
						if (pleinEcran)
							modePleinEcran();
						else
							redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					}
					if(caractereClavier()=='R'||caractereClavier()=='r')
						demandeTemporisation(20);
					if(caractereClavier()==J2Bombe && j2.vie==1)
						poseBombe(map, bombes, &j2);
					if(caractereClavier()==J1Bombe && j1.vie==1)
						poseBombe(map, bombes, &j1);
					break;
				case ClavierRelache:
					toucheAppuyee[(int)caractereClavier()] = 0;
					break;
				case ClavierSpecial:
					//printf("ASCII %d\n", toucheClavier());
					break;
				case BoutonSouris:
					if (etatBoutonSouris() == GaucheAppuye)
					{
						printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
						// Si le bouton gauche de la souris est appuye, faire repartir
						// la balle de la souris
						/*xBalle = abscisseSouris();
						yBalle = ordonneeSouris();*/
					}
					else if (etatBoutonSouris() == GaucheRelache)
					{
						printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
					}
					break;
				
				case Souris: // Si la souris est deplacee
					break;
				
				case Inactivite: // Quand aucun message n'est disponible
					break;
				
				case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
					// Donc le systeme nous en informe
					/*if (xBalle >= largeurFenetre())
						xBalle = largeurFenetre()-1;
					if (yBalle >= hauteurFenetre())
						yBalle = hauteurFenetre()-1;*/
					printf("Largeur : %d\t", largeurFenetre());
					printf("Hauteur : %d\n", hauteurFenetre());
					break;
			}
			break;
		case f1VIA://changerh 
			if (menuAct!=fenetre)
			{ 	
				if (menuAct!=fMenu1){
					fichier = fopen("map1.txt", "r+");
					if(fichier!=NULL){
						lireMap(fichier, map);
						fclose(fichier);
					}
					else
					{ 
						printf("Probleme a l'ouverture de la map txt f1VIA");
						termineBoucleEvenements();
					}
					j1.posX = 180;
					j1.posY = 545;
					j1.nb_feu=1;
					j1.vie=1;
					j1.nb_bombe=0;
					j1.nb_max=1;
					if(DiffDuJeu>=1)
					{
						nbperso=2;
						rob1.posX=485;rob1.posY=545;
						rob1.nb_feu=1;
						rob1.vie=1;
						rob1.nb_bombe=0;
						rob1.nb_max=1;
					}
					if(DiffDuJeu>=2)
					{
						nbperso=3;
						rob2.posX=180;rob2.posY=245;
						rob2.nb_feu=1;
						rob2.vie=1;
						rob2.nb_bombe=0;
						rob2.nb_max=1;
					}
					if(DiffDuJeu>=3)
					{
						nbperso=5;
						rob3.posX=240;rob3.posY=485;
						rob3.nb_feu=1;
						rob3.vie=1;
						rob3.nb_bombe=0;
						rob3.nb_max=1;
						rob4.posX=330;rob4.posY=365;
						rob4.nb_feu=1;
						rob4.vie=1;
						rob4.nb_bombe=0;
						rob4.nb_max=1;
					}
					initbomb(bombes);
					initfeu(feux);
				}
				toucheAppuyee[(int)J1H] = 0;
				toucheAppuyee[(int)J1B] = 0;
				toucheAppuyee[(int)J1D] = 0;
				toucheAppuyee[(int)J1G] = 0;
				toucheAppuyee[(int)J2H] = 0;
				toucheAppuyee[(int)J2B] = 0;
				toucheAppuyee[(int)J2D] = 0;
				toucheAppuyee[(int)J2G] = 0;
				menuAct=fenetre;
				demandeTemporisation(20);
			}
			switch (evenement)
			{
				case Initialisation:	
					
					break;
				case Temporisation:
					if(j1.vie==1){
						if (toucheAppuyee[(int)J1H] == 1)//Z 'z'
						{
							if(direcj1==2){direcj1=3;}
							else{direcj1=2;}
							j1.posY=deplacementhaut(map,p1,j1.posX,j1.posY,vyperso);
						}
						if (toucheAppuyee[(int)J1D] == 1)//D
						{
							if(direcj1==4){direcj1=5;}
							else{direcj1=4;}
							j1.posX=deplacementdroite(map,p1,j1.posX,j1.posY,vxperso);
						}
						if(toucheAppuyee[(int)J1G] == 1)//Q
						{
							if(direcj1==6){direcj1=7;}
							else{direcj1=6;}
							j1.posX=deplacementgauche(map,p1,j1.posX,j1.posY,vxperso);
						}
						if (toucheAppuyee[(int)J1B] == 1)//S
						{
							if(direcj1==0){direcj1=1;}
							else{direcj1=0;}
							j1.posY=deplacementbas(map,p1,j1.posX,j1.posY,vyperso);
						}
					}
					if(DiffDuJeu>=1)
					{
					direcrob1=verifrobot(map,prob1,direcrob1);
					if(verifposebombe(map,prob1,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob1);}
					if((prob1->vie)<=0){prob1->posX=0;prob1->posY=0;}
					else{deplacementrobot(direcrob1,prob1);}
					}
					if(DiffDuJeu>=2)
					{
					direcrob2=verifrobot(map,prob2,direcrob2);
					if(verifposebombe(map,prob2,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob2);}
					if((prob2->vie)<=0){prob2->posX=0;prob2->posY=0;}
					else{deplacementrobot(direcrob2,prob2);}
					}
					if(DiffDuJeu>=3)
					{
					direcrob3=verifrobot(map,prob3,direcrob3);
					if(verifposebombe(map,prob3,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob3);}
					if((prob3->vie)<=0){prob3->posX=0;prob3->posY=0;}
					else{deplacementrobot(direcrob3,prob3);}
					direcrob4=verifrobot(map,prob4,direcrob4);
					if(verifposebombe(map,prob4,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob4);}
					if((prob4->vie)<=0){prob4->posX=0;prob4->posY=0;}
					else{deplacementrobot(direcrob4,prob4);}
					}
					//poseBombe(map, bombes, &rob);
					verifbomb(map, bombes, feux);
					veriffeu(map, feux);
					if(DiffDuJeu==1){
						if(((j1.vie==0 && j2.vie==0)|| rob1.vie ==0) && pass == 0){
						timeA = time(NULL);
						pass=1;
						}
						if(((j1.vie==0 && j2.vie==0)|| rob1.vie ==0)&& (pass == 1 && difftime(time(NULL),timeA)>3)){
						fenetre=fMenu1;
						pass=0;
						}
					}
					if(DiffDuJeu==2){
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0)) && pass == 0){
						timeA = time(NULL);
						pass=1;
						}
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0)) && (pass == 1 && difftime(time(NULL),timeA)>3)){
						fenetre=fMenu1;
						pass=0;
						}
					}
					if(DiffDuJeu==3){
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0 && rob3.vie ==0 && rob4.vie ==0)) && pass == 0){
						timeA = time(NULL);
						pass=1;
						}
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0 && rob3.vie ==0 && rob4.vie ==0)) && (pass == 1 && difftime(time(NULL),timeA)>3)){
						fenetre=fMenu1;
						pass=0;
						}
					}
					
					rafraichisFenetre();
					break;
					
				case Affichage:
					effaceFenetre (0,0,0);
					afficherTerrain(map);
					couleurCourante(255,0,0);
					epaisseurDeTrait(10);
					if((p1->vie)==1){afficherperso(p1,direcj1,1);}
					if(DiffDuJeu>=1){if(verifmortrobot(map,prob1)==0){afficherperso(prob1,direcrob1,3);}
					if(DiffDuJeu==1){if(rob1.vie<=0 && rob2.vie<=0)			  {afficheChaine("Victoire", 100, 140,120);}}
					}
					if(DiffDuJeu>=2){if(verifmortrobot(map,prob2)==0){afficherperso(prob2,direcrob2,3);}
					if(DiffDuJeu==2){if(rob1.vie<=0 && rob2.vie<=0)			  {afficheChaine("Victoire", 100, 140,120);}}
					}
					if(DiffDuJeu>=3)
					{
						if(verifmortrobot(map,prob3)==0){afficherperso(prob3,direcrob3,3);}
						if(verifmortrobot(map,prob4)==0){afficherperso(prob4,direcrob4,3);}	
						if(rob1.vie<=0 && rob2.vie<=0 && rob3.vie<=0 && rob4.vie<=0){afficheChaine("Victoire", 100, 140,120);}
					}
					if(j1.vie==0){afficheChaine("Defaite", 50, 150, 80);}
					break;
					
				case Clavier:
					toucheAppuyee[(int)caractereClavier()] = 1;
					//printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
					if(caractereClavier()== 27){//Echap
						sauvegarde = fopen("sauvegarde.txt", "wb");
						if(sauvegarde!=NULL){
							if(lpObjets==NULL){lpObjets=(PERSO**)malloc(sizeof(PERSO*)*6);}
							lpObjets[0]=&j1;
							fseek(sauvegarde,0,SEEK_SET);
							if(DiffDuJeu>=1)
							{
								nbperso=2;
								lpObjets[2]=&rob1;
							}
							if(DiffDuJeu>=2)
							{
								nbperso=3;
								lpObjets[3]=&rob2;
							}
							if(DiffDuJeu>=3)
							{
								nbperso=5;
								lpObjets[4]=&rob3;
								lpObjets[5]=&rob4;
							}
							sauvegardeMap(sauvegarde,map,bombes,feux,lpObjets);
							sauvegardeObjets(sauvegarde, 1, lpObjets);
							sauvegardeObjets(sauvegarde, nbperso-1, &(lpObjets[1]));
							fclose(sauvegarde);
						}
						else
						{ 
							printf("Probleme a la sv 1VIA");
							termineBoucleEvenements();
						}
						fenetre = fMenu1;
					}
					if(caractereClavier()=='F'||caractereClavier()=='f'){
						pleinEcran = !pleinEcran; // Changement de mode plein ecran
						if (pleinEcran)
							modePleinEcran();
						else
							redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					}
					if(caractereClavier()=='R'||caractereClavier()=='r')
						demandeTemporisation(20);
					if(caractereClavier()==J1Bombe && j1.vie==1)
						poseBombe(map, bombes, &j1);
					break;
				case ClavierRelache:
					toucheAppuyee[(int)caractereClavier()] = 0;
					break;
				case ClavierSpecial:
					//printf("ASCII %d\n", toucheClavier());
					break;
				case BoutonSouris:
					if (etatBoutonSouris() == GaucheAppuye)
					{
						printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
						// Si le bouton gauche de la souris est appuye, faire repartir
						// la balle de la souris
						/*xBalle = abscisseSouris();
						yBalle = ordonneeSouris();*/
					}
					else if (etatBoutonSouris() == GaucheRelache)
					{
						printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
					}
					break;
				
				case Souris: // Si la souris est deplacee
					break;
				
				case Inactivite: // Quand aucun message n'est disponible
					break;
				
				case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
					// Donc le systeme nous en informe
					/*if (xBalle >= largeurFenetre())
						xBalle = largeurFenetre()-1;
					if (yBalle >= hauteurFenetre())
						yBalle = hauteurFenetre()-1;*/
					printf("Largeur : %d\t", largeurFenetre());
					printf("Hauteur : %d\n", hauteurFenetre());
					break;
			}
			break;
		case f2VIA://changer
			if (menuAct!=fenetre)
			{
				if(menuAct!=fMenu1){
					fichier = fopen("map1.txt", "r+");
					if(fichier!=NULL){
						lireMap(fichier, map);
						fclose(fichier);
					}
					else
					{ 
						printf("Probleme a l'ouverture de la map txt 2VIA");
						termineBoucleEvenements();
					}
					j1.posX = 180,j2.posX=485;
					j1.posY = 545,j2.posY=240;
					j1.nb_feu=1;
					j1.vie=1;
					j1.nb_bombe=0;
					j1.nb_max=1;
					j2.nb_feu=1;
					j2.vie=1;
					j2.nb_bombe=0;
					j2.nb_max=1;
					if(DiffDuJeu>=1)
					{
						nbperso=3;
						rob1.posX=485;rob1.posY=545;
						rob1.nb_feu=1;
						rob1.vie=1;
						rob1.nb_bombe=0;
						rob1.nb_max=1;
					}
					if(DiffDuJeu>=2)
					{
						nbperso=4;
						rob2.posX=180;rob2.posY=245;
						rob2.nb_feu=1;
						rob2.vie=1;
						rob2.nb_bombe=0;
						rob2.nb_max=1;
					}
					if(DiffDuJeu>=3)
					{
						nbperso=6;
						rob3.posX=240;rob3.posY=485;
						rob3.nb_feu=1;
						rob3.vie=1;
						rob3.nb_bombe=0;
						rob3.nb_max=1;
						rob4.posX=330;rob4.posY=365;
						rob4.nb_feu=1;
						rob4.vie=1;
						rob4.nb_bombe=0;
						rob4.nb_max=1;
					}
					initbomb(bombes);
					initfeu(feux);
				}
				toucheAppuyee[(int)J1H] = 0;
				toucheAppuyee[(int)J1B] = 0;
				toucheAppuyee[(int)J1D] = 0;
				toucheAppuyee[(int)J1G] = 0;
				toucheAppuyee[(int)J2H] = 0;
				toucheAppuyee[(int)J2B] = 0;
				toucheAppuyee[(int)J2D] = 0;
				toucheAppuyee[(int)J2G] = 0;
				menuAct=fenetre;
				demandeTemporisation(20);
			}
			switch (evenement)
			{
				case Initialisation:	
					
					break;
				case Temporisation:
					if(j1.vie==1){
						if (toucheAppuyee[(int)J1H] == 1)//Z 'z'
						{
							if(direcj1==2){direcj1=3;}
							else{direcj1=2;}
							j1.posY=deplacementhaut(map,p1,j1.posX,j1.posY,vyperso);
						}
						if (toucheAppuyee[(int)J1D] == 1)//D
						{
							if(direcj1==4){direcj1=5;}
							else{direcj1=4;}
							j1.posX=deplacementdroite(map,p1,j1.posX,j1.posY,vxperso);
						}
						if(toucheAppuyee[(int)J1G] == 1)//Q
						{
							if(direcj1==6){direcj1=7;}
							else{direcj1=6;}
							j1.posX=deplacementgauche(map,p1,j1.posX,j1.posY,vxperso);
						}
						if (toucheAppuyee[(int)J1B] == 1)//S
						{
							if(direcj1==0){direcj1=1;}
							else{direcj1=0;}
							j1.posY=deplacementbas(map,p1,j1.posX,j1.posY,vyperso);
						}
					}
					if(j2.vie==1){
						if (toucheAppuyee[(int)J2H] == 1)
						{
							if(direcj2==2){direcj2=3;}
							else{direcj2=2;}
							j2.posY=deplacementhaut(map,p2,j2.posX,j2.posY,vyperso);
						}
						if (toucheAppuyee[(int)J2D] == 1)
						{
							if(direcj2==4){direcj2=5;}
							else{direcj2=4;}
							j2.posX=deplacementdroite(map,p2,j2.posX,j2.posY,vxperso);
						}
						if(toucheAppuyee[(int)J2G] == 1)
						{
							if(direcj2==6){direcj2=7;}
							else{direcj2=6;}
							j2.posX=deplacementgauche(map,p2,j2.posX,j2.posY,vxperso);
						}
						if (toucheAppuyee[(int)J2B] == 1)
						{
							if(direcj2==0){direcj2=1;}
							else{direcj2=0;}
							j2.posY=deplacementbas(map,p2,j2.posX,j2.posY,vyperso);
						}
					}
					if(DiffDuJeu>=1)
					{
					direcrob1=verifrobot(map,prob1,direcrob1);
					if(verifposebombe(map,prob1,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob1);}
					if((prob1->vie)<=0){prob1->posX=0;prob1->posY=0;}
					else{deplacementrobot(direcrob1,prob1);}
					}
					if(DiffDuJeu>=2)
					{
					direcrob2=verifrobot(map,prob2,direcrob2);
					if(verifposebombe(map,prob2,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob2);}
					if((prob2->vie)<=0){prob2->posX=0;prob2->posY=0;}
					else{deplacementrobot(direcrob2,prob2);}
					}
					if(DiffDuJeu>=3)
					{
					direcrob3=verifrobot(map,prob3,direcrob3);
					if(verifposebombe(map,prob3,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob3);}
					if((prob3->vie)<=0){prob3->posX=0;prob3->posY=0;}
					else{deplacementrobot(direcrob3,prob3);}
					direcrob4=verifrobot(map,prob4,direcrob4);
					if(verifposebombe(map,prob4,fenetre,p1,p2)==1){poseBombe(map, bombes, &rob4);}
					if((prob4->vie)<=0){prob4->posX=0;prob4->posY=0;}
					else{deplacementrobot(direcrob4,prob4);}
					}
					
					if(DiffDuJeu==1){
						if(((j1.vie==0 && j2.vie==0)|| rob1.vie ==0) && pass == 0){
						timeA = time(NULL);
						pass=1;
						}
						if(((j1.vie==0 && j2.vie==0)|| rob1.vie ==0)&& (pass == 1 && difftime(time(NULL),timeA)>3)){
						fenetre=fMenu1;
						pass=0;
						}
					}
					if(DiffDuJeu==2){
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0)) && pass == 0){
						timeA = time(NULL);
						pass=1;
						}
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0)) && (pass == 1 && difftime(time(NULL),timeA)>3)){
						fenetre=fMenu1;
						pass=0;
						}
					}
					if(DiffDuJeu==3){
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0 && rob3.vie ==0 && rob4.vie ==0)) && pass == 0){
						timeA = time(NULL);
						pass=1;
						}
						if(((j1.vie==0 && j2.vie==0) || (rob1.vie ==0 && rob2.vie ==0 && rob3.vie ==0 && rob4.vie ==0)) && (pass == 1 && difftime(time(NULL),timeA)>3)){
						fenetre=fMenu1;
						pass=0;
						}
					}
					verifbomb(map, bombes, feux);
					veriffeu(map, feux);
					rafraichisFenetre();
					break;
					
				case Affichage:
					effaceFenetre (0,0,0);
					afficherTerrain(map);
					couleurCourante(255,0,0);
					epaisseurDeTrait(10);
					if((p1->vie)==1){afficherperso(p1,direcj1,1);}
					if((p2->vie)==1){afficherperso(p2,direcj2,2);}
					if(DiffDuJeu>=1){if(verifmortrobot(map,prob1)==0){afficherperso(prob1,direcrob1,3);}
					if(DiffDuJeu==1){if(rob1.vie<=0 && rob2.vie<=0)			  {afficheChaine("Victoire", 100, 140,120);}}
					}
					if(DiffDuJeu>=2){if(verifmortrobot(map,prob2)==0){afficherperso(prob2,direcrob2,3);}
					if(DiffDuJeu==2){if(rob1.vie<=0 && rob2.vie<=0)			  {afficheChaine("Victoire", 100, 140,120);}}
					}
					if(DiffDuJeu>=3)
					{
						if(verifmortrobot(map,prob3)==0){afficherperso(prob3,direcrob3,3);}
						if(verifmortrobot(map,prob4)==0){afficherperso(prob4,direcrob4,3);}	
						if(rob1.vie<=0 && rob2.vie<=0 && rob3.vie<=0 && rob4.vie<=0){afficheChaine("Victoire", 100, 140,120);}
					}
					if(j1.vie==0 && j2.vie==0){afficheChaine("Defaite", 50, 150, 80);}
					break;
					
				case Clavier:
					toucheAppuyee[(int)caractereClavier()] = 1;
					if(caractereClavier()== 27){//Echap
						sauvegarde = fopen("sauvegarde.txt", "wb");
						if(sauvegarde!=NULL){
							if(lpObjets==NULL){lpObjets=(PERSO**)malloc(sizeof(PERSO*)*6);}
							lpObjets[0]=&j1;
							lpObjets[1]=&j2;
							fseek(sauvegarde,0,SEEK_SET);
							if(DiffDuJeu>=1)
							{
								nbperso=3;
								lpObjets[2]=&rob1;
							}
							if(DiffDuJeu>=2)
							{
								nbperso=4;
								lpObjets[3]=&rob2;
							}
							if(DiffDuJeu>=3)
							{
								nbperso=6;
								lpObjets[4]=&rob3;
								lpObjets[5]=&rob4;
							}
							sauvegardeMap(sauvegarde,map,bombes,feux,lpObjets);
							sauvegardeObjets(sauvegarde, 2, lpObjets);
							sauvegardeObjets(sauvegarde, nbperso-2, &(lpObjets[2]));
							fclose(sauvegarde);
						}
						else
						{ 
							printf("Probleme a la sauvegarde 2VIA");
							termineBoucleEvenements();
						}
						fenetre = fMenu1;
					}
					if(caractereClavier()=='F'||caractereClavier()=='f'){
						pleinEcran = !pleinEcran; // Changement de mode plein ecran
						if (pleinEcran)
							modePleinEcran();
						else
							redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					}
					if(caractereClavier()=='R'||caractereClavier()=='r')
						demandeTemporisation(20);
					if(caractereClavier()==J2Bombe && j2.vie==1)
						poseBombe(map, bombes, &j2);
					if(caractereClavier()==J1Bombe && j1.vie==1)
						poseBombe(map, bombes, &j1);
					break;
				case ClavierRelache:
					toucheAppuyee[(int)caractereClavier()] = 0;
					break;
				case ClavierSpecial:
					//printf("ASCII %d\n", toucheClavier());
					break;
				case BoutonSouris:
					if (etatBoutonSouris() == GaucheAppuye)
					{
						printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
						// Si le bouton gauche de la souris est appuye, faire repartir
						// la balle de la souris
						/*xBalle = abscisseSouris();
						yBalle = ordonneeSouris();*/
					}
					else if (etatBoutonSouris() == GaucheRelache)
					{
						printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
					}
					break;
				
				case Souris: // Si la souris est deplacee
					break;
				
				case Inactivite: // Quand aucun message n'est disponible
					break;
				
				case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
					// Donc le systeme nous en informe
					/*if (xBalle >= largeurFenetre())
						xBalle = largeurFenetre()-1;
					if (yBalle >= hauteurFenetre())
						yBalle = hauteurFenetre()-1;*/
					printf("Largeur : %d\t", largeurFenetre());
					printf("Hauteur : %d\n", hauteurFenetre());
					break;
			}
			break;
		case OptionCommande:
			OPTIONCOMMANDE(evenement,pfenetre,pmenuAct);
			break;
		case OptionSkin:
			OPTIONSKIN(evenement,pfenetre,pmenuAct);
			break;
		case Option:
			OPTION(evenement,pfenetre,pmenuAct);
			break;
		case fMenu1:// MENU1
			if(lpObjets==NULL){lpObjets=(PERSO**)malloc(sizeof(PERSO*)*6);}//nb entite max
			lpObjets[0]=&j1;
			lpObjets[1]=&j2;
			lpObjets[2]=&rob1;
			lpObjets[3]=&rob2;
			lpObjets[4]=&rob3;
			lpObjets[5]=&rob4;
			MENU1(evenement,pfenetre,pmenuAct,map,bombes,feux,&nSbires, lpObjets);
			break;
		case fMenu2: // MENU2
			MENU2(evenement, pfenetre ,pmenuAct,pModeDeJeu);
			break;
		case fMenu3: // MENU3
			MENU3(evenement, pfenetre ,pmenuAct,pDiffDuJeu,pModeDeJeu);
			break;
	}
}
