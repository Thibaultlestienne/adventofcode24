#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int x, y;
    char c;
    int s =0;
    bool actif = true;

    char ligne[10000]; 
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        while(*curseur != '\0'){
            if (sscanf(curseur, "mul(%d,%d)%c", &x,&y,&c) == 3){s += x*y*actif;} // le %c force a verifier jusqu au bout
            curseur++;
        }
    }

    fclose(fichier);
    return s;
}


int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int x, y;
    char c;
    int s =0;
    bool actif = true;

    char ligne[10000]; 
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        while(*curseur != '\0'){
            if (sscanf(curseur, "mul(%d,%d)%c", &x,&y,&c) == 3){s += x*y*actif;} // le %c force a verifier jusqu au bout
            else if (sscanf(curseur, "don't()%c",&c) == 1){actif = false;}
            else if (sscanf(curseur, "do()%c",&c) == 1){actif = true;}
            curseur++;

        }
    }

    fclose(fichier);
    return s;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ3.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ3.txt"));
    return 0;
} 