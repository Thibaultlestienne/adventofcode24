#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define TAILLEMATRICE 100

int compterpositif(int matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;

    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] > 0){retour++;}
        }
    }

    return retour;
}

bool dansLimite(int matrice[TAILLEMATRICE][TAILLEMATRICE], int x, int y){
    return x>=0 && y>=0 && x<TAILLEMATRICE && y<TAILLEMATRICE && matrice[x][y]!=-1;
}

void parcours(int matrice[TAILLEMATRICE][TAILLEMATRICE], int min, int x, int y, int carte[TAILLEMATRICE][TAILLEMATRICE]){
    if ( dansLimite(matrice,x,y) && matrice[x][y]==min){
        if (min ==9){carte[x][y]++;}
        parcours(matrice, min+1, x+1,y, carte);
        parcours(matrice, min+1, x-1,y, carte);
        parcours(matrice, min+1, x,y+1, carte);
        parcours(matrice, min+1, x,y-1, carte);
    }
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    
    int matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            matrice[taille][k] = ligne[k]-'0';
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = -1; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matrice[i][j] = -1;
        }
    }
    
    int s = 0;

    for (int i = 0;i<taille;i++){
        for (int j = 0;j<taille;j++){
            printf("%d",matrice[i][j]);
        }
        printf("\n");
    }

    for (int i = 0;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            int carte[TAILLEMATRICE][TAILLEMATRICE] = {0};
            parcours(matrice,0,i,j, carte);
            s+= compterpositif(carte);
        }
    }

    fclose(fichier);
    return s;
}

int sommemat(int matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;

    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            retour+=matrice[i][j] ;
        }
    }

    return retour;
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    
    int matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            matrice[taille][k] = ligne[k]-'0';
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = -1; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matrice[i][j] = -1;
        }
    }
    
    int s = 0;

    for (int i = 0;i<taille;i++){
        for (int j = 0;j<taille;j++){
            printf("%d",matrice[i][j]);
        }
        printf("\n");
    }

    for (int i = 0;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            int carte[TAILLEMATRICE][TAILLEMATRICE] = {0};
            parcours(matrice,0,i,j, carte);
            s+= sommemat(carte);
        }
    }

    fclose(fichier);
    return s;
}


int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ10.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ10.txt"));
    return 0;
} 