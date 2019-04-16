#pragma once
#include <iostream>
using namespace std;
const int maxi = 100;

int distanceLeven_naive(string s1, string s2);

int distanceLeven_memo(string s1, string s2, int i, int j, int memo[][maxi]);

int distanceLeven_ite(string s1, string s2);

int distanceDamerauLeven_ite(string s1, string s2);

int distanceLeven_ite_chemin(string s1, string s2);
