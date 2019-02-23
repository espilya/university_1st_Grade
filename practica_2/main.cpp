
#include "pch.h"
#include "listaSudokus.h"

int main()
{
	int op;
	tListaSudokus lista;
	tJuego juego;
	creaListaVacia(lista,juego);
	if (cargarListaSudokus(lista))
		do {
			mostrarMenuPrincipal(juego);
			op = menuListaSudokus(lista, juego);
		} while (op != 0);
	else
		colorStr("Error al cargar 'listaSudokus.txt'.\nFinalizando programa.", ROJO);
	return 0;
}

