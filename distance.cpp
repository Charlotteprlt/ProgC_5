#include <vector>
#include <iostream>
using namespace std;
#include "distance.h"


//Implementation récursive directe du calcul de la distance de Levenshtein. Cette méthode ne conserve pas en mémoire les calculs effectués précédemment
//ce qui rend son implémentation très coûteuse.

int distanceLeven_naive(string s1, string s2){
    int cost = 0;
    int l1 = s1.size();
    int l2 = s2.size();
    if(l1 == 0){
        return l2;
    }
    if(l2 == 0){
        return l1;
    }
    if(s1[l1-1] != s2[l2-1]){
        cost += 1;
    }
    string s1_new = s1;
    string s2_new = s2;
    s1_new.erase(l1-1, 1);
    s2_new.erase(l2-1, 1);
    int d1 = distanceLeven_naive(s1_new, s2);
    int d2 = distanceLeven_naive(s1, s2_new);
    int d3 = distanceLeven_naive(s1_new, s2_new);
    return min(min(1+d1, 1+d2), d3+cost);
}

//Implémentation récursive avec mémoïsation du calcul de la distance de Levenshtein.
//Au préalable on suppose que l'on dispose d'un tableau de largeur égale à la longueur de s2
//et de hauteur égale à la longueur de s1. Ce tableau est initialisé avec que des -1.

int distanceLeven_memo(string s1, string s2, int i, int j, int memo[][maxi]){
    if(i == 0){
        return j;
    }
    if(j == 0){
        return i;
    }
    //si la valeur de la distance a déjà été calculée et stockée dans le tableau mémo, on la renvoie.
    if(memo[i-1][j-1] != -1){
        return memo[i-1][j-1];
    }
    //si la valeur de la distance n'a pas déjà été calculée, il y a deux cas : le cas où les dernières lettres des deux suffixes sont identiques et le
    //cas où ces deux dernières lettres sont différentes.
    if(s1[i-1] == s2[j-1]){
        return memo[i-1][j-1] = distanceLeven_memo(s1, s2, i-1, j-1, memo);
    }
    return memo[i-1][j-1] = 1+min(min(distanceLeven_memo(s1, s2, i-1, j, memo), distanceLeven_memo(s1, s2, i, j-1, memo)),distanceLeven_memo(s1, s2, i-1, j-1, memo));
}

//Algorithme itératif de calcul de la distance de Levenshtein. Afin de calculer itérativement les distances de Levenshtein, on stocke au
//fur et à mesure les distances calculées dans un tableau nommé distance.


int distanceLeven_ite(string s1, string s2){
int coutSubstitution = 0;
    //tableau de tableau dynamique
    int l1 = s1.size();
    int l2 = s2.size();
//creation d'un tableau dis dans lequel on stocke au fur et à mesure les valeurs des distances.
    int distance[l1+1][l2+1];
    for(int i=0; i<l1+1; i++){
        distance[i][0] = i;
    }
    for(int j=0; j<l2+1; j++){
        distance[0][j] = j;
    }
    for(int k=1; k<l1+1; k++){
        for(int l=1; l<l2+1; l++){
            if(s1[k] == s2[l]){
                distance[k][l] = distance[k-1][l-1];
            }
            else{
                distance[k][l] = min(min(distance[k-1][l]+1, distance[k][l-1]+1), distance[k-1][l-1]+1);
            }
        }
    }
    return distance[l1][l2];
}

//Version itérative de calcul de la distance de Damerau-Levenshtein cette fois-ci.
int distanceDamerauLeven_ite(string s1, string s2){
    int coutSubstitution = 0;
    //tableau de tableau dynamique
    int l1 = s1.size();
    int l2 = s2.size();
    //creation d'un tableau dis dans lequel on stocke au fur et à mesure les valeurs des distances.
    int distance[l1+1][l2+1];
    for(int i=0; i<l1+1; i++){
        distance[i][0] = i;
    }
    for(int j=0; j<l2+1; j++){
        distance[0][j] = j;
    }
    for(int k=1; k<l1+1; k++){
        for(int l=1; l<l2+1; l++){
            if(s1[k] == s2[l]){
                distance[k][l] = distance[k-1][l-1];
            }
//dans le cadre de la distance de Damerau-Levenshtein, il faut prendre en compte le cas d'inversion.
            if(s1[k-1] == s2[l] && s1[k] == s2[l-1]){
                if(distance[k-2][l-2]+1<distance[k][l]){
                    distance[k][l] = distance[k-2][l-2]+1;
                }
            }
            else{
                distance[k][l] = min(min(distance[k-1][l]+1, distance[k][l-1]+1), distance[k-1][l-1]+1);
            }
        }
    }
    return distance[l1][l2];
}


//Algorithme itératif de calcul de la distance de Levenshtein avec affichage des modifications successives. Pour cela, il faut stocker dans
//un tableau pred, tous les éléments prédécesseurs. Dans les cases d'un tableau il n'est pas possible de stocker des couples, donc on utilise
//plutôt un vecteur de vecteurs.


int distanceLeven_ite_chemin(string s1, string s2){
    string word1=s1;
    string word2=s2;
    int l1 = s1.size();
    int l2 = s2.size();

    //On commence par construire le tableau mémorisant les distances.
    int *dist[l1+1];
    for (int i=0;i<l1+1;++i){
        dist[i]=new int[l2+1];
        dist[i][0]=i;
    }

    for (int j=0;j<l2+1;++j){
        dist[0][j]=j;
    }


    for (int i=1;i<l1+1;++i){
            for (int j=1;j<l2+1;++j){
                int d1=dist[i-1][j]+1; //cela correspond au cas de la suppression d'une lettre.
                int d2=dist[i][j-1]+1; //cela correspond au cas de l'insertion d'une lettre.
                int cost=0;
                if (s1[i]!=s2[j])
                    cost += 1;
                int d3=dist[i-1][j-1]+cost; //cela correspond au cas de la substitution de deux lettres.

                dist[i][j]=min(d1,min(d2,d3));

                //Ajout du cas de l'inversion pour la distance de Damerau-Levenstein
                if (i>1 && j>1 && s1[i]==s2[j-1] && s1[i-1]==s2[j]){
                    dist[i][j]=min(dist[i][j],dist[i-2][j-2]+1);

                }
            }
        }

    //Affiche du chemin emprunté.
    int d=dist[l1][l2];
    int i0=l1;
    int j0=l2;
    int min0;
    string str0;
    string current_word1=s1;
    vector<string> C; //le vecteur contenant les chaines de caractères correspondant aux différentes modifications.
    cout<<current_word1<<endl;
    while(i0>0 && j0>0 && dist[i0][j0]>0){
        min0= min ( min( dist[i0][j0-1] , dist[i0-1][j0] ) , dist[i0-1][j0-1]) ;
        if(i0>1 && j0>1 && s1[i0-1]==s2[j0-2] && s1[i0-2]==s2[j0-1] && dist[i0-2][j0-2]<=min0){
            current_word1[i0-1]=s2[j0-1];
            current_word1[i0-2]=s2[j0-2];
            str0="We change";str0.push_back(s1[i0-1]); str0+= " and "; str0.push_back(s2[j0-1]);str0+="which gives"; str0+=current_word1;
            C.push_back(str0);
            i0-=2;
            j0-=2;
        }
        else if (min0==dist[i0-1][j0-1]){
            if(dist[i0-1][j0-1]==dist[i0][j0]-1 && s1[i0-1]!=s2[j0-1]){
                current_word1[i0-1]=s2[j0-1];
                str0="We replace";str0.push_back(s1[i0-1]); str0+= " by "; str0.push_back(s2[j0-1]);str0+=" which gives "; str0+=current_word1;
                C.push_back(str0);
                i0-=1;
                j0-=1;
            }
            else{
                i0-=1;j0-=1;
            }
        }
        else if ( min0 == dist[i0][j0-1] ){
            current_word1.insert(current_word1.begin()+i0,s2[j0-1]);
            char pos= ('0'+i0);
            str0="We insert ";str0.push_back(s2[j0-1]);str0+=" which gives ";str0+=current_word1;
            C.push_back(str0);
            j0-=1;
        }
        else{
            current_word1.erase(i0-1,1);
            str0="We suppress"; str0.push_back(s1[i0-1]);str0+="which gievs ";str0+=current_word1;
            C.push_back(str0);
            i0-=1;
        }
    }
    for (int i=0;i<C.size();i++){
        cout<<C[i]<<endl;
    }
    return d;
}


