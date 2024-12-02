#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool valide(int tab[], int taille){
    if(tab[0]-tab[1]>0){
        for (int i=0; i< taille-1; i++){
            if(3<tab[i] - tab[i+1] || tab[i] - tab[i+1]<1){
                return false;
            }
        }
    }
    else{
        for (int i=0; i< taille-1; i++){
            if(3<tab[i+1] - tab[i] || tab[i+1] - tab[i]<1){
                return false;
            }
        }
    }
    return true;
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int liste[10000] = {0};
    int taille = 0;
    int s =0;

    char ligne[10000]; 
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        taille = 0;
        while(sscanf(curseur, "%d", &liste[taille])==1){
            while (*curseur && *curseur != ' ') {curseur++;}
            while (*curseur == ' ') {curseur++;}
            taille++;
        }
        s += valide(liste,taille);
    }

    fclose(fichier);
    return s;
}

int* retirer(int * tab,int taille, int k){
    int * retour = malloc(sizeof(int) * 20);
    for (int i =0 ; i<k; i++){
        retour[i] = tab[i];
    }
    for (int i =k ; i<taille-1; i++){
        retour[i] = tab[i+1];
    }
    return retour;
}

bool valide2(int tab[], int taille){
    for (int k =0;k<taille;k++){
        int* test = retirer(tab,taille,k);
        if (valide(test, taille-1)){
            free(test);
            return true;
        }
        free(test);
    }
    return false;
}


int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int liste[10000] = {0};
    int taille = 0;
    int s =0;

    char ligne[10000]; 
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        taille = 0;
        while(sscanf(curseur, "%d", &liste[taille])==1){
            while (*curseur && *curseur != ' ') {curseur++;}
            while (*curseur == ' ') {curseur++;}
            taille++;
        }
        s += valide2(liste,taille);
    }

    fclose(fichier);
    return s;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ2.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ2.txt"));
    return 0;
} 