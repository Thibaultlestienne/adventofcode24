#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define TAILLECARTEX 101
#define TAILLECARTEY 103

int somme(int matrice[TAILLECARTEX][TAILLECARTEY], int dx , int fx, int dy, int fy){// somme les valeurs de tab sur un rectangle 
    int retour = 0;

    for (int i = dx; i<fx;i++){
        for (int j = dy; j<fy;j++){
            retour+=matrice[i][j];
        }
    }

    return retour;
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char ligne[10000]; 

    int retour = 0;
    int tps = 100;

    int position[TAILLECARTEX][TAILLECARTEY] = {0};
 
    int x,y,vx,vy;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "p=%d,%d v=%d,%d", &x,&y,&vx,&vy) == 4){
            position[(x+(vx+TAILLECARTEX)*tps) % TAILLECARTEX][(y+(vy+TAILLECARTEY)*tps) % TAILLECARTEY]++;
        }
    }
    fclose(fichier);

    return  somme(position, 0, TAILLECARTEX/2, 0, TAILLECARTEY/2) *
            somme(position, (TAILLECARTEX/2)+1, TAILLECARTEX, 0, TAILLECARTEY/2) *
            somme(position, 0, TAILLECARTEX/2, (TAILLECARTEY/2)+1, TAILLECARTEY) *
            somme(position, (TAILLECARTEX/2)+1, TAILLECARTEX, (TAILLECARTEY/2)+1, TAILLECARTEY);
} 

bool estSapin(int matrice[TAILLECARTEX][TAILLECARTEY], int x, int y){ // si il y a un carree de 3x3
    return (
            matrice[x-1][y-1]
        &&  matrice[x][y-1]
        &&  matrice[x+1][y-1]
        &&  matrice[x-1][y]
        &&  matrice[x][y]
        &&  matrice[x+1][y]
        &&  matrice[x-1][y+1]
        &&  matrice[x][y+1]
        &&  matrice[x+1][y+1]
    );
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char ligne[10000]; 

    int retour = 0;
    int tps = 0;
 
    int x,y,vx,vy;

    while (true){
        FILE *fichier = fopen(nom_fichier, "r");
        int position[TAILLECARTEX][TAILLECARTEY] = {0};
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            if (sscanf(ligne, "p=%d,%d v=%d,%d", &x,&y,&vx,&vy) == 4){
                position[(x+(vx+TAILLECARTEX)*tps) % TAILLECARTEX][(y+(vy+TAILLECARTEY)*tps) % TAILLECARTEY]++;
            }
        }

        for (int x = 1; x<TAILLECARTEX-1;x++){
            for (int y = 1; y<TAILLECARTEY-1;y++){

                if(estSapin(position, x,y)){

                    // printf("tps : %d\n", tps);
                    // for (int i = 0; i<TAILLECARTEX;i++){
                    //     for (int j = 0; j<TAILLECARTEY;j++){
                    //         printf(position[i][j]?".":" ");
                    //     }
                    //     printf("\n");
                    // }
                    return tps;
                }
            }
        }

        fclose(fichier);
        tps++;
    }
}



int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ14.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ14.txt"));
    return 0;
} 