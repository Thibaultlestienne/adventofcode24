#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

bool verifiercouple(int a, int b, int liste1[], int liste2[], int taille){ // renvoie true si b|a n existe pas
    for(int i = 0; i<taille; i++){
        if(liste1[i] == b && liste2[i] == a){// regle violé 
            return false;
        }
    }
    return true; 
}

bool verifierliste(int liste[], int nbelm, int liste1[], int liste2[], int taille){// verifie qu une liste ne viole aucune regle
    for(int i = 0; i<nbelm ; i++){
        for(int j = i+1; j<nbelm ; j++){
            if(!verifiercouple(liste[i] , liste[j], liste1, liste2, taille)){
                return false;
            }
        }
    }
    return true;
}

int traiterLigne1(char ligne[], int liste1[], int  liste2[], int taille){ // renvoie la valeur de chaque ligne dans le cas de l'etoile 1
    char * curseur = ligne;
    int nbelm = 0;

    int liste[1000] = {0};

    while(sscanf(curseur, "%d", &liste[nbelm])==1){
        while (*curseur && *curseur != ',') {curseur++;}
        while (*curseur == ',') {curseur++;}
        nbelm++;
    }
    return liste[nbelm/2] * verifierliste(liste, nbelm, liste1, liste2, taille);
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int liste1[2000] = {0};
    int liste2[2000] = {0};

    int taille = 0;
    char ligne[1000]; // Taille maximale d'une ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if(strcmp("\n",ligne) == 0){break;}
        sscanf(ligne, "%d|%d", &liste1[taille], &liste2[taille]); 
        taille++;
    }
    
    int s =0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        s += traiterLigne1(ligne, liste1, liste2, taille); 
    }

    fclose(fichier);
    return s;
}

void swap(int tab[], int i, int j){ // echange les elements aux indices i et j dans tab
    int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

int indicevraipremier(int liste[], int nbelm, int liste1[], int liste2[], int taille){
    //renvoie l indice de celui qui devrait etre en premier
    
    bool indicevalide; // memorise si lindice est valide

    for(int i = 0; i <nbelm; i++){
        indicevalide = true; // par default oui
        for(int j = 0; j <nbelm; j++){
            if(i == j){j++;} // on evite l auto test
            if(!(verifiercouple(liste[i] , liste[j], liste1, liste2, taille))){indicevalide = false;} // plus mtn
        }
        if (indicevalide){return i;} // si l indice est valide on le renvoie
    }
    return nbelm-1;
}

int traiterLigne2(char ligne[], int liste1[], int  liste2[], int taille){
    char * curseur = ligne;
    int nbelm = 0;

    int liste[1000] = {0};

    while(sscanf(curseur, "%d", &liste[nbelm])==1){
        while (*curseur && *curseur != ',') {curseur++;}
        while (*curseur == ',') {curseur++;}
        nbelm++;
    }

    if (verifierliste(liste, nbelm, liste1, liste2, taille)){return 0;}

    int compteur = 0;

    // on trie la liste (tri par selection)
    for(int k = 0; k<nbelm; k++){
        swap(liste+k, indicevraipremier(liste + k,nbelm-k,liste1,liste2,taille),0);
    }

    return liste[nbelm/2];
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int liste1[2000] = {0};
    int liste2[2000] = {0};

    int taille = 0;
    char ligne[1000]; // Taille maximale d'une ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if(strcmp("\n",ligne) == 0){break;}
        sscanf(ligne, "%d|%d", &liste1[taille], &liste2[taille]); 
        taille++;
    }
    
    int s =0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        s += traiterLigne2(ligne, liste1, liste2, taille); 
    }

    fclose(fichier);
    return s;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ5.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ5.txt"));
    return 0;
} 