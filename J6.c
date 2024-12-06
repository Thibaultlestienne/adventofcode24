#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define TAILLEMATRICE 200
// Si infini  = (TAILLEMATRICE * TAILLEMATRICE * 4 +1) Alors il existe une case dans laquelle le personage est passee deux fois dans la meme direction
// dans la pratique INFINI  = 2 * resultat de la question 1 suffit et ne fait pas exploser la pile d appel (empirique)
#define INFINI 10000// longeur de chemin a partir duquel un chemin eset considerer comme infini

int compterX(char matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;

    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] == 'X'){retour++;}
        }
    }

    return retour;
}

void parcourir(char matrice[TAILLEMATRICE][TAILLEMATRICE] ,int x, int y, int dx, int dy){
    if (x+dx < 0 || y+dy<0 || matrice[x+dx][y+dy] == 'H'){matrice[x][y] = 'X'; return ;}
    if ( matrice[x+dx][y+dy] == '#'){//tourner
        if (dx == 1){parcourir(matrice,x, y, 0 ,-1);}
        if (dx ==-1){parcourir(matrice,x, y, 0 , 1);}
        if (dy == 1){parcourir(matrice,x, y, 1 , 0);}
        if (dy ==-1){parcourir(matrice,x, y,-1 , 0);}
    }
    else {matrice[x][y] = 'X';  parcourir(matrice,x +dx, y+dy,dx,dy);}
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int depart_x, depart_y;
    char c;
    bool actif = true;

    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0';k++) {
            if (ligne[k] == '^'){matrice[taille][k] = 'X';depart_x = taille; depart_y = k;}
            else {matrice[taille][k] = ligne[k];}
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = 'H'; // caractere innutile
        }
        taille++;
    }
    for (int i = 0; i<TAILLEMATRICE;i++){
        matrice[taille][i] = 'H';
    }

    parcourir(matrice,depart_x, depart_y, -1,0);
    return compterX(matrice);
}


bool cheminInfini(char matrice[TAILLEMATRICE][TAILLEMATRICE] ,int x, int y, int dx, int dy, int couprestant){
    if (couprestant == 0 ){return false;}

    if (x+dx < 0 || y+dy<0 || matrice[x+dx][y+dy] == 'H'){return true ;}
    if ( matrice[x+dx][y+dy] == '#'){//tourner
        if (dx == 1){return cheminInfini(matrice,x, y, 0 ,-1, couprestant);}
        if (dx ==-1){return cheminInfini(matrice,x, y, 0 , 1, couprestant);}
        if (dy == 1){return cheminInfini(matrice,x, y, 1 , 0, couprestant);}
        if (dy ==-1){return cheminInfini(matrice,x, y,-1 , 0, couprestant);}
    }
    else {return cheminInfini(matrice,x +dx, y+dy,dx,dy,couprestant -1);}

}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int depart_x, depart_y;
    char c;
    int s =0;
    bool actif = true;

    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0';k++) {
            if (ligne[k] == '^'){matrice[taille][k] = '.';depart_x = taille; depart_y = k;}
            else {matrice[taille][k] = ligne[k];}
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = 'H'; // caractere innutile
        }
        taille++;
    }
    for (int i = 0; i<TAILLEMATRICE;i++){
        matrice[taille][i] = 'H';
    }

    for (int i = 0 ; i< taille;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] == 'H'){break;}
            if (matrice[i][j] == '.'){
                matrice[i][j] = '#';
                if (!cheminInfini(matrice,depart_x, depart_y, -1,0,INFINI)){s++;}
                matrice[i][j] = '.';
            }
        }
    }

    return s;
}


int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ6.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ6.txt"));
    return 0;
} 