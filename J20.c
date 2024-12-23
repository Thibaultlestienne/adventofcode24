#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define TAILLEMATRICE 150

// On utilisera le fait qu il n existe qu un unique chemin passant par tout les '.'

int abs(int a){
    if(a>0){return a;}
    return -a;
}

int dist(int x1,int y1,int x2,int y2){
    return abs(x2-x1)+abs(y2-y1);
}

void remplir(int matricedistance[TAILLEMATRICE][TAILLEMATRICE], char carte[TAILLEMATRICE][TAILLEMATRICE], int xd, int yd, int xa, int ya, int i){
    matricedistance[xd][yd] = i;
    if (xd == xa && yd == ya){return ;}
    if (carte[xd+1][yd] != '#' && matricedistance[xd+1][yd] == -1){remplir(matricedistance, carte, xd+1, yd, xa, ya, i+1) ;return;}
    if (carte[xd-1][yd] != '#' && matricedistance[xd-1][yd] == -1){remplir(matricedistance, carte, xd-1, yd, xa, ya, i+1) ;return;}
    if (carte[xd][yd+1] != '#' && matricedistance[xd][yd+1] == -1){remplir(matricedistance, carte, xd, yd+1, xa, ya, i+1) ;return;}
    if (carte[xd][yd-1] != '#' && matricedistance[xd][yd-1] == -1 ){remplir(matricedistance, carte, xd, yd-1, xa, ya, i+1) ;return;}
}


int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int xd,yd, xa,ya;
    char carte[TAILLEMATRICE][TAILLEMATRICE] = {0};
    int matricedistance[TAILLEMATRICE][TAILLEMATRICE];

    for (int i = 0;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matricedistance[i][j] = -1;
        }
    }

    char ligne[10000]; 

    int taille = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (ligne[0] == '\n'){break;}
        int k = 0;
        carte[taille][0] = '#';
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] == 'S'){xd=taille;yd=k;carte[taille][k] = '.';}
            else if (ligne[k] == 'E'){xa=taille;ya=k;carte[taille][k] = '.';}
            else {carte[taille][k] = ligne[k];}
        }
        for (;k<TAILLEMATRICE;k++) {
            carte[taille][k] = '#'; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            carte[i][j] = '#';
        }
    }

    remplir(matricedistance, carte, xd, yd, xa, ya, 0);

    int retour = 0;
    for(int x1 = 1; x1< taille - 1; x1++){
        for(int y1 = 1; y1< taille - 1; y1++){
            if (carte[x1][y1] != '.' ){continue;}
            for(int x2 = x1; x2< taille - 1; x2++){
                for(int y2 = (y1+1) * (x1 == x2); y2< taille - 1; y2++){
                    if (carte[x2][y2] != '.' ){continue;}
                    if (dist(x1,y1,x2,y2)>2){continue;}//racourcis impossible
                    if (abs(matricedistance[x1][y1] - matricedistance[x2][y2]) - dist(x1,y1,x2,y2) >= 100){retour++;}
                }
            }
        }
    }

    fclose(fichier);
    return retour;
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int xd,yd, xa,ya;
    char carte[TAILLEMATRICE][TAILLEMATRICE] = {0};
    int matricedistance[TAILLEMATRICE][TAILLEMATRICE];

    for (int i = 0;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matricedistance[i][j] = -1;
        }
    }

    char ligne[10000]; 

    int taille = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (ligne[0] == '\n'){break;}
        int k = 0;
        carte[taille][0] = '#';
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] == 'S'){xd=taille;yd=k;carte[taille][k] = '.';}
            else if (ligne[k] == 'E'){xa=taille;ya=k;carte[taille][k] = '.';}
            else {carte[taille][k] = ligne[k];}
        }
        for (;k<TAILLEMATRICE;k++) {
            carte[taille][k] = '#'; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            carte[i][j] = '#';
        }
    }

    remplir(matricedistance, carte, xd, yd, xa, ya, 0);

    int retour = 0;
    for(int x1 = 1; x1< taille - 1; x1++){
        for(int y1 = 1; y1< taille - 1; y1++){
            if (carte[x1][y1] != '.' ){continue;}
            for(int x2 = x1; x2< taille - 1; x2++){
                for(int y2 = (y1+1) * (x1 == x2); y2< taille - 1; y2++){
                    if (carte[x2][y2] != '.' ){continue;}
                    if (dist(x1,y1,x2,y2)>20){continue;}//racourcis impossible
                    if (abs(matricedistance[x1][y1] - matricedistance[x2][y2]) - dist(x1,y1,x2,y2) >= 100){retour++;}
                }
            }
        }
    }

    fclose(fichier);
    return retour;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ20.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ20.txt"));  
    return 0;
} 