#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLEMATRICE 150

bool verifier(char tab[TAILLEMATRICE][TAILLEMATRICE], int x, int y, int dx, int dy){
    if ( x +dx * 3 >= 0 && x +dx * 3 < TAILLEMATRICE && y +dy * 3 >= 0 && y +dy * 3 < TAILLEMATRICE && 
        tab[x][y] =='X'
        && tab[x +dx * 1][y + dy * 1] == 'M'
        && tab[x +dx * 2][y + dy * 2] == 'A'
        && tab[x +dx * 3][y + dy * 3] == 'S'
    ){return true;}
    else {return false;}
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int x, y;
    char c;
    int s =0;
    bool actif = true;

    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0';k++) {
            matrice[taille][k] = ligne[k];
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = '.'; // caractere innutile
        }
        taille++;
    }

    for(int i = 0;i<TAILLEMATRICE;i++) { 
        for(int j = 0;j<taille;j++) {
            s +=  verifier(matrice,i,j,-1,-1);
            s +=  verifier(matrice,i,j,-1,0);
            s +=  verifier(matrice,i,j,-1,1);
            s +=  verifier(matrice,i,j,0,-1);
            s +=  verifier(matrice,i,j,0,1);
            s +=  verifier(matrice,i,j,1,-1);
            s +=  verifier(matrice,i,j,1,0);
            s +=  verifier(matrice,i,j,1,1);
        }
    }

    fclose(fichier);
    return s;
}

bool verifier2(char tab[TAILLEMATRICE][TAILLEMATRICE], int x, int y){
    if (!( x >= 1 && x < TAILLEMATRICE -1 && y >= 1 && y < TAILLEMATRICE-1)){return false;}

    int nbM = 0;
    int nbS = 0;
    
    if(tab[x - 1][y - 1] == 'M'){nbM++;}
    if(tab[x - 1][y - 1] == 'S'){nbS++;}

    if(tab[x - 1][y + 1] == 'M'){nbM++;}
    if(tab[x - 1][y + 1] == 'S'){nbS++;}

    if(tab[x + 1][y - 1] == 'M'){nbM++;}
    if(tab[x + 1][y - 1] == 'S'){nbS++;}

    if(tab[x + 1][y + 1] == 'M'){nbM++;}
    if(tab[x + 1][y + 1] == 'S'){nbS++;}

    if (tab[x][y] == 'A' && nbM == 2 && nbS == 2 && tab[x + 1][y + 1] != tab[x - 1][y - 1]){return true;}
    else {return false;}
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int x, y;
    char c;
    int s =0;
    bool actif = true;

    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0';k++) {
            matrice[taille][k] = ligne[k];
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = '.'; // caractere innutile
        }
        taille++;
    }

    for(int i = 0;i<TAILLEMATRICE;i++) { 
        for(int j = 0;j<taille;j++) {
            s +=  verifier2(matrice, i, j);
        }
    }

    fclose(fichier);
    return s;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ4.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ4.txt"));
    return 0;
} 