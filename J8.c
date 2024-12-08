#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>



#define TAILLEMATRICE 100

int compterdiese(char matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;

    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] == '#'){retour++;}
        }
    }

    return retour;
}

bool dansLimites(char tab[TAILLEMATRICE][TAILLEMATRICE],int i, int j){
    return i<TAILLEMATRICE && j<TAILLEMATRICE && i>=0 && j>=0 && tab[i][j]!='\0';
}

void parcours(char mat[TAILLEMATRICE][TAILLEMATRICE],char cartechamps[TAILLEMATRICE][TAILLEMATRICE], char c){//prend une matrice avec des diese et des . et ajoute les diese manquant
    for(int i1 = 0; i1<TAILLEMATRICE; i1++){
        for(int j1 = 0; j1<TAILLEMATRICE; j1++){
            if(mat[i1][j1] == c){
                for(int i2 = i1; i2<TAILLEMATRICE; i2++){
                    for(int j2 = (j1+1)*(i1 == i2); j2<TAILLEMATRICE; j2++){
                        if(mat[i2][j2] == c){
                            
                            if(dansLimites(mat,2 * i1 -i2, 2 * j1 -j2) ){
                                cartechamps[2 * i1 -i2][2 * j1 -j2] = '#';
                            }
                            if(dansLimites(mat,2 * i2 -i1, 2 * j2 -j1)){
                                cartechamps[2 * i2 -i1][2 * j2 -j1] = '#';
                            }
                        }
                    }
                }
            }
        }
    }
}


int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int x, y;
    char c;
    int s =0;
    bool actif = true;

    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    char cartechamps[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            matrice[taille][k] = ligne[k];
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = '\0'; //hors limite
        }
        taille++;
    }
    
    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matrice[i][j] = '\0';
        }
    }

    for (int c = '0';c<='9';c++){
        parcours(matrice,cartechamps,c);
    }
    for (int c = 'a';c<='z';c++){
        parcours(matrice,cartechamps,c);
    }
    for (int c = 'A';c<='Z';c++){
        parcours(matrice,cartechamps,c);
    }

    fclose(fichier);
    return compterdiese(cartechamps);
}

void parcours2(char mat[TAILLEMATRICE][TAILLEMATRICE],char cartechamps[TAILLEMATRICE][TAILLEMATRICE], char c){//prend une matrice avec des diese et des . et ajoute les diese manquant
    for(int i1 = 0; i1<TAILLEMATRICE; i1++){
        for(int j1 = 0; j1<TAILLEMATRICE; j1++){
            if(mat[i1][j1] == c){
                for(int i2 = i1; i2<TAILLEMATRICE; i2++){
                    for(int j2 = (j1+1)*(i1 == i2); j2<TAILLEMATRICE; j2++){
                        if(mat[i2][j2] == c){
                            int k = 0;
                            while(dansLimites(mat,(k+1) * i1 -(k *i2), (k+1) * j1 -(k *j2)) ){
                                cartechamps[(k+1) * i1 -(k *i2)][(k+1) * j1 -(k *j2)] = '#';
                                k++;
                            }
                            k =0;
                            while(dansLimites(mat,(k+1) * i2 -(k *i1), (k+1) * j2 -(k *j1))){
                                cartechamps[(k+1) * i2 -(k *i1)][(k+1) * j2 - (k *j1)] = '#';
                                k++;
                            }
                        }
                    }
                }
            }
        }
    }
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int x, y;
    char c;
    int s =0;
    bool actif = true;

    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    char cartechamps[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0' && ligne[k] != '\n' ;k++) {
            matrice[taille][k] = ligne[k];
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = '\0'; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matrice[i][j] = '\0';
        }
    }

    for (int c = '0';c<='9';c++){
        parcours2(matrice,cartechamps,c);
    }
    for (int c = 'a';c<='z';c++){
        parcours2(matrice,cartechamps,c);
    }
    for (int c = 'A';c<='Z';c++){
        parcours2(matrice,cartechamps,c);
    }
    fclose(fichier);

    return compterdiese(cartechamps);
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ8.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ8.txt"));
    return 0;
} 