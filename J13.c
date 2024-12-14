#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

int prix(int Ax, int Ay, int Bx, int By, int Px, int Py){
    int retour = 0;
    int restantx, restanty;

    int ka = 0;
    while(Ax * ka <= Px && Ay * ka <= Py){
        restantx = Px-(Ax*ka);
        restanty = Py-(Ay*ka);

        if (restantx%Bx == 0 && restanty%By == 0 && restantx/Bx == restanty/By ){
            if (retour == 0 || retour>((3*ka) + (restantx/Bx))){
                retour = 3*ka + restantx/Bx;
            }
        }

        ka++;
    }    
    return retour;


}

int etoile1(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");

    char ligne[10000]; 

    int retour = 0;

    int Ax,Ay,Bx,By,Px,Py;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "Button A: X+%d, Y+%d", &Ax,&Ay) == 2){}
        if (sscanf(ligne, "Button B: X+%d, Y+%d", &Bx,&By) == 2){}
        if (sscanf(ligne, "Prize: X=%d, Y=%d", &Px,&Py) == 2){retour += prix(Ax,Ay,Bx,By,Px,Py);}
    }

    fclose(fichier);
    return retour;
}


//On s inspire de la resolution matriciel du systeme
// On note 
//        
//  M = (xa xb)
//      (ya yb)
//
//  P = (xp)
//      (yp)
//
//
//  K = (ka)
//      (kb)
//
// donc MK =P

long long int prix2(long long int Ax,long long int Ay, long long int Bx, long long int By, long long int Px, long long int Py){
    // long long int M[2][2] = {{Ax,Bx},{Ay,By}};
    long long int det = (Ax * By) - (Ay * Bx);
    if (det == 0){ // A et B colineaires
        if (Ax * Py != Ay * Px){return 0;}// pas de solution
        else{ // A B et P colineaires
            if (Ax / Bx > 3){// on utilise un max de A
                int restantx, restanty;
                int kb = 0;
                while(Bx * kb <= Px && By * kb <= By){
                    restantx = Px-(Bx*kb);
                    restanty = Py-(By*kb);
                    if (restantx%Ax == 0 && restanty%Ay == 0 && restantx/Ax == restanty/Ay ){
                        return kb + 3 * restantx/Ax;
                    }
                    kb++;
                }
                return 0;
            }
            else{// on utilise un max de B
                int restantx, restanty;
                int ka = 0;
                while(Ax * ka <= Px && Ay * ka <= Ay){
                    restantx = Px-(Ax*ka);
                    restanty = Py-(Ay*ka);
                    if (restantx%Bx == 0 && restanty%By == 0 && restantx/Bx == restanty/By ){
                        return ka * 3 + restantx/Bx;
                    }
                    ka++;
                }
                return 0;
            }
        }
    }
    // on évite l utilisation de double pour les arrondis
    // double Minv[2][2] = (1/det) * {{By,(-Bx)},{(-Ay),Ax}};
    long long int ka = -1;
    long long int kb = -1;
    if ((By * Px + ((-Bx)*Py)) % det == 0){
        ka = (By * Px + ((-Bx)*Py)) / det;
    }
    if (((-Ay) * Px + (Ax*Py)) % det == 0){
        kb = ((-Ay) * Px + (Ax*Py)) / det;
    }
    if (ka != -1 && kb != -1 ){
        return 3*ka + kb;
    }
    return 0;

}

long long int etoile2(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    char ligne[10000]; 

    long long int retour = 0;

    long long int Ax,Ay,Bx,By,Px,Py;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "Button A: X+%lld, Y+%lld", &Ax,&Ay) == 2){}
        if (sscanf(ligne, "Button B: X+%lld, Y+%lld", &Bx,&By) == 2){}
        if (sscanf(ligne, "Prize: X=%lld, Y=%lld", &Px,&Py) == 2){
                                                                Px += 10000000000000;
                                                                Py += 10000000000000;
                                                                retour += prix2(Ax,Ay,Bx,By,Px,Py);
                                                            }
    }

    fclose(fichier);
    return retour;
}

int main(){
    printf("etoile 1 : %d\n",etoile1("entreeJ13.txt"));
    printf("etoile 2 : %lld\n",etoile2("entreeJ13.txt"));
    return 0;
} 