#include "listaSudokus.h"

//
//

void creaLista(tListaSudokus &lista) {
	for (int i = 0; i < MAX_SUDOKUS; i++) {
		lista.array[i].fichero = "VACIO";
		lista.array[i].nivel = 0;
	}
	lista.cont = 0;
}

bool cargar(tListaSudokus &lista) {
	bool ok = false;
	string nombre;
	int nivel, ctd = 0;
	ifstream file;
	file.open(listaSudoku);
	if (file.is_open()) {
		while ((!file.eof()) && (ctd < MAX_SUDOKUS) && (file >> nombre) && (nombre != "")) {
			file >> nivel;
			// cout << nombre << '\t' << nivel << endl;
			lista.array[ctd].fichero = nombre;
			lista.array[ctd].nivel = nivel - 1;
			ctd++;
		}
		lista.cont = ctd;
		ok = true;
	}
	return ok;
}

int menuListaSudokus(const tListaSudokus &LISTA, tJuego &juego) {
	int op;
	cout << "Seleciona un sudoku." << endl;
	mostrar(LISTA);
	cout << "Introduze el numero del sudoku:\n>";
	op = leerOpcion(0, (LISTA.cont));
	if (op != 0) {
		juego.sudoku.fichero = LISTA.array[op - 1].fichero;
		juego.sudoku.nivel = LISTA.array[op - 1].nivel;
		juego.esSalvado = false;
	}
	clear();
	return op;
}

void mostrar(const tListaSudokus &LISTA) {
	//clear();
	cout << "Los sudokus disponibles son los siguientes:" << endl;
	colorStr("#  ", VERDE_OSC);
	colorStr("Nombre:", MAGENTA_OSC);
	colorStr("\tPuntos:\n", AMARILLO_OSC);
	for (int i = 0; i < LISTA.cont; i++) {
		colorStr(to_string(i), VERDE_OSC);
		cout << "  ";
		colorStr(LISTA.array[i].fichero, MAGENTA_OSC);
		cout << '\t';
		colorStr(to_string(LISTA.array[i].nivel), AMARILLO_OSC);
		cout << '\n';
	}
	colorStr("0. Salir\n", CYAN_OSC);
}

//----------------VERSION 2------------------

bool guardar(const tListaSudokus &lista) {
	ofstream file;
	int i = 0;
	file.open(listaSudoku);
	while (i < MAX_SUDOKUS && lista.array[i].fichero != "VACIO") {
		file << lista.array[i].fichero << '\t' << lista.array[i].nivel << '\n';
		i++;
	}
	return true;
}

bool registrarSudoku(tListaSudokus &lista) {
	int pos;
	bool ok, noExiste;
	tSudoku sudokuNuevo;
	if (lista.cont < MAX_SUDOKUS) {
		cout << "Introduzca el nombre completo del nuevo sudoku:\n>";
		do {
			getline(cin, sudokuNuevo.fichero);
			ok = comprobarStr(sudokuNuevo.fichero);
			noExiste = !buscarFichero(lista, sudokuNuevo.fichero);
			if (!ok)
				cout << "Nombre incorrecto. Prueba otra vez." << endl;
			if (!noExiste)
				cout << "Nombre existente. Prueba otra vez." << endl;
		} while (!ok || !noExiste);
		cout << endl << "Introduzca los puntos del sudoku:\n>";
		cin >> sudokuNuevo.nivel;
		pos = buscarPos(lista, sudokuNuevo);
		cout << pos;

		lista.cont++;
		insertarSudoku(lista, sudokuNuevo, pos);
		ok = true;
	}
	else
		colorStr("Error al insertar sudoku.\n LISTA COMPLETA\n", ROJO);
	return ok;
}

bool buscarFichero(const tListaSudokus &LISTA, const string NOMBRE) {
	int i = 0, x = LISTA.cont;
	bool encontrado = false;
	while ((x-- > 0) && !encontrado) {
		if (NOMBRE == LISTA.array[i].fichero)
			encontrado = true;
		i++;
	}
	return encontrado;
}


int buscarPos(const tListaSudokus &LISTA, const tSudoku &SUDOKU) {
	// Y POR Q NO INSERTAR AL FINAL??
	// hacerla por nivel o nombre?
	int pos;
	// por nombre
	int ini = 0, fin = LISTA.cont - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (SUDOKU.fichero == LISTA.array[mitad].fichero) {
			encontrado = true;
		}
		else if (SUDOKU < LISTA.array[mitad]) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	pos = mitad;
	return ini;
}


void insertarSudoku(tListaSudokus &lista, const tSudoku &SUDOKU, const int POS) {
	for (int i = lista.cont - 1; i > POS; i--)
		lista.array[i] = lista.array[i - 1];
	lista.array[POS] = SUDOKU;
}

bool operator<(const tSudoku &opIzq, const tSudoku &opDer) {
	bool menor = true;
	bool encontrado = false;
	int i = 0;
	const int MAX = 50;
	while ((!encontrado) && (i < (int)opIzq.fichero.size()) && (i < (int)opDer.fichero.size())) {
		if (opIzq.fichero[i] != opDer.fichero[i]) {
			menor = opIzq.fichero[i] < opDer.fichero[i];
			encontrado = true;
		}
		i++;
	}
	if ((!encontrado) && (opIzq.fichero.size() != opDer.fichero.size())) {
		if (opIzq.fichero.size() < opDer.fichero.size())
			menor = true;
		else
			menor = false;
	}
	return menor;
}