#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

typedef struct liste{
    long long int elm;
    struct liste *suivant;
} liste; 

void ajouter(liste ** l, int e){
    liste * ajout = malloc(sizeof(liste));
    assert(ajout!=NULL);
    if (*l == NULL){
        ajout->suivant = NULL;
        ajout->elm = e;
        *l = ajout;
    }

    else{   
        ajout->suivant = (*l)->suivant;
        ajout->elm = e;
        (*l)->suivant = ajout;
    }
}

void liberer(liste * l){
    if (l == NULL){return;}
    liberer(l->suivant);
    free(l);
}

void afficher(liste * l){
    if (l == NULL){printf("\n");return ;}
    printf("%lld ", l->elm);
    afficher(l->suivant);
}

int compter(liste * l){
    if (l == NULL){return 0;}
    return 1 + compter(l->suivant);
}

long long int nbChiffre(long long int n){
    if (n== 0){return 0;}
    return 1+nbChiffre(n/10);
}

long long int puissance10(long long int n){
    if (n == 0) {return 1;}
    return 10 * puissance10(n-1);
}

void blink(liste ** l){//blink 1 fois
    if (*l == NULL){return ;}
    int nc = nbChiffre((*l)->elm);
    if ((*l)->elm == 0){(*l)->elm = 1;blink(&((*l)->suivant));}
    else if (nc%2 == 1){(*l)->elm = (*l)->elm * 2024;blink(&((*l)->suivant));}
    else{ 
        long long int puissance = puissance10(nc/2);
        long long int nb1 = (*l)->elm / puissance;
        long long int nb2 = (*l)->elm % puissance;
        (*l)->elm = nb1;
        ajouter(l,nb2);
        blink(&((*l)->suivant->suivant));
    }
    
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char ligne[10000];
    liste * l = NULL;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        int val;
        while(sscanf(curseur, "%d", &val)==1){
            ajouter(&l,val);
            while (*curseur && *curseur != ' ') {curseur++;}
            while (*curseur == ' ') {curseur++;}
        }
    }

    fclose(fichier);
    for (int i = 0; i< 25; i++){
        blink(&l);
    }

    int s = compter(l);
    liberer(l);
    return s;
}

bool dedans(long long int e, liste* l){
    if (l == NULL){return false;}
    if (l->elm == e){return true;}
    return dedans(e,l->suivant);
}

void ajouterdifferent(liste ** different, liste* l){
    if (l == NULL){return ;}
    if (!(dedans(l->elm, *different))){ajouter(different,l->elm);}
    ajouterdifferent(different,l->suivant);
}

void supprimer(liste ** l){
    liste* suite = (*l)->suivant;
    free(*l);
    *l = suite;
}

void supprimerDoublon(liste ** l){
    if (*l == NULL){return ;}
    else if (dedans((*l)->elm, (*l)->suivant)){
        supprimer(l);supprimerDoublon(l);
    }
    else {supprimerDoublon(&((*l)->suivant));}
}

int chercher(long long int e, liste* l){
    if (l == NULL){return -1;}
    if (l->elm == e){return 0;}
    return 1 + chercher(e,l->suivant);
}

void copier(liste * l ,long long int tab[]){
    if (l == NULL){return;}
    tab[0] = l->elm;
    copier(l->suivant, tab+1);
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char ligne[10000];
    liste * l = NULL;
    liste * copiel = NULL;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        int val;
        while(sscanf(curseur, "%d", &val)==1){
            ajouter(&l,val);
            ajouter(&copiel,val);
            while (*curseur && *curseur != ' ') {curseur++;}
            while (*curseur == ' ') {curseur++;}
        }
    }



    fclose(fichier);

    liste * different = NULL;
    supprimerDoublon(&l);
    ajouterdifferent(&different, l);

    for (int i = 0; i< 75; i++){
        blink(&l);
        supprimerDoublon(&l);
        ajouterdifferent(&different, l);
        //printf("%d %d\n",i, compter(different));
    }

    int taille = compter(different);

    long long int* Mi = malloc(sizeof(long long int) * taille); // Matrice de depart
    assert(Mi!=NULL);
    long long int* Miprime = malloc(sizeof(long long int) * taille); // Matrice de depart
    assert(Miprime!=NULL);

    for(int j=0;j<taille;j++){
        Mi[j] = 0;
    }

    //init de Mi
    liste * listepourparcours = copiel; 
    while (listepourparcours!=NULL){
        Mi[chercher(listepourparcours->elm,  different)]++;
        listepourparcours = listepourparcours->suivant;
    }

    long long int* tab = malloc(sizeof(long long int) * taille);
    copier(different, tab);

    for (int i = 0; i < 6; i++ ){
        for(int j=0;j<taille;j++){
            Miprime[j] = 0;
        }

        for(int j=0;j<taille;j++){
            if (Mi[j] != 0){
                int nc = nbChiffre(tab[j]);
                printf("%lld %d, %lld %d %d\n",tab[j],nc, 2024 * tab[j], chercher(2024 * tab[j],different), chercher(tab[j],different));

                if (tab[j] == 0){Miprime[chercher(1,different)]+= Mi[j];}
                else if (nc % 2 == 1){Miprime[chercher(2024 * tab[j],different)]+= Mi[j];}
                else {
                    long long int puissance = puissance10(nc/2);
                    Miprime[chercher(tab[j]/ puissance,different)]+= Mi[j];
                    Miprime[chercher(tab[j]%puissance,different)]+= Mi[j];
                }
            }
        }        

        for(int j=0;j<taille;j++){
            Mi[j] = Miprime[j];
        }
        printf("----------------------\n");
    } 


    long long int s = 0;
    for (int i = 0; i < taille; i++ ){
        s+=Mi[i];
    } 

    liberer(different);
    liberer(l);
    liberer(copiel);

    free(tab);
    free(Mi);
    free(Miprime);

    return s;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ11.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ11.txt"));
    return 0;
} 