// vaja5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <stdlib.h>
#include <string>
#define INF 12345689
#define NIL -1
using namespace std;

int C[20][20];
int vel;

void beri(string f) {
	fstream dat(f.c_str(), fstream::in);
	dat >> vel;
	int i = 0;
	int p, q, c;

	while (!dat.eof()) {
		dat >> p >> q >> c;
		C[q - 1][p - 1] = INF;
		C[p - 1][q - 1] = c;
		i++;
	}
	dat.close();
}

void floyd_warshall(int C[][20], int D[][20], int pi[][20]) {

	for (int i = 0; i < vel; i++) {
		for (int j = 0; j < vel; j++) {
			D[i][j] = C[i][j];
			if (i != j && C[j][i] == INF) {
				pi[i][j] = i;
			}
			else {
				pi[i][j] = NIL;
			}
		}
	}

	for (int k = 0; k < vel; k++) {
		for (int i = 0; i < vel; i++) {
			for (int j = 0; j < vel; j++) {
				if (D[i][j] > (D[i][k] + D[k][j])) {
					D[i][j] = D[i][k] + D[k][j];
					pi[i][j] = pi[k][j];
				}
			}
		}
	}
	cout << "D matrika" << endl;
	for (int i = 0; i < vel; i++) {
		for (int j = 0; j < vel; j++) {
			cout << D[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	cout << "pi matrika" << endl;
	for (int i = 0; i < vel; i++) {
		for (int j = 0; j < vel; j++) {
			cout << pi[i][j] << " ";
		}
		cout << endl;
	}
}
void izpisPoti(int pi[][20], int s, int g) {

	if (s == g) {
		cout << s << " ";
	}
	else {
		if (pi[s][g] == NIL) {
			cout << "Med " << s << " in " << g << " ni poti." << endl;
			exit(0);
		}
		else {
			izpisPoti(pi, s, pi[s][g]);
			cout << g << " ";
		}
	}
}
int main()
{
	
	int izbira = 0, S, G;
	int D[20][20];
	int pi[20][20];

	
	while (izbira != 4) {
		cout << "\nFloyd-Warshallov algoritem - izbira:" << endl;
		cout << "1 Preberi graf iz datoteke" << endl;
		cout << "2 Zagon algoritma" << endl;
		cout << "3 Izpis najkrajse poti med vozliscema s in g" << endl;
		cout << "4 konec" << endl;
		cout << endl;
		cout << "Vasa izbira: " << endl;
		cin >> izbira;
		if (izbira == 1) {
			beri("Testni_graf.txt");
		}
		else if (izbira == 2) {
			floyd_warshall(C, D, pi);
		}
		else if (izbira == 3) {
			cout << "Vnesite vozlisce s: " << endl;
			cin >> S;
			cout << "Vnesite vozlisce g: " << endl;
			cin >> G;
			izpisPoti(pi, S, G);
		}
		else if(izbira == 4){
			return 0;
		}
	}
    return 0;
}

