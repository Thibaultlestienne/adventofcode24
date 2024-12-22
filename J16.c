#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define TAILLEMATRICE 150
 
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

    while (true){

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
        etat tournerd = {.poids = etatactuel.poids +1000,
                            .x = etatactuel.x,
                            .y = etatactuel.y,
                            .dx = -etatactuel.dy, 
                            .dy = etatactuel.dx, 
                            };
        inserer(f, tournerd);
        etat tournerg = {.poids = etatactuel.poids +1000,
                            .x = etatactuel.x,
                            .y = etatactuel.y,
                            .dx = etatactuel.dy, 
                            .dy = -etatactuel.dx, 
                            };
        inserer(f, tournerg);
    }


    free(f);
    libererfile(f);
    return 0;
}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int xdepart,ydepart, xarrive,yarrive;
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[10000]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (ligne[0] == '\n'){break;}
        int k = 0;
        matrice[taille][0] = '#';
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] == 'S'){xdepart=taille;ydepart=k;matrice[taille][k] = '.';}
            else if (ligne[k] == 'E'){xarrive=taille;yarrive=k;matrice[taille][k] = '.';}
            else {matrice[taille][k] = ligne[k];}
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = '#'; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matrice[i][j] = '#';
        }
    }


    fclose(fichier);
    return djkstra(matrice, xdepart,ydepart,xarrive,yarrive);
}

///////////////////////////////////// PART2
 
typedef struct listeetat2 listeetat2;

typedef struct etat2{
    listeetat2 * chemin;
    int poids; 
    int x;
    int y;
    int dx; 
    int dy;  
}etat2;

typedef struct listeetat2{
    etat2 e;
    struct listeetat2* suivant;
}listeetat2;

typedef struct filedeprio2{
    int taillealloue;
    int taille;
    etat2* file; 
}filedeprio2;

void initfile2(filedeprio2 * f){
    f->taillealloue = 1;
    f->taille = 0;
    etat2 * tab = malloc(sizeof(etat2));
    f->file = tab;
}

void libererfile2(filedeprio2 * f){
    free(f->file);
}

void copier2(etat2* copie, etat2* tabacopier, int taille){
    for (int i=0; i<taille;i++){
        copie[i] = tabacopier[i];
    }
}

void swap2(etat2 tab[], int i, int j){
    etat2 tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

void reordonnerinsertion2(filedeprio2* f,int indice){
    if (indice == 0){return;}
    if (f->file[indice].poids < f->file[(indice-1)/2].poids){
        swap2(f->file, indice, (indice-1)/2);
        reordonnerinsertion2(f,(indice-1)/2);
    }
}

void inserer2(filedeprio2* f, etat2 val){
    if (f->taille < f->taillealloue){
        f->file[f->taille] = val;
        reordonnerinsertion2(f, f->taille);
        f->taille++;
    }
    else{
        f->taillealloue = 2*f->taillealloue;
        etat2 * nouvellefile = malloc(sizeof(etat2) * f->taillealloue);
        copier2(nouvellefile, f->file, f->taille);
        free(f->file);
        f->file = nouvellefile;
        inserer2(f,val);
    }
}

void reordonnerpop2(filedeprio2* f, int indice) {
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
        swap2(f->file, indice, plus_petit);
        reordonnerpop2(f, plus_petit);
    }
}

etat2 pop2(filedeprio2* f){
    assert(f->taille>0);
    f->taille--;
    etat2 retour = f->file[0];
    f->file[0] = f->file[f->taille];
    reordonnerpop2(f,0);
    return retour;
}

listeetat2* ajout(etat2 e, listeetat2* l){
    listeetat2* retour = malloc(sizeof(listeetat2));
    retour->e = e;
    retour->suivant = l;
    return retour;

}

void marquerchemin(char matrice[TAILLEMATRICE][TAILLEMATRICE],listeetat2 * c){
    if (c==NULL){return;}
    matrice[c->e.x][c->e.y] = 'O';
    marquerchemin(matrice, c->suivant);
}


void djkstra2(char matrice[TAILLEMATRICE][TAILLEMATRICE],int xd,int yd,int xa,int ya){
    
    etat2 etatinit = {.chemin = NULL, .poids = 0, .x = xd, .y = yd, .dx = 0, .dy = 1 };
    filedeprio2* f = malloc(sizeof(filedeprio2));
    initfile2(f);
    inserer2(f,etatinit);

    bool visites[TAILLEMATRICE][TAILLEMATRICE][3][3] = {false};
    int poidsopt = INT_MAX;

    while (true){

        etat2 etatactuel = pop2(f);

        if (visites[etatactuel.x][etatactuel.y][etatactuel.dx][etatactuel.dy]){continue;}
        visites[etatactuel.x][etatactuel.y][etatactuel.dx][etatactuel.dy] = true;


        if(etatactuel.x == xa && etatactuel.y == ya){
            matrice[xa][ya] = 'O';
            marquerchemin(matrice, etatactuel.chemin);
            poidsopt = etatactuel.poids ;
        } 
        if (etatactuel.poids > poidsopt){
            return;
        }

        if (matrice[etatactuel.x + etatactuel.dx][etatactuel.y + etatactuel.dy] != '#'){
            etat2 etatavancer = {.chemin = ajout(etatactuel,etatactuel.chemin),
                                .poids = etatactuel.poids + 1,
                                .x = etatactuel.x + etatactuel.dx, 
                                .y = etatactuel.y + etatactuel.dy, 
                                .dx = etatactuel.dx, 
                                .dy = etatactuel.dy, 
                                };
            inserer2(f,etatavancer);
            }
        etat2 tournerd = {  .chemin = etatactuel.chemin,
                            .poids = etatactuel.poids +1000,
                            .x = etatactuel.x,
                            .y = etatactuel.y,
                            .dx = -etatactuel.dy, 
                            .dy = etatactuel.dx, 
                            };
        inserer2(f, tournerd);
        etat2 tournerg = {  .chemin = etatactuel.chemin,
                            .poids = etatactuel.poids +1000,
                            .x = etatactuel.x,
                            .y = etatactuel.y,
                            .dx = etatactuel.dy, 
                            .dy = -etatactuel.dx, 
                            };
        inserer2(f, tournerg);
    }


    free(f);
    libererfile2(f);
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

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int xdepart,ydepart, xarrive,yarrive;
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[10000]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (ligne[0] == '\n'){break;}
        int k = 0;
        matrice[taille][0] = '#';
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] == 'S'){xdepart=taille;ydepart=k;matrice[taille][k] = '.';}
            else if (ligne[k] == 'E'){xarrive=taille;yarrive=k;matrice[taille][k] = '.';}
            else {matrice[taille][k] = ligne[k];}
        }
        for (;k<TAILLEMATRICE;k++) {
            matrice[taille][k] = '#'; //hors limite
        }
        taille++;
    }

    for (int i = taille;i<TAILLEMATRICE;i++){
        for (int j = 0;j<TAILLEMATRICE;j++){
            matrice[i][j] = '#';
        }
    }


    fclose(fichier);
    djkstra2(matrice, xdepart,ydepart,xarrive,yarrive);

    for (int i = 0; i<TAILLEMATRICE;i++){
        for (int j = 0; j<TAILLEMATRICE;j++){
            printf("%c",matrice[i][j]);
        }
        printf("\n");
    }

    return compterO(matrice);
}



int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ16.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ16.txt"));
    return 0;
} 