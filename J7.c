#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

bool peutEtreEgale1(long long int valeurcible, int liste[], int longeur){
    if (longeur == 1){return (valeurcible == liste[0]);}
    return 
        // +
        peutEtreEgale1(valeurcible-liste[longeur-1], liste, longeur-1) 
        // *
        || (valeurcible % liste[longeur-1] == 0)
            && peutEtreEgale1(valeurcible/liste[longeur-1], liste, longeur-1);
}

long long int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    long long int valeurcible;
    int liste[100] = {0};

    long long int retour = 0;

    int i = 0;
    int longeur =0;

    char ligne[1000]; // Taille maximale d'une ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {  
        char * curseur = ligne;

        sscanf(ligne, "%lld",&valeurcible); 
        while (*curseur != ':'){curseur++;}
        curseur++;
        while (*curseur == ' '){curseur++;}
        
        longeur = 0;

        while (sscanf(curseur, "%d",&liste[longeur]) == 1){
            longeur++;
            while (*curseur != ' ' && *curseur != '\0'){curseur++;}
            if(*curseur == '\0'){break;}
            while (*curseur == ' '){curseur++;}
            
        }
        if(peutEtreEgale1(valeurcible, liste, longeur)){retour += valeurcible;}
    }

    fclose(fichier);
    return retour;
}

long long int ordreDeGrandeur(long long int n){// pour 2459 renvoie 10000
    if (n<1){return 1;}
    else{return 10 * ordreDeGrandeur(n/10);}
}

bool peutEtreEgale2(long long int valeurcible, long long int liste[], int longeur){
    if (longeur == 1){return (valeurcible == liste[0]);}
    return 
        // +
        peutEtreEgale2(valeurcible-liste[longeur-1], liste, longeur-1) 
        // *
        || (valeurcible % liste[longeur-1] == 0)
            && peutEtreEgale2(valeurcible/liste[longeur-1], liste, longeur-1)
        // ||
        || (valeurcible % ordreDeGrandeur(liste[longeur-1]) == liste[longeur-1]
            && peutEtreEgale2((valeurcible-liste[longeur-1])/ordreDeGrandeur(liste[longeur-1]), liste, longeur-1));
}

long long int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    long long int valeurcible;
    long long int liste[100] = {0};

    long long int retour = 0;

    int i = 0;
    int longeur =0;

    char ligne[1000]; // Taille maximale d'une ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {  
        char * curseur = ligne;

        sscanf(ligne, "%lld",&valeurcible); 
        while (*curseur != ':'){curseur++;}
        curseur++;
        while (*curseur == ' '){curseur++;}
        
        longeur = 0;

        while (sscanf(curseur, "%lld",&liste[longeur]) == 1){
            longeur++;
            while (*curseur != ' ' && *curseur != '\0'){curseur++;}
            if(*curseur == '\0'){break;}
            while (*curseur == ' '){curseur++;}
            
        }
        if(peutEtreEgale2(valeurcible, liste, longeur)){retour += valeurcible;}
    }

    fclose(fichier);
    return retour;
}

int main(){
    printf("etoile 1 : %lld\n",etoile1("entreeJ7.txt"));
    printf("etoile 2 : %lld\n",etoile2("entreeJ7.txt"));
    return 0;
} 