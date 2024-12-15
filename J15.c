#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define TAILLEMATRICE 100

int score(char matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;
    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] == 'O'){
                retour += 100 *i + j;
            }
        }
    }
    return retour;
}

void afficher(char matrice[TAILLEMATRICE][TAILLEMATRICE]){
    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            printf("%c", matrice[i][j]);
        }
        printf("\n");
    }
}

bool unmouvement(char matrice[TAILLEMATRICE][TAILLEMATRICE], int dx, int dy, int x, int y){    


    if (matrice[x+dx][y+dy] == '#'){return false;}
    if (matrice[x+dx][y+dy] == '.'){matrice[x+dx][y+dy] = matrice[x][y]; return true;}

    if (unmouvement(matrice,dx,dy,x+dx,y+dy)){matrice[x+dx][y+dy] = matrice[x][y];return true;}
    else{return false;}

    
}    


int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int x,y;
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[10000]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (ligne[0] == '\n'){break;}
        int k = 0;
        matrice[taille][0] = '#';
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] == '@'){x=taille;y=k;matrice[taille][k] = '.';}
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

    int dx =0, dy=0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] ==  '^'){dx = -1; dy =  0;}
            else if (ligne[k] ==  'v'){dx =  1; dy =  0;}
            else if (ligne[k] ==  '>'){dx =  0; dy =  1;}
            else if (ligne[k] ==  '<'){dx =  0; dy = -1;}
            else{exit(1);}
            if (unmouvement(matrice,dx,dy,x,y)){x+=dx;y+=dy;}
        }
    }

    fclose(fichier);
    return score(matrice);
}

int score2(char matrice[TAILLEMATRICE][TAILLEMATRICE]){
    int retour = 0;
    for (int i = 0 ; i< TAILLEMATRICE;i++){
        for (int j = 0 ; j< TAILLEMATRICE;j++){
            if (matrice[i][j] == '['){
                retour += 100 *i + j;
            }
        }
    }
    return retour;
}

bool testermouvement(char matrice[TAILLEMATRICE][TAILLEMATRICE], int dx, int dy, int x, int y){
    if (dx == 0){//vers la droite ou vers la gauche
        if (matrice[x+dx][y+dy] == '.'){return true;}
        else if (matrice[x+dx][y+dy] == '#'){return false;}
        else {return testermouvement(matrice,dx,dy,x+dx,y+dy);}
    }
    else{
        if (matrice[x+dx][y+dy] == '.'){return true;}
        else if (matrice[x+dx][y+dy] == '#'){return false;}
        else if (matrice[x+dx][y+dy] == '['){return testermouvement(matrice,dx,dy,x+dx,y+dy) && testermouvement(matrice,dx,dy,x+dx,y+1+dy);}
        else if (matrice[x+dx][y+dy] == ']'){return testermouvement(matrice,dx,dy,x+dx,y+dy) && testermouvement(matrice,dx,dy,x+dx,y-1+dy);}
    }
}

void fairemouvement(char matrice[TAILLEMATRICE][TAILLEMATRICE],bool aetemodifie[TAILLEMATRICE][TAILLEMATRICE], int dx, int dy, int x, int y){
    
    if (dx == 0){//vers la droite ou vers la gauche
        if (matrice[x+dx][y+dy] == '.'){matrice[x+dx][y+dy] = matrice[x][y]; return ;}
        else if (matrice[x+dx][y+dy] == '#'){exit(1);}// impossible
        else {fairemouvement(matrice,aetemodifie,dx,dy,x+dx,y+dy); matrice[x+dx][y+dy] = matrice[x][y]; return; }
    }

    else{
        if (matrice[x+dx][y+dy] == '.'){matrice[x+dx][y+dy] = matrice[x][y];return;}
        else if (matrice[x+dx][y+dy] == '#'){exit(1);}// impossible
        else if (matrice[x+dx][y+dy] == '[' && !aetemodifie[x][y])
                                            {   aetemodifie[x][y] = true;
                                                aetemodifie[x][y+1] =true;
                                                fairemouvement(matrice,aetemodifie,dx,dy,x+dx,y+dy); 
                                                fairemouvement(matrice,aetemodifie,dx,dy,x+dx,y+1+dy);
                                                matrice[x+dx][y+dy] = matrice[x][y];
                                                matrice[x+dx][y+1+dy] = '.';
                                            }

        else if (matrice[x+dx][y+dy] == ']' && !aetemodifie[x][y]){  
                                                aetemodifie[x][y] = true;
                                                aetemodifie[x][y-1] =true; 
                                                fairemouvement(matrice,aetemodifie,dx,dy,x+dx,y+dy); 
                                                fairemouvement(matrice,aetemodifie,dx,dy,x+dx,y-1+dy);
                                                matrice[x+dx][y+dy] = matrice[x][y];
                                                matrice[x+dx][y-1-dy] = '.';
                                            }
    }
}

int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    

    int x,y;
    char matrice[TAILLEMATRICE][TAILLEMATRICE] = {0};

    char ligne[10000]; 

    int taille = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (ligne[0] == '\n'){break;}
        int k = 0;
        matrice[taille][0] = '#';
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] == '@'){x=taille;y=2*k;matrice[taille][2*k] = '.';matrice[taille][2*k+1] = '.';}
            else if (ligne[k] == 'O'){matrice[taille][2*k] = '[';matrice[taille][2*k+1] = ']';}
            else {matrice[taille][2*k] = ligne[k];matrice[taille][2*k+1] = ligne[k];}
        }
        k*=2;
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

    int dx =0, dy=0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int k = 0;
        for(;ligne[k] != '\0'&& ligne[k] != '\n' ;k++) {
            if (ligne[k] ==  '^'){dx = -1; dy =  0;}
            else if (ligne[k] ==  'v'){dx =  1; dy =  0;}
            else if (ligne[k] ==  '>'){dx =  0; dy =  1;}
            else if (ligne[k] ==  '<'){dx =  0; dy = -1;}
            else{exit(1);}
            if (testermouvement(matrice,dx,dy,x,y)){
                bool aetemodifie[TAILLEMATRICE][TAILLEMATRICE] ={0};
                fairemouvement(matrice,aetemodifie,dx,dy,x,y);x+=dx;y+=dy;
            }
        }
    }

    fclose(fichier);
    return score2(matrice);
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ15.txt"));
    printf("etoile 2 : %d\n",etoile2("entreeJ15.txt"));
    return 0;
} 