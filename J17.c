#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define TAILLESEMIDYN 1000

typedef struct tableausemidyn{//la taille aloué vaut TAILLESEMIDYN
    int taille;
    int tab[TAILLESEMIDYN];
}tableausemidyn;

tableausemidyn sortie;
 
int A,B,C,pointeur;

int combo(int operande){
    if (operande >= 0 && operande <=3){return operande;}
    if (operande == 4){return A;}
    if (operande == 5){return B;}
    if (operande == 6){return C;}

    printf("\n!!!!!!!!!!!!!!Error!!!!!!!!!!!!\n");exit(-1);
}

int pow2(int n){
    if (n == 0) {return 1;}
    return 2 * pow2(n-1);
}

void operation0(int operande){
    A = A/pow2(combo(operande));
}

void operation1(int operande){
    B = B^operande;
}

void operation2(int operande){
    B = combo(operande)%8;
}

void operation3(int operande){
    if(A!=0){pointeur = operande-2;}
}

void operation4(int operande){
    B = B^C;
}

void operation5(int operande){
    sortie.tab[sortie.taille] = combo(operande)%8;
    sortie.taille++;
}

void operation6(int operande){
    B = A/pow2(combo(operande));
}

void operation7(int operande){
    C = A/pow2(combo(operande));
}

void executer(int instructions[]){
    int instruction = instructions[pointeur];
    int operande = instructions[pointeur+1];

    //printf("Operation %d operande %d A %d B %d C %d\n", instruction, operande, A,B,C);

    if (instruction == 0){operation0(operande);}
    else if (instruction == 1){operation1(operande);}
    else if (instruction == 2){operation2(operande);}
    else if (instruction == 3){operation3(operande);}
    else if (instruction == 4){operation4(operande);}
    else if (instruction == 5){operation5(operande);}
    else if (instruction == 6){operation6(operande);}
    else if (instruction == 7){operation7(operande);}

    
    pointeur+=2;
}

void vider(int * tab){
    for (int i = 0; i < TAILLESEMIDYN; i++) {
        tab[i] = 0;
    }
}

void etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int instructions[TAILLESEMIDYN] = {0};
    int taille = 0;

    char ligne[10000]; 

    pointeur = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        taille = 0;
        if(sscanf(curseur, "Register A: %d", &A)==1){continue;}
        if(sscanf(curseur, "Register B: %d", &B)==1){continue;}
        if(sscanf(curseur, "Register C: %d", &C)==1){continue;}
        else{           
            curseur+=9; 
            while(sscanf(curseur, "%d", &instructions[taille])==1){
                while (*curseur && *curseur != ',') {curseur++;}
                while (*curseur == ',') {curseur++;}
                taille++;
            }
        }
    }

    sortie.taille = 0;
    vider(sortie.tab);

    while(pointeur < taille){executer(instructions);}

    for (int i = 0;i<sortie.taille-1;i++){
        printf("%d,",sortie.tab[i]);
    }
    printf("%d\n",sortie.tab[sortie.taille-1]);
    fclose(fichier);
}

bool comparer(int * tab1, int* tab2 , int taille1, int taille2){
    if (taille1!=taille2){return false;}
    for (int i = 0; i < taille1; i++) {
        if(tab1[i] != tab2[i]){
            return false;
        }
    }
    return true;
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    int instructions[TAILLESEMIDYN] = {0};
    int taille = 0;

    char ligne[10000]; 

    pointeur = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char * curseur = ligne;
        taille = 0;
        if(sscanf(curseur, "Register A: %d", &A)==1){continue;}
        if(sscanf(curseur, "Register B: %d", &B)==1){continue;}
        if(sscanf(curseur, "Register C: %d", &C)==1){continue;}
        else{           
            curseur+=9; 
            while(sscanf(curseur, "%d", &instructions[taille])==1){
                while (*curseur && *curseur != ',') {curseur++;}
                while (*curseur == ',') {curseur++;}
                taille++;
            }
        }
    }

    int i = 0;
    while (true){
        A = i;
        B = 0;
        C = 0;
        pointeur = 0;
        sortie.taille = 0;
        vider(sortie.tab);

        while(pointeur < taille){executer(instructions);}
        if (comparer(sortie.tab,instructions,sortie.taille,taille)){break;}
        i++;
    }
    fclose(fichier);
    return i;
}

int main(){
    printf("etoile 1 : ");
    etoile1("entreeJ17.txt");
    //printf("etoile 2 : %d\n",etoile2("entreeJ17.txt"));
    return 0;
} 