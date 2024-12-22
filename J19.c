#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

int longeurmotif(char * motif){
    int i = 0;
    for (; motif[i] != '\0'; i++){}
    return i;
}

bool motifutilisable(char* motif, char* serviette){
    for (int i =0; motif[i] != '\0'; i++){
        if (motif[i] != serviette[i]){
            return false;
        }
    }
    return true;
}

bool realisable(char * serviette, char motifs[1000][1000], int nbmotifs){
    if (serviette[0] == '\0'){return true;}
    for (int i = 0; i<nbmotifs; i++){
        if (motifutilisable(motifs[i],serviette) && realisable(serviette + longeurmotif(motifs[i]), motifs,nbmotifs)){
            return true;
        }
    }
    return false;
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char motifs[1000][1000] = {0};
    int nbmotifs = 0;
    char c; // pour le scanf
    char ligne[10000]; 

    fgets(ligne, sizeof(ligne), fichier);
    char * curseur = ligne;
    while(sscanf(curseur, "%[^,\n]", motifs[nbmotifs]) == 1){
        while (*curseur && *curseur != ' ') {curseur++;}
        while (*curseur == ' ') {curseur++;}
        nbmotifs++;
    }
    fgets(ligne, sizeof(ligne), fichier); // passer le \n

    char serviette[1000];
    int nbservietterealisable = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%[^\n]", serviette);
        nbservietterealisable+=realisable(serviette, motifs, nbmotifs);
    }
    

    fclose(fichier);
    return nbservietterealisable;
}

long long int nombresolution(char * serviette , char motifs[1000][1000], int nbmotifs){
    long long int memoisation[1000] = {0};
    int taille = longeurmotif(serviette);
    memoisation[taille] = 1;

    for (int k = taille-1; k >= 0; k--){
        for (int i = 0; i<nbmotifs; i++){
            if (motifutilisable(motifs[i],serviette+k)){
                memoisation[k] += memoisation[k + longeurmotif(motifs[i])];
            }
        }
    }
    return memoisation[0];
}

long long int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char motifs[1000][1000] = {0};
    int nbmotifs = 0;
    char c; // pour le scanf
    char ligne[10000]; 

    fgets(ligne, sizeof(ligne), fichier);
    char * curseur = ligne;
    while(sscanf(curseur, "%[^,\n]", motifs[nbmotifs]) == 1){
        while (*curseur && *curseur != ' ') {curseur++;}
        while (*curseur == ' ') {curseur++;}
        nbmotifs++;
    }
    fgets(ligne, sizeof(ligne), fichier); // passer le \n

    char serviette[1000];
    long long int nbservietterealisable = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%[^\n]", serviette);
        nbservietterealisable+=nombresolution(serviette, motifs, nbmotifs);
    }
    

    fclose(fichier);
    return nbservietterealisable;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ19.txt"));
    printf("etoile 2 : %lld\n",etoile2("entreeJ19.txt"));
    return 0;
} 