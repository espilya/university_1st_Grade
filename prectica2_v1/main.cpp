
#include "pch.h"
#include "listaSudokus.h"

int main()
{
	int op;
	tListaSudokus lista;
	tJuego juego;
  creaListaVacia(lista); //iniciamos lista de sudoku a VACIO
  iniciaJuego(juego);  //iniciamos juego.
  if (cargarListaSudokus(lista)) //cargamos listaSudoku
    do {
      cout << "1. - Jugar\n"
        << "0. - Salir" << endl;
      op = leerOpcion(0, 1);
      switch (op)
      {
      case 1:
        int op2 = menuListaSudokus(lista, juego);
        if (op2 != 0)
          startJuego(juego);
        break;
        //... para otros modos
      }

      clear();
    } while (op != 0);

  else
    colorStr("Error al cargar 'listaSudokus.txt'.\nFinalizando programa.", ROJO);
  return 0;
}
