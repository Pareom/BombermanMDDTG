#ifndef STRUCTURES_H
#define STRUCTURES_H
typedef struct perso {
    int vie;
    int posX;
    int posY;
    int nb_feu;
    int nb_bombe;
    int nb_max;
} PERSO;
typedef struct bombe {
    time_t spawn;
    double detente;//5 sec
    int nb_feu;
    PERSO* Joueur;
} BOMBE;
typedef struct feu {
    time_t spawn;
    double detente;//1 sec
} FEU;
typedef struct monstre {
    int vie;
    int posX;
    int posY;
} MONSTRE;
#define LargeurFenetre 800
#define HauteurFenetre 600
#define CoteMAP 13
#define CASE 30
#define vHerbe 0
#define vCaisse 1
#define vSolid 2
#define vBombe 3
#define vFeu 4
#define vBonusFeu 5
#define vBonusBombe 6
#define vCaisse_Feu 7
#define f1V1 0
#define fMenu1 1
#define fMenu2 2
#define fMenu3 3
#define f1VIA 4
#define f2VIA 5
#define fMenu4 6
#define Option 7
#define OptionCommande 8
#define OptionSkin 9
#endif
