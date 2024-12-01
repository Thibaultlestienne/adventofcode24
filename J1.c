#include <stdio.h>
#include <stdlib.h>


int abs(int a){
    if (a>0){return a;}
    else {return -a;}
}

void swap(int tab[], int i, int j){
    int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

void trier(int tab[], int taille){
    for (int i=0; i< taille; i++){
        for (int j=i+1; j< taille; j++){
            if(tab[i]>tab[j]){
                swap(tab, i,j);
            }
        }
    }
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int liste1[10000] = {0};
    int liste2[10000] = {0};

    int taille = 0;
    char ligne[10000]; // Taille maximale d'une ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%d   %d", &liste1[taille], &liste2[taille]); // Affiche la ligne
        taille++;
    }

    trier(liste1,taille);
    trier(liste2,taille);
    
    int s =0;

    for (int i = 0; i < taille; i++){
        s += abs(liste1[i]-liste2[i]);
    }

    fclose(fichier);
    return s;
}

int compter(int tab[], int taille , int valeur){
    int retour = 0; 
    for (int i = 0;i<taille;i++){
        if (tab[i] == valeur){
            retour++;
        }
    }
    return retour;
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int liste1[10000] = {0};
    int liste2[10000] = {0};

    int taille = 0;
    char ligne[10000]; // Taille maximale d'une ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%d   %d", &liste1[taille], &liste2[taille]); // Affiche la ligne
        taille++;
    }

    trier(liste1,taille);
    trier(liste2,taille);
    
    int s =0;

    for (int i = 0; i < taille; i++){
        s += compter(liste2, taille, liste1[i] ) * liste1[i];
    }

    fclose(fichier);
    return s;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ1.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ1.txt"));
    return 0;
} 