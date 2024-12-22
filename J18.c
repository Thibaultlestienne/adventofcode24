#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define TAILLEMATRICE 80
 
typedef struct etat{
    int poids; 
    int x;
    int y;
    int dx; 
    int dy;  
}etat;

typedef struct filedeprio{
    int taillealloue;
    int taille;
    etat* file; 
}filedeprio;

void initfile(filedeprio * f){
    f->taillealloue = 1;
    f->taille = 0;
    etat * tab = malloc(sizeof(etat));
    f->file = tab;
}

void libererfile(filedeprio * f){
    free(f->file);
}

void copier(etat* copie, etat* tabacopier, int taille){
    for (int i=0; i<taille;i++){
        copie[i] = tabacopier[i];
    }
}

void swap(etat tab[], int i, int j){
    etat tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

void reordonnerinsertion(filedeprio* f,int indice){
    if (indice == 0){return;}
    if (f->file[indice].poids < f->file[(indice-1)/2].poids){
        swap(f->file, indice, (indice-1)/2);
        reordonnerinsertion(f,(indice-1)/2);
    }
}

void inserer(filedeprio* f, etat val){
    if (f->taille < f->taillealloue){
        f->file[f->taille] = val;
        reordonnerinsertion(f, f->taille);
        f->taille++;
    }
    else{
        f->taillealloue = 2*f->taillealloue;
        etat * nouvellefile = malloc(sizeof(etat) * f->taillealloue);
        copier(nouvellefile, f->file, f->taille);
        free(f->file);
        f->file = nouvellefile;
        inserer(f,val);
    }
}

void reordonnerpop(filedeprio* f, int indice) {
    int plus_petit = indice;
    int gauche = (2 * indice) + 1;
    int droite = (2 * indice) + 2;

    if (gauche < f->taille && f->file[gauche].poids < f->file[plus_petit].poids) {
        plus_petit = gauche;
    }
    if (droite < f->taille && f->file[droite].poids < f->file[plus_petit].poids) {
        plus_petit = droite;
    }

    if (plus_petit != indice) {
        swap(f->file, indice, plus_petit);
        reordonnerpop(f, plus_petit);
    }
}

etat pop(filedeprio* f){
    assert(f->taille>0);
    f->taille--;
    etat retour = f->file[0];
    f->file[0] = f->file[f->taille];
    reordonnerpop(f,0);
    return retour;
}

int djkstra(char matrice[TAILLEMATRICE][TAILLEMATRICE],int xd,int yd,int xa,int ya){
    
    etat etatinit = {.poids = 0, .x = xd, .y = yd, .dx = 0, .dy = 1 };
    filedeprio* f = malloc(sizeof(filedeprio));
    initfile(f);
    inserer(f,etatinit);

    bool visites[TAILLEMATRICE][TAILLEMATRICE][3][3] = {false};

    while (f->taille > 0){

        etat etatactuel = pop(f);

        if (visites[etatactuel.x][etatactuel.y][etatactuel.dx][etatactuel.dy]){continue;}
        visites[etatactuel.x][etatactuel.y][etatactuel.dx][etatactuel.dy] = true;


        if(etatactuel.x == xa && etatactuel.y == ya){
            return etatactuel.poids;
        } 

        if (matrice[etatactuel.x + etatactuel.dx][etatactuel.y + etatactuel.dy] != '#'){
            etat etatavancer = {.poids = etatactuel.poids + 1,
                                .x = etatactuel.x + etatactuel.dx, 
                                .y = etatactuel.y + etatactuel.dy, 
                                .dx = etatactuel.dx, 
                                .dy = etatactuel.dy, 
                                };
            inserer(f,etatavancer);
            }
        etat tournerd = {.poids = etatactuel.poids +0,
                            .x = etatactuel.x,
                            .y = etatactuel.y,
                            .dx = -etatactuel.dy, 
                            .dy = etatactuel.dx, 
                            };
        inserer(f, tournerd);
        etat tournerg = {.poids = etatactuel.poids +0,
                            .x = etatactuel.x,
                            .y = etatactuel.y,
                            .dx = etatactuel.dy, 
                            .dy = -etatactuel.dx, 
                            };
        inserer(f, tournerg);
    }


    free(f);
    return -1;
}

int compterO(char matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;

    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] == 'O'){retour++;}
        }
    }

    return retour;
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int x,y;
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (i<1 || i>71 || j<1 || j>71){matrice[i][j] = '#';}// les bords
            else {matrice[i][j] = '.';}
        }
    }

    char ligne[10000]; 


    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && taille < 1024) {
        sscanf(ligne, "%d,%d\n", &x, &y);
        matrice[x+1][y+1] = '#';
        taille++;
    }

    fclose(fichier);
    return djkstra(matrice, 1,1,71,71);
}

void etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};
    int x,y;

    int i = 0;

    // 100 par 100

    do {

        fseek(fichier, 0, SEEK_SET);
        
        for (int i = 0 ; i< TAILLEMATRICE;i++){
            for (int j = 0 ; j< TAILLEMATRICE;j++){
                if (i<1 || i>71 || j<1 || j>71){matrice[i][j] = '#';}// les bords
                else {matrice[i][j] = '.';}
            }
        }

        char ligne[10000]; 

        int taille = 0;
        while (fgets(ligne, sizeof(ligne), fichier) != NULL && taille < i) {
            sscanf(ligne, "%d,%d\n", &x, &y);
            matrice[x+1][y+1] = '#';
            taille++;
        }
        i+=100;
    } while (djkstra(matrice, 1,1,71,71)!=-1);

    i-=200;

    //10 par 10 
    
    do {

        fseek(fichier, 0, SEEK_SET);
        
        for (int i = 0 ; i< TAILLEMATRICE;i++){
            for (int j = 0 ; j< TAILLEMATRICE;j++){
                if (i<1 || i>71 || j<1 || j>71){matrice[i][j] = '#';}// les bords
                else {matrice[i][j] = '.';}
            }
        }

        char ligne[10000]; 

        int taille = 0;
        while (fgets(ligne, sizeof(ligne), fichier) != NULL && taille < i) {
            sscanf(ligne, "%d,%d\n", &x, &y);
            matrice[x+1][y+1] = '#';
            taille++;
        }
        i+=10;
    } while (djkstra(matrice, 1,1,71,71)!=-1);

    i-=20;

    //1 par 1 
    do {
        fseek(fichier, 0, SEEK_SET);     
        for (int i = 0 ; i< TAILLEMATRICE;i++){
            for (int j = 0 ; j< TAILLEMATRICE;j++){
                if (i<1 || i>71 || j<1 || j>71){matrice[i][j] = '#';}// les bords
                else {matrice[i][j] = '.';}
            }
        }

        char ligne[10000]; 

        int taille = 0;
        while (fgets(ligne, sizeof(ligne), fichier) != NULL && taille < i) {
            sscanf(ligne, "%d,%d\n", &x, &y);
            matrice[x+1][y+1] = '#';
            taille++;
        }
        i++;
    } while (djkstra(matrice, 1,1,71,71)!=-1);

    i--;

    // recuperation de la sortie 
    
    char sortie[10000]; 

    fseek(fichier, 0, SEEK_SET);     
    for (int j = 0; j < i; j++) {
        char ligne[10000]; 
        fgets(sortie, sizeof(sortie), fichier);
    }

    fclose(fichier);
    printf("%s",sortie);
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ18.txt"));
    printf("etoile 2 : ");
    etoile2("entreeJ18.txt");
    return 0;
} 