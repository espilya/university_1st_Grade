﻿#include "tablero.h"

//
//		Al eliminar un numero en una casilla, hace falta poner posibles valores para casillas rellenas/fijas?
//		Al poner un numero en una casilla, hace falta eliminar posibles valores para casillas rellenas/fijas?
//
//		--arreglar si se introduze valor malo
//
//		como mejor pasar constantes: "const string &fichero" o "const string fichero"??
//
//		dibujarTablero..

void iniciaTablero(tTablero tablero) {
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			iniciaCasilla(tablero[i][j]);
		}
	}
}

bool cargarTablero(const string &fichero, tTablero t) {
	char ch;
	bool ok = false;
	ifstream file;
	file.open(fichero);
	if (file.is_open()) {
		for (int i = 0; i < DIMENSION; i++) {
			for (int j = 0; j < DIMENSION; j++) {
				file.get >> ch;
				rellenaCasilla(t[i][j], ch, true);
			}
			calcElementosPosibles(t);
		}
		ok = true;
	}
	file.close();
	return ok;
}

void dibujarTablero(const tTablero tablero) {

}

bool ponerNum(tTablero t, int x, int y, int c) {
	const int modo = 1;
	bool ok = false;

	if (t[x][y].estado == VACIO && (0 < c && c < 10) && (0 < x&& x < 10) && (0 < y && y < 10)){
		rellenaCasilla(t[x][y], c);
		calcElementosPosibles(t, x, y, modo);
		ok = true;
	}
	return ok;
}

bool borraNum(tTablero t, int x, int y) {
	const int modo = 2;
	bool ok = false;
	const int numero = t[x][y].numero;

	if (t[x][y].estado == RELLENO && (0 < x && x < 10) && (0 < y && y < 10)) {
		borraCasilla(t[x][y]);
		calcElementosPosibles(t, x, y, modo, numero);
		ok = true;
	}
	return ok;
}


bool tableroLleno(const tTablero t) {
	bool lleno = true;
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			if (t[i][j].estado == VACIO) {
				lleno = false;
			}
		}
	}
	return lleno;
}


void mostrarPosibles(const tTablero t, int x, int y) {
	//muestra los valores posibles de la casilla del tablero dado que tiene
	//coordenadas(fila, col) (fila y col estarán en el intervalo[1, 9])
	if ((0 < x&& x < 10) && (0 < y && y < 10)) {
		if (t[x][y].estado != FIJA) {
			cout << "Valores posibles: ";
			for (int i = 0; i < DIMENSION; i++) {
				cout << t[x][y].posibles.elementos << ' ';
			}
			cout << endl;
		}
		else {
			cout << t[x][y].numero << endl;
		}
	}
	else cout << "Coordenada incorrecta." << endl;
}


void rellenarSimples(tTablero t) {
	int numero;
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			if (esSimple(t[i][j], numero))
				ponerNum(t, i, j, numero);
		}
	}
}

void calcElementosPosibles(tTablero t, int x = -1, int y = -1, int mode = 0, int c = -1) {
	if (mode == 0) {
		for (int i = 0; i < DIMENSION; i++) {
			for (int j = 0; j < DIMENSION; j++) {
				if (t[i][j].estado == VACIO)
					for (int a = 0; a < DIMENSION; a++) {
						if (t[a][j].estado == FIJA)
							delElemento(t[i][j].posibles, t[a][j].numero);
					}
				for (int b = 0; b < DIMENSION; b++) {
					if (t[i][b].estado == FIJA)
						delElemento(t[i][j].posibles, t[i][b].numero);
				}
			}
		}
	}
	else {
		for (int a = 0; a < DIMENSION; a++) {
			if (t[a][y].estado != FIJA) { //tampoco es necesario. de todos modos en ningun caso se va a modificar el valor de casilla FIJA
				if (mode == 1)
					delElemento(t[a][y].posibles, t[x][y].numero);
				else
					addElemento(t[a][y].posibles, c);
			}
		}
		for (int b = 0; b < DIMENSION; b++) {
			if (t[x][b].estado != FIJA) {
				if (mode == 1)
					delElemento(t[x][b].posibles, t[x][y].numero);
				else
					addElemento(t[x][b].posibles, c);

			}
		}
	}
}

void resolver(tTablero t, int nCasilla, bool &exito) {
	const int limiteCtd = 25;
	int ctd = 0; //para no entrar en un bucle infinito, si no se puede resolver con esta algoritmo/funcion rellenarSimples()
	exito = false;

	while ((!exito) && (ctd<limiteCtd)) {
		rellenarSimples(t);
		ctd++;
		exito = tableroLleno(t);
	}
}

