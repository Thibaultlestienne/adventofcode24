#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

void ajouter(int * memoire,int * taille,int plein,int vide,int ID){
    for (int i = 0; i< plein; i++){
        memoire[*taille] = ID;
        (*taille)++;
    }
    for (int i = 0; i< vide; i++){
        memoire[*taille] = -1;
        (*taille)++;
    }
}

void compresser(int * memoire,int taille){
    if (taille==0){return;}
    if (memoire[0] != -1){
        compresser(memoire+1, taille-1);
    }
    else if (memoire[taille - 1] == -1){
        compresser(memoire, taille-1);
    }
    else {
        memoire[0] = memoire[taille - 1];
        memoire[taille - 1] =-1;
        compresser(memoire, taille);
    }
}

long long int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    long long int retour = 0;

    int longeur =0;

    char ligne[100000] = {0}; // Taille maximale d'une ligne
    int memoire[100000] = {0};
    int tailleMemoire =0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {  

        char * curseur = ligne;

        int ID =0;
        char cplein = 0;
        char cvide = 0;
        int plein = 0;
        int vide = 0;


        while (sscanf(curseur, "%c%c",&cplein,&cvide) >= 1){
            plein = cplein -'0';
            if (cvide == '\n' || cvide == '\0' ){vide = 0;}
            else {vide = cvide -'0';}
            ajouter(memoire,&tailleMemoire,plein,vide,ID);
            ID++;
            curseur += 2;
            if(*curseur == '\0' ||*curseur == '\n' ){break;}
        }
    }

    compresser(memoire,tailleMemoire);

    int i = 0;
    while (true){
        if (memoire[i] ==-1){break;}
        retour+= memoire[i] * i;
        i++;
    }


    fclose(fichier);
    return retour;
}


int espacelibre(int * memoire,int tailleMemoire){
    int retour = 0;
    while(retour< tailleMemoire && memoire[retour] == -1 ){retour++;}
    return retour;
}

int chercherespacelibre(int * memoire,int tailleMemoire,int taille){
    int retour = 0;
    while(retour<tailleMemoire && espacelibre(memoire+retour,tailleMemoire) < taille){retour++;}
    if (retour == tailleMemoire){return -1;}
    return retour;
}

int tailledernierbloc(int * memoire, int taille, int ID){
    int retour = 0;
    while(retour>=0 && taille && memoire[taille-(retour+1)] == ID ){retour++;}
    return retour;
}



void compresser2(int * memoire,int taille){
    if (taille==0){return;}
    else if (memoire[taille - 1] == -1){
        compresser2(memoire, taille-1);
    }
    else {
        int tailleplein = tailledernierbloc(memoire, taille, memoire[taille -1]);

        int indicelibre = chercherespacelibre(memoire, taille, tailleplein);

        if (indicelibre != -1){
            for (int i = 0; i< tailleplein; i++){
                memoire[indicelibre+i] = memoire[taille- (i+1)];
                memoire[taille- (i+1)] = -1;
            }
        }

        compresser2(memoire, taille-tailleplein);
    }
}

long long int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    long long int retour = 0;

    int longeur =0;

    char ligne[100000] = {0}; // Taille maximale d'une ligne
    int memoire[100000] = {0};
    int tailleMemoire =0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {  

        char * curseur = ligne;

        int ID =0;
        char cplein = 0;
        char cvide = 0;
        int plein = 0;
        int vide = 0;


        while (sscanf(curseur, "%c%c",&cplein,&cvide) >= 1){
            plein = cplein -'0';
            if (cvide == '\n' || cvide == '\0' ){vide = 0;}
            else {vide = cvide -'0';}
            ajouter(memoire,&tailleMemoire,plein,vide,ID);
            ID++;
            curseur += 2;
            if(*curseur == '\0' ||*curseur == '\n' ){break;}
        }
    }

    compresser2(memoire,tailleMemoire);

    for(int i = 0;i<100000;i++){
        if (memoire[i] !=-1){retour+= memoire[i] * i;}
    }


    fclose(fichier);
    return retour;
}

int main(){
    printf("etoile 1 : %lld\n",etoile1("entreeJ9.txt"));
    printf("etoile 2 : %lld\n",etoile2("entreeJ9.txt"));
    return 0;
} 