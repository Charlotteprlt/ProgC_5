#include<iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "distance.h"
using namespace std ;


//Ajout au traitement de calcul de la distance de Levenshtein d'une fonction permettant de renvoyer le temps d'exécution.
int main(){
//    clock_t t1 = clock();
//    cout<< distanceLeven_naive("ecoles", "ecloses") <<endl;
//    clock_t t2 = clock();
//    cout<< (t2-t1)/CLOCKS_PER_SEC;

    string s1 = "ecoles";
    string s2 = "ecloses";
//    int l1 = s1.size();
//    int l2 = s2.size();

//    int memo[l1][maxi];
//    for(int i = 0; i<l1; i++){
//        for(int j = 0; j<maxi; j++){
//            memo[i][j] = -1;
//        }
//    }
//    clock_t t3 = clock();
//    cout<< distanceLeven_memo(s1, s2, l1, l2, memo) << endl;
//    clock_t t4 = clock();
//    cout<< (t3-t4)/CLOCKS_PER_SEC;

//    clock_t t5 = clock();
//    cout << distanceLeven_ite(s1, s2) << endl;
//    clock_t t6 = clock();
//    cout << (t6-t5)/CLOCKS_PER_SEC;

//    string s3 = "chien";
//    string s4 = "chine";
//    clock_t t7 = clock();
//    cout<< distanceDamerauLeven_ite(s3, s4) << endl;
//    clock_t t8 = clock();
//    cout << (t8-t7)/CLOCKS_PER_SEC;

    clock_t t9 = clock();
    cout<< distanceLeven_ite_chemin(s1, s2) << endl;
    clock_t t10 = clock();
    cout << (t10-t9)/CLOCKS_PER_SEC;


    return 0;
}

