#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define TAILLEMATRICE 200

bool dansLimite(char matrice[TAILLEMATRICE][TAILLEMATRICE], int x, int y){
    return x>=0 && y>=0 && x<TAILLEMATRICE && y<TAILLEMATRICE && matrice[x][y]!='\0';
}

void parcours(char matrice[TAILLEMATRICE][TAILLEMATRICE], char culture, int x, int y, bool parcouru[TAILLEMATRICE][TAILLEMATRICE],int * surface, int* perimetre){
    if ( dansLimite(matrice,x,y) && matrice[x][y]==culture && !parcouru[x][y]){

        *perimetre +=   (matrice[x][y] != matrice[x+1][y])
                        + (x == 0 || matrice[x][y] != matrice[x-1][y])
                        + (matrice[x][y] != matrice[x][y+1])
                        + (y == 0 || matrice[x][y] != matrice[x][y-1]);
        *surface += 1;
        parcouru[x][y] = true;

        parcours(matrice, culture, x+1,y, parcouru,surface,perimetre);
        parcours(matrice, culture, x-1,y, parcouru,surface,perimetre);
        parcours(matrice, culture, x,y+1, parcouru,surface,perimetre);
        parcours(matrice, culture, x,y-1, parcouru,surface,perimetre);
    }
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    bool parcouru[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[TAILLEMATRICE]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            matrice[taille][k] = ligne[k]-'0';
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
    
    int retour = 0;
    int surface = 0;
    int perimetre = 0;

    for (int i = 0;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            surface = 0;
            perimetre = 0;
            parcours(matrice,matrice[i][j],i,j, parcouru,&surface,&perimetre );
            retour += surface * perimetre;
        }
    }

    fclose(fichier);
    return retour;
}

void parcours2(char matrice[TAILLEMATRICE][TAILLEMATRICE], char culture, int x, int y, bool parcouru[TAILLEMATRICE][TAILLEMATRICE],int * surface, int* coin){
    if ( dansLimite(matrice,x,y) && matrice[x][y]==culture && !parcouru[x][y]){

        // Ancien perimetre local
        int cotecase = (matrice[x][y] != matrice[x+1][y])
                        + (x == 0 || matrice[x][y] != matrice[x-1][y])
                        + (matrice[x][y] != matrice[x][y+1])
                        + (y == 0 || matrice[x][y] != matrice[x][y-1]);

        // coin aux bords
        if(x == 0 && y == 0 ){*coin +=1;} // un coin compté une seul fois
        if(x == 0 && y != 0 && matrice[x][y] != matrice[x][y-1]){*coin +=1;}// un coin compté une seul fois
        if(y == 0 && x != 0 && matrice[x][y] != matrice[x-1][y]){*coin +=1;}

        if(x == 0           && matrice[x][y] != matrice[x][y+1]){*coin +=1;}// un coin compté une seul fois
        if(y == 0           && matrice[x][y] != matrice[x+1][y]){*coin +=1;}

        // coin Type 1 (1 seul bout du coin a l interieur ) 
        if(x != 0 && y != 0 && matrice[x][y] != matrice[x][y-1] && matrice[x][y] != matrice[x-1][y]){*coin +=1 ;}// un coin compté une seul fois
        if(          y != 0 && matrice[x][y] != matrice[x][y-1] && matrice[x][y] != matrice[x+1][y]){*coin +=1 ;}// un coin compté une seul fois
        if(x != 0           && matrice[x][y] != matrice[x][y+1] && matrice[x][y] != matrice[x-1][y]){*coin +=1 ;}// un coin compté une seul fois
        if(                    matrice[x][y] != matrice[x][y+1] && matrice[x][y] != matrice[x+1][y]){*coin +=1 ;}// un coin compté une seul fois

        // coin Type 3 (3 bout du coin a l interieur ) 
        if(x != 0 && y != 0 && matrice[x][y] == matrice[x][y-1] && matrice[x][y] == matrice[x-1][y] && matrice[x][y] != matrice[x-1][y-1]){*coin +=1 ;}// un coin compté une seul fois
        if(          y != 0 && matrice[x][y] == matrice[x][y-1] && matrice[x][y] == matrice[x+1][y] && matrice[x][y] != matrice[x+1][y-1]){*coin +=1 ;}// un coin compté une seul fois
        if(x != 0           && matrice[x][y] == matrice[x][y+1] && matrice[x][y] == matrice[x-1][y] && matrice[x][y] != matrice[x-1][y+1]){*coin +=1 ;}// un coin compté une seul fois
        if(                    matrice[x][y] == matrice[x][y+1] && matrice[x][y] == matrice[x+1][y] && matrice[x][y] != matrice[x+1][y+1]){*coin +=1 ;}// un coin compté une seul fois



        *surface += 1;
        parcouru[x][y] = true;

        parcours2(matrice, culture, x+1,y, parcouru,surface,coin);
        parcours2(matrice, culture, x-1,y, parcouru,surface,coin);
        parcours2(matrice, culture, x,y+1, parcouru,surface,coin);
        parcours2(matrice, culture, x,y-1, parcouru,surface,coin);
    }
}


int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    bool parcouru[TAILLEMATRICE][TAILLEMATRICE] = {0};

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
    
    int retour = 0;
    int surface = 0;
    int coin = 0;// Autant de cote que de coin

    for (int i = 0;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            surface = 0;
            coin = 0;
            parcours2(matrice,matrice[i][j],i,j, parcouru,&surface,&coin );
            retour += surface * coin;
        }
    }

    fclose(fichier);
    return retour;
}


int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ12.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ12.txt"));
    return 0;
} 